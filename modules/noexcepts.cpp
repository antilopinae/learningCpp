module;

#include <iostream>

export module noexcepts;

namespace NOEXCEPTS
{
    /*
    спецификатор времени компиляции noexcept, которой говорит компилятору о том, что функция не будет выбрасывать исключения.
    */
    namespace A
    {
        class my_class
        {
            int i_;
        public:
            explicit my_class (int i) : i_(i) {}
            int get() const
            {
                return i_;
            }
        };

        inline int operator+(const my_class& v1, const my_class& v2)
        {
            return v1.get() + v2.get();
        }

        int main()
        {
            int res = 0;
            try
            {
                // Если при вызове конструктора для var0 произойдет исключение,
                // распечатываем сообщение об ошибке и выставляем res в -1
                my_class var0(10);

                // Если при вызове конструктора для var1 произойдет исключение,
                // то компилятор должен будет вызвать деструктор
                // переменной var0, распечатать сообщение об ошибке
                // и выставить res в -1
                my_class var1(100);

                // Если при сложении произошло исключение,
                // распечатываем сообщение об ошибке и выставляем res в -1

                // Вызов деструкторов var1 и var0 произойдет в любом случае,
                // вне зависимости от генерации исключения.
                res = (var1 + var0 > 0 ? 0 : 1);
            }
            catch (...)
            {
                std::cout << "Произошла ошибка" << std::endl;
                res = -1;
            }

            return 0;
        }
    }

    void noexcepts_a()
    {
        using namespace A;
        main();
    }

    /*
     * Именно из-за такого разбухания кода, в некоторых крупных корпорациях (не будем тыкать пальцем в Google) при разработке на С++ запрещено использование исключений. Еще одним примером могут послужить правила разработки для GCC начиная с версии 4.8 (да, GCC теперь разрабатывается с использованием С++, см изменения для 4.8).
     */

    namespace B
    {
        class my_class
        {
            int i_;
        public:
            explicit my_class (int i) noexcept : i_(i) {}
            int get() const noexcept
            {
                return i_;
            }
        };

        inline int operator+(const my_class& v1, const my_class& v2) noexcept
        {
            return v1.get() + v2.get();
        }

        int main()
        {
            // std::terminate при исключении
            my_class var0(10);

            // std::terminate при исключении
            my_class var1(100);

            // std::terminate при исключении
            int res = (var1 + var0 > 0 ? 0 : 1);

            // Вызов деструкторов var1 и var0

            return 0;
        }
    }

    void noexcepts_b()
    {
        using namespace B;
        main();
    }

    /*
    Если в кратце, в ней говорится, что стандартные алгоритмы и контейнеры не должны использовать move assignment и move construction если эти методы могут кидать исключения. Чем это может грозить рассмотрим на примере:
    */
    namespace C
    {
        class move_fast_copy_slow
        {
        public:
            move_fast_copy_slow(move_fast_copy_slow&&); //1 noexcept
            move_fast_copy_slow(const move_fast_copy_slow&); //2

            move_fast_copy_slow& operator=(move_fast_copy_slow&&); //3 noexcept
            move_fast_copy_slow& operator=(move_fast_copy_slow&); //4
        };

        /*
         Если методы 1 и 3 не пометить noexcept, то стандартные контейнеры будут использовать более медленные методы 2 и 4. Вследствие этого работа с контейнерами std::vector и std::deque может замедлиться на пару порядоков. При том, данное замедление коснется и всех типов наследуемых или использующих move_fast_copy_slow в качестве члена.
        */
    }

    void noexcepts_c()
    {
        using namespace C;
        move_fast_copy_slow* mv;
    }

    /*
     Совместимость                                                                                                                                                               *
     На момент написания данной статьи не все ведущие компиляторы поддерживают noexcept. Используйте макрос BOOST_NOEXCEPT из библиотеки boost вместо noexcept для переносимости кода.
    */

    /*
     Подводные камни                                                                                                                                                                                                                 *
     По стандарту, noexcept не является частью типа функции, однако при использовании виртуальных функций все перегруженные функции должны иметь такую же либо более строгую спецификацию исключений. То есть следующий код не соберется:
    */

    namespace D
    {
        class base
        {
        public:
            virtual void foo() noexcept {}
        };

        class derived: public base
        {
        public:
            //«error: looser throw specifier for ‘virtual void derived::foo()’».
            virtual void foo() noexcept override {} //!!!NOEXCEPT
        };

        int main ()
        {
            derived d;
            base* p = &d;
            p->foo();
            return 0;
        }
    }

    void noexcepts_d()
    {
        using namespace D;
        main();
    }

    namespace E
    {
        class my_exception : public std::exception
        {
            const char* what () noexcept //mandatory!!
            {
                return "my_exception::what()";
            }
        };
    }

    void noexcepts_e ()
    {
        using namespace E;
        my_exception me;
    }

    /*
    Спецификатор времени компиляции noexcept сильно уменьшает размер итогового файла и ускоряет работу программы. Главное при использовании noexcept не переусердствовать. Помните, что если функция помеченная noexcept выпустит исключение наружу, то ваша программа вызовет std::terminate() и завершится, даже не соблаговолив вызвать деструкторы для уже созданных переменных.
    */

    /*
     Еще стоит добавить, что кроме спецификатора noexcept есть еще и оператор noexcept, который на этапе компиляции может вычислить, можно применить спецификатор noexcept или нет. Это очень полезно для шаблонов
    */
    namespace F
    {
        struct B {
            int i_;
            explicit B(int i) : i_(i) {}
            B& operator=(B& b) noexcept
            {
                i_ = b.i_;
                return *this;
            }
            friend std::ostream& operator<<(std::ostream& os, const B& obj) {
                os << obj.i_;
                return os;
            }
        };
        //Здесь спецификатор noexcept будет включен только если A::operator= и все что он вызывает, тоже имеют спецификатор noexcept
        template<class A>
        void swap (A& a, A& b) noexcept(noexcept(A::operator=))
        {
            A tmp = a;
            a = b;
            b = tmp;
        }
        //В boost постарались решить путаницу, введя макросы BOOST_NOEXCEPT, BOOST_NOEXCEPT_IF(предикат)
        //BOOST_NOEXCEPT_EXPR(выражение).
    }

    void noexcepts_f ()
    {
        using F::B, F::swap;
        B a{1};
        B b{2};
        B& pa =a;
        B& pb = b;
        swap(pa,pb);
        std::cout<<a<<b<<std::endl;

    }
}

void noexcepts()
{
    using namespace NOEXCEPTS;
    noexcepts_a();
    noexcepts_b();
    noexcepts_c();
    noexcepts_d();
    noexcepts_e();
    noexcepts_f();
}

export void test_noexcepts()
{
    using namespace std;
    cout << "Test noexcepts" << endl;
    noexcepts();
}
