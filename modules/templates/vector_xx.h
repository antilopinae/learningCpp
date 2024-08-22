#pragma once

#include <iostream>
#include <list>

template<typename T>
class Vector_xx
{
private:
    T* elem;
    int sz;
public:
    using value_type = T;

    explicit Vector_xx(int s)
    {
        if (s<0)
            throw std::out_of_range{"Vector::Vector(int s)"};
        elem = new T[s];
        sz = s;
    }
    Vector_xx(std::initializer_list<T> lst): elem{new T[lst.size()]}, sz{static_cast<int>(lst.size())}
    {
        std::copy(lst.begin(), lst.end(), elem);
    }
    ~Vector_xx() {delete[] elem;}
    const T& operator[](int i) const
    {
        if (i<0 || size()<=i)
            throw std::out_of_range{"Vector::operator[]"};
        return elem[i];
    }
    const T& operator[](int i)
    {
        if (i<0 || size()<=i)
            throw std::out_of_range{"Vector::operator[]"};
        return elem[i];
    }
    // ..Операции копирования и перемещения

    int size() const { return sz;}

    T* begin()
    {
        return this->size() ? const_cast<T*>(&((*this)[0])) : nullptr; //указатель на первый элемент или nullptr
    }
    T* end()
    {
        return this->size() ? const_cast<T*>(&((*this)[0]))+this->size() : nullptr;
    }
};
