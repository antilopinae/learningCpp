
class Vector
{
public:
    Vector(int s) :elem{new double[s]}, sz{s}
    {
        for (int i=0; i!=s; ++i)
            elem[i]=0;
    }
    ~Vector()
    {
        delete[] elem;
    }
    double& operator[](int i);
    int size() const;
private:
    double* elem;
    int sz;
};

void test_vector()
{
    int n = 5;
    Vector v(n);
    {
        Vector v2(2*n);
    }
}
