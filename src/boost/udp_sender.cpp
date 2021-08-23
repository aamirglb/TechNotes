#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <fstream>
#include <iterator>

// using boost::asio::ip;
using boost::asio::ip::udp;
using namespace std::chrono_literals;

int main(int argc, char* argv[])
{
  try
  {
    argc = argc;
    argv = argv;
    boost::asio::io_context io_context;

    udp::socket socket(io_context, udp::endpoint(udp::v4(), 12345));
    auto remote_endpoint = udp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 54321);
    uint32_t cnt = {};

    while(true) {
        ++cnt;
        std::this_thread::sleep_for(200ms);
        std::string msg("MSG-");
        msg += std::to_string(cnt);
        std::vector<char> v(msg.begin(), msg.end());
        // std::cout << msg;
        socket.send_to(boost::asio::buffer(v), remote_endpoint);
        if(cnt > 60) break;
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}