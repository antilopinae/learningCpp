#include <iostream>

template<typename T>
class Vector2
{
private:
    T* elem;
    int sz;
public:
    using value_type = T;

    Vector2(std::initializer_list<T> lst): elem{new T[lst.size()]}, sz{static_cast<int>(lst.size())}
    {
        std::copy(lst.begin(), lst.end(), elem);
    }

    // Конструктор из диапазона [b;e)
    template<typename Iter>
    Vector2(Iter b, Iter e)
    {
        elem = new T[2];
        // some code
        sz = 2;
    }

    explicit Vector2(int s)
    {
        if (s<0)
            throw std::out_of_range{"Vector::Vector(int s)"};
        elem = new T[s];
        sz = s;
    }

    const T& operator[](int i) const
    {
        if (i<0 || size()<=i)
            throw std::out_of_range{"Vector::operator[]"};
        return elem[i];
    }

    const T& operator[](int i)
    {
        if (i<0 || size()<=i)
            throw std::out_of_range{"Vector::operator[]"};
        return elem[i];
    }

    int size() const { return sz;}

    T* begin()
    {
        return this->size() ? const_cast<T*>(&((*this)[0])) : nullptr; //указатель на первый элемент или nullptr
    }

    T* end()
    {
        return this->size() ? const_cast<T*>(&((*this)[0])) + this->size(): nullptr; //указатель на первый элемент или nullptr
    }

    ~Vector2() {delete[] elem;}
};

// Помощь компилятору, правило вывода
template<typename Iter>
Vector2(Iter,Iter) -> Vector2<typename std::iterator_traits<Iter>::value_type>;

// Vector2(const char *) -> Vector2<std::string>;

template<typename T>
void write_vector(Vector2<T>& vc)
{
    for (auto& s: vc)
        std::cout<< s <<'\n';
}

void test_deduction_guide()
{
    Vector2 v1 {1,2,3,4,5}; //int
    /*ERROR!*/
    Vector2 v2(v1.begin(), v1.begin()+2); //нужна помощь компилятору
    write_vector(v1);
    //write_vector(v2);
}
