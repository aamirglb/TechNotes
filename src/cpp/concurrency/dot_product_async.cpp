#include <chrono>
#include <iostream>
#include <future>
#include <random>
#include <vector>
#include <numeric>

static const int NUM = 100'000'000;

long long get_do_product(std::vector<int> &v, std::vector<int> &w)
{
    auto f1 = std::async([&]
                         {
        size_t start = 0;
        size_t end = v.size() / 4;
        return std::inner_product(&v[start], &v[end], &w[start], 0LL); });

    auto f2 = std::async([&]
                         {
        size_t start = v.size() / 4;
        size_t end = v.size() / 2;
        return std::inner_product(&v[start], &v[end], &w[start], 0LL); });

    auto f3 = std::async([&]
                         {
        size_t start = v.size() / 2;
        size_t end = v.size() * 3 / 4;
        return std::inner_product(&v[start], &v[end], &w[start], 0LL); });

    auto f4 = std::async([&]
                         {
        size_t start = v.size() * 3 / 4;
        size_t end = v.size() - 1;
        return std::inner_product(&v[start], &v[end], &w[start], 0LL); });

    return f1.get() + f2.get() + f3.get() + f4.get();
}

int main()
{
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<int> dist(0, 200);

    std::vector<int> v, w;
    v.reserve(NUM);
    w.reserve(NUM);

    for (int i = 0; i < NUM; ++i)
    {
        v.push_back(dist(engine));
        w.push_back(dist(engine));
    }

    // measure execution time
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    std::cout << "dot_product(v, w): " << get_do_product(v, w) << std::endl;
    std::chrono::duration<double> dur = std::chrono::system_clock::now() - start;
    using namespace std::chrono_literals;
    std::cout << "parallel execution time: " << std::chrono::duration_cast<std::chrono::milliseconds>(dur).count() << std::endl;

    std::cout << std::endl;
}