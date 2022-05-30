#include <array>
#include <iostream>
#include <string>
#include <sstream>

using u8 = unsigned char;

class ipv4
{
public:
    constexpr ipv4() : data { {0} } {}
    constexpr ipv4(const u8 a, const u8 b, const u8 c, const u8 d) :
        data{{a, b, c, d}} {}

    explicit constexpr ipv4(uint64_t a) :
        data { {
            static_cast<u8>((a >> 24) & 0xFF),
            static_cast<u8>((a >> 16) & 0xFF),
            static_cast<u8>((a >> 8) & 0xFF),
            static_cast<u8>(a & 0xFF)
        }} {}

    ipv4(ipv4 const & other)  noexcept :
        data(other.data) {}

    ipv4& operator=(ipv4 const & other) {
        data = other.data;
        return *this;
    }

    std::string to_string() const {
        std::stringstream sstr;
        sstr << *this;
        return sstr.str();
    }

    constexpr uint64_t to_ulong() const noexcept
    {
        return (static_cast<uint64_t>(data[0] << 24) |
            static_cast<uint64_t>(data[1] << 16) |
            static_cast<uint64_t>(data[2] << 8) |
            static_cast<uint64_t>(data[3])
            );
    }

    friend std::ostream& operator<<(std::ostream& os, const ipv4& a)
    {
        os << static_cast<int32_t>(a.data[0]) << '.'
           << static_cast<int32_t>(a.data[1]) << '.'
           << static_cast<int32_t>(a.data[2]) << '.'
           << static_cast<int32_t>(a.data[3]);
        return os;
    }

    friend std::istream& operator>>(std::istream& is, ipv4& a)
    {
        u8 d1, d2, d3;
        int32_t b1, b2, b3, b4;
        std::cout << "Enter IPv4 address in x.x.x.x format\n";

        is >> b1 >> d1 >> b2 >> d2 >> b3 >> d3 >> b4;
        if(d1 == '.' && d2 == '.' && d3 == '.') {
            a = ipv4(b1, b2, b3, b4);
        } else {
            is.setstate(std::ios_base::failbit);
        }
        return is;
    }

    ipv4& operator++() {
        *this = ipv4(1+ to_ulong());
        return *this;
    }

    ipv4 operator++(int) {
        ipv4 result(*this);
        ++(*this);
        return result;
    }

    friend bool operator==(const ipv4 &ip1, const ipv4 &ip2) noexcept {
        return ip1.data == ip2.data;
    }

    friend bool operator!=(const ipv4 &ip1, const ipv4& ip2) noexcept {
        return !(ip1 == ip2);
    }

    friend bool operator<(const ipv4 &ip1, const ipv4 &ip2) noexcept {
        return ip1.to_ulong() < ip2.to_ulong();
    }

    friend bool operator>(const ipv4 &ip1, const ipv4 &ip2) noexcept {
        return ip2 < ip1;
    }

    friend bool operator<=(const ipv4 & ip1, const ipv4 &ip2) noexcept {
        return !(ip1 > ip2);
    }

    friend bool operator>=(const ipv4 &ip1, const ipv4 &ip2) noexcept {
        return !(ip1 < ip2);
    }

private:
    std::array<u8, 4> data;
};

int main()
{
    ipv4 address(192, 168, 0, 102);
    std::cout << address << std::endl;

    ipv4 ip;
    std::cout << ip << std::endl;
    std::cin >> ip;
    if(!std::cin.fail()) {
        std::cout << ip << std::endl;
    }
    std::cout << ip++ << std::endl;
    std::cout << ip << std::endl;

    std::cout << "Input IP range: ";
    ipv4 low, high;

    std::cin >> low >> high;

    if(high > low) {
        for(ipv4 ip = low; ip <= high; ++ip ) {
            std::cout << ip << std::endl;
        }
    } else {
        std::cerr << "Invalid Range!" << std::endl;
    }
}