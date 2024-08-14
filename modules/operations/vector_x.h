#pragma once

#include <iostream>
#include <sstream>

//конкретный тип
class Vector_x
{
public:
    //инициализация списком элементов типа double
    Vector_x(std::initializer_list<double>); //Vector v1 = {1,2,3,4,5};
    Vector_x(int s);
    ~Vector_x();

    //Копирующий конструктор
    Vector_x(const Vector_x& a);
    //Копирующее присваивание
    Vector_x& operator=(const Vector_x& a);
    const double& operator[](int i) const;

    double& operator[](int i);
    int size() const;
    //добавление элемента в конец с увеличением размера на 1
    void push_back(double);
private:
    double* elem;
    int sz;
};
