#include <asio.hpp>
#include <iostream>

int main()
{
    asio::streambuf buf;
    std::ostream output(&buf);
    output << "Message-1\nMessage-2";
    std::istream input(&buf);
    std::string msg1, msg2;
    std::getline(input, msg1);
    std::cout << "msg-1: " << msg1 << std::endl;
    std::getline(input, msg2);
    std::cout << "msg-2: " << msg2 << std::endl;
}