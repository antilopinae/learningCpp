#include <functional>
#include <iostream>
#include <vector>
#include <memory>

#include "vector_xx.h"


//policy object
template<typename T>
class Less_than
{
    const T val; // Значение, с которым выполняется сравнение
public:
    Less_than(const T& v) :val{v} { }
    bool operator() (const T& x) const //Оператор вызова
    {
        return x<val;
    }
};

int sum2(int lhs, int rhs)
{
    return lhs+rhs;
}
//Каррирование
auto curried_sum2(int lhs)
{
    return [=](int rhs) {
        return sum2(lhs,rhs);
    };
}

int foo(int v1, int v2, int v3)
{
    return v1+v2+v3;
}

void fct(int n, const std::string & s, Less_than<int>& lti, Less_than<std::string>& lts)
{
    bool b1 = lti(n); // true if n<42
    bool b2 = lts(s);
}

// Можно подсчитать вхождений значений, для которых предикат возвращает true
//requires Sequence<C> && Callable<P,Value_type<P>>
template<typename C, typename P>
int count(C& c, P pred)
{
    int cnt = 0;
    for (const auto& x : c)
        if (pred(x))
            ++cnt;
    return cnt;
}

void f(Vector_xx<int>& vec, std::list<std::string>& lst, int x, std::string& s)
{
    std::cout << "Количество значений, меньших " << x << ": " << count(vec, Less_than{x}) << '\n';
    std::cout << "Количество значений, меньших " << s << ": " << count(lst, Less_than{s}) << '\n';
}

// лучше
void f2(Vector_xx<int>& vec, std::list<std::string>& lst, int x, std::string& s)
{
    std::cout << "Количество значений, меньших " << x << ": " << count(vec, [&] (int a){return a<x;}) << '\n';
    // [&] (int a) { return a<x;} - лямбда-выражение, генерирует Less_than<int>{x}
    // [&x] - ссылка на обьект
    // чтобы передать копию х - [=x]
    // [] - не захватываются никакие локальные имена
    // [&] - запись для захвата всех локальных имен по ссылке
    // [=] - запись для захвата всех локальных имен по значению
    std::cout << "Количество значений, меньших " << s << ": " << count(lst, [&] (const std::string& a){return a<s;}) << '\n';
}
template<typename C, typename Oper>
void for_all(C& c, Oper op)
// requires Sequence<C> && Callable<Oper,Value_type<C>>
{
    for (auto& x : c)
        op(x);
}
class Shape{
public:
    void draw() {
        std::cout<<"draw"<<std::endl;
    }
    void rotate() {
        std::cout<<"rotate"<<std::endl;
    }
};
std::unique_ptr<Shape> read_shape(std::istream& c)
{
    auto p = std::unique_ptr<Shape>(new Shape{});
    return p;
}
void user2()
{
    std::vector<std::unique_ptr<Shape>> v;
    for(int i=0;i<3;++i)
        v.push_back(read_shape(std::cin));
    //draw_all
    for_all(v, [](std::unique_ptr<Shape>& ps){ ps->draw(); });
    //rotate_all
    for_all(v, [](std::unique_ptr<Shape>& ps){ ps->rotate(); });
}
//лямбда функция может быть обобщенной
template<class S>
void rotate_and_draw(std::vector<S>& v)
{
    for_all(v, [](auto& s){ s->rotate(); s->draw(); });
}


void test_template_func_obj()
{
    using namespace std;
    using namespace std::placeholders;

    Less_than lti{42};
    cout<<lti(5)<<endl;
    Less_than lts{"Backus"s};
    Less_than<string> lts2{"Naur"};

    // Каррирование
    cout<<sum2(40,2)<<endl; //- 42
    cout<<curried_sum2(5)(10)<<endl; //- 15

    auto c0 = std::bind(foo, _1, _2, _3);
    auto c1 = std::bind(c0, 15, _1, _2);
    auto c2 = std::bind(c1, 12, _1);
    auto rr = c2(5);
    cout << rr << endl; // 32

    Vector_xx vec {1, 2, 3, 4, 5, 26};
    list lt {"Hello"s, "World"s};
    string str {"AA"s};
    f(vec, lt, 15, str);
    f2(vec, lt, 15, str);

    user2();

    vector<unique_ptr<Shape>> v;
    v.push_back(std::unique_ptr<Shape>(new Shape()));

    for(int i=0;i<2;++i)
        v.push_back(read_shape(cin));

    rotate_and_draw(v);
}
