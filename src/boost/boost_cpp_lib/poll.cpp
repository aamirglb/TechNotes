#include <asio.hpp>
#include <iostream>

// The poll function 'runs the io_context object's event processing loop
// to execute ready handlers.

// poll function will not block while there is more work to do. It simply
// executes the current set of work and then returns.

// To get the io_context working for us, we have to use the run or poll family
// of functions. Run will block and wait for work if we assign it a work object
// while the poll function does not.

int main()
{
    asio::io_context ioc;
    asio::io_context::work work(ioc);

    for (int i = 0; i < 10; ++i)
    {
        ioc.poll();
        std::cout << "counter: " << i << std::endl;
    }
}