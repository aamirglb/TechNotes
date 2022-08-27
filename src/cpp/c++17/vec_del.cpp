#include <iostream>
#include <vector>
#include <algorithm>

template <typename R>
void print(R& range, std::string msg = "") {
    std::cout << msg << ": ";
    for(const auto& ele : range) {
        std::cout << ele << ", ";
    }
    std::cout << std::endl;
}

template <typename T>
void quick_remove_at(std::vector<T>& v, std::size_t idx) {
    if(idx < v.size()) {
        v[idx] = std::move(v.back());
        v.pop_back();
    }
}

template <typename T>
void quick_remove_at(std::vector<T> &v, typename std::vector<T>::iterator it) {
    if(it != std::end(v)) {
        *it = std::move(v.back());
        v.pop_back();
    }
}

int main() {
    std::vector<int> v{1, 5, 3, 8, 9, 10, 6, 2};
    print(v, "original");
    quick_remove_at(v, 4);
    print(v, "after 8 remove");
    quick_remove_at(v, std::find(std::begin(v), std::end(v), 3));
    print(v, "after 3 remove");
}