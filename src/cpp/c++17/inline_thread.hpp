#include <string>
#include <iostream>

struct MyData {
    inline static std::string gName = "global";
    inline static thread_local std::string tName = "tls";
    std::string lName = "local";

    void print(const std::string& msg) const {
        std::cout << msg << std::endl;
        std::cout << "- gName: " << gName << '\n';
        std::cout << "- tName: " << tName << '\n';
        std::cout << "- lName: " << lName << '\n';
    }
};

inline thread_local MyData myThreadData;