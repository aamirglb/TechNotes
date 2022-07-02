#include <iostream>
#include <chrono>
#include <iomanip>

template <typename C>
void printClockData()
{
    std::cout << "- precision: ";
    typedef typename C::period P;

    if(std::ratio_less_equal<P, std::milli>::value) {
        typedef typename std::ratio_multiply<P, std::kilo>::type TT;
        std::cout << std::fixed << double(TT::num)/TT::den << " milliseconds" << std::endl;
    } else {
        std::cout << std::fixed <<double(P::num)/P::den << " seconds" << std::endl;
    }
    std::cout << "- is_steady: " << std::boolalpha << C::is_steady << std::endl;
}

int main()
{
    std::cout << "system_clock: " << std::endl;
    printClockData<std::chrono::system_clock>();

    std::cout << "\nhigh_resolution_clock: " << std::endl;
    printClockData<std::chrono::high_resolution_clock>();

    std::cout << "\nsteady_clock: " << std::endl;
    printClockData<std::chrono::steady_clock>();
}