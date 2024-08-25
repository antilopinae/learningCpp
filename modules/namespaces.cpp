module;

#include <iostream>

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
}

export void test_namespaces()
{
    using namespace std;
    cout << "Test namespaces" << endl;
    NAMESPACES::namespaces();
    NAMESPACES::namespaces2();
}
