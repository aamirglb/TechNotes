#include <iostream>
#include <string>
#include <thread>

class Data {
private:
    std::string name;
public:
    Data(const std::string& s) :
        name{s}
    {}
    auto startThreadWithCopyOfThis() const {
        using namespace std::literals;
        std::thread t([this]{
            std::this_thread::sleep_for(3s);
            std::cout << name << '\n';
        });
    return t;
    }
};

int main() {
    std::thread t;
    {
        Data d{"c1"};
        t = d.startThreadWithCopyOfThis();
    }
    t.join();
}