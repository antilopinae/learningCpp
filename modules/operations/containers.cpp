for (size_t i=0; i<c.size(); ++i)
    c[i] = 0;

for (auto p=c.begin(); p!=c.end(); ++p)
    *p = 0;

// Итераторы ислользуются для лередачи лоследовательностей алгоритмам стандартной библиотеки. Наnример:
sort(v.begin(), v.end());

for (auto&x : c)
    x = 0;
// Здесь c.begin() и c.end() используется неявно
