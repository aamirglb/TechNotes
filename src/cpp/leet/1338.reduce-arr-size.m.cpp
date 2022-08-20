// You are given an integer array arr. You can choose a set of integers and remove all the occurrences of these integers in the array.
// Return the minimum size of the set so that at least half of the integers of the array are removed.

#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <fmt/core.h>
using namespace std;

// This causes TLE
int minSetSize(vector<int>& arr) {
    size_t n = arr.size();
    unordered_map<int, int> m;
    set<int> s;

    for(const auto& e: arr)  m[e]++;
    // fmt::print("{}", m);

    while(arr.size() > n/2) {
        auto itr = std::max_element(m.begin(), m.end(),
            [](const auto& p1, const auto& p2) {
                return p1.second < p2.second;
            });
        fmt::print("Removing max element: {}\n", itr->first);
        // cout << "Removing max element: " << itr->first << endl;
        s.insert(itr->first);
        arr.erase(std::remove(arr.begin(), arr.end(), itr->first), arr.end());
        fmt::print("Array size after erase: {}\n", arr.size());
        m.erase(itr);
    }

    return s.size();
}

int minSetSize_V2(vector<int>& arr) {
    size_t n = arr.size();

    unordered_map<int, int> m;
    int count {};

    for(const auto& e: arr)  m[e]++;
    vector<int> freqCount;
    for(auto &[k, v] : m) freqCount.push_back(v);
    sort(freqCount.begin(), freqCount.end(), greater<>());

    int total = 0;
    for(size_t i = 0; i < freqCount.size(); ++i) {
        total += freqCount[i];
        ++count;
        if( (total*2) >= n) break;
    }
    return count;
}

int main() {
    vector<int> a{3,3,3,3,5,5,5,2,2,7};
    fmt::print("min set size: {}", minSetSize(a));
}