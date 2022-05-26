#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>

void threadFunc(std::vector<int> &speeds, int& res);

int main()
{
    std::vector<int> speeds = {5, 10, 15, 20, 25};
    int result = 0;

    std::thread t(threadFunc, std::ref(speeds), std::ref(result));
    t.join();
    std::cout << "Result = " << result << std::endl;
}

void threadFunc(std::vector<int> &speeds, int& res)
{
    std::cout << "Starting Thread...\n";
    for(const auto &s : speeds) {
        std::cout << s << ", ";
        res += s;
    }
    std::cout << "Thread Ends...\n";
}