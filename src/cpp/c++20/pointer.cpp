#include <memory>
#include <iostream>
#include "format"

struct Simple
{
    Simple() { fmt::print("Simple Constructor!!\n"); }
    ~Simple() { fmt::print("Simple Destructor!!\n"); }
};

void update(std::unique_ptr<const int>&  ptr) {
    // *ptr = 50;
    fmt::print("{}\n", *ptr);
}

void legacy(const int* const ptr) {
    std::cout << __func__ << " : " << *ptr << std::endl;
}

void modern(const std::unique_ptr<int>& ptr) {
    std::cout << __func__ << " : " << *ptr << std::endl;
    ++(*ptr);
    std::cout << __func__ << " : " << *ptr << std::endl;
}

void useResource(std::weak_ptr<Simple>& wp) {
    auto resource {wp.lock()};
    if(resource) {
        fmt::print("Resource still alive\n");
    } else {
        fmt::print("Resource has been freed!!\n");
    }
}

struct Foo
{
    explicit Foo(int value) : m_data{value} {}
    int m_data;
};

struct Bar : public std::enable_shared_from_this<Bar>
{
    std::shared_ptr<Bar> getPointer() {
        return shared_from_this();
    }
};

int main()
{
    int *p = new int(22);
    std::cout << __func__ << " : " << *p << std::endl;
    legacy(p);

    auto mp = std::make_unique<int>(53);
    std::cout << __func__ << " : " << *mp << std::endl;
    modern(mp);

    auto sp { std::make_unique<Simple>() };

    auto foo { std::make_shared<Foo>(42) };

    {
        auto sp { std::make_shared<Simple>() };
        std::weak_ptr<Simple> wp {sp};
        useResource(wp);
        sp.reset();
        useResource(wp);
    }

    auto p1 { std::make_shared<Bar>() };
    auto p2 { p1->getPointer() };
    // auto ptr = std::make_unique<int>(10);
    // fmt::print("*ptr = {}\n", *ptr);
    // update(static_cast<std::unique_ptr<const int>>(ptr));
    // fmt::print("*ptr = {}\n", *ptr);
}

