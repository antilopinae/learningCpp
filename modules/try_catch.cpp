#include <iostream>

float throw_exception(){
    throw std::out_of_range("Throwing random exception...");
    return 1.2f;
}

void no_exception() noexcept
{
    //no exception гарантированно!
//     иначе вызовется std::terminate()
}

// class Vector{
// public:
//     Vector();
// };
//
// Vector::Vector(){
//     try {
//         Vector v = Vector();
//     }
//     catch (std::length_error&) {
//         std::cout<<"Сбой test()";
//         throw; //повторная генерация исключения
//     }
//     catch (std::bad_alloc&) {
//         std::terminate();
//     }
// }

constexpr double C = 299792.458;

void f(double speed)
{
    constexpr double local_max = 160.0/(60*60);
    static_assert(local_max < C, "Недостижимая скорость");

    static_assert(4<=sizeof(int)); //Выводит сообщение по умолчанию
}

void test_exception(){
    static_assert(4<=sizeof(int), "int слишком мал"); //Проверка размера

    try
    {
        throw_exception();
//         std::length_error
//         std::bad_alloc - если new не может выделить память
    }
    catch (std::out_of_range& err)
    {
        std::cout << err.what() << std::endl;
    }
    no_exception();
}
