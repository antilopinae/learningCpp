module;

#include <iostream>

// helloworld.cpp
export module concept; // module declaration

// #include <iostream>        // import declaration

export void test_concept()       // export declaration
{
    std::cout<<"Test concept" << std::endl;
}
