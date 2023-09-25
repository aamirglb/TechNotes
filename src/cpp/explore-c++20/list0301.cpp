#include <iostream>

int main()
{
    try
    {
        int sum{0};
        int count{};

        int x;
        while (std::cin >> x)
        {
            sum += x;
            count++;
        }
        std::cout << "average = " << sum / count << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}