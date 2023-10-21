export module my_math;

// template <typename T>
// concept Numeric = std::is_integral<T> || std::is_floating_point<T>

export template <typename T>
T add(T lhs, T rhs)
{
    return lhs + rhs;
}