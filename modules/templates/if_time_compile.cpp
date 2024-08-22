#include <iostream>
#include <vector>
#include <type_traits>

template<typename T>
void slow_and_safe(T arg)
{
    std::cout<<"Slow and safe"<<std::endl;
}

template<typename T>
void simple_and_fast(T arg)
{
    std::cout<<"Simple and fast"<<std::endl;
}

template<typename T>
void update(T& target)
{
    using namespace std;
    // ...
    //If T is a POD type ("plain old data type"), provides the member
    //constant value equal to true. For any other type, value is false.
    if constexpr(is_pod<T>::value)
        simple_and_fast(target);
    else
        slow_and_safe(target);
    // ...
}

void test_if_time_compile()
{
    using namespace std;
    vector v {1,2,3};
    update(v);
    int x {5};
    update(x);
}
