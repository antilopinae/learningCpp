#include "vector.h"

template<typename T>
Vector<T>::Vector(int s)
{
    if (s<0)
        throw std::out_of_range{"Vector::Vector(int s)"};
    elem = new T[s];
    sz = s;
}
template<typename T>
const T& Vector<T>::operator[](int i) const
{
    if (i<0 || size()<=i)
        throw std::out_of_range{"Vector::operator[]"};
    return elem[i];
}
template<typename T>
const T& Vector<T>::operator[](int i)
{
    if (i<0 || size()<=i)
        throw std::out_of_range{"Vector::operator[]"};
    return elem[i];
}
template<typename T>
T* Vector<T>::begin()
{
    return this->size() ? const_cast<T*>(&((*this)[0])) : nullptr; //указатель на первый элемент или nullptr
}
template<typename T>
T* Vector<T>::end()
{
    return this->size() ? const_cast<T*>(&((*this)[0]))+this->size() : nullptr;
}

void write(const Vector<std::string>& vs)
{
    for (int i = 0; i!=vs.size(); ++i)
        std::cout << vs[i] << '\n';
}

void f2(Vector<std::string>& vs)
{
    for (auto& s : vs)
        std::cout << s << '\n';
}

void test_vector_t()
{
    Vector<char> vc(200);
    Vector<std::string> vs(17);
    Vector<std::list<int>> vli(45);
    // write(vs);
    f2(vs);
}


