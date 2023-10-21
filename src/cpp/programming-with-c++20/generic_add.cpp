// programming before C++20 Concept, Add using C++17
#include <iostream>

template <typename T, typename... Ts>
constexpr inline bool are_same_v = std::conjunction_v<std::is_same<T, Ts>...>;

template <typename T, typename...>
struct first_arg
{
    using type = T;
};

template <typename... Args>
using first_arg_t = typename first_arg<Args...>::type;

#if _MSVC_LANG >= 202002L
// solution using C++20 concepts
template <typename... Args>
    requires are_same_v<Args...>
auto Add(Args &&...args) noexcept
{
    return (... + args);
}
#elif _MSVC_LANG >= 201703L
template <typename... Args>
std::enable_if_t<are_same_v<Args...>, first_arg_t<Args...>>
Add(const Args &...args) noexcept
{
    return (... + args);
}
#endif

int main()
{
    std::cout << __cplusplus << " " << _MSVC_LANG << std::endl;
    std::cout << Add(1, 2, 3, 4, 5);
}
