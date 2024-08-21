#pragma once

#include <iostream>
#include <list>

template<typename T>
class Vector_t
{
private:
    T* elem;
    int sz;
public:
    using value_type = T;

    explicit Vector_t(int s);
    Vector_t(std::initializer_list<T> lst);
    ~Vector_t() {delete[] elem;}
    const T& operator[](int i) const;
    const T& operator[](int i);
    // ..Операции копирования и перемещения

    int size() const { return sz;}

    T* begin();
    T* end();

    // T* begin() const;
    // T* end() const;
};
