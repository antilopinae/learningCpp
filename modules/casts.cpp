module;

#include <iostream>

export module casts;

// c-casts
struct foo {};
struct bar {};

struct baz : bar {};
struct quux : bar {};

int c_casts()
{
    // касты из Си

    int i =5;
    double d = 111.222;
    char c = 'a';
    int* pi = &i;
    double* pd = &d;
    const int* pci = &i;
    void *pv = NULL;

    //обьекты классов
    foo oFoo;
    bar oBar;
    baz oBaz;
    quux oQuux;

    //указатели на обьекты классов
    foo* pFoo = &oFoo;
    bar* pBar = &oBar;
    baz* pBaz = &oBaz;
    quux* pQuux = &oQuux;

    i = (int)d;
    d = (double)i;
    // c = (char)pi; //ERROR - loses inf
    // pv = (void*)c; //ERROR - loses information
    pi = (int*)pv;

    pFoo = (foo*)pBar;
    /*
    приводим указатель на double к double
    d = (double)*pd; //ERROR!
    pd = (double*)d; //ERROR!
    */

    // перемещение из одной иерархии наследования в другую
    pBar = (bar*)pBaz;
    pQuux = (quux*)pBar;

    return 0;
}

void foo(const int* pc, const int& r)
{
    int* p;
    //сняли константность и записали 33
    p = const_cast<int*>(pc);
    *p = 33;
    //сняли константность и записали 55
    const_cast<int&>(r) = 55;
}

void bar(int* p, int& r)
{
    const int* pc;
    pc = const_cast<const int*>(p);
    //*pc = 33; //ERROR
    //const_cast<const int&>(r) = 55; //ERROR
}

/*
volatile обозначит компилятору не оптимизировать переменные, нужно тогда, когда они будут меняться незаметно от компилятора
const MAX_COUNT_PEOPLE = 4;
volatile size_t countPeople = 0;
...
if(countPeople>MAX_COUNT_PEOPLE) {} // компилятор не будет хардкодить это условие сразу в true
*/

//снятие volatile
void baz(volatile int* pv, volatile int& r)
{
    int* p;
    p = const_cast<int*>(pv); // сняли volatile и записали значение
    *p=33;
    const_cast<int&>(r) = 55;
}

void quux(int* p, int& r)
{
    volatile int* pv;
    pv = const_cast<volatile int*>(p);
    *pv = 33;
    // добавили volatile и записали 55
    const_cast<volatile int&>(r) = 55;
}

namespace CONST_CASTS {
    using namespace std;

    void f(int* x)
    {
        cout << __PRETTY_FUNCTION__ << endl;
    }
}

int const_casts()
{
    /*
    Оператор приведения const_cast удаляет или добавляет квалификаторы const и volatile с исходного типа данных (простые типы, пользовательские типы, указатели, ссылки). Например, был const int, а после преобразования стал int или наоборот. Квалификаторы const и volatile называют cv-квалификаторы (cv-qualifiers). Данные квалификаторы указываются перед именами типов. Как ни трудно догадаться квалификатор const задает константность, т.е. защищает переменную от изменения. Квалификатор volatile говорит о том, что значение переменной может меняться без явного выполнения присваивания. Это обеспечивает защиту от оптимизации компилятором операций с данной переменной.
    */
    int x = 3, y = 5;
    foo(&x, y);
    bar(&x, y);
    baz(&x, y);
    quux(&x, y);

    int* px = &x;
    CONST_CASTS::f(px);
    // CONST_CASTS::f(const_cast<const int*>(px));
    return 0;
}


export void test_casts()
{
    std::cout << "Test casts" << std::endl;
    c_casts();
    const_casts();
}
