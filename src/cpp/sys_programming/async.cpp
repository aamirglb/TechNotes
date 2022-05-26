#include <iostream>
#include <future>

int asyncFunction();

int main()
{
    std::future<int> f = std::async(asyncFunction);
    std::cout << "max = " << f.get() << std::endl;
}

int asyncFunction()
{
    std::cout << "starting asynFunc...\n";
    int max = 0;
    for(auto i = 0; i < 100000; ++i) {
        max +=i;
    }
    std::cout << "Finishing asyncFunc...\n";
    return max;
}