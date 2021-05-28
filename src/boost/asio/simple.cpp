
// g++ -Wall -Wextra -I./asio-1.18.2/include -o simple simple.cpp -lpthread

#include <iostream>
#include <chrono>

#ifdef _WIN32
    #define _WIN32_WINNT 0x0A00
#endif

#define ASIO_STANDALONE

#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

std::vector<char> vBuffer(1*1024);

void GrabSomeData(asio::ip::tcp::socket& socket) {
    socket.async_read_some(asio::buffer(vBuffer.data(), vBuffer.size()),
        [&](std::error_code ec, std::size_t length) {
            if(!ec) {
                std::cout << "\n\nRead " << length << " bytes\n\n";
                for(std::size_t i = 0; i < length; ++i)
                    std::cout << vBuffer[i];
                GrabSomeData(socket);
            }
        }
    );
}

int main() {
    asio::error_code ec;

    asio::io_context context;

    // Give some fake tasks to asio so the context doesn't finish
    asio::io_context::work idleWork(context);

    std::thread thrContext = std::thread([&](){context.run();});

    // example.com
    // asio::ip::tcp::endpoint endpoint(asio::ip::make_address("93.184.216.34", ec), 80);

    asio::ip::tcp::endpoint endpoint(asio::ip::make_address("51.38.81.49", ec), 80);
    // asio::ip::tcp::endpoint endpoint(asio::ip::make_address("127.0.0.1", ec), 80);
    asio::ip::tcp::socket socket(context);
    socket.connect(endpoint, ec);

    if(!ec) {
        std::cout << "Connected!\n";
    } else {
        std::cout << "Failed to connect to address:\n" << ec.message() << '\n';
    }

    if(socket.is_open()) {
        GrabSomeData(socket);

        std::string sRequest = 
            "GET /index.html HTTP/1.1\r\n"
            "Host: example.com\r\n"
            "Connection: close\r\n\r\n";

        socket.write_some(asio::buffer(sRequest.data(), sRequest.size()), ec);

        
        // socket.wait(socket.wait_read);

        using namespace std::chrono_literals;
        std::this_thread::sleep_for(20s);

        // size_t bytes = socket.available();
        // std::cout << "Bytes Available: " << bytes << '\n';

        // if(bytes > 0) {
        //     std::vector<char> vBuffer(bytes);
        //     socket.read_some(asio::buffer(vBuffer.data(), vBuffer.size()), ec);

        //     for(auto c: vBuffer)
        //         std::cout << c;
        // }

    }
    // system("pause");
    return 0;
}