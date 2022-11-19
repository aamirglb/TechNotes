#include "format"
#include <string>
#include <utility>
#include <vector>

void handleMessage(std::string& msg)
{
    fmt::print("handleMessage with lvalue reference: {}\n", msg);
}

void helper(std::string&& msg) {
    fmt::print("{}: with rvalue referece: {}\n", __func__, msg);
}

void handleMessage(std::string&& msg)
{
    fmt::print("handleMessage with rvalue reference: {}\n", msg);
    helper(std::move(msg));
}

class DataHolder
{
public:
    void setData(const std::vector<int>& data)
    {
        fmt::print("lvalue - copying verctor\n");
        m_data = data;
    }

    void setData(const std::vector<int>&& data)
    {
        fmt::print("rvalue - moving vector\n");
        m_data = std::move(data);
    }
private:
    std::vector<int> m_data;
};

class Test
{
public:
    void show() & { fmt::print("called on non-temporary instance.\n"); }
    void show() && { fmt::print("called on temporary instance."); }
};

Test getTest()
{
    return Test{};
}

int main()
{
    std::string a {"hello "};
    handleMessage(a);
    handleMessage(a + "world");

{
    int a{11}, b{22};
    fmt::print("a={}, b={}\n", a, b);
    int old { std::exchange(a, b) };
    fmt::print("a={}, b={}\n", a, b);
    fmt::print("old = {}\n", old);
}

    fmt::print("\n\n");
    DataHolder d1;
    std::vector<int> data{11, 22, 33};
    d1.setData(data);
    d1.setData({1, 2, 3, 4});

    fmt::print("\n\n");
    Test t;
    t.show();
    getTest().show();
}