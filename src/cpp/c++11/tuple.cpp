#include <iostream>
#include <tuple>

template<int32_t IDX, int32_t MAX, typename... Args>
struct PrintTuple {
    static void print(std::ostream& os, const std::tuple<Args...>& t)
    {
        os << std::get<IDX>(t) << (IDX+1==MAX ? "" : ",");
        PrintTuple<IDX+1, MAX, Args...>::print(os, t);
    }
};

// structure specialization
template<int MAX, typename... Args>
struct PrintTuple<MAX, MAX, Args...> {
    static void print(std::ostream& os, const std::tuple<Args...>& t)
    {}
};

template<typename... Args>
std::ostream& operator <<(std::ostream& os, const std::tuple<Args...>& t)
{
    os << "[";
    PrintTuple<0, sizeof...(Args), Args...>::print(os, t);
    return os << "]";
}

int main()
{
    std::tuple<int32_t, float, double, std::string> t(43, 11.2f, 3.1452, "tuple printing");
    std::cout << "io: " << t << std::endl;
}