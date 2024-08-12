module;

#include <iostream>

// helloworld.cpp
export module helloworld; // module declaration

// #include <iostream>        // import declaration

export int hello()       // export declaration
{
    std::cout<<"Hello world" << std::endl;
    return 5;
}
