#include <iostream>

namespace My_code {
    int Hello();
}

int My_code::Hello(){
    std::cout << "Hello" << std::endl;
    return 1;
}

int hi()
{
    return My_code::Hello();
}
