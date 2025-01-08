// g++ -Wall -Wextra -Wpedantic -std=c++20 -ID:\SW\asio-1.30.2\include .\server.cpp -lws2_32 -lwsock32
#include <memory>
#include <iostream>
#include <cstdint>

#define _WIN32_WINNT 0x0601
#include <asio.hpp>

using asio::ip::tcp;

class session : public std::enable_shared_from_this<session>
{
public:
    session(tcp::socket socket, int32_t id) :
        m_socket(std::move(socket)),
        m_client_id{id}
    {
    }

    void run()
    {
        wait_for_request();
    }
private:
    void wait_for_request()
    {
        // Create a shared_ptr named self to this instance of the class
        auto self{shared_from_this()};

        asio::async_read_until(m_socket, m_buffer, '\n',
            [this, self](const std::error_code& ec, std::size_t len)
            {
                // std::cout << "received " << len << " bytes\n";
                if(!ec)
                {
                    std::string data{
                        std::istreambuf_iterator<char>(&m_buffer),
                        std::istreambuf_iterator<char>()
                    };

                    // std::cout << "client-" << m_client_id << ": " << data;
                    std::cout << std::format("client-{} ({}): {}", m_client_id, len, data);

                    if( data != "quit\n")
                    {
                        wait_for_request();
                    }
                    else
                    {
                        std::cout << "good bye, client-" << m_client_id << std::endl;
                        m_socket.close();
                    }
                }
                else
                {
                    std::cout << "error: " << ec.message() << std::endl;
                }
            });
    }
private:
    tcp::socket m_socket;
    asio::streambuf m_buffer;
    int32_t m_client_id;
};

class server
{
public:
    server(asio::io_context& io_context, short port) :
        m_acceptor(io_context, tcp::endpoint(tcp::v4(), port))
    {
        std::cout << "Server started at port 25000.\n";
        std::cout << "Waiting for clients to connect\n\n";

        do_accept();
    }
private:
    void do_accept()
    {
        m_acceptor.async_accept([this](std::error_code ec, tcp::socket socket)
        {
            if(!ec)
            {
                std::cout << "creating session on: "
                    << socket.remote_endpoint().address().to_string()
                    << ":" << socket.remote_endpoint().port()
                    << " for client-" << m_client_id << std::endl;
                std::make_shared<session>(std::move(socket), m_client_id)->run();
                m_client_id += 1;
            }
            else
            {
                std::cout << "error: " << ec.message() << std::endl;
            }
            do_accept();
        });
    }
private:
    tcp::acceptor m_acceptor;
    int32_t m_client_id{1};
};


int main(int argc, char* argv[])
{
    asio::io_context ioc;
    server s(ioc, 25000);
    ioc.run();
    return 0;
}