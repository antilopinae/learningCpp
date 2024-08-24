module;

#include <iostream>

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

//частичное применение
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
    template<class Y> requires Small<Y, SB::Size, SB::Alignment>
    any(Y const & t) {}
};

export void test_concept3_x()
{
    using namespace std;
    cout<<"Test concept 3"<<endl;
    cout<<Even<3><<endl;


}
