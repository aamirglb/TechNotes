#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <type_traits>

// template <typename T>
// struct sum {
//     T value;

//     // template <typename ... Ts>
//     // sum(Ts&& ... values) -> sum<std::common_type_t<Ts...>>;

//     template<typename ... Ts>
//     sum(Ts&& ... values)
//         : value{(values + ... )}
//     {}
// };

template <typename T>
class addable
{
    T val;
public:
    addable(T v) : val{v} {}

    template <typename U>
    T add(U x) const {
        if constexpr (std::is_same_v<T, std::vector<U>>) {
            auto copy {val};
            for(auto &n : copy) n += x;
            return copy;
        } else {
            return val + x;
        }
    }
};

template <typename T>
struct Foo {
    T a;
    Foo(T a_) : a{a_} {}
};

template <typename T>
Foo<T> operator+(const Foo<T>& lhs, const Foo<T>& rhs) {
    return Foo(lhs.a + rhs.a);
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Foo<T>& f) {
    return os << f.a;
}

template <typename ... Ts>
auto sum(Ts ... ts) {
    // if constexpr()
    return (ts + ...);
}

template <typename R, typename ... Ts>
auto matches(const R& range, Ts ... ts) {
    return (std::count(std::begin(range), std::end(range), ts) + ...);
}

template <typename T, typename ... Ts>
bool insert_all(T& s, Ts ... ts) {
    return (s.insert(ts).second && ...);
}

int main() {
    std::cout << addable<int>{1}.add(2) << std::endl;
    std::cout << addable<float>{1.}.add(2) << std::endl;
    std::cout << addable<int>{2}.add(3.6) << std::endl;
    std::cout << addable<std::string>{"aa"}.add("bcde") << std::endl;

    std::vector<int> v {1, 2, 3};
    auto rv = addable<std::vector<int>>{v}.add(10);
    for(auto &e : rv) std::cout << e << ", ";
    std::cout << std::endl;

    std::vector<std::string> sv{"a", "b", "c"};
    auto rsv = addable<std::vector<std::string>>{sv}.add(std::string{"z"});
    for(auto &e : rsv) std::cout << e << ", ";
    std::cout << std::endl;

    int isum { sum(1, 2, 3, 4, 5) };
    std::cout << "isum = " << isum << std::endl;

    std::cout << sum(std::string("hello"), std::string("world")) << std::endl;

    Foo f1(10), f2(20), f3(5), f4(6);
    auto f = sum(f1, f2, f3, f4);
    std::cout << f << std::endl;

    std::vector<int> v2{1, 2, 3, 4, 5, 6};
    std::cout << matches(v2, 2, 3, 5, 7, 3, 3) << std::endl;
    std::cout << matches("abcdefg", 'a', 'b', 'c', 'h', 'j') << std::endl;

    std::set<int> my_set{v.begin(), v.end()};
    std::cout << std::boolalpha << insert_all(my_set, 4, 5, 6) << std::endl;
    std::cout << std::boolalpha << insert_all(my_set, 7, 8, 1) << std::endl;
}

// int main() {
//     // sum<float> s {1u, 2.0, 3, 4.0f};
//     // sum ss {std::string{"abc"}, "def"};

//     // std::cout << ss.value << std::endl;
//     // std::cout << s.value << std::endl;
// }