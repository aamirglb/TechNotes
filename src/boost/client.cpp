// g++ -Wall -Wextra -std=c++2a client.cpp -o client -lboost_system -lpthread

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <fstream>
#include <iterator>

using boost::asio::ip::udp;

int main(int argc, char* argv[])
{
  try
  {
    // if (argc != 2)
    // {
    //   std::cerr << "Usage: client <host>" << std::endl;
    //   return 1;
    // }

    argc = argc;
    argv = argv;
    boost::asio::io_context io_context;

    // udp::resolver resolver(io_context);
    // udp::endpoint receiver_endpoint =
    //   *resolver.resolve(udp::v4(), argv[1], "daytime").begin();

    udp::socket socket(io_context, udp::endpoint(udp::v4(), 44444));
    // socket.open(udp::v4());

    // boost::array<char, 1> send_buf  = {{ 0 }};
    // socket.send_to(boost::asio::buffer(send_buf), receiver_endpoint);

    const int32_t block_size = {(4 * 1024)+4};
    int32_t counter{};
    std::ofstream out;
    int32_t block_num;

    while(true) {
        std::array<char, block_size> recv_buf;
        udp::endpoint sender_endpoint;
        size_t len = socket.receive_from(
            boost::asio::buffer(recv_buf), sender_endpoint);

        auto unpack_to_int = [](char *b) -> int32_t {
            int32_t n = 0;
            for(auto i = 0; i < 4; ++i) 
                n |= static_cast<uint8_t>(b[i]) << (8*(3-i));
            return n;
            };

        // Extract block size
        int32_t blk_num = unpack_to_int(recv_buf.data());

        if(blk_num == 0) {
            if(out.is_open()) {
                out.flush();
                out.close();
            }
            // Extract filename 
            std::string file_name;
            std::copy(recv_buf.begin()+4, recv_buf.begin()+len, std::back_inserter(file_name));
            std::cout << "block: " << blk_num << " len: " << len << " filename: " << file_name << '\n';
            out.open(file_name, std::ios::out | std::ios::binary);
            block_num = 0;
            continue;
        } else {
            if(blk_num == (block_num+1)) {
                ++block_num;
                // out.write(recv_buf.data()+4, len-4);
            } else {
                // TODO: Retry mising block
                std::cout << "Invalid block number. Expected: " << (block_num+1) << " Received: " << blk_num << '\n';
            }
            out.write(recv_buf.data()+4, len-4);
            // std::cout << "received block: " << block_num << " Len: " << len << " bytes\n";
            
        }

        if(len < block_size) {
            out.close();
            ++counter;
        }
        // std::cout.write(recv_buf.data(), len);
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}