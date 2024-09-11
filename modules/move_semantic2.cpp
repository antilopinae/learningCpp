module;

#include <iostream>
#include <cstring>

export module move_semantic2;

namespace MOVE_SEMANTIC2
{
    class String
    {
    public:
        explicit String(const char *const c_string)
        {
            using namespace std;
            cout << __PRETTY_FUNCTION__ << endl;
            size = strlen(c_string) + 1;
            this->c_string = new char[size];
            strcpy(this->c_string, c_string);
        }

        String(const String& other)
        {
            using namespace std;
            cout << __PRETTY_FUNCTION__ << endl;
            c_string = new char[other.size];
            strcpy(c_string, other.c_string);
            size = other.size;
        }

        ~String() noexcept
        {
            using namespace std;
            cout << __PRETTY_FUNCTION__ << endl;
            delete[] c_string; // delete на nullptr не дает никакого эффекта
        }

        String(String &&other) noexcept //rvalue ссылка, а не lvalue
        { // конструктор перемещения
            using namespace std;
            cout << __PRETTY_FUNCTION__ << endl;
            c_string = other.c_string;
            size = other.size;
            other.c_string = nullptr;
            other.size = 0;
        }

    private:
        char *c_string;
        size_t size;
    };

    void by_value(String str) {}
}

export void test_move_semantic2()
{
    using namespace MOVE_SEMANTIC2;
    auto string = String("Hello, C++11");
    by_value(string);

    /*
     MOVE_SEMANTIC2::String::String(const char *const)
     MOVE_SEMANTIC2::String::String(const String &) // копирование string в by_value
     MOVE_SEMANTIC2::String::~String()
     MOVE_SEMANTIC2::String::~String()

     олучается 4 обращения к аллокатору, что достаточно накладно. Но если объект String больше не понадобится, а функцию by_value() менять нельзя, то можно переместить объект, а не копировать. Для этого необходимо написать конструктор перемещения для класса String
    */
    // Для вызова конструктора перемещения вместо конструктора копирования можно использовать std::move(). Теперь пример выглядит следующим образом:

    std::cout << "\n";
    auto string2 = String("Hello, C++11");
    by_value(std::move(string)); // перемещение string в by_value(), string теперь пустая


}
