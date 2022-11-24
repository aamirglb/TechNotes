#include "format"
#include <stdexcept>

class MyException : public std::exception
{
public:
    MyException(std::string msg)
    : m_message { std::move(msg) }
    {}

private:
    std::string m_message;
};

void throwException()
{
    try {
        throw std::runtime_error {"Throwing runtime_error exception"};
    } catch(const std::runtime_error& e) {
        fmt::print("{} caught a runtime_error\n", __func__);
        fmt::print("{} throwing MyException\n", __func__);
        std::throw_with_nested(MyException{"MyException with nested runtime_error"});
    }
}

int main()
{
    try {
        throwException();
    } catch(const MyException& e) {
        fmt::print("{} caught MyException: {}\n", __func__, e.what());
        const auto* nested { dynamic_cast<const std::nested_exception*>(&e) };
        if(nested) {
            try {
                nested->rethrow_nested();
            } catch(const std::runtime_error& e) {
                fmt::print("\tNested exception: {}\n", e.what());
            }
        }
    }
}