#include <iostream>
#include <vector>

void print(std::string &&s)
{
    std::cout << "print (std::string &&s)" << std::endl;
    std::string str(std::move(s));
    std::cout << "universal reference ==> str = " << str << std::endl;
    std::cout << "universal reference ==> s = " << s << std::endl;
}

void print(std::string &s)
{
    std::cout << "print(std::string &s)" << std::endl;
}

int main()
{
    std::vector<int> a = {1, 2, 3, 4, 5};
    auto b = std::move(a);
    std::cout << "a: " << a.size() << std::endl;
    std::cout << "b: " << b.size() << std::endl;

    std::string str("this is a string");
    print(str);
    std::cout << "==> str = " << str << std::endl;

    print("this is another string");
}