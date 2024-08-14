class complex_x
{
    double re = 0;
    double im = 0;
public:
    complex_x(double r, double i):re{r},im{i}{}
    complex_x(double r):re{r} {}
    complex_x() {}
    complex_x& operator=(const complex_x&) = default; //копирующее присваивание
    complex_x& operator=(complex_x&&) = default; //перемещающее присваивание
    complex_x(const complex_x&) = default; //копирующий конструктор
    complex_x(complex_x&&) = default; //перемещающий конструктор
};

void test_complex_x()
{
    complex_x z1{};
    complex_x z2 {z1}; //копирующая инициализация
    complex_x z3;
    z3 = z2; //копирующее присваивание
}
