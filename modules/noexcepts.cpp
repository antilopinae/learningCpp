module;

#include <iostream>

export module noexcepts;

namespace NOEXCEPTS
{
    /*
    спецификатор времени компиляции noexcept, которой говорит компилятору о том, что функция не будет выбрасывать исключения.
    */
    namespace A
    {
        class my_class
        {
            int i_;
        public:
            explicit my_class (int i) : i_(i) {}
            int get() const
            {
                return i_;
            }
        };

        inline int operator+(const my_class& v1, const my_class& v2)
        {
            return v1.get() + v2.get();
        }

        int main()
        {
            int res = 0;
            try
            {
                // Если при вызове конструктора для var0 произойдет исключение,
                // распечатываем сообщение об ошибке и выставляем res в -1
                my_class var0(10);

                // Если при вызове конструктора для var1 произойдет исключение,
                // то компилятор должен будет вызвать деструктор
                // переменной var0, распечатать сообщение об ошибке
                // и выставить res в -1
                my_class var1(100);

                // Если при сложении произошло исключение,
                // распечатываем сообщение об ошибке и выставляем res в -1

                // Вызов деструкторов var1 и var0 произойдет в любом случае,
                // вне зависимости от генерации исключения.
                res = (var1 + var0 > 0 ? 0 : 1);
            }
            catch (...)
            {
                std::cout << "Произошла ошибка" << std::endl;
                res = -1;
            }

            return 0;
        }
    }

    void noexcepts_a()
    {
        using namespace A;
        main();
    }
}

void noexcepts()
{
    using namespace NOEXCEPTS;
    noexcepts_a();

}

export void test_noexcepts()
{
    using namespace std;
    cout << "Test noexcepts" << endl;
    noexcepts();
}
