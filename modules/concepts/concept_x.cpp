module;

#include <iostream>

// helloworld.cpp
export module concept_x; // module declaration

// #include <iostream>        // import declaration

export void test_concept_x()       // export declaration
{
    std::cout<<"Test concept" << std::endl;
}
