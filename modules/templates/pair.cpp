#include <iostream>

void test_pair()
{
    std::pair<int,double> p = {1,5.2};
    // но можно и так
    auto d = std::make_pair(1,5.2);
    std::pair l = {1, 5.2};

}
