#include <deque>
#include <mutex>
#include <future>
#include <thread>
#include <utility>
#include <iostream>

std::mutex m;
std::deque<std::packaged_task<void()>> tasks;
bool shutdown{};
bool gui_shutdown_message_received()
{
    return shutdown;
}

void get_and_process_gui_message()
{
}

void gui_thread()
{
    while (!gui_shutdown_message_received())
    {
        get_and_process_gui_message();
        std::packaged_task<void()> task;
        {
            std::scoped_lock<std::mutex> lock{m};
            if (tasks.empty())
                continue;
            task = std::move(tasks.front());
            tasks.pop_front();
        }
        task();
    }
}

template <typename Func>
std::future<void> post_task_for_gui_thread(Func f)
{
    std::packaged_task<void()> task(f);
    std::future<void> res = task.get_future();
    std::scoped_lock<std::mutex> lock{m};
    tasks.push_back(std::move(task));
    return res;
}

//
int main()
{
    // start gui thread
    std::thread gui_bg_thread(gui_thread);

    auto mouse_click = []
    { std::cout << "mouse clicked." << std::endl; };
    auto button_click = []
    { std::cout << "button clicked." << std::endl; };
    auto mouse_move = []
    { std::cout << "mouse moved." << std::endl; };

    int choice;
    do
    {
        std::cout << "1 => Mouse clicked " << std::endl;
        std::cout << "2 => Button clicked" << std::endl;
        std::cout << "3 => Mouse moved" << std::endl;
        std::cout << "4 => Application closed" << std::endl;
        std::cout << "Enter your choice: " << std::endl;
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            post_task_for_gui_thread(mouse_click);
            break;
        case 2:
            post_task_for_gui_thread(button_click);
            break;
        case 3:
            post_task_for_gui_thread(mouse_move);
            break;
        }
    } while (choice != 4);
    // using namespace std::chrono_literals;
    // std::this_thread::sleep_for(3000ms);
    shutdown = true;
    gui_bg_thread.join();

    // int choice;
    // std::cout << "Enter your choice: ";
    // std::cin >> choice;
    // switch()
}