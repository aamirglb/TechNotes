#include <asio.hpp>
#include <iostream>
#include <fmt/core.h>

int main()
{
    std::string server_ip{"127.0.0.1"};
    std::uint16_t port{3333};

    try
    {
        asio::ip::tcp::endpoint endpoint{asio::ip::address::from_string(server_ip), port};
        asio::io_context io_ctx;
        auto socket = std::make_shared<asio::ip::tcp::socket>(io_ctx, endpoint.protocol());
        socket->async_connect(endpoint, [socket](const asio::error_code &ec)
                              {
            if(ec.value() != 0)
            {
                if(ec == asio::error::operation_aborted)
                {
                    std::cout << "Operation cancelled!!" << std::endl;
                }
                else
                {
                    std::cout << fmt::format("Error: {}, {}", ec.value(), ec.message()) << std::endl;
                }
                return;
            } });

        std::jthread worker_thread([&io_ctx]
                                   { io_ctx.run(); });
        std::this_thread::sleep_for(std::chrono::seconds(2));
        socket->cancel();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}