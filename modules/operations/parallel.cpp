#include <iostream>
#include <vector>
#include <thread>

#include "vector_x.h"
void heartbeat()
{
    int i;
    //smth
    while(true)
        i++;
}

std::vector<std::thread> my_threads;

Vector_x init(int n)
{
    // Параллельное выполнение heartbeat (в отдельном потоке):
    std::thread t{}; //heartbeat
    // Перемещение t в my_threads:
    my_threads.push_back(std::move(t));
    // Другие инициализации
    Vector_x vec(n);
    for (int i=0; i!=vec.size(); ++i)
        vec[i] = 777;
    return vec;
}


void test_parallel()
{
    auto v = init(1'000'000);
}
