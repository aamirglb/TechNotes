#include <cstddef>
#include <new>
#include <iostream>
#include <iomanip>
#include <cstdio>

template <std::size_t N>
class SmallObjectBuffer
{
private:
    alignas(std::max_align_t) char d_buffer[N];
public:
    template <typename T>
    void set(const T& object);

    friend std::ostream& operator<<(std::ostream& out, SmallObjectBuffer sob)
    {
        out << std::hex << sob.d_buffer;
        return out;
    }
};

template <std::size_t N>
template <typename T>
void SmallObjectBuffer<N>::set(const T& object)
{
    static_assert(sizeof(T) <= N, "Object does not fit in the buffer.");
    new (&d_buffer) T(object);
}

int main()
{
    SmallObjectBuffer<8> so;
    int a{0xFF};
    so.set(a);

    // int c{'X'};
    // so.set(c);
    std::cout << so << std::endl;

    // encoding examples
    char s0[] = "Hello"; //unspecified encoding most probably ASCII
    char s1[] = u8"Hello"; // guaranteed to be encoded as UTF-8
    auto s2 = u"Hello";
    auto s3 = U"Hello";

    std::cout << sizeof(s0) << ", " << sizeof(s1) << ", " << sizeof(s2) << ", " << sizeof(s3) << std::endl;

    char *ptr = static_cast<char *>(s0);
    for(int i = 0; i < sizeof(s0); ++i)
    {
        std::cout << std::setw(2) << std::setfill('0') << std::showbase << std::hex << std::uppercase << 
            static_cast<int>(ptr[i] & 0xFF) << ' ';
        ++ptr;
    }
    std::cout << std::endl;

    const char * ptr1 = reinterpret_cast<const char *>(&s2[0]);
    for(int i = 0; i < sizeof(s2); ++i)
    {
        std::cout << std::setw(2) << std::setfill('0') << std::showbase << std::hex << std::uppercase << 
            static_cast<int>(ptr1[i] & 0xFF) << ' ';
        ++ptr1;
    }
    std::cout << std::endl;

    // std::puts(u8"\U0001F378");
}
