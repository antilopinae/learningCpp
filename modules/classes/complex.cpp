class complex
{
    double re, im;
public:
    complex(double r, double i):re{r}, im{i}{}
    complex(double r):re{r}, im{0}{}
    complex():re{0},im{0}{}
    double real() const {return re;}
    void real(double d) { re=d; }
    double imag() const {return im;}
    void imag(double d) { im=d;}
    complex& operator+=(complex z)
    {
        re+=z.re;
        im+=z.im;
        return *this;
    }
    complex& operator-=(complex z)
    {
        re-=z.re;
        im-=z.im;
        return *this;
    }
    complex& operator*=(complex); //определена вне класса
    complex& operator/=(complex);
};

//дополнительно
// 1/a означает operator/(complex{1},a)
complex operator+(complex a, complex b) {return a+=b;}
complex operator-(complex a, complex b) {return a-=b;}
bool operator==(complex a, complex b)
{
    return a.real()==b.real() && a.imag()==b.imag();
}
bool operator!=(complex a, complex b)
{
    return !(a==b);
}
