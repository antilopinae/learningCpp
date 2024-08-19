#include "vector.h"
#include <iostream>

template<typename T, int N>
struct Buffer
{
    using value_type = T; //доступ только для чтения к аргументам шаблона
    constexpr int size() { return N; }
    T vec[N];
};

Buffer<char, 1024> glob; // global buffer

void test_template_args()
{
    Buffer<int, 16> buf; // local buffer in stack
    std::cout << buf.size();
}
