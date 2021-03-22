#include <boost/signals2.hpp>
#include <iostream>
#include <cstdlib>

struct Hello {
    void operator()() const {
        std::cout << "Hello";
    }
};

struct World {
    void operator()() const {
        std::cout << ", World!!" << std::endl;
    }
};

struct GoodMorning {
    void operator()() const {
        std::cout << "... and good morning!!" << std::endl;
    }
};

int main(int argc, char *argv[]) {
    boost::signals2::signal<void ()> sig;

    if(argc == 2) {
        int32_t option = atoi(argv[1]);
        switch(option) {
            case 1:
                sig.connect(World());
                sig.connect(Hello());
                break;
            case 2:
                sig.connect(1, World());
                sig.connect(0, Hello());
                break;
            case 3:
                sig.connect(Hello());
                sig.connect(World());
                sig.connect(GoodMorning());
                break;
            case 4:
                break;
            default:
                std::cout << "Invalid option..."<<std::endl;
                break;

        }
        if(argv[1] == "1") {
            sig.connect(World());
        sig.connect(Hello());
        }
        
    } else {
        sig.connect(Hello());
        sig.connect(World());
    }
    

    // Call all of the slots
    sig();
}