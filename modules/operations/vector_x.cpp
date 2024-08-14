#include "vector_x.h"
#include <iostream>

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
    Vector_x v1 = {1,2,3,4,5};
    Vector_x v2 = v1;
    Vector_x v3{9};
    v3 = v2;
    v2 = {1,2,3};
    for (int i=0; i<v2.size(); ++i)
        std::cout<<v2[i];
    for (int i=0; i<v3.size(); ++i)
        std::cout<<v3[i];
}
