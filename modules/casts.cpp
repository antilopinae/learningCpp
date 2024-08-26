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

    void f(const int* x)
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

    using namespace CONST_CASTS;
    f(px);
    f(const_cast<const int*>(px));
    /*
    Квалификаторы const и volatile можно удалить или добавить только с помощью оператора приведения const_cast и приведения типов в стиле языка C. Другие операторы приведения типов не влияют на квалификаторы const и volatile (reinterpret_cast, static_cast, dynamic_cast).
    */
    return 0;
}

namespace REINERPRET_CASTS
{
    /*
    Оператор приведения reinterpret_cast используется для приведения несовместимых типов. Может приводить целое число к указателю, указатель к целому числу, указатель к указателю (это же касается и ссылок). Является функционально усеченным аналогом приведения типов в стиле языка С. Отличие состоит в том, что reinterpret_cast не может снимать квалификаторы const и volatile, а также не может делать небезопасное приведение типов не через указатели, а напрямую по значению. Например, переменную типа int к переменной типа double привести при помощи reinterpret_cast нельзя.
    */

    struct foo {};
    struct bar {};

    struct baz : bar {};
    struct quux : bar {};

    int main()
    {
        int i = 5;
        double d = 111.222;
        char c = 'a';
        int* pi = &i;
        double* pd = &d;
        const int* pci = &i;
        void* pv = nullptr;

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

        //приводим явно double к int
        // i = reinterpret_cast<int>(d); //ERROR
        // d = reinterpret_cast<int>(i); //ERROR

        //указатель на int к char
        // c = reinterpret_cast<char>(pi); //error: loses inf

        //char к указателю на void
        pv = reinterpret_cast<void*>(c);

        //указатель на void к указателю на int
        pi = reinterpret_cast<int*>(pv);

        //const int* -> int*
        // pi = reinterpret_cast<int*>(pci); //ERROR

        //bar* -> foo* (из разных иерархий)
        pFoo = reinterpret_cast<foo*>(pBar);

        //double* -> double
        // d = reinterpret_cast<double>(pd); //error

        // double -> *double
        // pd = reinterpret_cast<double*>(d); //error

        //из одной иерархии в другую
        pBar = reinterpret_cast<bar*>(pBaz);
        pQuux = reinterpret_cast<quux*>(pBar);

        return 0;
    }
}

void reinterpret_casts()
{
    using namespace REINERPRET_CASTS;
    main();
}

namespace STATIC_CASTS
{
    /*
     Оператор приведения static_cast применяется для неполиморфного приведения типов на этапе компиляции программы. Отличие static_cast от приведения типов в стиле языка C состоит в том, что данный оператор приведения может отслеживать недопустимые преобразования, такие как приведение указателя к значению или наоборот (unsigned int к указателю на double не приведет), а также приведение указателей и ссылок разных типов считается корректным только, если это приведение вверх или вниз по одной иерархии наследования классов, либо это указатель на void. В случае фиксации отклонения от данных ограничений будет выдана ошибка при компиляции программы. При множественном наследовании static_cast может вернуть указатель не на исходный объект, а на его подобъект.
    */

    struct foo {};
    struct bar {};
    struct baz : bar {};
    struct quux : bar {};

    int main()
    {
        // Переменные простых типов и указатели на переменные простых типов
        int i = 5;
        double d = 111.222;
        char c = 'a';
        int* pi = &i;
        double* pd = &d;
        const int* pci = &i;
        void* pv = nullptr;

        // Объекты классов
        foo oFoo;
        bar oBar;
        baz oBaz;
        quux oQuux;

        // Указатели на объекты классов
        foo* pFoo = &oFoo;
        bar* pBar = &oBar;
        baz* pBaz = &oBaz;
        quux* pQuux = &oQuux;

        //приводим явно double к int
        i = static_cast<int>(d);
        std::cout << i << std::endl;

        //int->double
        d = static_cast<double>(i);
        std::cout << d << std::endl;

        //int*->char
        // c = static_cast<char>(*pi); //error!

        //char&->void
        // pv = static_cast<void*>(&c); //error

        pi = static_cast<int*>(pv); //void* -> int*

        //const int* -> int*
        // pi = static_cast<int*>(pci); //error!

        // pFoo = static_cast<foo*>(pBar); //error!
        // перемещение из одной иерархии наследования в другую
        pBar = static_cast<bar*>(pBaz);
        pQuux = static_cast<quux*>(pBar);

        // it works!
        pv = static_cast<void*>(pBar);

        return 0;
    }
}

void static_casts()
{
    using namespace STATIC_CASTS;
    main();
}

namespace DYNAMIC_CASTS
{
    /*
    Оператор приведения dynamic_cast применяется для полиморфного приведения типов на этапе выполнения программы (класс считается полиморфным, если в нем есть хотя бы одна виртуальная функция). Если указатель, подлежащий приведению, ссылается на объект результирующего класса или объект класса производный от результирующего то приведение считается успешным. То же самое для ссылок. Если приведение невозможно, то на этапе выполнения программы будет возвращен NULL, если приводятся указатели. Если приведение производится над ссылками, то будет сгенерировано исключение std::bad_cast.
    */
    /*
    Несмотря на то, что dynamic_cast предназначен для приведения полиморфных типов по иерархии наследования, он может быть использован и для обычных неполиморфных типов вверх по иерархии. В этом случае ошибка будет получена на этапе компиляции. Оператор приведения dynamic_cast может приводить указатель на полиморфный тип к указателю на void, но не может приводить указатель на void к другому типу. Способность dynamic_cast приводить полиморфные типы обеспечивается системой RTTI (Run-Time Type Identification), которая позволяет идентифицировать тип объекта в процессе выполнения программы. При множественном наследовании dynamic_cast может вернуть указатель не на исходный объект, а на его подобъект.
    */

    struct foo
    {
        virtual void do_some() {};
    };

    struct bar
    {
        virtual void do_some() {};
    };

    struct baz : bar {};
    struct quux : bar {};

    int main()
    {
        void* pv = nullptr;

        // Объекты классов
        foo oFoo;
        bar oBar;
        baz oBaz;
        quux oQuux;

        // Указатели на объекты классов
        foo* pFoo = &oFoo;
        bar* pBar = &oBar;
        baz* pBaz = &oBaz;
        quux* pQuux = &oQuux;

        pFoo = dynamic_cast<foo*>(pBar);
        if(pFoo == nullptr)
        {
            std::cout << "Fail" << std::endl; //error in runtime
        }

        //void* -> bar*
        // pBar = dynamic_cast<foo*>(pv); //error in compile-time

        //bar* -> void*
        pv = dynamic_cast<void*>(pBar);

        //перемещение из одной иерархии наследования в другую
        pBar = dynamic_cast<bar*>(pBaz);
        pQuux = dynamic_cast<quux*>(pBar); //its nullptr now!
        if (pQuux == nullptr)
        {
            std::cout << "Fail baz->bar->quux" << std::endl;
        }

        return 0;
    }
}

void dynamic_casts()
{
    using namespace DYNAMIC_CASTS;
    main();
}

export void test_casts()
{
    std::cout << "Test casts" << std::endl;
    c_casts();
    const_casts();
    reinterpret_casts();
    static_casts();
    dynamic_casts();
}
