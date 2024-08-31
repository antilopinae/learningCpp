module;

#include <iostream>
#include <type_traits>
#include <utility>

export module move_semantic;

namespace MOVE_SEMANTICS
{
    /* lvalue, prvalue и xvalue:
     * lvalue [2] (от left-hand value – значение слева от равно) – фактически всё, чему может быть присвоено значение, например, переменная, результат разыменовывания указателя, ссылка.
     *
     * prvalue [3] (от pure rvalue) – выражение, которое непосредственно инициализирует объект или описывает операнд, например, результат вызова функции, не являющийся ссылкой, результат постфиксных инкремента или декремента, результат арифметической операции.
     *
     * xvalue [4] (от expiring value) – объекты, которые близки к концу времени жизни (lifetime [5]). Фактически xvalue – это анонимные ссылки на rvalue (о ссылках на rvalue – чуть позже), например, результаты вызова функций, возвращающих ссылки на rvalue.
     *
     * Определив три основные категории значений, можно определить две оставшиеся (составные) – glvalue и rvalue:
     *
     * glvalue [6] (от generalized lvalue) – либо lvalue, либо xvalue.
     *
     * rvalue [7] (от right-hand value – значение справа от равно) – либо prvalue, либо xvalue.
     *
     * Грубо говоря, lvalue – всё, чему может быть явно присвоено значение. rvalue – это временные объекты или значения, не связанные ни с какими объектами; что-то витающее в воздухе и ни за чем не закреплённое.
     */

    namespace AA
    {
        void foo(){}
    }

    void test_lvalue()
    {
        using namespace AA;
        //So-called, historically, because lvalues could appear on the left-hand side of an assignment expression. In general, it's not always the case:
        int a; // Expression `a` is lvalue
        a = 4; // OK, could appear on the left-hand side of an assignment expression

        int &b{a}; // Expression `b` is lvalue
        b = 5; // OK, could appear on the left-hand side of an assignment expression

        const int &c{a}; // Expression `c` is lvalue
        // c = 6;           // ill-formed, assignment of read-only reference

        // Expression `foo` is lvalue
        // address may be taken by built-in address-of operator
        void (*p)() = &foo;

        // foo = baz; // ill-formed, assignment of function
    }

    namespace A
    {
        struct S
        {
            S() : m{42} {}
            S(int a) : m{a} {}
            int m;
        };
    }

    void test_rvalue()
    {
        //an rvalue is a prvalue or an xvalue;
        //So-called, historically, because rvalues could appear on the right-hand side of an assignment expression. In general, it's not always the case:
        using namespace A;

        S s;

        // Expression S{} is prvalue
        // May appear on the right-hand
        s = S{};

        std::cout << s.m << '\n';

        // Expression `S{}` is prvalue
        // Can be used on the left-hand side too
        std::cout << (S{} = S{7}).m << '\n';
    }

    namespace C
    {
        int foo()
        {
            return 5;
        }
        int& foo1()
        {
            return *(new int{5});
        }
        const int foo2()
        {
            return 5;
        }
        const int& foo3()
        {
            return static_cast<const int>(*(new int{4}));
        }
    }

    void test_auto()
    {
        using namespace C;
        auto ri = foo(); // int
        auto ri1 = foo1(); // int
        auto ri2 = foo2(); // int
        auto ri3 = foo3(); // int

        // auto& ri4 = foo(); // Не скомпилируется
        auto& ri5 = foo1(); // int&
        // auto& ri6 = foo2(); // Не скомпилируется
        auto& ri7 = foo3(); // const int&

        /*
        Здесь действует придуманное (или по крайней мере озвученное) Скоттом Мейерсом правило “универсальных ссылок”. Оно заключается в том, что тип var будет зависеть от того какая value category у some_expression. Если rvalue, то тип var будет T&&, если же lvalue, то T&. Cv квалификаторы при этом сохраняются.
        */
        auto&& ri8 = foo(); // int&&
        auto&& ri9 = foo1(); // int&
        auto&& ri10 = foo2(); // const int&&
        auto&& ri11 = foo3(); // const int&

        /*
        decltype(expr), expr — выражение. В этом случае типом decltype(expr) будет тип, которое могло бы вернуть это выражение, с той оговоркой, что decltype(expr) будет иметь тип T& (const T&), если expr возвращает lvalue, T, если expr возвращает rvalue типа Т (const T) и T&& (const T&&), если expr возвращает xvalue (rvalue reference).
        */
        int k = 5;
        // decltype(k)&& rk = k; // Не скомпилируется
        decltype(foo())&& ri12 = foo(); // int&&
        decltype(foo1())&& ri13 = foo1(); // int&

        int i = 3;
        decltype(i) ri14; // int
        // decltype((i)); // int&
    }

