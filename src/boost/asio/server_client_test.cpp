#include <asio.hpp>
#include <iostream>
#include <functional>
#include <thread>

void noop() {}

std::string make_string(asio::streambuf &streambuf)
{
    return {asio::buffers_begin(streambuf.data()), asio::buffers_end(streambuf.data())};
}

int main()
{
    asio::io_context io_ctx;
    asio::ip::tcp::acceptor acceptor(io_ctx, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 0));
    asio::ip::tcp::socket server_socket(io_ctx);
    asio::ip::tcp::socket client_socket(io_ctx);

    acceptor.async_accept(server_socket, std::bind(&noop));
    client_socket.async_connect(acceptor.local_endpoint(), std::bind(&noop));
    // std::jthread t([&]
    //                { io_ctx.run(); });
    io_ctx.run();

    asio::streambuf write_buffer;
    std::ostream output(&write_buffer);
    output << "abc";
    std::cout << "writing: " << make_string(write_buffer) << std::endl;
    auto bytes_transferred = asio::write(server_socket, write_buffer);

    asio::streambuf read_buffer;
    bytes_transferred = asio::read(client_socket, read_buffer, asio::transfer_exactly(bytes_transferred));
    std::cout << "Read: " << make_string(read_buffer) << std::endl;
    read_buffer.consume(bytes_transferred);

    output << "def";
    std::cout << "Writing: " << make_string(write_buffer) << std::endl;
    bytes_transferred = asio::write(server_socket, write_buffer);

    bytes_transferred = asio::read(client_socket, read_buffer.prepare(bytes_transferred));
    read_buffer.commit(bytes_transferred);
    std::cout << "Read: " << make_string(read_buffer) << std::endl;
    read_buffer.consume(bytes_transferred);
    io_ctx.stop();
}

/*

heap = make_heap(begin, end);

std::pop_heap(begin, end);

sort
partial_sort
nth_element
sort_heap
inplace_merge

rotate
shuffle




*/