#include <iostream>
#include "vector_t.cpp"

// Каждый контейнер стандартной библиотеки предоставляет для имени типа значений своих элементов псевдоним value_type.
// Это позволяет писать код, который будет работать для любого контейнера, следующего этому соглашению
template<typename C>
using Value_type = typename C::value_type; //Тип элементов C

template<typename Container>
void algo(Container& c)
{
    // explicit!
    Vector_t<Value_type<Container>> vec (5); // Храним здесь результаты
    // ...
}

// Механизм псевдонимов для определения нового шаблона
template<typename Key, typename Value>
class Map {
    // ...
};

template<typename Value>
using String_map = Map<std::string, Value>;


void test_template_value_ex()
{
    Vector_t v {1,2,3,4,5};
    algo(v);
    String_map<int> map; // Map<string,int>
}
