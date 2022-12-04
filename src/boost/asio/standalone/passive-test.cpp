#include <asio.hpp>
#include <iomanip>
#include <iostream>

int main() {
    using namespace asio;
    io_context ioc;
    ip::tcp::resolver r(ioc);

    auto report = [](auto results) {
        std::cout << "---\n";
        for (auto el : results)
            std::cout << std::quoted(el.host_name()) << "+"
                      << std::quoted(el.service_name()) << " -> "
                      << el.endpoint() << "\n";
    };

    std::cout << "using passive flag...\n";
    report(r.resolve("", "finger", ip::resolver_base::flags::passive));

    std::cout << "without using passive flag...\n";
    report(r.resolve("", "finger"));
}