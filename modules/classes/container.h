#pragma once

#include <iostream>

class Container //чистый интерфейс
{
public:
    //Чисто виртуальная функция
    virtual double& operator[] (int) = 0;
    // Константная функция-член
    virtual int size() const = 0;
    // Деструктор
    virtual ~Container() {}
    void use(Container&);
};
