#include <array>
#include<iomanip>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>

template<typename Iter>
std::string bytes_to_hexstr(Iter begin, Iter end, const bool uppercase = false)
{
    std::ostringstream oss;
    if(uppercase)
        oss.setf(std::ios_base::uppercase);

    for(; begin != end; ++begin) {
        oss << std::hex << std::setw(2) << std::setfill('0')
            << static_cast<int32_t>(*begin);
    }
    return oss.str();
}

template<typename C>
std::string bytes_to_hexstr(const C &c, const bool uppercase = false)
{
    return bytes_to_hexstr(std::cbegin(c), std::cend(c), uppercase);
}


// binary to string
uint8_t hexchar_to_int(const uint8_t ch)
{
    // static std::map<uint8_t, int32_t> char_map {
    //     { '0', 0 }, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4},
    //     {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}
    // };
    if(ch >= '0' && ch <= '9') return ch - '0';
    if(ch >= 'A' && ch <= 'F') return ch - 'A' + 10;
    if(ch >= 'a' && ch <= 'f') return ch - 'a' + 10;

    throw std::invalid_argument("Invalid hexadecimal character");
}

std::vector<uint8_t> hexstr_to_bytes(std::string_view str)
{
    std::vector<uint8_t> result;
    for(size_t i = 0; i < str.size(); i += 2) {
        result.push_back( (hexchar_to_int(str[i]) << 4 | hexchar_to_int(str[i+1])));
    }
    return result;
}

// std::string capitalize()

int main()
{
    std::vector<uint8_t> v{ 0xBA, 0xAD, 0xF0, 0x0D };
    std::array<uint8_t, 6> a{ {1, 2, 3, 4, 5, 6} };
    uint8_t buf[5] = { 0x11, 0x22, 0x33, 0x44, 0x55 };

    std::cout << bytes_to_hexstr(v, true) << std::endl;
    std::cout << bytes_to_hexstr(a, true) << std::endl;
    std::cout << bytes_to_hexstr(buf, true) << std::endl;

    std::cout << bytes_to_hexstr(v, false) << std::endl;
    std::cout << bytes_to_hexstr(a, false) << std::endl;
    std::cout << bytes_to_hexstr(buf, false) << std::endl;

    std::vector<uint8_t> result = hexstr_to_bytes("BAADF00D42");
    for(const auto & i : result) std::cout << std::hex << static_cast<int32_t>(i) << " ";
    std::cout << std::endl;

    result = hexstr_to_bytes("BaaDf00d42");
    for(const auto & i : result) std::cout << std::hex << static_cast<int32_t>(i) << " ";
    std::cout << std::endl;
}