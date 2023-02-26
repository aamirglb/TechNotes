#include <list>
#include <mutex>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>

class some_data
{
public:
    void do_something();

private:
    int a;
    std::string b;
};

class data_wrapper
{
public:
    template <typename Function>
    void process_data(Function func)
    {
        std::scoped_lock<std::mutex> guard{m};
        func(data);
    }

private:
    some_data data;
    std::mutex m;
};

some_data *unprotected_ptr;
void malicious_function(some_data &protected_data)
{
    unprotected_ptr = &protected_data;
}

data_wrapper x;
void foo()
{
    x.process_data(malicious_function);
}
std::list<int> shared_list;
std::mutex list_mutex;

void add_to_list(int);

struct populate_list
{
    void operator()(int start, int end)
    {
        while (start <= end)
        {
            add_to_list(start++);
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
        }
    }
};

void add_to_list(int new_value)
{
    // std::lock_guard<std::mutex> guard{list_mutex};
    std::scoped_lock<std::mutex> guard{list_mutex};
    shared_list.push_back(new_value);
}

bool list_contains(int value_to_find)
{
    // std::lock_guard<std::mutex> guard{list_mutex};
    std::scoped_lock<std::mutex> guard{list_mutex};
    return std::find(shared_list.begin(), shared_list.end(), value_to_find) != shared_list.end();
}

int main()
{
    std::thread t1(populate_list(), -25, -1);
    std::thread t2(populate_list(), 1, 25);
    t1.join();
    t2.join();

    std::copy(shared_list.begin(), shared_list.end(), std::ostream_iterator<int>(std::cout, "\n"));
}