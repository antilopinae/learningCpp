#include "vector.h"

Vector::Vector(int s) :elem{new double[s]}, sz{s}
{
    for (int i=0; i!=s; ++i)
        elem[i]=0;
}

Vector::~Vector()
{
    delete[] elem;
}

Vector::Vector(std::initializer_list<double> lst) :elem{new double[lst.size()]}, sz{static_cast<int>(lst.size())}
{
    //Копирование в elem из lst
    std::copy(lst.begin(), lst.end(), elem);
}

double& Vector::operator[](int i)
{
    return elem[i];
}

int Vector::size() const
{
    return sz;
}

void Vector::push_back(double el)
{
    //smth
}

void test_vector()
{
    int n = 5;
    Vector v(n);
    {
        Vector v2(2*n);
    }
}

//reinterpret_cast - для трактовки обьекта как простой последовательности байтов
//const_cast - для отбрасывания const


// Shape* ps{read_shape(cin) );
//     if (Smiley*p = dynamic_cast<Smiley*>(ps)) // ps указывает на Smiley? если Shape не Smiley, то вернет nullptr

// Vector read(std::istream& is)
// {
//     Vector v;
//     for(double d; is>>d; ) //до достижения конца файла или при ошибки форматирования
//         v.push_back(d);
//     return v;
// }
