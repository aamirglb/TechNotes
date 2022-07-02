#include <iostream>
#include <memory>
#include <functional>
#include <thread>
#include <future>

void func(int x, int y)
{
    std::cout << "func() called with " << x << " " << y << std::endl;
}

auto l = [](int x, int y) {
    std::cout << "lambda called with " << x << " " << y << std::endl;
};

class C
{
public:
    void operator()(int x, int y) const {
        std::cout << "operator() called with " << x << " " << y << std::endl;
    }

    void memfunc(int x, int y) const {
        std::cout << "memfunc called with " << x << " " << y << std::endl;
    }
};

int main()
{
    C c;
    std::shared_ptr<C> sp = std::make_shared<C>();

    std::bind(func, 77, 33)();
    std::bind(l, 88, 33)();
    std::bind(C(), 66, 22)();
    std::bind(&C::memfunc, c, 11, 55)();
    std::bind(&C::memfunc, sp, 44, 88)();

    [[maybe_unused]]
    std::async(func, 42, 77);
    std::async(l, 42, 77);
    std::async(c, 42, 77);
    std::async(&C::memfunc, &c, 42, 77);
    std::async(&C::memfunc, sp, 42, 77);
}