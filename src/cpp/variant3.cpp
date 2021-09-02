#include <iostream>
#include <string>
#include <variant>
#include <vector>
#include <type_traits>

int main() {
    using Var = std::variant<int, double, std::string, long int>;
    std::vector<Var> values {42, 0.19, "hello world", 0.815, 1234L};

    for(const Var& val: values) {
        std::visit([](const auto& v) {
            if constexpr(std::is_same_v<decltype(v), const std::string&>) {
                std::cout << '"' << v << "\" ";
            } else {
                std::cout << v << ' ';
            }
        }, val);
    }
    std::cout << "\n";

    std::variant<bool, std::string> v;
    v = "hi";
    std::cout << "index: " << v.index() << '\n';
    std::visit([](const auto& val){
        std::cout << "value: " << val << '\n';
    }, v);
    v.emplace<1>("hello");
    std::cout << "index: " << v.index() << '\n';
    std::visit([](const auto& val){
        std::cout << "value: " << val << '\n';
    }, v);
}