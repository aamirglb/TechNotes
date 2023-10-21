#include <iostream>
#include <variant>
#include <vector>

class NotSimple
{
public:
    NotSimple(int, float) {}
};

struct Visitor
{
    void operator()(std::monostate) const
    {
        std::cout << "visiting monostate." << std::endl;
    }
    void operator()(NotSimple s) const
    {
        std::cout << "visiting NotSimple." << std::endl;
    }

    void operator()(int i) const
    {
        std::cout << "visiting int." << std::endl;
    }
};

int main()
{
    std::variant<int, float> intFloat;
    std::cout << "index = " << intFloat.index() << ", value = " << std::get<int>(intFloat) << std::endl;

    // std::variant<NotSimple, int> cannotInit;
    std::variant<std::monostate, NotSimple, int> okInit;
    std::cout << "index = " << okInit.index() << /*", value = " << std::get<int>(okInit) <<*/ std::endl;
    std::visit(Visitor{}, okInit);
    NotSimple s(10, 3.f);
    okInit = s;
    std::visit(Visitor{}, okInit);

    std::variant<int, float, std::string> intFloatString{10.5f};
    std::cout << intFloatString.index() << ", value = " << std::get<float>(intFloatString) << std::endl;

    std::variant<long, float, std::string> longFloatString{std::in_place_index<1>, 7.6};
    std::cout << longFloatString.index() << ", value = " << std::get<float>(longFloatString) << std::endl;

    std::variant<std::vector<int>, std::string> vecStr{std::in_place_index<0>, {0, 1, 2, 3}};
    std::cout << "index = " << vecStr.index() << ", vector size = " << std::get<std::vector<int>>(vecStr).size() << std::endl;

    std::variant<int, float> intFloatSecond{intFloat};
    std::cout << "index = " << intFloatSecond.index() << ", value = " << std::get<int>(intFloatSecond) << std::endl;

    // assiging to variants
    {
        std::variant<int, float, std::string> intFloatString{"hello"};
        intFloatString = 10;
        intFloatString.emplace<2>(std::string("world"));
        std::get<std::string>(intFloatString) += std::string(" hello");
        intFloatString = 10.f;
        if (auto floatPtr = std::get_if<float>(&intFloatString); floatPtr)
        {
            *floatPtr = 2.f;
        }
    }

    {
        struct MultiplyVisitor
        {
            float m_Factor{0.5};
            MultiplyVisitor(float factor) : m_Factor{factor} {}

            void operator()(int &i) const
            {
                i *= static_cast<int>(m_Factor);
            }
            void operator()(float &f) const
            {
                f *= m_Factor;
            }

            void operator()(std::string &s) const {}
        };

        auto PrintVisitor = [](auto &value)
        { std::cout << value << std::endl; };

        std::variant<int, float, std::string> v;
        v = 10;
        std::visit(MultiplyVisitor{2.5}, v);
        std::visit(PrintVisitor, v);

        v = 5.5f;
        std::visit(MultiplyVisitor{0.5}, v);
        std::visit(PrintVisitor, v);
    }
}