#pragma once

#include <list>
#include <iostream>
#include "container.h"

class List_container : public Container
{
public:
    List_container();
    List_container(std::initializer_list<double>);
    ~List_container();
    double& operator[](int i) override;
    int size() const override;
private:
    std::list<double> ld;
};
