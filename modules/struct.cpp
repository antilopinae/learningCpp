#include <iostream>
#include <map>

struct Entry{
    std::string name;
    int value;
};

Entry read_entry(std::istream& is) //наивная функция чтения
{
    std::string s;
    int i;
    is >> s >> i;
    return {s,i}; // запаковка
}
// auto [n,v] - механизм структурного связывания
// struture building

void test_struct(){
    auto e = read_entry(std::cin);
    std::cout << "{ " << e.name << ", " << e.value << " }\n";

    auto [n,v] = read_entry(std::cin); //распаковка
    std::cout << "{ " << n << ", "<< v << " }\n";
}

namespace Testing_structure_building
{

    void example(){
        std::map<std::string,int> m;
        for (const auto [key,value] : m)
            std::cout << "{ " << key << ", "<< value << " }\n";
    }

    void incr(std::map<std::string, int>& m){
        for (auto& [key,value] : m)
            ++value;
    }
}
