#include <ctime>
#include <iostream>
#include <string>
#include <asio.hpp>

using asio::ip::tcp;

std::string make_daytime_string() {
    std::time_t now = std::time(0);
    return std::ctime(&now);
}

int main() {
    try {
        asio::io_context io;
        tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), 13));
        while(true) {
            tcp::socket socket(io);
            acceptor.accept(socket);

            std::string message = "Time from server: ";
            message += make_daytime_string();

            asio::error_code ignored_error;
            asio::write(socket, asio::buffer(message), ignored_error);
        }
    } catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
