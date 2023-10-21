#include <condition_variable>
#include <mutex>
#include <future>
#include <thread>
#include <iostream>
#include <queue>

std::queue<int> queue;
std::mutex queueMutex;
std::condition_variable queueCondVar;

void provider(int val)
{
    for (int i = 0; i < 9; ++i)
    {
        {
            std::lock_guard<std::mutex> lg(queueMutex);
            queue.push(val + i);
        }
        queueCondVar.notify_one();
        // queueCondVar.notify_all();
        std::this_thread::sleep_for(std::chrono::milliseconds(val));
    }
}

void consumer(int num)
{
    int counter{};
    // pop values if available
    while (true)
    {
        int val;
        {
            std::unique_lock<std::mutex> ul(queueMutex);
            queueCondVar.wait(ul, [&]
                              { ++counter; return !queue.empty(); });
            val = queue.front();
            queue.pop();
        }
        std::cout << "consumer " << num << ": " << val << std::endl;
    }
    std::cout << "wait function was called: " << counter << " timers." << std::endl;
}

int main()
{
    // start three providers
    auto p1 = std::async(std::launch::async, provider, 100);
    auto p2 = std::async(std::launch::async, provider, 200);
    auto p3 = std::async(std::launch::async, provider, 300);

    // start two consumers
    auto c1 = std::async(std::launch::async, consumer, 1);
    auto c2 = std::async(std::launch::async, consumer, 2);
}
