#include <boost/asio.hpp>
#include <iostream>

int main() {
    // boost::asio::io_service srv;
    // boost::asio::io_service::work worker(srv);
    // srv.run();
    // std::cout << "After srv.run() call." << std::endl;

    boost::asio::io_service srv;
    boost::asio::io_service::work worker(srv);
    for(int i = 0; i < 5; ++i) {
        srv.poll();
        std::cout << "Line: " << i << std::endl;
    }
}