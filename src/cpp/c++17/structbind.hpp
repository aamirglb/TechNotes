#include "customer.hpp"
#include <utility>

template<>
struct std::tuple_size<Customer> {
    static constexpr int value = 3;
};

template<>
struct std::tuple_element<2, Customer> {
    using type = long;
};

template<std::size_t Idx>
struct std::tuple_element<Idx, Customer> {
    using type = std::string;
};

template<std::size_t I> decltype(auto) get(Customer& c) {
    static_assert(I < 3);

    if constexpr(I == 0) {
        return c.firstname();
    } else if constexpr (I == 1) {
        return c.lastname();
    } else {
        return c.value();
    }
}

template<std::size_t I> decltype(auto) get(Customer&& c) {
    static_assert(I < 3);

    if constexpr(I == 0) {
        return std::move(c.firstname());
    } else if constexpr (I == 1) {
        return std::move(c.lastname());
    } else {
        return c.value();
    }
}
template<std::size_t I> decltype(auto) get(const Customer& c) {
    static_assert(I < 3);

    if constexpr(I == 0) {
        return c.firstname();
    } else if constexpr (I == 1) {
        return c.lastname();
    } else {
        return c.value();
    }

    // if constexpr(I == 0) {
    //     return c.getFirst();
    // } else if constexpr (I == 1) {
    //     return c.getLast();
    // } else {
    //     return c.getValue();
    // }
}
template<> decltype(auto) get<0>(const Customer& c) { return c.firstname(); }
template<> decltype(auto) get<1>(const Customer& c) { return c.lastname(); }
template<> decltype(auto) get<2>(const Customer& c) { return c.value(); }
