#include <iostream>
#include <vector>
#include <random>
#include <ctime>

std::vector<uint32_t> bad_randVec() {
    std::default_random_engine e;
    std::uniform_int_distribution<uint32_t> u(0, 9);
    std::vector<uint32_t> ret;
    for(size_t i = 0; i < 100; ++i) {
        ret.push_back(u(e));
    }
    return ret;
}

std::vector<uint32_t> good_randVec() {
    static std::default_random_engine e;
    static std::uniform_int_distribution<uint32_t> u(0, 9);
    std::vector<uint32_t> ret;
    for(size_t i = 0; i < 100; ++i) {
        ret.push_back(u(e));
    }
    return ret;
}

int main() {
    std::vector<uint32_t> v1{bad_randVec()};
    std::vector<uint32_t> v2{bad_randVec()};
    std::cout << ((v1 == v2) ? "equal" : "not equal") << std::endl;

    std::vector<uint32_t> v3{good_randVec()};
    std::vector<uint32_t> v4{good_randVec()};
    std::cout << ((v3 == v4) ? "equal" : "not equal") << std::endl;

    std::cout << time(0) << std::endl;
}

