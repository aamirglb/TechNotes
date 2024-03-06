// g++ -Wall -Wextra -Wpedantic -std=c++20 -Ic:/sw/asio-1.24.0/include user_server.cpp -lws2_32 -lwsock32
#include <asio.hpp>
#include <deque>
#include <iostream>
#include <map>

using asio::error_code;
using asio::ip::tcp;
using namespace std::placeholders;

using Message = std::string;

struct UserSession : std::enable_shared_from_this<UserSession>
{
    UserSession(tcp::socket s, int id) : socket_(std::move(s))
    {
        std::cout << "New UserSession from " << ep_ << std::endl;
    }

    ~UserSession()
    {
        std::cout << "Closed UserSession from " << ep_ << std::endl;
    }

    void start()
    {
        read_loop();
    }

    void send(Message msg)
    {
        outbox_.push_back(std::move(msg));
        if (outbox_.size() == 1)
        {
            write_loop();
        }
    }

private:
    tcp::socket socket_;
    tcp::endpoint ep_;
    Message incoming_;
    std::deque<Message> outbox_;

    void read_loop()
    {
        async_read(socket_, asio::dynamic_buffer(incoming_),
                   [this, self = shared_from_this()](error_code ec, size_t)
                   {
                       if (!ec)
                           //    std::cout << incoming_ << std::endl;
                           read_loop();
                   });
    }

    void write_loop()
    {
        if (outbox_.empty())
        {
            return;
        }
        async_write(socket_, asio::buffer(outbox_.front()),
                    [this, self = shared_from_this()](error_code ec, size_t)
                    {
                        if (!ec)
                        {
                            outbox_.pop_front();
                            write_loop();
                        }
                    });
    }
};

using Handle = std::weak_ptr<UserSession>;

struct Server
{
    explicit Server(asio::any_io_executor ex, uint16_t port) : m_acceptor{ex, {{}, port}}
    {
        std::cout << "[DEBUG] bound on " << m_acceptor.local_endpoint() << std::endl;
    }

    void listen() { accept_loop(); }

    void broadcast(Message msg)
    {
        auto shared_msg = std::make_shared<Message>(std::move(msg));
        for (auto &[id, handle] : m_users)
        {
            if (auto usr = handle.lock())
            {
                usr->send(msg);
            }
        }
    }

private:
    int next_user_id = 0;
    std::map<int, Handle> m_users;

    void accept_loop()
    {
        m_acceptor.async_accept([this](error_code ec, tcp::socket s)
                                {
            if(!ec) {
                auto id = next_user_id++;
                auto usr = std::make_shared<UserSession>(std::move(s), id);
                m_users.emplace(id, usr);
                usr->start();

                accept_loop();
            } });
    }

    tcp::acceptor m_acceptor;
};

int main()
{
    asio::io_context ioc;
    Server s(ioc.get_executor(), 34444);
    s.listen();

    ioc.run();
}