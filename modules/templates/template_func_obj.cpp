template<typename T>
class Less_than
{
    const T val; // Значение, с которым выполняется сравнение
public:
    Less_than(const T& v) :val{v} { }
    bool operator() (const T& x) const //Оператор вызова
    {
        return x<val;
    }
};

void test_template_func_obj()
{

}
