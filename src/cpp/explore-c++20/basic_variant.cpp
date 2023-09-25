#include <string>
#include <iostream>
#include <variant>

struct SampleVisitor
{
    void operator()(int i) const
    {
        std::cout << "int: " << i << std::endl;
    }

    void operator()(float f) const
    {
        std::cout << "float: " << f << std::endl;
    }

    void operator()(const std::string &s) const
    {
        std::cout << "string: " << s << std::endl;
    }
};

int main()
{
    std::variant<int, float, std::string> intFloatString;
    static_assert(std::variant_size_v<decltype(intFloatString)> == 3);

    // default init to the first alternative
    std::visit(SampleVisitor{}, intFloatString);
    std::cout << "index = " << intFloatString.index() << std::endl;
    intFloatString = 100.0f;
    std::cout << "index = " << intFloatString.index() << std::endl;

    intFloatString = "hello variant world";
    std::cout << "index = " << intFloatString.index() << std::endl;

    // use get_if
    if (const auto intPtr = std::get_if<int>(&intFloatString); intPtr)
    {
        std::cout << "int! " << *intPtr << std::endl;
    }
    else if (const auto floatPtr = std::get_if<float>(&intFloatString); floatPtr)
    {
        std::cout << "float! " << *floatPtr << std::endl;
    }

    // use holds_alternative
    if (std::holds_alternative<int>(intFloatString))
    {
        std::cout << "the variant holds an int!" << std::endl;
    }
    else if (std::holds_alternative<float>(intFloatString))
    {
        std::cout << "the variant holds a float" << std::endl;
    }
    else if (std::holds_alternative<std::string>(intFloatString))
    {
        std::cout << "the variant holds a string" << std::endl;
    }

    try
    {
        auto f = std::get<float>(intFloatString);
        std::cout << "float!!" << f << std::endl;
    }
    catch (const std::bad_variant_access &e)
    {
        std::cerr << "our variant doesn't hold folat at this moment. " << e.what() << '\n';
    }

    // visit
    std::visit(SampleVisitor{}, intFloatString);
    intFloatString = 10;
    std::visit(SampleVisitor{}, intFloatString);
    intFloatString = 23.5f;
    std::visit(SampleVisitor{}, intFloatString);
    intFloatString = "hello";
    std::visit(SampleVisitor{}, intFloatString);
}