#include <iostream>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <string>

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


std::string asString(const std::chrono::system_clock::time_point& tp)
{
    std::time_t t = std::chrono::system_clock::to_time_t(tp);
    // std::string ts = std::ctime(&t);
    std::string ts = std::asctime(gmtime(&t));
    ts.resize(ts.size()-1);
    return ts;
}

int main()
{
    std::cout << "system_clock: " << std::endl;
    printClockData<std::chrono::system_clock>();

    std::cout << "\nhigh_resolution_clock: " << std::endl;
    printClockData<std::chrono::high_resolution_clock>();

    std::cout << "\nsteady_clock: " << std::endl;
    printClockData<std::chrono::steady_clock>();

    // time as string
    std::chrono::system_clock::time_point tp;
    std::cout << "epoch: " << asString(tp) << std::endl;

    tp = std::chrono::system_clock::now();
    std::cout << "now:   " << asString(tp) << std::endl;

    tp = std::chrono::system_clock::time_point::min();
    // std::cout << "min: " << asString(tp) << std::endl;

    tp = std::chrono::system_clock::time_point::max();
    std::cout << "max:   " << asString(tp) << std::endl;

    // high resolution clock
    std::chrono::high_resolution_clock::time_point hctp;
    std::cout << "high resolution clock epoch: " << asString(hctp) << std::endl;

    // std::chrono::steady_clock::time_point sctp;
    // std::cout << "steady clock epoch: " << asString(sctp) << std::endl;
}