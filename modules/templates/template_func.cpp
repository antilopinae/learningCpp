#include <iostream>

template<typename Sequence, typename Value>
Value sum(const Sequence& s, Value v)
{
    for (auto x : s)
        v+=x;
    return v;
}
//Такая функция может быть функцией-членом, но не виртуальной функцией
//Компилятор не в состоянии знать все инстанцирования такого шаблона в программе
//а потому не в состоянии корректно генерировать vtbl в данной ситуации

void user(Vector<int>& vi, std::list<double>& ld, std::vector<std::complex<double>>& vc)
{
    int x = sum(vi,0);
    double d = sum(vi, 0.0);
    double dd = sum(ld, 0.0);
    auto z = sum(vc,std::complex{0.0,0.0});
}

void test_template_func()
{

}
