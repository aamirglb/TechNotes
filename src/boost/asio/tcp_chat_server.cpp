#include <asio.hpp>
#include <optional>
#include <queue>
#include <unordered_set>

using tcp = asio::ip::tcp;
using error_code = asio::error_code;

using message_handler = std::function<void(std::string)>;
using error_handler = std::function<void()>;

class session : public std::enable_shared_from_this<session>
{
public:
    session(tcp::socket &&socket)
        : socket(std::move(socket))
    {
    }

    void start(message_handler &&on_message, error_handler &&on_error)
    {
        this->on_message = std::move(on_message);
        this->on_error = std::move(on_error);
        async_read();
    }

    void post(const std::string &message)
    {
        bool idle = outgoing.empty();
        outgoing.push(message);
        if (idle)
        {
            async_write();
        }
    }

private:
    void async_read()
    {
        using namespace std::placeholders;
        asio::async_read_until(socket, streambuf, "\n", std::bind(&session::on_read, shared_from_this(), _1, _2));
        // asio::async_read_until(socket, streambuf, "\n", [self = shared_from_this()](error_code ec, std::size_t bytes_transferred)
        //                        { self->on_read(ec, bytes_transferred); });
    }

    void on_read(error_code ec, std::size_t bytes_transferred)
    {
        if (!ec)
        {
            std::stringstream message;
            message << socket.remote_endpoint(ec) << ": " << std::istream(&streambuf).rdbuf();
            streambuf.consume(bytes_transferred);
            on_message(message.str());
            async_read();
        }
        else
        {
            socket.close(ec);
            on_error();
        }
    }

    void async_write()
    {
        using namespace std::placeholders;
        asio::async_write(socket, asio::buffer(outgoing.front()), std::bind(&session::on_write, shared_from_this(), _1, _2));
        // asio::async_write(socket, asio::buffer(outgoing.front()), [self = shared_from_this()](error_code ec, std::size_t bytes_transferred)
        //                   { self->on_write(ec, bytes_transferred); });
    }

    void on_write(error_code ec, std::size_t bytes_transferred)
    {
        if (!ec)
        {
            outgoing.pop();
            if (!outgoing.empty())
            {
                async_write();
            }
        }
        else
        {
            socket.close(ec);
            on_error();
        }
    }

    tcp::socket socket;
    asio::streambuf streambuf;
    std::queue<std::string> outgoing;
    message_handler on_message;
    error_handler on_error;
};

class server
{
public:
    server(asio::io_context &ctx, std::uint16_t port)
        : ctx(ctx), acceptor(ctx, tcp::endpoint(tcp::v4(), port))
    {
    }

    void async_accept()
    {
        socket.emplace(ctx);
        // clang-format off
        acceptor.async_accept(*socket, [&](error_code ec)
        {
            auto client = std::make_shared<session>(std::move(*socket));
            client->post("Welcome to chat\n\r");
            post("We have a newcomer\n\r");
            clients.insert(client);
            client->start(
                std::bind(&server::post, this, std::placeholders::_1),
                [&, weak = std::weak_ptr(client)]
                {
                    if(auto shared = weak.lock(); shared && clients.erase(shared))
                    {
                        post("We are one less\n\r");
                    }
                }
            );
            async_accept(); 
        });
        ; // clang-format on
    }

    void post(const std::string &message)
    {
        for (auto &client : clients)
        {
            client->post(message);
        }
    }

private:
    asio::io_context &ctx;
    tcp::acceptor acceptor;
    std::optional<tcp::socket> socket;
    std::unordered_set<std::shared_ptr<session>> clients;
};

int main()
{
    asio::io_context ctx;
    server s(ctx, 15001);
    s.async_accept();
    ctx.run();
}