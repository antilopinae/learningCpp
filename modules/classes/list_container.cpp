#include "list_container.h"

List_container::List_container() { }
List_container::List_container(std::initializer_list<double> il) : ld{il} { }
List_container::~List_container() { }
int List_container::size() const { return ld.size(); }
double& List_container::operator[] (int i)
{
    for (auto& x : ld)
    {
        if (i==0)
            return x;
        --i;
    }
    throw std::out_of_range{"List container"};
}

void test_list_container()
{
    List_container lc = { 1, 2, 3, 4, 5};
    lc.use(lc);
}

