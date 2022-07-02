#include <iostream>
#include <utility>
#include <bitset>

struct Test {
    Test(int a) : m_a{a} {
        std::cout << "Test(int)" << " called.\n";
    }
    Test(const Test& t) : m_a{t.m_a} {
        std::cout << "Test(const Test& t)" << " called.\n";
    }
    Test(const Test&& t) : m_a{std::move(t.m_a)} {
        std::cout << "Test(const Test&& t)" << " called.\n";
    }

    friend std::ostream& operator<<(std::ostream& os, const Test &t) {
        os << "a: " << t.m_a;
        return os;
    }

    int32_t m_a;
};

void print() {}
static int32_t i{};
template <typename T, typename... Types>
void print(const T& firstArg, const Types&... args)
{
    std::cout << "calling: " << __PRETTY_FUNCTION__ << std::endl;
    std::cout << ++i << ". " << firstArg << std::endl;
    print(args...);
}

using namespace std::string_literals;

template <typename T>
class MyClass {
    typename T::SubType *ptr;
};

class Q {
};

int main()
{
    Test t1(10);
    Test t2 = 20;

    std::string s1{"hello world"s};
    std::cout << s1 << std::endl;

    std::string s2{std::move(s1)};
    std::cout << "s2: " << s2 << std::endl;
    std::cout << "s1: " << s1 << std::endl;

    auto s3 = u"hello world";
    std::cout << "s3: " << *s3 << " " << std::endl;
    // Test t3{Test(30)};
    // Test t4 = std::move(t2);

    print(7.5, "hello world", std::bitset<16>(377), 42, t2);

    {
        int x = 10;
        {
            int y = 20;
            auto l = [&]() { ++x; ++y; };
            l();
            std::cout << y << "\n";
        }
        std::cout << x << "\n";
    }

    MyClass<Q> x;
}