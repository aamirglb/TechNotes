#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>

std::mutex mutex;
std::condition_variable cv;
bool data_ready;

void do_work()
{
    std::cout << "processing shared data." << std::endl;
}

void waiting_for_work()
{
    std::cout << "worker: waiting for work." << std::endl;

    // should use unique_lock, instead of lock_gurad because wait has to unlock the mutex if
    // wait condition is not satisfied.
    std::unique_lock<std::mutex> lock{mutex};
    cv.wait(lock /*, []
             { return data_ready; } */
    );
    do_work();
    std::cout << "work done." << std::endl;
}

void set_data_ready()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    data_ready = true;
    std::cout << "sender: data is ready." << std::endl;
    cv.notify_one();
}

int main()
{
    std::thread t1{waiting_for_work};
    std::thread t2{set_data_ready};

    t1.join();
    t2.join();
    std::cout << "main thread finished." << std::endl;
}