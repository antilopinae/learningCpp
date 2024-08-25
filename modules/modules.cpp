module;

#include <iostream>

//module partition
export module A:B; // declares a module interface unit for module A, partition :B
//A-B.cpp

module A:C; //A-C.cpp

export module A;

import :C;
export import :B;

export module modules;

export void test_modules()
{
    std::cout << "Test modules" << std::endl;
}



export int test_modules_f();

module: private;

int test_modules_f() //definition not reachable from importers of foo
{
    using namespace std;
    cout << __PRETTY_FUNCTION__ << endl;
    cout << "definition not reachable from importers of foo" << endl;
    return 43;
}
