// Шаблоны переменных

template <class T>
constexpr T viscosity = 0.4;

template <class T>
constexpr space_vector<T> external_acceleration = { T{}, T{-9.8}, T{} };

auto vis2 = 2*viscosity<double>;
auto acc = external_acceleration<float>;

// is_assignable - свойство типа
template<typename T, typename T2>
constexpr bool Assignable = is_assignable<T&,T2>::value;

template<typename T>
void testing()
{
    static_assert(Assignable<T&,double>, "нельзя присваивать double");
    static_assert(Assignable<T&,string>, "нельзя присваивать string");
}


// Псевдонимы
// <cstddef> содержит возможно using size_t = unsigned int;
// псевдонимы для типов, связанных с его аргументами шаблона
template<typename T>
class Vector
{
public:
    using value_type = T;
    // ...
};

// Каждый контейнер стандартной библиотеки предоставляет для имени типа значений своих элементов псевдоним value_type.
// Это позволяет писать код, который будет работать для любого контейнера, следующего этому соглашению
template<typename C>
using Value_type = typename C::value_type; //Тип элементов C

template<typename Container>
void algo(Container& c)
{
    Vector<Value_type<Container>> vec; // Храним здесь результаты
    // ...
}
