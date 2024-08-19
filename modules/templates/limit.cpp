#include <iostream>
#include <thread>

template<Element T> //Для всех T, таких что Element(T)
class Vector
{
private:
    T* elem;
    int sz;
};


void test_limit()
{
    Vector<int> v1;
    Vector<std::thread> v2;
}
