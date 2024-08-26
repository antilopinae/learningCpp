module;

#include <iostream>
#include <iterator>
#include <vector>
#include <type_traits>
#include <concepts>

export module concept3_x;

template <typename T> concept NoThrowDefaultConstructible = noexept(T{});

template<typename From, typename To>
concept Assignable = std::is_assignable_v<From, To>;

// концепты можно определять и на нетиповых шаблонных параметрах
template<int I> concept Even = I % 2 == 0;

//define concept constexpr bool??
// концепты как и constexpr bool переменные можно использовать везде, где вам в compile-time нужно булевое выражение
// например, в static_assert или внутри noexcept
static_assert(Assignable<int&,int>);

template<typename T>
void test() noexcept(NoThrowDefaultConstructible<T>) {
    T t;
    //...
}

template<typename T>
concept Trivial = true;

template<Trivial T>
class simple_optional {
    T value;
    bool initialized = false;
};

//назовем тип маленьким, если его размер не превосходит ограничений

template<typename T, size_t MaxSize, size_t MaxAlign>
concept Small = sizeof(T) <= MaxSize && alignof(T) <= MaxAlign;

template<typename T>
class any {
    struct SB {
        static constexpr size_t Size = sizeof(T);
        static constexpr size_t Alignment = alignof(T);

        std::aligned_storage_t<Size,Alignment> storage;
    };
    union {
        SB sb;
        void* handle;
    };
    template<class Y = T> requires Small<Y, SB::Size, SB::Alignment>
    any(Y const & t) {}
};

// можно так
template<typename T>
class any2 {
    struct SB {
        static constexpr size_t Size = sizeof(T);
        static constexpr size_t Alignment = alignof(T);

        std::aligned_storage_t<Size, Alignment> storage;
    };
    union {
        SB sb;
        void* handle;
    };
    any2(Small<SB::Size, SB::Alignment> auto const& t): sb() {}
};


template<typename T>
concept LEPtr = Small<T, sizeof(void *), alignof(void *)>; //малые обьекты

template<typename T>
LEPtr auto get_handle(T& object) {
    if constexpr (LEPtr<T>)
        return object;
    else
        return &object;
}


/// requires expression - тип bool и вычисляются в compile-time
template<typename T, typename... Args>
concept Constructible = requires(Args... args) { T{args...}; };

template<typename T>
concept Comparable = requires(T const & a, T const & b) {
    {a<b} -> std::convertible_to<bool>;
};

template<typename T>
using ValueType = T::value_type;

template<typename Iterator>
concept RandomAccessIterator = std::bidirectional_iterator<Iterator> /*&& ...*/;

template<typename T>
using Iterator = T::iterator;

//можно так

// template<typename R>
// concept Sortable = RandomAccessIterator<Iterator<R>> && Comparable<ValueType<R>>;
//
// //requires - clause
// template<typename Range> requires Sortable<Range>
// void sort(Range& range) {/**/}

//а можно так
template<typename Range> requires RandomAccessIterator<Iterator<Range>> && Comparable<ValueType<Range>>
void sort(Range& range) {/**/}

//__if_exists
//__if_not_exists
//позволяет в compile-time проверять существование имени и в зависимости включать или выключать компиляцию блока кода

// можно было делать так
// struct Point2 { float x, y; };
// struct Point3 { float x, y, z; };
//
// template<typename Point>
// void f(Point const & p) {
//     float h;
//     __if_exists(Point::z) {
//         h = p.z;
//     }
//     __if_not_exists(Point::z) {
//         ///
//     }
// }

struct Point2 { float x, y; };
struct Point3 { float x, y, z; };

template<typename Point>
void f(Point const & p) {
    float h;
    if constexpr(requires { Point::z; })
        h = p.z;
    else
        h = 0;
}

template<typename Container>
concept Sizable = requires(Container const & c) {
    {c.size()} -> std::convertible_to<size_t>;
};
static_assert(Sizable<std::vector<int>>);

/*
template<typename F, typename S> struct pair {
    F f; S s;
    pair(): f(), s() {}
};

хотим сделать это
struct A {
    A(int);
};

pair<int A> a2; //must fail
pair<int, A> a1 { 1,2 }; //must be ok
*/

template<typename F, typename S> struct pair {
    F f; S s;
    template<typename T = F, typename U = S, typename = std::enable_if_t<std::conjunction_v<
        std::is_default_constructible<T>,
        std::is_default_constructible<U>,
        std::is_trivially_default_constructible<T>, //is_implicity_default_constructible
        std::is_trivially_default_constructible<U>
    >>>
    pair() :f(), s() {}

    template<typename T = F, typename U = S>
    explicit pair() : f(), s() {}
};
/*
template<typename T> true_type test(T, int);
template<typename T> false_type test(int, ...);

template<typename T>
using is_implicity_default_constructible = decltype(test<T>({},0));

или так, чтобы сгенерировать понятную ошибку
template<...,
typename = enable_if_t<is_default_constructible<T>::value>>,
typename = enable_if_t<is_default_constructible<U>::value>>,
typename = enable_if_t<is_implicity_default_constructible<T>::value>>,
typename = enable_if_t<is_implicity_default_constructible<U>::value>>
>
*/

// С++ 20
template<typename T>
concept ImplicitlyDefaultConstructible = requires (T) { [] (T) {} ({}); };

template<typename T>
concept DefaultConstructible = std::is_default_constructible<T>();

template<typename F, typename S> struct pair2 {
    F f; S s;
    pair2() requires DefaultConstructible<F>
        && DefaultConstructible<S>
        && ImplicitlyDefaultConstructible<F>
        && ImplicitlyDefaultConstructible<S>
        : f(), s() {}
    explicit pair2() {}
};

// в с++ 20 можно навешивать условия на explicit

template<typename F, typename S>
struct pair3
{
    F f; S s;
    explicit(!ImplicitlyDefaultConstructible<F> ||
    !ImplicitlyDefaultConstructible<S>)
    pair3() requires DefaultConstructible<F>
    && DefaultConstructible<S>
    : f(), s() {}
};

void test()
{
    std::vector<int> vi;
    sort(vi); //успех!
}

// class Optional<T> //java???
// {
//     final T value;
//     Optional() {this.value = null; }
//     Optional(T value) {this.value = value; }
// };

template<typename T>
class optional
{
    bool initialized;
    std::aligned_storage_t<sizeof(T), alignof(T)> storage;

    T & get() &
    {
        return reinterpret_cast<T&>(storage);
    }
    T const & get() const &
    {
        return reinterpret_cast<T const &>(storage);
    }
    T && get() &&
    {
        return std::move(get());
    }
    optional() noexcept: initialized(false) {}
    // optional(T const & val) noexcept(NothrowCopyConstructible<T>) : initialized(true)
    // {
    //     new (&storage) T(value);
    // }
    // ~optional() : noexcept(NothrowDestructible<T>)
    // {
    //     if (initialized) get().~T();
    // }
};

export void test_concept3_x()
{
    using namespace std;
    cout<<"Test concept 3"<<endl;
    cout<<Even<3><<endl;

}
