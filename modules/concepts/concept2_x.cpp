module;

#include <iostream>
#include <cstddef>
#include <concepts>
#include <functional>

export module concept2_x;

//import declaration

template<typename T>
concept Equality_comparable = requires (T a, T b) {
        { a == b } -> std::convertible_to<bool>; //сравнение Ts с помощью ==
        { a != b } -> std::convertible_to<bool>; //сравнение Ts с помощью !=
    };

template<typename T> //можно использовать constexpr func
constexpr bool get_value() { return T::value; }

template<typename T>
    requires (sizeof(T) > 1 && get_value<T>())
void F(T); //#1

void F(int)
{}// #2

void g()
{
    F('A'); // вызывает #2
}

template<class T>
concept Addable =
requires (T a, T b) {
    a + b;
};

template<class T, class U = T>
concept Swappable = requires(T&& t, U&& u) {
    std::swap(std::forward<T>(t), std::forward<U>(u));
    std::swap(std::forward<U>(u), std::forward<T>(t));
}; // код выполнится когда это скомпилится без ошибок

// проверка корректности типа
template<class T> using Ref = T&;
template<class T> concept C =
requires {
    typename T::inner;
    // typename S<T>;
    typename Ref<T>;
};

template<class T> concept C1 =
requires(T x) {
    {x+1} -> std::same_as<int>;
};

template<class T> concept C2 =
requires(T x) {
    {*x} -> std::convertible_to<typename T::inner>; //*x и T::inner - корректно, *x конвертируется к T::inner
    {x * 1} -> std::convertible_to<T>; //x*1 корректно и его результат конвертируется к T
};

template<class T>
concept Incrementable =
requires (T a) {
    a++;
};

//ограничения для функции можно записать в трех разных местах
template<Incrementable T>
void f1(T arg);

template<class T>
requires Incrementable<T>
void f2(T arg);

template<class T>
void f3(T arg) requires Incrementable<T>;

//четвертый способ
void f4(Incrementable auto arg); //неявный шаблон, С++ 20

//для класса есть два способа
template<Incrementable T>
class X {};

template<class T>
requires Incrementable<T>
class Y {};

template<class T>
void ReadAndFill(T& container, int size)
{
    if constexpr (requires {container.reserve(size); }) {
        container.reserve(size);
    }
    //заполняем контейнер
    // мы можем использовать это для vector и для list, причем для vector будет вызвана reserve()
    static_assert(requires {container.reserve(size); });
} // requires можно использовать в static_assert

/*
Интересно, что концепт может иметь несколько шаблонных параметров. При использовании концепта нужно задать все, кроме одного — того, который мы проверяем на ограничение.*/

template<class T, class U>
concept Derived = std::is_base_of<U, T>::value;

template<class Other, class X> requires Derived<X, Other>
void f5(X arg);

// //Derived<X,Other>
// template<Derived<Other> X>
// void f6(X arg);

export void test_concept2_x()
{
    using namespace std;
    cout<<"Test concept2"<<endl;

    static_assert(Equality_comparable<int>); //успех
}

// concept theory
/*
 * <concepts>
 *
 * same_as, derived_from, convertible_to, common_reference_with, common_with,
 * integral, signed_integral, unsigned_integral, floating_point,
 * assignable_from, swappable, swappable_with,
 * destructible, constructible_from,
 * default_initializable, move_constructible,
 * copy_constructible
 *
 * <comparison concepts>
 * equality_comparable, equality_comparable_with,
 * totally_ordered, totally_ordered_with
 *
 * <object concepts>
 * movable, copyable, semiregular, reqular
 *
 * <callable concepts>
 * Invocable, reqular_invocable, predicate, relation,
 * equivalence_relation, strict_weak_order
 *
 * концепты в <iterator>
 * indirectly_readable, indirectly_writable,
 * weakly_incrementable, incrementable,
 * input_or_output_iterator, sentinel_for,
 * sized_sentinel_for, input_iterator, output_iterator,
 * forward_iterator, bidirectional_iterator,
 * random_access_iterator, contiquous_iterator
 *
 * концепты в <ranges>
 * ranges::range, ranges::borrowed_range,
 * ranges_sized_range, ranges::view,
 * ranges::input_range, ranges::output_range,
 * ranges::forward_range, ranges::bidirectional_range,
 * ranges::random_access_range,
 * ranges::contiguous_range, ranges::common_range,
 * ranges::viewable_range
 */

