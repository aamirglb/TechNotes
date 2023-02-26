#include <future>
#include <iostream>
#include <string>

struct X
{
    void foo(int a, const std::string &s)
    {
        std::cout << "foo called: " << a << ' ' << s << std::endl;
    }
    std::string bar(const std::string &s)
    {
        return s + s;
    }
};

int find_the_answer_to_ltuae()
{
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1400ms);
    return 42;
}

void do_other_stuff()
{
    std::cout << "main thread doing other stuff..." << std::endl;
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(800ms);
}

int main()
{
    std::future<int> the_answer = std::async(find_the_answer_to_ltuae);
    do_other_stuff();
    std::cout << "The answer is " << the_answer.get() << std::endl;

    X x;
    std::future<void> f1 = std::async(&X::foo, &x, 42, "hello");
    auto f2 = std::async(&X::bar, x, "goodbye");

    struct Y
    {
        double operator()(double d)
        {
            std::cout << "double Y::operartor()(double): " << d << std::endl;
            return d;
        }
    };

    Y y;
    auto f3 = std::async(Y(), 3.141);
    auto f4 = std::async(std::ref(y), 2.718);

    // std::cout << "f1 = " << f1.get() << std::endl;
    // std::cout << "f2 = " << f2.get() << std::endl;
    std::cout << "f3 = " << f3.get() << std::endl;
    std::cout << "f4 = " << f4.get() << std::endl;
    // X baz(X &);
    // std::async(baz, std::ref(x));
}