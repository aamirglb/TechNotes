// simple chat server using ASIO
// g++ -Wall -Wextra -Wpedantic -std=c++20 -Ic:/sw/asio-1.24.0/include chat_server.cpp -lws2_32 -lwsock32
#include <asio.hpp>
#include <deque>
#include <iostream>
#include <map>

using asio::error_code;
using asio::ip::tcp;
using namespace std::placeholders;

using Id = std::int32_t;

struct Message
{
    Id sender;
    std::string text;
};

struct IServer
{
    virtual ~IServer() = default;
    virtual void broadcast(Message msg) = 0;
};

struct UserSession : std::enable_shared_from_this<UserSession>
{
    UserSession(tcp::socket s, Id id, IServer &srv) : socket_(std::move(s)), id_(id), srv_(srv)
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

    Id get_id() const { return id_; }

private:
    tcp::socket socket_;
    Id id_;
    IServer &srv_;
    tcp::endpoint ep_;
    Message incoming_;
    std::deque<Message> outbox_;

    void read_loop()
    {
        incoming_.sender = id_;
        async_read_until(
            socket_,
            asio::dynamic_buffer(incoming_.text),
            "\n",
            [this, self = shared_from_this()](error_code ec, size_t n)
            {
                std::cout << ep_ << ": Read " << ec.message() << std::endl;
                if (!ec)
                {
                    srv_.broadcast(std::move(incoming_));
                    incoming_.text.erase(0, n);
                    read_loop();
                }
            });
    }

    void write_loop()
    {
        if (outbox_.empty())
        {
            return;
        }

        async_write(
            socket_,
            asio::buffer("user-" + std::to_string(outbox_.front().sender) + ": " + outbox_.front().text),
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

struct Server : public IServer
{
    Server(asio::any_io_executor ex, uint16_t port) : m_acceptor{ex, {{}, port}}
    {
        std::cout << "[DEBUG] bound on " << m_acceptor.local_endpoint() << std::endl;
    }

    void listen()
    {
        accept_loop();
    }

    virtual void broadcast(Message msg) override
    {
        m_history.push_back(msg);
        while (m_history.size() > MAX_HIST)
        {
            m_history.pop_front();
        }

        for (auto &[id, handle] : m_users)
        {
            if (auto usr = handle.lock())
            {
                if (usr->get_id() != msg.sender)
                {
                    usr->send(msg);
                }
            }
        }
    }

private:
    Id next_user_id = 0;
    std::map<Id, Handle> m_users;
    static size_t constexpr MAX_HIST = 100;
    std::deque<Message> m_history;

    void accept_loop()
    {
        m_acceptor.async_accept([this](error_code ec, tcp::socket s)
                                {
            if(!ec) {
                erase_if(m_users, [](auto& pair) { return pair.second.expired();}); // garbage collect

                auto id = next_user_id++;
                auto usr = std::make_shared<UserSession>(std::move(s), id, *this);
                m_users.emplace(id, usr);

                for(auto& msg : m_history) {
                    usr->send(msg);
                }
                broadcast({-1, "** Now " + std::to_string(m_users.size()) + " user online **\n"});
                usr->start();

                accept_loop();
            } });
    }

    tcp::acceptor m_acceptor;
};

int main()
{
    asio::io_context ioc;

    Server s(ioc.get_executor(), 34443);
    s.listen();
    ioc.run();
}