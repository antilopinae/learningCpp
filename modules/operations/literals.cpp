Суффиксы стандартной библиотеки для литералов

<chrono>
std::literals::chrono_literals
h,min,s,ms,us,ns

<string>
std::literals::string_literals
s

<string_view>
std::literals::string_literals
sv

<complex>
std::literals::complex_literals
i, il, if

Неудивительно, что литералы с такими определяемыми пользователем суффиксами называются пользовательскими литералами (user-defined literal -UDL). Они определяются с использованием литеральных операто­
ров. Литеральный оператор преобразует литерал типа своего аргумента в его
возвращаемый тип. Например, суффикс i для мнимых чисел может быть реализован следующим образом:

// Мнимые числа
constexpr complex<double> operator""i(long double arg) //литеральный оператор, i-литеральный оператор, long double - оператор определен для литералов с плавающей точкой, complex<double> - тип возвращаемого значения
{
    return {0,arg};
}
//теперь можно написать
complex<double> z = 2.718 + 6.28i;