    namespace TEST_DECLTYPE
    {
        const int&& foo2()
        {
            int* a = new int{4};
            return static_cast<const int>(*a);
        }
    }

    void test_decltype()
    {
        int i;
        // decltype(i); //int
        // decltype(i + 1); //int
        // decltype((i)); //int&
        // decltype(i = 4); //int&
        // const int foo();
        // decltype(foo()); //int
        // int&& foo1();
        // decltype(foo1()); //int&&

        //Decltype(auto)
        /*
         Это новая “фишка” языка, которая войдет в С++14. Она нужна для сохранения семантики decltype при объявлении auto переменных и будет использоваться в тех случаях, когда нас не будет устраивать то, что auto отбрасывает ссылки и cv квалификаторы и, возможно, в связке с новой возможностью С++14 — выводом типа возвращаемого функцией значения.
        */

        using namespace TEST_DECLTYPE;
        auto ii = foo2(); //ii будет иметь тип int
        decltype(auto) i2 = foo2(); //i2 будет иметь тип const int&&
        //В последнем случае мы могли бы написать decltype(foo()), но представьте, если бы вместо foo() было выражение на 2 строчки, а такие в С++ не редкость.
    }


    namespace B
    {
        template<class T> struct is_prvalue : std::true_type {};
        template<class T> struct is_prvalue<T&> : std::false_type {};
        template<class T> struct is_prvalue<T&&> : std::false_type {};

        template<class T> struct is_lvalue : std::false_type {};
        template<class T> struct is_lvalue<T&> : std::true_type {};
        template<class T> struct is_lvalue<T&&> : std::false_type {};

        template<class T> struct is_xvalue : std::false_type {};
        template<class T> struct is_xvalue<T&> : std::false_type {};
        template<class T> struct is_xvalue<T&&> : std::true_type {};
    }

    void test_xvalue()
    {
        using namespace B;

        int a{42};
        int& b{a};
        int&& r{std::move(a)};

        // Expression `42` is prvalue
        static_assert(is_prvalue<decltype((42))>::value);

        // Expression `a` is lvalue
        static_assert(is_lvalue<decltype((a))>::value);

        // Expression `b` is lvalue
        static_assert(is_lvalue<decltype((b))>::value);

        // Expression `std::move(a)` is xvalue
        static_assert(is_xvalue<decltype((std::move(a)))>::value);

        // Type of variable `r` is rvalue reference
        static_assert(std::is_rvalue_reference<decltype(r)>::value);

        // Type of variable `b` is lvalue reference
        static_assert(std::is_lvalue_reference<decltype(b)>::value);

        // Expression `r` is lvalue
        static_assert(is_lvalue<decltype((r))>::value);
    }

    namespace REFERENCE_RVALUE
    {
        class X
        {
        public:
            void setA(double a)
            {
                //какой-то сеттер
            }
        };

        X someFunctionReturningX()
        {
            X x;
            return x;
        }
    }

    void test_reference_rvalue()
    {
        using namespace REFERENCE_RVALUE;
        // X& xLvalueRef = someFunctionReturningX(); //Не скомпилируется - нельзя привязать rvalue к ссылке на lvalue
        const X& xConstLvalueRef = someFunctionReturningX(); //можно привязывать rvalue к константным ссылкам на lvalue
        // xConstLvalueRef.setA(0); //Не скомпилируется
        X&& xRvalueRef = someFunctionReturningX(); //Привязывание временного объекта к ссылке на rvalue - объект можно менять
        xRvalueRef.setA(0);
        //Время жизни rvalue, привязанного к ссылке на rvalue, расширяется до времени жизни этой ссылки.
        //Важно понимать, что сама ссылка на rvalue является lvalue!!!
    }

    namespace REFERENCE_RVALUE2
    {

    }

    void test_reference_rvalue2()
    {
        using namespace REFERENCE_RVALUE2;

    }
}



export void test_move_semantic()
{
    using namespace std;
    using namespace MOVE_SEMANTICS;
    cout << "Test move semantic" << endl;

    test_decltype();
    test_auto();

    test_lvalue();
    test_rvalue();
    test_xvalue();

    test_reference_rvalue();
    test_reference_rvalue2();
}
