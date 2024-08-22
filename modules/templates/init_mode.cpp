#include "vector_t.cpp"
#include <iostream>
#include <vector>

enum class Init_mode { zero, seq, cpy, patrn };

void init_mode1()
{
    using enum Init_mode;
    using namespace std;
    //Грязный код
    int n = 3;
    Init_mode m = zero;
    auto arg = vector<int>(2);

    int * p, *q;
    p = new int[4];
    q = p + 4;

    vector<int> v;
    switch (m)
    {
        case zero:
            v = vector<int>(n);
            break;
        case cpy:
            v = arg;
            break;
        case seq:
        case patrn:
            break;
    };

    // ... это не инициализация, а присвоение!!

    if (m == seq)
        v.assign(p,q);
}
void init_mode2()
{
    using enum Init_mode;
    using namespace std;
    int n = 3;
    Init_mode m = zero;
    auto arg = vector<int>(2);
    int * p, *q;
    p = new int[4];
    q = p + 4;

    vector<int> v = [&]
    {
        switch (m) {
            case zero:
                return vector<int>(n);
            case seq:
                return vector<int>{p,q};
            case cpy:
                return arg;
            ///
        }
    } ();

}
void test_init_mode()
{
    Vector_t t {1,2,3,4};
    init_mode1();
}
