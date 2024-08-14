#include "container.h"
#include "vector.h"

class Vector_container : public Container
{
public:
    Vector_container(int s) :v(s) { }
    ~Vector_container() {} //неявно вызывается деструктор Vector()

    double& operator[](int i) override { return v[i]; }
    int size() const override { return v.size(); }
private:
    Vector v;
};

void test_vector_container()
{
    Vector_container v(4);
    v.use(v);
}
