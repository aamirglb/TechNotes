// g++ -Wall -Wextra -Wpedantic struct_bind.cpp

#include <iostream>
#include <string>
#include <map>
#include <cassert>
#include <array>
#include <functional>
#include <filesystem>

using namespace std::string_literals;
using namespace std::filesystem;

struct MyStruct {
    int32_t i = 10;
    std::string s = "hello"s;
};

struct S {
    const char x[6] = "hello";
    const char y[3] = "ab";
};

MyStruct s { 42, "world"s};

MyStruct& getStruct() {
    // return MyStruct{42, "world"s };
    return s;
}

std::array<int32_t, 3> getArray() {
    return {1, 2, 3};
}

int main()
{
    MyStruct ms;
    auto [u, v] = ms;
    std::cout << u << '\t' << v << std::endl;
    assert(&((MyStruct*)&u)->s == &v); // Should be OK

    const auto& [id, val] = getStruct();
    std::cout << id << " " << val << std::endl;
    ++s.i;
    std::cout << id << " " << val << std::endl;

    std::map<int32_t, std::string> m {
        {1, "one"s},
        {2, "two"s},
        {3, "three"},
        {4, "four"},
        {5, "five"},
    };

    // C++17
    for(const auto& [key, value] : m) {
        std::cout << "key: " << key << ", value: " << value << std::endl;
    }
    auto [pos, ok] = m.insert({6, "six"});
    if(!ok) {
        std::cout << "insert failed\n";
    } else {
        std::cout << "{6, \"six\"} inserted successfully\n";
    }
    // if with initalisation
    if(auto [pos, ok] = m.insert({5, "five"}); !ok) {
        const auto& [key, val] = *pos;
        std::cout << "already here: " << key << '\n';
    }

    // Pre-C++17
    auto ret = m.insert({7, "seven"});
    if(!ret.second) {
        std::cout << "insert failed\n";
    } else {
        std::cout << "{7, \"seven\"} inserted successfully\n";
    }
    for(const auto& pair : m) {
        std::cout << pair.first << " " << pair.second << std::endl;
    }

    // std::boyer_moore_searcher bm{m.begin(), m.end()};
    S s1{};
    auto [a, b] = s1;
    std::cout << a << " " << b << std::endl;
    // a[0] = 'H';

    struct B {
        int32_t a {1};
        int32_t b {2};
    };

    struct D1 : B {
    };
    auto [x, y] = D1{};

    struct D2 : B {
        int32_t c = 3;
    };
    // auto [i, j, k] = D2{};

    int arr[] = { 47, 57, 67 };
    auto [i, j, k] = arr;
    std::cout << i << " " << j << " " << k << std::endl;

    // auto getArr() -> int(&)[2] {
    //     return {5, 8};
    // };

    // auto [x, y] = getArr();

    auto [a_, b_, c_] = getArray();
    std::cout << a_ << " " << b_ << " " << c_ << std::endl;

    std::array<int32_t, 4> stdarr { 5, 6, 7, 8};

    auto& [ii, jj, kk, ll] = stdarr;
    ii += 10;
    std::cout << ii << " " << jj << " " << kk << " " << ll << std::endl;

    // switch with initialization
    switch(path p("."); status(p).type()) {
    case file_type::directory:
        std::cout << p << ":\n";
        for(auto& e : std::filesystem::directory_iterator(p)) {
            std::cout << "- " << e.path() << '\n';
        }
        break;
    default:
        std::cout << p << " exists\n";
        break;
    }
}
