#pragma once

#include <iostream>
#include <list>

template<typename T>
class Vector
{
private:
    T* elem;
    int sz;
public:
    explicit Vector(int s);
    ~Vector() {delete[] elem;}
    const T& operator[](int i) const;
    const T& operator[](int i);
    // ..Операции копирования и перемещения

    int size() const { return sz;}

    T* begin();
    T* end();
};
