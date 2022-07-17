#include <iostream>
#include <map>
#include <map>
#include <string>

int minIndexChar(std::string str, std::string patt)
{
    std::multimap<char, int> m;
    for (int i = 0; i < str.size(); ++i)
        m.insert({str[i], i});
        // m[str[i]] = i;

    for(const auto& [k, v] : m) {
        std::cout << k << " : " << v << std::endl;
    }
    std::multimap<char, int>::iterator itr;

    for (int i = 0; i < patt.size(); ++i)
    {
        itr = m.find(patt[i]);
        if (itr != m.end()) {
            std::cout << "*** " << itr->second << std::endl;
            return itr->second;
        }
    }
    return -1;
}

int main()
{
    std::string str = "geeksforgeeks";
    std::string patt = "set";

    minIndexChar(str, patt);
}