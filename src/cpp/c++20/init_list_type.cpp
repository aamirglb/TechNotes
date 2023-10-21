#include <iostream>
#include <typeinfo>
#include <string>
#include <functional>
#include <array>
#include <algorithm>
#include <cstdint>

class MyClass
{};

template <typename T>
auto GetParam(T parameter) -> decltype(parameter)
{
    if constexpr (std::is_same_v<T, std::string>)
    {
        return parameter + parameter;
        // std::cout << "std::string type" << std::endl;
    }
    else
    {
        return parameter * 2;
    }
}

auto closure = [](auto&& number) {
    std::cout << number << std::endl;
};

using MyArray = std::array<uint32_t, 5>;
void PrintArray(const std::function<void(MyArray::value_type)>& func)
{
    MyArray a{1, 2, 3, 4, 5};
    std::for_each(a.begin(), a.end(), func);
}

int main()
{
    auto variable{1};
    std::cout << "Type of variable: " << typeid(variable).name() << std::endl;
    auto v2{ MyClass{} };
    std::cout << "Type of variable: " << typeid(v2).name() << std::endl;

    auto t = GetParam(5);
    std::cout << "t = " << t << std::endl;

    using namespace std::string_literals;
    auto s = "Hello"s;
    auto ss = GetParam(s);
    std::cout << " ss = " << ss << std::endl;

    std::cout << typeid(closure).name() << std::endl;
    PrintArray(closure);
}