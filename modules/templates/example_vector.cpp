#include <iostream>

template<typename T>
class Vector_e
{
public:
    Vector_e(int){}
    Vector_e(std::initializer_list<T>){}
};

void example_vector()
{
    using namespace std;
    // Vector<string>
    Vector_e<string> vs1 {"Hello","World"};
    // Вывод Vector<const char*> Сюрприз?
    Vector_e vs {"Hello","World"};
    // Вывод Vector<string>
    Vector_e vs2 {"Hello"s,"World"s};
    //Vector vs3 {"Hello","World"s}; Ошибка - негомогенный список инициализаторов
}

void test_example_vector()
{
    Vector_e v1 {1,2,3}; //Вывод типа из типа элементов инициализатора
    Vector_e v2 = v1; //Вывод типа элементов v2 из типа v1
    auto p = new Vector_e {1,2,3}; // p указывает на Vector<int>
    Vector_e<int> v3(1); //Тип элемента должен быть указан явно
    example_vector();
}
