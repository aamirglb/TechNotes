#include <iostream>
#include <limits>

#define SHOW_LIMITS(T) \
    std::cout << #T << " " << std::numeric_limits<T>::min() \
        << " - " << std::numeric_limits<T>::max() \
        << " size (bytes) = " << sizeof(T) << std::endl;


int main()
{
    std::cout << "char: " << int(std::numeric_limits<char>::min())
        << " - " << int(std::numeric_limits<char>::max())
        << " size (bytes) = " << sizeof (char) << std::endl;

    SHOW_LIMITS(wchar_t)
    SHOW_LIMITS(int)
    SHOW_LIMITS(bool)
    SHOW_LIMITS(float)
    SHOW_LIMITS(double)
    SHOW_LIMITS(long double)
}