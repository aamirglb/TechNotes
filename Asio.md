# ASIO (Asynchronous Input/Output) Library

* ASIO is a cross-platform C++ library for network and low-level I/O programming.

* The core object of boost::asio is `io_context`.

* `io_context`'s `run()` function blocks until all work has finished and there are no more handlers to be dispatched, or until `io_context` has been stopped.

* The `poll()` function runs the io_context object's event processing loop to execute ready handlers.

* The `poll()` function will not block while there is more work to do. It simply executes the current set of work and then returns.

* To removed work object from io_context, use a `shared_ptr<>` to create the work object and `reset()` method of work object to remove the work from io_context.

* `asio::make_work_guard<>()` ensures that io_context stands by until work is posted at a later time.

* Multiple threads may call the `run()` function to setup a pool of threads from which `io_context` may execute handlers. 

* `io_context.stop()` signal the `io_context` that all work should be stopped, so after the current batch of work finishes, no more work will be done.

* Wrapping a function invocation with `std::bind()` creates an **object**/**function object**.

* `std::bind` converts our completion handler (a member function) into a function object that can be invoked as though it has the signature `void(const boost::system::error_code&)`.

* The `post()` function is used to ask the io_context to execute the given handler, but without allowing the io_context to call the handler from inside this function.

* The `dispatch()` function *guarantees that the handler will only be called in a thread in which the `run()`, `run_one()`, `poll()` or `poll_one()` member function is currently being invoked*.

* The subtle difference between `post()` and `dispatch()` is that `dispatch()` could even execute directly the passed function, where `post()` always request to `io_context` to run it.

* `strand` class template is use to synchronise completion handlers in a multithreaded program.

* The `strand` class template is an _executor adapter_ that guarantees that, for those handlers that are dispatched through it, an executing handler will be **allowed to complete before the next one is started**.

* By binding the handlers to the _same strand_, we are ensuring that they cannot execute concurrently.

* IPv6 contains 128 bits where as IPv4 contains 32 bits. IPv6 expresses the address in hexadecimal characters.

# ASIO Network Programming Cookbook

* Distributed software
developers usually deal with transport level protocols such as TCP or UDP. Lower layer
protocols are usually hidden from the developer and are handled by the operating system
and network devices.

* TCP protocols:
    * Reliable
    * logical connection establishment
    * point-to-point communication model (no multicasting)
    * stream-oriented (stream of bytes, messages may be broken into as many parts)

* UDP protocols:
    * Unreliable
    * Connectionless
    * Both one-to-one and one-to-many communication models (multicasting supported)
    * datagram oriented (data as messages of particular size).

* The TCP/IP standard does not standardize the protocol API implementation;
therefore, several API implementations exist. However, the one based on **Berkeley Sockets
API** is the most widely used.

* Boost.ASIO characteristics
    * Hides C-style API, provides object-oriented APIs
    * Provides rich-type system, catches many errors at compile time
    * cross-platform library
    * Auxiliary functionality such as scatter/gather I/O operations, stream-based I/O
    * Easily extendable

* Asio provides three classes used to represent an IP address:
    * `asio::ip::address_v4`: This represents an IPv4 address
    * `asio::ip::address_v6`: This represents an IPv6 address
    * `asio::ip::address`: This IP-protocol-version-agnostic class can represent both IPv4 and IPv6 addresses

* 
```
asio::ip::address ip_address = asio::ip::address_v6::any();
asio::ip::tcp::endpoint ep(ip_address, port_num);
```

* The IP address is not provided because the server application usually wants to listen for the incoming messages on all IP addresses available on the host, not only on a specific one

* IP-protocol-version-agnostic class `asio::ip::address` does not provide the
`any()` method. The server application must explicitly specify whether it wants to receive
requests either on IPv4 or on IPv6 addresses by using the object returned by the `any()` method.

* RFC #793 describes TCP protocol, RFC #768 describes UDP protocol

* **active socket**, use to send and receive data
* **passive socket**: passively wait for incoming connection (no data transmission)

* In Boost.Asio a passive socket is represented by the `asio::ip::tcp::acceptor` class.

* The free function `asio::connect()` accepts an active socket object and an object of the 
`asio::ip::tcp::resolver::iterator` class as input arguments, iterates over a collection
of endpoints, and tries to connect the socket to each endpoint.

* Unless we call the `listen()` method on the acceptor object, all connection requests arriving at corresponding endpoint will be
rejected by the operating system network software.

* Memory buffers are contiguous blocks of memory allocated in the process's address space used to store the data.

* Boost.Asio supports two types of I/O operations: synchronous and asynchronous.

* The Boost.Asio library is implemented as a framework, which exploits an **inversion of control** approach. 

* After one or more asynchronous operations are initiated, the application hands over
_one of its threads of execution to the library_, and the latter uses this thread to run the event
loop and invoke the callbacks provided by the application to notify it about the completion of
the previously initiated asynchronous operation. The results of asynchronous operations are
passed to the callback as arguments.

* **Inversion of Control (IoC**) is a design principle used in software engineering to achieve loose coupling between components. 
It involves inverting the flow of control in a program, meaning that instead of the custom code controlling the flow, **an external source (such as a framework) takes over this responsibility**

* In Boost.Asio, a fixed length buffer is represented by one of the two classes:
    * `asio::mutable_buffer` (writable buffer) or 
    * `asio::const_buffer` (read-only buffer)

* However, neither the `asio::mutable_buffer` nor `asio::const_buffer` classes are used in Boost.Asio I/O functions and methods directly. 
Instead, the `MutableBufferSequence` and `ConstBufferSequence` concepts are introduced

* `MutableBufferSequence`: a collection of the `asio::mutable_buffer` objects. 
* `ConstBufferSequence` : an object that represents a collection of the `asio::const_buffer` objects.

* The `asio::buffer()` free function has _28_ overloads that accept a variety of
representations of a buffer and return an object of either the `asio::mutable_buffers_1` or `asio::const_buffers_1` classes.

* **Extensible buffers** are those buffers that dynamically increase their size when new data is written to them.

* **Extensible stream-oriented buffers** are represented in Boost.Asio with the `asio::streambuf`, class, which is a typedef for `asio::basic_streambuf`
`typedef basic_streambuf<> streambuf;`

* The most basic way to write to the socket provided by the Boost.Asio library is to use the
`write_some()` method of the `asio::ip::tcp::socket` class.

* The `asio::ip::tcp::socket` class contains another method to synchronously write data to the socket named `send()`.

* `asio::write()` function writes all the data available in the buffer.

* The `read_until()` function has several overloads, which provide
more sophisticated ways to specify termination conditions, such as `string delimiters`, `regular expressions`, or `functors`