// так гораздо понятнее (Страуструп)
template<typename Container>
using Value_type = typename Container::value_type;

//requirements
//template<Sequence Seq> = requires Sequence<Seq>
template<Sequence Seq, Number Num> requires Arithmetic<Value_type<Seq>,Num>
Num sum(Seq s, Num v);

// Arithemtic<X,Y> - concept

//можно так
template<typename Seq, typename Num> requires Sequence<Seq> && Number<Num> && Arithmetic<Value_type<Seq>,Num>
Num sum(Seq s, Num n);

//или так
template<Sequence Seq, Arithemtic<Value_type<Seq>> Num>
Num sum(Seq s, Num n);



template<Forward_iterator Iter>
void advance(Iter p, int n)
{
    while(n--)
        ++p; //Однонаправленный оператор имеет ++, но не + или +=
}

template<Random_access_iterator Iter>
void advance(Iter p, int n)
{
    p+=n; // Итератор с произвольным доступом имеет операцию +=
}

// компилятор сам выберет шаблон с наиболее строгими требованиями
void user(vector<int>::iterator vip, list<string>::iterator lsp)
{
    advance(vip,10);
    advance(lsp,10);
}

// если аргумент не соответствует концепту, данная альтернатива не может быть выбрана.
// если аргумент соответствует концепту только в одной альтернативе, то выбирается именно эта альтернатива.
// если аргументы двух альтернатив одинаково хорошо соответствуют концепту, мы сталкиваемся с неоднозначностью
// если аргументы двух альтернатив соотвтетствуют концепту и один из них более строгий, чем другой (соответствует всем тем же требованиям, что и другой, и еще некоторым), то выбирается именно эта альтернатива.

template<Forward_iterator Iter>
void advance(Iter p, int n)
{
    while(n--)
        ++p;
}

template<Forward_iterator Iter, int n>
requires requires(Iter p, int i) // requires-выражение
{
    p[i]; p+i;
}

void advance(Iter p, int n)
{
    p+=n;
}
