#pragma once

#include <iostream>
#include <sstream>

//конкретный тип
class Vector
{
public:
    //инициализация списком элементов типа double
    Vector(std::initializer_list<double>); //Vector v1 = {1,2,3,4,5};
    Vector(int s);
    ~Vector();
    double& operator[](int i);
    int size() const;
    //добавление элемента в конец с увеличением размера на 1
    void push_back(double);
private:
    double* elem;
    int sz;
};
