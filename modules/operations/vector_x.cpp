#include "vector_x.h"

Vector_x::Vector_x(const Vector_x& a) //Копирующий конструктор
:elem {new double[a.sz]},
sz {a.sz}
{
    for (int i=0; i!=sz; ++i)
        elem[i] = a.elem[i];
}

Vector_x& Vector_x::operator=(const Vector_x&a)//Копирующее присваивание
{
    double* p = new double[a.sz];
    for (int i=0; i!=a.sz; ++i)
        p[i] = a.elem[i];
    delete[] elem;
    elem=p;
    sz = a.sz;
    return *this;
}

// упускаем копирование при каждом +
// Vector_x operator+(const Vector_x& a, const Vector_x& b)
// {
//     if (a.size()!=b.size())
//         throw Vector_size_mismatch{};
//     Vector_x res(a.size());
//     for(int i=0; i!=a.size(); ++i)
//         res[i]=a[i]+b[i];
//     return res;
// }

//делаем так: перемещающий конструктор
Vector_x::Vector_x(Vector_x&& a) :elem{a.elem}, sz{a.sz} //забираем элементы из а
{
    a.elem = nullptr; // Теперь в А нет элементов
    a.sz = 0;
}

// Vector_x Vector_x::operator+(Vector_x b,const Vector_x& a)
// {
//     if (a.size()!=b.size())
//         throw std::range_error{ "Vector_x" };
//     Vector_x res(a.size());
//     for(int i=0; i!=a.size(); ++i)
//         res[i]=a[i]+b[i];
//     return b;
// }

Vector_x& Vector_x::operator=(Vector_x&& a)
{
    this->elem = a.elem;
    this->sz = a.sz;
    a.elem = nullptr;
    a.sz = 0;
    return *this;
}


Vector_x::Vector_x(int s) :elem{new double[s]}, sz{s}
{
    for (int i=0; i!=s; ++i)
        elem[i]=0;
}

Vector_x::~Vector_x()
{
    delete[] elem;
}

Vector_x::Vector_x(std::initializer_list<double> lst) :elem{new double[lst.size()]}, sz{static_cast<int>(lst.size())}
{
    //Копирование в elem из lst
    std::copy(lst.begin(), lst.end(), elem);
}

double& Vector_x::operator[](int i)
{
    return elem[i];
}

int Vector_x::size() const
{
    return sz;
}

void Vector_x::push_back(double el)
{
    //smth
}

void test_vector_x()
{
    Vector_x x(1000);
    Vector_x y(2000);
    Vector_x z(3000);
    //получаем копию
    z = x;
    //выполняем перемещение (перемещающее присваивание)
    y = std::move(x);
    // return z; //используется перемещение
}
