#include <exception>
#include <memory>
#include <mutex>
#include <stack>

struct empty_stack : public std::exception
{
    const char *what() const noexcept;
};

template <typename T>
class threadsafe_stack
{
private:
    std::stack<T> data;
    mutable std::mutex m;

public:
    threadsafe_stack(){};
    threadsafe_stack(const threadsafe_stack &other)
    {
        std::scoped_lock<std::mutex> lock(other.m);
        data = other.data;
    }

    threadsafe_stack &operator=(const threadsafe_stack &) = delete;
    void push(T new_value)
    {
        std::scoped_lock<std::mutex> lock{m};
        data.push(std::move(new_value));
    }

    std::shared_ptr<T> pop()
    {
        std::scoped_lock<std::mutex> lock{m};
        if (data.empty())
        {
            throw empty_stack();
        }
        const std::shared_ptr<T> res(std::make_shared<T>(data.top()));
        data.pop();
        return res;
    }

    void pop(T &value)
    {
        std::scoped_lock<std::mutex> lock{m};
        if (data.empty())
        {
            throw empty_stack();
        }
        value = data.top();
        data.pop();
    }

    bool empty() const
    {
        std::scoped_lock<std::mutex> lock{m};
        return data.empty();
    }
};