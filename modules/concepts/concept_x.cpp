module;

#include <iostream>
#include <vector>

export module concept_x; // module declaration

// #include <iostream>        // import declaration

template<typename Seq, typename Num>
Num sum(Seq s, Num v)
{
    //vector, list, map - for example (int, double, Matrix)
    for (const auto& x : s)
        v+=x;
    return v;
}


export void test_concept_x()       // export declaration
{
    using namespace std;
    cout<<"Test concept" << endl;
    vector v{1,2,3};
    int x{5};
    cout<<sum(v,x)<<endl;
}
