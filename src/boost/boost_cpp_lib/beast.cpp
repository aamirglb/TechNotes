#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <iostream>
#include <string>
#include <thread>

using tcp = boost::asio::ip::tcp;
using namespace boost::asio::ip;

int main()
{
    auto const address = boost::asio::ip::make_address("127.0.0.1");
    auto const port = static_cast<unsigned short>(std::atoi("8083"));

    boost::asio::io_context ioc{1};

    tcp::acceptor acceptor{ioc, {address, port}};

    while (true)
    {
        tcp::socket socket(ioc);
        acceptor.accept(socket);
        std::cout << "socket accepted." << std::endl;

        std::thread([q = std::move(socket)]() mutable
                    { 
                        boost::beast::websocket::stream<tcp::socket> ws{std::move(q)}; 
                        ws.accept();
                        while(true)
                        {
                            boost::beast::flat_buffer buffer;
                            ws.read(buffer);
                            auto out = boost::beast::buffers_to_string(buffer.cdata());
                            std::cout << out << std::endl;
                        } })
            .detach();
    }
}