#include <queue>
#include <mutex>
#include <condition_variable>
#include <iostream>

#include <fmt/core.h>
#include <fmt/color.h>

template <typename T>
class threadsafe_queue
{
private:
    std::mutex mut;
    std::queue<T> data_queue;
    std::condition_variable cv;

public:
    void push(T new_value)
    {
        std::lock_guard<std::mutex> lock{mut};
        data_queue.push(new_value);
        cv.notify_one();
    }

    void wait_and_pop(T &value)
    {
        std::unique_lock<std::mutex> lock{mut};
        cv.wait(lock, [this]
                { return !data_queue.empty(); });
        value = data_queue.front();
        data_queue.pop();
    }
};

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
void data_preparation_thread(threadsafe_queue<int> &data_queue)
{
    while (more_data_to_prepare())
    {
        const int data = prepare_data();
        data_queue.push(data);
        std::cout << fmt::format(fmt::fg(fmt::rgb(0xFFFF00)), "data {} is ready.", data) << std::endl;
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(500ms);
    }
}

void data_processing_thread(threadsafe_queue<int> &data_queue)
{
    while (true)
    {
        int data;
        data_queue.wait_and_pop(data);
        std::cout << fmt::format(fmt::fg(fmt::rgb(0x00FFFF)), "processing {}.", data) << std::endl;
        if (is_last_data(data))
        {
            std::cout << "finished processing." << std::endl;
            break;
        }
    }
}

int main()
{
    threadsafe_queue<int> data_queue;
    std::thread t1(data_preparation_thread, std::ref(data_queue));
    std::thread t2(data_processing_thread, std::ref(data_queue));

    t1.join();
    t2.join();
}