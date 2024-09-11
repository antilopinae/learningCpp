module;

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <queue>
#include <future>
#include <unordered_set>


export module thread_pool;

namespace TEST_THREAD
{
    void sleep(int duration)
    {
        // Simulate expensive operation
        std::this_thread::sleep_for(std::chrono::seconds(duration));
    }

    void test_thread1()
    {
        std::cout << "Starting first thread...\n";
        std::thread th1(sleep, 1);

        std::cout << "Starting second thread...\n";
        std::thread th2(sleep, 2); //(function, parameters)

        std::cout << "Waiting for threads to finish...\n";

        th1.join(); //th1.detach()
        std::cout << "The first thread finished\n";

        th2.join();
        std::cout << "The second thread finished\n";

        std::cout << "Done\n";
    }

    void func(int a)
    {
        for (int i = 0; i< 3; ++i)
        {
            std::cout << a + i;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << " ";
        }
        std::cout << "\n";
    }

    void test_thread2()
    {
        // You can see unpredictable result
        std::thread th1(func, 1);
        std::thread th2(func, 4);

        th1.join();
        th2.join();
    }

    std::mutex mtx;

    void func_synchronized(int a)
    {
        mtx.lock();
        for (int i = 0; i< 3; ++i)
        {
            std::cout << a + i;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << " ";
        }
        std::cout << "\n";
        mtx.unlock();
    }

    void test_synchronize()
    {
        std::thread th1(func_synchronized, 1);
        std::thread th2(func_synchronized, 4);

        th1.join();
        th2.join();

        // You can also see in <mutex>
        // std::lock_guard
        // std::unique_lock and std::condition_variable
        // std::scoped_lock

        // In <condition_variable>
        // std::condition_variable - as lock with alarm
    }

    namespace THREAD_POOL_CPP14
    {
        class thread_pool
        {
        public:
            thread_pool(uint32_t num_threads)
            {
                threads.reserve(num_threads);
                for (uint32_t i = 0; i< num_threads; ++i)
                    threads.emplace_back(&thread_pool::run, this);
            }

            /*
             * std::async(std::launch::deferred, task_func, args...) данная функция не смотря на название async ничего не делает асинхронно благодаря параметру  std::launch::deferred. Мы просто запоминаем аргументы функции, как в случае с std::bind . Отличаем является лишь то, bind не требует заполнять все аргументы функции, в отличает от std::async.
            */
            template <typename Func, typename ...Args>
            int64_t add_task(const Func& task_func, Args&&... args)
            {
                // получаем значение индекса для новой задачи
                int64_t task_idx = last_idx++;

                std::lock_guard<std::mutex> q_lock(q_mtx);
                q.emplace(std::async(std::launch::deferred, task_func, args...), task_idx);

                // делаем notify_one, чтобы проснулся один спящий поток (если такой есть)
                // в методе run
                q_cv.notify_one();
                return task_idx;
            }

            void wait(int64_t task_id)
            {
                std::unique_lock<std::mutex> lock(completed_task_ids_mtx);

                // ожидаем вызова notify в функции run (сработает после завершения задачи)
                completed_task_ids_cv.wait(lock, [this, task_id]()->bool {
                    return completed_task_ids.find(task_id) != completed_task_ids.end();
                });
            }

            /*
             * Обратите внимание, что wait_all внутри wait использует ещё одну блокировку для очереди для проверки на пустоту (мы должны блокировать каждый разделяемый ресурс, чтобы избежать data race).
             *
             * Так же обратите внимание, что std::lock_guard стоит там, где нет wait для мьютекса и не нужно делать unlock (std::unique_lock в остальных случаях). Если вы будите придерживаться данного правила, то программисты, смотрящие ваш код скажут вам спасибо.
            */
            void wait_all()
            {
                std::unique_lock<std::mutex> lock(q_mtx);

                // ожидаем вызова notify в функции run (сработает после завершения задачи)
                completed_task_ids_cv.wait(lock, [this]()->bool {
                    std::lock_guard<std::mutex> task_lock(completed_task_ids_mtx);
                    return q.empty() && last_idx == completed_task_ids.size();
                });
            }

            /*
             * Неблокирующий метод проверки задачи на завершённость возвращает true если задача с данным task_id уже посчитана, иначе - false.
            */
            bool calculated(int64_t task_id) {
                std::lock_guard<std::mutex> lock(completed_task_ids_mtx);
                if (completed_task_ids.find(task_id) != completed_task_ids.end()) {
                    return true;
                }
                return false;
            }

