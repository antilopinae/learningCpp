#include <iostream>

template<typename T>
class Vector
{
public:
    Vector(int){}
    Vector(std::initializer_list<T>){}
};

void example_vector()
{
    using namespace std;
    // Vector<string>
    Vector<string> vs1 {"Hello","World"};
    // Вывод Vector<const char*> Сюрприз?
    Vector vs {"Hello","World"};
    // Вывод Vector<string>
    Vector vs2 {"Hello"s,"World"s};
    //Vector vs3 {"Hello","World"s}; Ошибка - негомогенный список инициализаторов
}

void test_example_vector()
{
    Vector v1 {1,2,3}; //Вывод типа из типа элементов инициализатора
    Vector v2 = v1; //Вывод типа элементов v2 из типа v1
    auto p = new Vector {1,2,3}; // p указывает на Vector<int>
    Vector<int> v3(1); //Тип элемента должен быть указан явно
    example_vector();
}
