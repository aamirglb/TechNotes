#include <iostream>

template <typename T, typename... Ts>
constexpr inline bool are_same_v =
    std::conjunction_v<std::is_same<T, Ts>..>;

template <typename T, typename...>
struct first_arg {
    using type = T;
};

template <typename... Args>
using first_arg_t = typename first_arg<Args...>::type;

template <typename... Args>
std::enable_if_t<are_same_v<Args...>, first_arg_t<Args...>>
Add(const Args&... args) noexcept
{
    return (... + args);
}

int main() {
    // const auto x = Add(1, 2, 4, 10, 15);
    // std::cout << Add(1, 2, 4, 10, 15) << std::endl;
}