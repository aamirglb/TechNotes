// g++ -Wall -Wextra -std=c++2a server.cpp -o server -lboost_system -lpthread

#include <ctime>
#include <iostream>
#include <string>
#include <queue>
#include <thread>
#include <chrono>
#include <fstream>
#include <random>
#include <algorithm>
#include <iterator>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

class udp_server
{
public:
    udp_server(boost::asio::io_context &io_context, std::string remote_ip = "127.0.0.1", int32_t remote_port = 44444)
        : socket_(io_context, udp::endpoint(udp::v4(), 44445)),
        remote_endpoint_(boost::asio::ip::address::from_string(remote_ip), remote_port)
    {
        // start_receive();
    }

    void enqueue_image(std::string file) const {
        image_queue.push(file);
    }

    void transfer_file(std::string filename) {
        std::ifstream in(filename, std::ios::in | std::ios::binary);
        // get file size
        in.seekg(0, std::ios::end);
        auto file_size = in.tellg();
        in.clear();
        in.seekg(0);

        udp::endpoint remote_endpoint;
        remote_endpoint = udp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 44444);

        // zeroth block consist of block_id=0000, followed by filename
        std::vector<char> zeroth_block = {0, 0, 0, 0};
        auto found = filename.find_last_of("/");
        auto file = filename.substr(found+1);
        std::copy(file.begin(), file.end(), std::back_inserter(zeroth_block));
        // send block-0 with filename
        socket_.send_to(boost::asio::buffer(zeroth_block), remote_endpoint);

        // read 4K blocks
        const int32_t block_size {4 * 1024};
        auto bytes_remaining {file_size};
        int32_t block_num{};
        int32_t read_size{};

        while (bytes_remaining > 0) {
            ++block_num;

            if(bytes_remaining >= block_size) {
                read_size = block_size;
            } else {
                read_size = bytes_remaining;
            }
            std::vector<char> buffer(read_size+4);
            auto copy_big_endian = [](char *b, int32_t n) {
                for(auto i = 0; i < 4; ++i) 
                    b[i] = (n >> (8 * (3-i))) & 0xFF;
            };
            copy_big_endian(buffer.data(), block_num);
            in.read(buffer.data() + 4, read_size);
            bytes_remaining -= read_size;
            socket_.send_to(boost::asio::buffer(buffer), remote_endpoint);
            std::cout << "file: " << file << " block: " << block_num << " size: " << read_size << '\n';
        }
    }
    // thread work horse
    void send_images() {
        while (true) {
            // If pending images in the queue
            while (image_queue.size() > 0) {
                auto file = image_queue.front();
                image_queue.pop();

                // open image in binary mode
                std::string full_filename = "/home/strio/Pictures/" + file;
                transfer_file(full_filename);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }

private:
    // void start_receive()
    // {
    //     socket_.async_receive_from(
    //         boost::asio::buffer(recv_buffer_), remote_endpoint_,
    //         boost::bind(&udp_server::handle_receive, this,
    //                     boost::asio::placeholders::error,
    //                     boost::asio::placeholders::bytes_transferred));
    // }

    void handle_receive(const boost::system::error_code & /*error*/,
                        std::size_t /*bytes_transferred*/)
    {
    }

    void handle_send(boost::shared_ptr<std::string> /*message*/,
                     const boost::system::error_code & /*error*/,
                     std::size_t /*bytes_transferred*/)
    {
    }

    udp::socket socket_;
    udp::endpoint remote_endpoint_;
    // boost::array<char, 1> recv_buffer_;
    mutable std::queue<std::string> image_queue;
};

void generate_images(const udp_server &s)
{
    std::default_random_engine dre;
    std::uniform_int_distribution<int> id(10, 2000);
    std::uniform_int_distribution<int> id2(0, 4);
    std::vector<std::string> files{
        "Qt_Install_3.png",
        "qgc_pip_issue.png",
        "mission.png",
        "uav1_geofence.png",
        "smartlink_error.png"};
    decltype(files.size()) cnt{};

    while (cnt < files.size()) {
        auto sleep_time = id(dre);
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
        s.enqueue_image(files[cnt++]);
    }
}

int main()
{
    try
    {
        boost::asio::io_context io_context;
        udp_server server(io_context);
        std::thread t1(&udp_server::send_images, &server);
        std::thread t2(generate_images, std::cref(server));
        io_context.run();
        t1.join();
        t2.join();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}