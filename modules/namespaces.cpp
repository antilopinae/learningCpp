module;

#include <iostream>
#include <vector>

export module namespaces;

namespace NAMESPACES
{
    void namespaces()
    {
        {
            using namespace std::string_literals; //makes visible operator""s from std::literals::string_literals
            auto str = "abc"s;
        }

        {
            using namespace std::literals; //makes visible both std::literals::string_literals::operator""s
            //and std::literals::chrono_literals::operator""s

            auto str = "abc"s;
            // auto min = 60s;
        }

        {
            using std::operator""s; //makes both std::literals::string_literals::operator""s
            //and std::literals::chrono_literals::operator""s visible
            auto str = "abc"s;
            // auto min = 60s;
        }
    }
    namespace Lib
    {
        /*
        A n inline namespace is a namespace that uses the optional keyword inline in its original-namespace-definition.                                                                                                                                                                                                             *
        Members of an inline namespace are treated as if they are members of the enclosing namespace in many situations (listed below). This property is transitive: if a namespace N contains an inline namespace M, which in turn contains an inline namespace O, then the members of O can be used as though they were members of M or N.
        */
        inline namespace Lib_1
        {
            template<typename T> class A;
        }

        template<typename T> int g(T) {/* ... */ return 42;}
    }

    struct MyClass { /*...*/ };

    namespace Lib
    {
        template<> class A<MyClass> { /*...*/ };
    }

    int namespaces2()
    {
        Lib::A<MyClass> a;
        return g(a); //ok, Lib is associated namespace of A
    }

    //Unnamed namespaces
    namespace
    {
        int i; // defines ::(unique)::i
    }

    void f()
    {
        i++; // increments ::(unique)::i
    }

    namespace A
    {
        namespace
        {
            int i = 0; // A::(unique)::i
            int j; // A::(unique)::j
        }

        void g() { i++; } // A::(unique)::i++
    }

    int namespaces3()
    {
        using namespace A;
        // i++; Error: ::(unique)::i and ::A::(unique)::i are both in scope
        A::i++; //ok increments ::A::(unique)::i
        j++; //ok increments ::A::(unique)::j
        f();
        g();
        std::cout << A::i << std::endl; //2
        return A::i;
    }

    namespace B
    {
        void f(){
            std::cout << "F" << std::endl;
        }
        namespace A
        {
            void g(){
                std::cout << "G" << std::endl;
            }
        }
        namespace X
        {
            using NAMESPACES::B::f; //global f is now visible as ::X::f
            using NAMESPACES::B::A::g; // A::g is now visible as ::X::g
            using NAMESPACES::B::A::g, NAMESPACES::B::A::g; //C++17 - ok double declaration allowed at namespace scope
            void x()
            {
                g();
                f();
            }
        }
        void h()
        {
            X::f(); //calls ::f
            X::g(); //calls A::g
            X::x();
        }
    }

    void namespaces4()
    {
        using B::h;
        h(); //FGGF
    }

    namespace C
    {
        namespace A
        {
            void f(int){
                using namespace std;
                cout << __PRETTY_FUNCTION__ << endl;
            }
        }
        using NAMESPACES::C::A::f; //::f is now a synonym for A::f(int)
        namespace A
        {
            void f(char){
                using namespace std;
                cout << __PRETTY_FUNCTION__ << endl;
            } //doesnt change what ::f means
        }
        void foo()
        {
            f('A'); //calls f(int), even though f(char exists)
        }
        void bar()
        {
            using NAMESPACES::C::A::f; //this f is a synonym for both A::f(int) and A::f(char)
            f('a'); //calls f(char)
        }
    }

    void namespaces5()
    {
        using namespace C;
        foo();
        bar();
    }

    namespace D
    {
        namespace A
        {
            int x = 6;
        }

        namespace B
        {
            int i;
            struct g {};
            struct x {};
            void f(int)
            {
                using namespace std;
                cout << __PRETTY_FUNCTION__ << endl;
            }
            void f(double)
            {
                using namespace std;
                cout << __PRETTY_FUNCTION__ << endl;
            }
            void g(char)
            {
                using namespace std;
                cout << __PRETTY_FUNCTION__ << endl;
            }//OK: function name g(char) hides struct g
        }

        void func()
        {
            int i;
            // using B::i; //error: i declared twice

            void f(char);
            using B::f; //OK: f(char), f(int), f(double) are overloaded
            f(3.5);

            using B::g;
            g('a'); //calls B::g(char)
            struct g g1; //declares g1 to have type struct B::g

            using B::x;
            using A::x; // Ok, hides struct B::x
            std::cout<<x<<std::endl; //6
            x = 99;
            struct x x1; //declares x1 to have type struct B::x
        }
    }

    void namespaces6()
    {
        using namespace D;
        std::cout<<'\n';
        func();
    }

    namespace E
    {
        namespace B
        {
            void f(int);
            void f(double);
        }

        namespace C
        {
            void f(int);
            void f(double);
            void f(char)
            {
                using namespace std;
                cout << __PRETTY_FUNCTION__ << endl;
            }
        }

        void h()
        {
            using B::f; //introduces B::f(int), B::f(double)
            using C::f; //introduces C::f(int), C::f(double), C::f(char)
            f('h'); //calls C::f(char)
            //f(1); ERROR: B::f(int) or C::f(int)?
            // void f(int); // ERROR f(int) conflicts with C::f(int) and B::f(int)
        }
    }

    void namespaces7()
    {
        using namespace E;
        std::cout<<'\n';
        h();
    }

    namespace F
    {
        namespace D
        {
            int d1;
            void f(char x)
            {
                std::cout << __PRETTY_FUNCTION__ << std::endl;
            }
        }
        using namespace D; // introduces D::d1, D::f, D::d2, D::f, E::e, E::f into global namespace!

        int d1; // Ok: no conflict with D::d1 when declaring

        namespace E
        {
            int e;
            void f(int);
        }

        namespace D //namespace extension
        {
            int d2;
            using namespace E; //transitive using-directive
            void f(int);
        }

        void f()
        {
            std::cout << __PRETTY_FUNCTION__ << std::endl;
            using namespace F;
            // d1++; ERROR: ambiguous ::d1 or D::d1?
            F::d1++; //OK
            F::D::d1++; //OK
            F::d2++; //OK, d2 is D::d2

            F::e++; //OK, e is E::e

            // f(1); ERROR D::f(int) or E::f(int)
            f('a'); // OK D::f(char);
        }
    }

    void namespaces8()
    {
        using F::f;
        std::cout<<'\n';
        f();
    }
}

namespace NAMESPACES_EXAMPLE
{
    namespace vec
    {
        template<typename T>
        class vector {};
    }


    int main()
    {
        std::vector<int> v1;
        vec::vector<int> v2;
        {
            using namespace std;
            vector<int> v3;
            v1 = v3; //ok
        }

        {
            using vec::vector;
            vector<int> v4;
            v2 = v4;
        }

        {
            using namespace vec;
            vector<int> v5;
            v2 = v5;
        }
        return 0;
    }
}

export void test_namespaces()
{
    using namespace std;
    cout << "Test namespaces" << endl;
    using namespace NAMESPACES;
    namespaces();
    namespaces2();
    namespaces3();
    namespaces4();
    namespaces5();
    namespaces6();
    namespaces7();
    namespaces8();

    using namespace NAMESPACES_EXAMPLE;
    main();
}
