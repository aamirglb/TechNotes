#include <iostream>
#include <vector>
#include <numeric>

int main()
{
    std::vector<std::string> v;
    std::string s;
    // Enter Ctrl-Z to terminate
    while(std::cin >> s) {
        v.push_back(s);
    }
    auto all = std::accumulate(v.begin(), v.end(), std::string(""));
    std::cout << all << std::endl;

    // struct AddDelimiter {
    //     std::string delim;
    //     AddDelimiter(const std::string& d) : delim{d} {}

    //     //functor
    //     std::string operator()(const std::string& s1, const std::string& s2) {
    //         std::string result{s1};
    //         if(!s1.empty() && !s2.empty())
    //             result += delim;
    //         result += s2;
    //         return result;
    //     }
    // };

    // define a delimiter
    std::string delim{"-"};
    auto addDelimiter = [=](const std::string& s1, const std::string& s2) {
        std::string result{s1};
        if(!s1.empty() && !s2.empty())
            result += delim;
        result += s2;
        return result;
    };


    auto all2 = std::accumulate(v.begin(), v.end(), std::string(""), addDelimiter);
    std::cout << all2 << std::endl;
}

// int main()
// {
//     std::vector<std::string> v;
//     std::string s, all_strs;
//     while(std::cin >> s) {
//         v.push_back(s);
//     }

//     struct StrDelimiter {
//         std::string sep;

//         StrDelimiter(const std::string& delim) : sep{delim} {}

//         //functor
//         std::string operator()(const std::string& s1, const std::string& s2) {
//             return s1 + sep + s2;
//         }
//     };

//     // auto add_delimiter = [=](auto s1, auto s2) {
//     //     return s1 + delimiter + s2;
//     // };

//     all_strs = std::accumulate(v.begin(), v.end(), std::string());
//     std::cout << all_strs << std::endl;

//     auto all = std::accumulate(v.begin(), v.end(), std::string(), StrDelimiter("-"));
//     std::cout << all << std::endl;
// }