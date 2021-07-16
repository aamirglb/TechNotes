#include <iostream>
#include <set>
#include <vector>
#include <iterator>
#include <thread>
#include <chrono>
#include <algorithm>

int main() {
    std::vector<int> v;
    auto limit = 100000;
    for(auto i = 0; i < limit; ++i) {
        v.push_back(i);
    }
    
    std::set<int> s;

    std::copy(v.begin(), v.end(), std::inserter(s, s.begin()));
    // for(auto i : s) {
    //     std::cout << i << ' ';
    // }
    // std::cout << '\n';

    // int ele = 40;
    // if(s.count(ele) > 0) {
    //     std::cout << ele << " in set\n";
    // } else {
    //     std::cout << ele << " not in set\n";
    // }

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    bool found {};
    auto t1 = high_resolution_clock::now();
    if(std::count_if(v.begin(), v.end(), [=](int i){return i==99999;}) > 0) {
        found = true;
    }
    auto t2 = high_resolution_clock::now();

    auto ms_int = duration_cast<milliseconds>(t2 -t1);
    duration<double, std::milli> ms_double = t2 -t1;
    std::cout << ms_int.count() << "ms\n";
    std::cout << ms_double.count() << "ms\n";

    t1 = high_resolution_clock::now();
    if(s.count(99999) > 0) {
        found = true;
    }
    t2 = high_resolution_clock::now();

    ms_int = duration_cast<milliseconds>(t2 -t1);
    ms_double = t2 -t1;
    std::cout << ms_int.count() << "ms\n";
    std::cout << ms_double.count() << "ms\n";
}