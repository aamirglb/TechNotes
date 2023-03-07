#include <asio.hpp>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <list>

#include <iostream>

int main(int argc, char *argv[])
{
    std::list<std::string> hostnames{
        "google.com",
        "bing.com",
        "duckduckgo.com",
        "outlook.com",
    };

    if (argc > 1)
    {
        for (int i = 1; i < argc; ++i)
        {
            hostnames.push_front(argv[i]);
        }
    }

    asio::io_context ctx;
    asio::error_code ec;
    asio::ip::tcp::resolver resolver(ctx);

    for (const auto &host : hostnames)
    {
        std::string msg = fmt::format("Resolving Host '{}'", host);
        std::string line(msg.size(), '-');
        fmt::print("{}\n", msg);
        fmt::print("{}\n", line);
        asio::ip::tcp::resolver::results_type results = resolver.resolve(host, "80", ec);
        for (const asio::ip::tcp::endpoint &endpoint : results)
        {
            std::cout << endpoint << std::endl;
        }
        std::cout << std::endl;
    }
}