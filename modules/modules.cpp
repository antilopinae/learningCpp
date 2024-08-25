module;

#include <iostream>

export module modules;

import A;

export void test_modules()
{
    std::cout << "Test modules" << std::endl;
    std::cout << Hello() << ' ' << World() << '\n';
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
