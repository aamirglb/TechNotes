#include <iostream>
#include <functional>

template <typename T, typename ... Ts>
auto concat(T t, Ts ... ts) {
    if constexpr (sizeof...(ts) > 0) {
        return [=](auto ... params) {
            return t(concat(ts...)(params...));
        };
    } else {
        return t;
    }
}

int main() {
    auto twice {[](int i){ return i * 2; }};
    auto thrice {[](int i){ return i * 3; }};

    auto combined {concat(twice, thrice, std::plus<int>{})};
    std::cout << combined(2, 3) << '\n';
}
