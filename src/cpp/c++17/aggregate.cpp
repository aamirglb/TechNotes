#include <iostream>

struct Data {
    std::string name;
    double value;
};

struct MoreData : public Data {
    bool done;
};

int main()
{
    MoreData y{{"test1", 3.1425}, false};
    std::cout << std::is_aggregate<decltype(y)>::value << std::endl;
}