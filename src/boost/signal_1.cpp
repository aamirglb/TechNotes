#include <boost/signals2.hpp>
#include <iostream>

struct HelloWorld {
    void operator()() const {
        std::cout << "Hello, World!!" << std::endl;
    }
};

int main(int argc, char *argv[]) {
    boost::signals2::signal<void ()> sig;

    HelloWorld hw;
    sig.connect(hw);

    // Call all of the slots
    sig();
}