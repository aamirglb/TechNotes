#include <iostream>
#include <type_traits>
#include <vector>
#include <functional>
#include <ratio>
#include <chrono>

template <typename T>
void foo(const T& val)
{
    if(std::is_pointer<T>::value) {
        std::cout << "foo() called for a pointer" << std::endl;
    } else {
        std::cout << "foo() called for a value" << std::endl;
    }
}

void func(int x, int y) {
    std::cout << "func() " << x << " " << y << std::endl;
}

class C {
public:
    void memfunc(int x, int y) const {
        std::cout << "C::memfunc: " << x << " " << y << std::endl;
    }
};

template <typename V, typename R>
std::ostream& operator<<(std::ostream& os, const std::chrono::duration<V,R>& d)
{
    os << "[" << d.count() << " of " << R::num << "/" << R::den << "]";
    return os;
}

int main()
{
    int32_t a;
    int32_t *p = &a;
    foo(a);
    foo(p);

    std::vector<std::function<void(int, int)>> tasks;
    tasks.push_back(func);
    tasks.push_back([](int x, int y) {
        std::cout << "lambda " << x << " " << y << std::endl;
    });

    for(std::function<void(int, int)> f : tasks) {
        f(33, 54);
    }

    std::function<void(const C&, int, int)> mf;
    mf = &C::memfunc;
    mf(C(), 42, 77);

    using FiveThirds = std::ratio<5, 3>;

    std::cout << FiveThirds::num << "/" << FiveThirds::den << std::endl;

    std::cout << std::atto::num << "/" << std::atto::den << std::endl;
    std::cout << std::kilo::num << "/" << std::kilo::den << std::endl;

    std::chrono::seconds twentySec(20);
    std::chrono::hours  aDay(24);

    std::chrono::milliseconds ms;
    ms += twentySec + aDay;
    std::cout << ms.count() << " ms" << std::endl;
    --ms;
    std::cout << ms.count() << " ms" << std::endl;
    ms *= 2;
    std::cout << ms.count() << " ms" << std::endl;
    std::cout << std::chrono::nanoseconds(ms).count() << " ns" << std::endl;
    std::cout << "milliseconds max = " << std::chrono::seconds::max().count() << std::endl;
    std::cout << "milliseconds min = " << std::chrono::seconds::min().count() << std::endl;
    // std::cout << "milliseconds rep = " << std::chrono::seconds::rep() << std::endl;
    // std::cout << "milliseconds period = " << std::chrono::seconds::period() << std::endl;

    std::cout << ms << std::endl;
    std::cout << twentySec << std::endl;
    std::cout << aDay << std::endl;
}