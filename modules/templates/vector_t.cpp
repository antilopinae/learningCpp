#include "vector_t.h"

template<typename T>
Vector_t<T>::Vector_t(std::initializer_list<T> lst): elem{new T[lst.size()]}, sz{static_cast<int>(lst.size())}
{
    std::copy(lst.begin(), lst.end(), elem);
}

template<typename T>
Vector_t<T>::Vector_t(int s)
{
    if (s<0)
        throw std::out_of_range{"Vector::Vector(int s)"};
    elem = new T[s];
    sz = s;
}

template<typename T>
const T& Vector_t<T>::operator[](int i) const
{
    if (i<0 || size()<=i)
        throw std::out_of_range{"Vector::operator[]"};
    return elem[i];
}
template<typename T>
const T& Vector_t<T>::operator[](int i)
{
    if (i<0 || size()<=i)
        throw std::out_of_range{"Vector::operator[]"};
    return elem[i];
}
template<typename T>
T* Vector_t<T>::begin()
{
    return this->size() ? const_cast<T*>(&((*this)[0])) : nullptr; //указатель на первый элемент или nullptr
}
template<typename T>
T* Vector_t<T>::end()
{
    return this->size() ? const_cast<T*>(&((*this)[0]))+this->size() : nullptr;
}

void write(const Vector_t<std::string>& vs)
{
    for (int i = 0; i!=vs.size(); ++i)
        std::cout << vs[i] << '\n';
}

void f2(Vector_t<std::string>& vs)
{
    for (const auto& s : vs)
        std::cout << s << '\n';
}

void test_vector_t()
{
    Vector_t<char> vc(200);
    Vector_t<std::string> vs(17);
    Vector_t<std::list<int>> vli(45);
    // write(vs);
    f2(vs);
}


