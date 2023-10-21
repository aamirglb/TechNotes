#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <queue>
#include <chrono>

std::mutex mutex;
std::queue<int> data_queue;
std::condition_variable cv;

int max_data{25};
int curr_data{};
bool more_data_to_prepare()
{
    return curr_data < max_data;
}

int prepare_data()
{
    return ++curr_data;
}

bool is_last_data(int data)
{
    return data == max_data;
}
void data_preparation_thread()
{
    while (more_data_to_prepare())
    {
        const int data = prepare_data();
        {
            std::lock_guard<std::mutex> lock{mutex};
            data_queue.push(data);
        }
        cv.notify_one();
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(400ms);
    }
}

void data_processing_thread()
{
    int counter{};
    while (true)
    {
        std::unique_lock<std::mutex> lock{mutex};
        // std::unique_lock<std::mutex> lock{mutex};
        cv.wait(lock, [&]
                { ++counter; return !data_queue.empty(); });
        int data = data_queue.front();
        data_queue.pop();
        lock.unlock();
        std::cout << "processing... " << data << std::endl;
        if (is_last_data(data))
        {
            std::cout << "Done processing." << std::endl;
            break;
        }
    }
    std::cout << "wait function was called: " << counter << " timers." << std::endl;
}

int main()
{
    std::thread t1{data_preparation_thread};
    std::thread t2{data_processing_thread};

    t1.join();
    t2.join();
}
