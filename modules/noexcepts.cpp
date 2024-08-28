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
        // class Base {
        //     int i_;
        // public:
        //     explicit Base(int i) noexcept : i_(i) {}
        //     Base& operator=(Base& b) noexcept
        //     {
        //         i_ = b.i_;
        //         return *this;
        //     }
        //     Base(Base&& other) noexcept
        //     {
        //         i_=other.i_;
        //     }
        //     friend std::ostream& operator<<(std::ostream& os, const Base& obj) {
        //         os << obj.i_;
        //         return os;
        //     }
        // };
        //Здесь спецификатор noexcept будет включен только если A::operator= и все что он вызывает, тоже имеют спецификатор noexcept
        // template<class A>
        // void swap (A& a, A& b) noexcept(noexcept(std::declval<A&>() = std::declval<A&&>()))
        // {
        //     A temp = std::move(a);
        //     a = std::move(b);
        //     b = std::move(temp);
        // }
        //В boost постарались решить путаницу, введя макросы BOOST_NOEXCEPT, BOOST_NOEXCEPT_IF(предикат)
        //BOOST_NOEXCEPT_EXPR(выражение).
    }

    void noexcepts_f ()
    {
        using namespace F;
        // Base a{1};
        // Base b{2};
        // swap(a,b);
        // std::cout<<a<<b<<std::endl;

    }

    namespace G
    {
        template<typename T>
        struct Holder
        {
            T value;

            template<typename... Args>
            Holder(Args&&... args) : value(std::forward<Args>(args)...) {}
        };
        template<typename U> Holder(U&&) -> Holder<std::remove_reference_t<U>>;
        /*
        The noexcept keyword has another purpose: You can use it as an operator in an expression, and it evaluates to true if the evaluation of the argument would be considered non-throwing by the compiler. Like sizeof, the argument itself is not evaluated.
        */
        /*
         Whether the T constructor is pot*entially-throwing given the forwarded args... can be calculated by asking the noexcept(...) operator to pretend to construct it, and report whether the result is potentially-throwing.

         noexcept(T(std::forward<Args>(args)...))
        */
        /*
        The result of that calculation is then fed to the noexcept specifier to tell it whether the Holder constructor, given those arguments, should also be considered potentially-throwing.

        noexcept(noexcept(T(std::forward<Args>(args)...)))
        */
        void example1()
        {
            bool example1 = noexcept(1+2); //true
            bool example2 = noexcept(1/0); //true
            /*
            The compiler says that dividing by zero will not raise a C++ exception. Now, dividing by zero is actually undefined behavior, but the compiler isn’t performing any division here. It’s just checking whether operator/(int, int) is potentially-throwing, and it is not.
            */
            bool example3 = noexcept(
                std::declval<std::string>().clear()); // true
            /*
            The third example highlights that the inner expression is not evaluated. We are using the std::declval<T> function which pretends to return a T, although you are not allowed to actually call it. It may be used only in unevaluated contexts.
            */
            bool example4 = noexcept(
                std::declval<std::string>().resize(0)); // false
            /*
            The fourth example is a bit interesting: Although resizing a string to zero is functionally equivalent to clearing it, it has a different exception specifier, because the resize() method may throw if asked to make a string bigger and it cannot allocate memory for the bigger string.
            */
        }

        template<typename T>
        struct Holder2
        {
            T value;

            template<typename... Args>
            Holder2(Args&&... args) noexcept(noexcept(T(std::forward<Args>(args)...)))
            : value(std::forward<Args>(args)...) {}
            /*
            We want our constructor to have the same potentially-throwing behavior as the construction of value, so we use the repetitive noexcept(noexcept(...)) idiom to say “I’m noexcept if that guy is”, and “that guy” is itself a repetition of the thing we’re actually going to do one line later.

            The noexcept(noexcept(...)) idiom could be pejoratively called the “Please repeat yourself twice” idiom. You have to repeat the keyword noexcept, and you also have to repeat the expression whose potentially-throwing behavior you want to propagate.
            */
        };
        template<typename U> Holder2(U&&) -> Holder2<std::remove_reference_t<U>>;
    }

    void noexcepts_g()
    {
        using namespace G;
        example1();
        Holder v{3};
        Holder2 vv{5};
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
    noexcepts_g();
}

export void test_noexcepts()
{
    using namespace std;
    cout << "Test noexcepts" << endl;
    noexcepts();
}
