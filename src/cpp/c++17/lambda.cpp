#include <iostream>
#include <string>
#include <thread>
// #include <chrono>

class Data {
private:
    std::string name;
public:
    Data(const std::string& s) : name{s} {}

    void updateName(std::string s) {
        name += s;
    }

    auto startThreadWithCopyOfThis() const {
        using namespace std::literals;
        std::thread t([*this]{
            std::this_thread::sleep_for(5s);
            // (*this).updateName(": thread");
            std::cout << name << '\n';
        });
        return t;
    }

    ~Data() {
        std::cout << "~Data(): " << name << " destroyed\n";
    }
};

class C
{
private:
    std::string name;
public:
    C(std::string _name) : name{_name} {}
    void foo() {
        auto l1 = [this]{ std::cout << name << '\n'; };
        auto l2 = [=]{ std::cout << name << '\n'; };
        auto l3 = [&]{ std::cout << name << '\n'; };

        l1();
        l2();
        l3();
    }
};

int main()
{
    C c1{"test"};
    c1.foo();

    std::thread t;
    {
        Data d{"c1"};
        t = d.startThreadWithCopyOfThis();
    }
    t.join();
}