#include <compare>
#include <iostream>
#include <string>
#include <vector>

class MyInt {
public:
    constexpr MyInt(int32_t value) : _value{value} {}
    auto operator<=>(const MyInt& rhs) const = default;
private:
    int32_t _value;
};

int main()
{
    int32_t a[] {2011, 2011, 2014};
    int32_t b[] {2014, 2011, 2011};

    for(auto i = 0; i < 3; ++i) {
        auto res = a[i] <=> b[i];
        if(res < 0) std::cout << "a < b" << std::endl;
        else if(res == 0) std::cout << "a == b" << std::endl;
        else if(res > 0) std::cout << "a > b" << std::endl;
    }

    std::string str1{"2020"};
    std::string str2{"2017"};

    auto res2 = str1 <=> str2;
    if(res2 < 0) std::cout << "str1 < str2" << std::endl;
    else if(res2 == 0) std::cout << "str1 == str2" << std::endl;
    if(res2 > 0) std::cout << "str1 > str2" << std::endl;

    std::vector<int32_t> vec1{1, 2, 3};
    std::vector<int32_t> vec2{1, 2, 3};

    auto res3 = vec1 <=> vec2;
    if(res3 < 0) std::cout << "vec1 < vec2" << std::endl;
    else if(res3 == 0) std::cout << "vec1 == vec2" << std::endl;
    if(res3 > 0) std::cout << "vec1 > vec2" << std::endl;

    constexpr MyInt myInt2011{2011};
    constexpr MyInt myInt2014{2014};

    constexpr int32_t int2011{2011};
    constexpr int32_t int2014{2014};

    if(myInt2011 < myInt2014) {
        std::cout << "myInt2011 < myInt2014" << std::endl;
    }

    if( (myInt2011 <=> myInt2014) < 0) {
        std::cout << "myInt2011 < myInt2014" << std::endl;
    }

    std::cout << std::endl;

    if(myInt2011 < int2014) {
        std::cout << "myInt2011 < int2014" << std::endl;
    }

    // if(myInt2011 <=> int2014) {
    //     std::cout << "myInt2011 < int2014" << std::endl;
    // }
}