            /*
             * Если экземпляр класса thread_pool удаляется, то мы дожидаемся завершения всех потоков в деструкторе. При этом, если в очереди есть ещё задачи, то каждый поток выполнит ещё одну задачу и завершит работу (это поведение можно поменять и, например, дожидаться выполнения всех задач перед завершением).
            */
            ~thread_pool() {
                // можно добавить wait_all() если нужно дождаться всех задачь перед удалением
                quite = true;
                for (uint32_t i = 0; i < threads.size(); ++i) {
                    q_cv.notify_all();
                    threads[i].join();
                }
            }

        private:
            // очередь задач - хранит функцию (задачу), которую надо исполнить и номер задачи
            std::queue<std::pair<std::future<void>, int64_t>> q;
            /*
             * Очередь хранит std::future<void> - объект, который в будущем вернёт тип void, использование std::future позволяет не сразу вычислять функцию, а отложить вызов до нужного нам момента, также можно использовать и std::function<void()> (такой способ тоже допустим).
            */

            std::mutex q_mtx;
            std::condition_variable q_cv;

            // контейнер для выполненных задач
            std::unordered_set<int64_t> completed_task_ids;

            std::condition_variable completed_task_ids_cv;
            std::mutex completed_task_ids_mtx;

            std::vector<std::thread> threads;

            // флаг завершения работы thread_pool
            std::atomic<bool> quite{ false };

            // переменная хранящая id для следующей задачи
            std::atomic<int64_t> last_idx = 0;


            void run()
            {
                while(!quite)
                {
                    std::unique_lock<std::mutex> lock(q_mtx);

                    // если есть задачи, то берем задачу, иначе - засыпаем
                    // если мы зашли в деструктор, то quite будет true и мы не будем
                    // ждать завершения всех задач и выйдем из цикла
                    q_cv.wait(lock, [this]()->bool { return !q.empty() || quite; });
                    /*
                     * condition_variable на методе wait (q_cv) захватывает мьютекс, проверяет условие, если условие верно, то мы идём дальше по коду, иначе - засыпаем, отпускаем мьютекс и ждём вызов notify из метода добавления задач (когда приходит notify процедура повторяется - захватываем мьютекс и проверяем условие). Таким образом мы берём задачи до тех пор, пока они не кончатся, а когда кончатся и придёт новая задача мы разбудим поток.
                    */

                    if (!q.empty())
                    {
                        auto elem = std::move(q.front());
                        q.pop();
                        lock.unlock();

                        // вычисляем объект типа std::future (вычисляем функцию)
                        elem.first.get();

                        std::lock_guard<std::mutex> lock(completed_task_ids_mtx);

                        // добавляем номер выполненой задачи в список завершённых
                        completed_task_ids.insert(elem.second);

                        // делаем notify, чтобы разбудить потоки
                        completed_task_ids_cv.notify_all();
                    }
                }
            }
        };

        void sum(int& ans, std::vector<int>& arr)
        {
            for (int i = 0; i < arr.size(); ++i)
                ans += arr[i];
        }

        void test_thread_pool_cpp14()
        {
            thread_pool tp(3);
            std::vector<int> s1 = { 1, 2, 3 };
            int ans1 = 0;

            std::vector<int> s2 = { 4, 5 };
            int ans2 = 0;

            std::vector<int> s3 = { 8, 9, 10 };
            int ans3 = 0;


            /*
             * Стоит обратить внимание на std::ref благодаря ему будет передана ссылка, а не копия объекта (это особенность передачи аргумента в std::future)
            */
            // добавляем в thread_pool выполняться 3 задачи
            auto id1 = tp.add_task(sum, std::ref(ans1), std::ref(s1));
            auto id2 = tp.add_task(sum, std::ref(ans2), std::ref(s2));
            auto id3 = tp.add_task(sum, std::ref(ans3), std::ref(s3));

            if (tp.calculated(id1)) {
                // если результат уже посчитан, то просто выводим ответ
                std::cout << ans1 << std::endl;
            }
            else {
                // если результат ещё не готов, то ждём его
                tp.wait(id1);
                std::cout << ans1 << std::endl;
            }
            tp.wait_all();

            std::cout << ans2 << std::endl;
            std::cout << ans3 << std::endl;

            /*
             * Функция обязательно должна быть void
             * Приходится хранить дополнительно переменную для ответа
            */
        }
    }

    namespace THREAD_POOL_CPP17
    {
        class thread_pool
        {

        };

        void test_thread_pool_cpp17()
        {

        }
    }

    void test_thread()
    {
        test_thread1();
        test_thread2(); // Unpredictable behaviour
        test_synchronize();

        THREAD_POOL_CPP14::test_thread_pool_cpp14();
        THREAD_POOL_CPP17::test_thread_pool_cpp17();
    }
}


export void test_thread_pool()
{
    using namespace std;
    cout << "Test Thread Pool" << endl;

    TEST_THREAD::test_thread();
}

