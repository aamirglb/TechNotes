#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <fstream>
#include <iterator>

// using boost::asio::ip;
using boost::asio::ip::udp;
using namespace std::chrono_literals;

static void read_data(udp::socket *s) {
    auto bytes_avail = 0;
    while((bytes_avail = s->available()) > 0) {
            std::vector<uint8_t> buf(bytes_avail);
            udp::endpoint        sender_endpoint;
            size_t len = s->receive_from(boost::asio::buffer(buf), sender_endpoint);
            std::cout << "RX: Len=" << len << "Bytes: " << buf.data() << "\n";
        }
        std::cout << "Out of while\n";
}
int main(int argc, char* argv[])
{
  try
  {
    argc = argc;
    argv = argv;
    boost::asio::io_context io_context;

    udp::socket socket(io_context, udp::endpoint(udp::v4(), 54321));

    while(true) {
        std::this_thread::sleep_for(1s);
        read_data(&socket);
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
  }