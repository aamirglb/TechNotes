# Boost C++ Library

C++ GCC get all warnings: gcc -Q --help=warning

* Most of Boost libraries consist solely of header files that can be used directly, some of the libraries require compilation.

![boost_lib](images/cpp/boost_lib.png)

## Boost.Signals2

* Boost.Signals2 library is an implementation of a _managed_ signals and slots system. Boost.Signals2 allows the user to specify the manner in which multiple return values are combined. 

```
// define a signal with no arguments and void return value
boost::signals2::signal<void ()> sig;

// connect a callback to signal
sig.connect(call_back);

// call all slots
sig();
```

* By default, slots are pushed onto the back of the slot list.

* The Boost.Signals2 library allows slots to be placed into groups that are ordered in some way. supply an extra parameter at the beginning of the connect call that specifies the group. Group values are, by default, ints, and are ordered by the integer < relation.

```
sig.connect(1, World());
sig.connect(0, Hello());
```

* pass argument to slot
```
  boost::signals2::signal<void (float, float)> sig;
```

* Just as slots can receive arguments, they can also return values. These values can then be returned back to the caller of the signal through a _combiner_.

* the default behavior of a signal that has a return type (float, the first template argument given to the boost::signals2::signal class template) is to call all slots and then return a boost::optional containing the result returned by the last slot called. 

## Boost.ASIO

* Boost.Asio is a cross-platform C++ library mainly for networking and
some other low-level input/output programming.

* The most important class that sits at the heart of Boost.Asio `io_service`. (In Boost 1.66, `io_service` is deprecated. Yes, you should use `io_context`. )

* Boost.Asio has successfully abstracted the concepts of input and output that work not just for networking but for COM serial ports, files, and so on.

```cpp
# synchronous input/output
read(stream, buffer [, extra options])
write(stream, buffer [, extra options])

# asynchronous input/output
async_read(stream, buffer [, extra options], handler)
async_write(stream, buffer [, extra options], handler)

```

* Boost.Asio was accepted into Boost 1.35 in December 2005

* Boost.Asio depends on 
* **Boost.System** (provide OS support) 
* **Boost.Regex** (optional, required for `read_until()` or `async_read_until()`)
* **Boost.DateTime** (optional: used for timers) 
* **OpenSSL**

* synchronous servers/clients are usually multi-threaded. [synchronous: blocking calls and multi-threading]

* asynchronous programming is _event-driven_. You start an operation,
but you don't know when it will end; you supply a _callback_, which the API will call when the operation ends, together with the operation result. [asynchronous: less-threads and events].

* Boost.Asio uses `io_service` to talk to the operating system's input/output service.

```cpp
using boost::asio;
io_service service;
ip::tcp::endpoint ep( ip::address::from_string("127.0.0.1"), 2001);
ip::tcp::socket sock(service);
sock.connect(ep);
```

* `service.run()` loop will run as long as there are asynchronous
operations pending.

* Boost.Asio allows for both _exceptions_ or _error codes_. All the synchronous functions have overloads that either throw in case of error or can return an error code. In case the function throws, it will always throw a `boost::system::system_error` error.

* All asynchronous functions return an error code, which you
can examine in your callback. Asynchronous functions never throw an exception.

```cpp
void client_session(socket_ptr sock) {
try {
...
} catch ( boost::system::system_error e) {
// handle the error
}
}
```

```cpp
char data[512];
boost::system::error_code error;
size_t length = sock.read_some(buffer(data), error);
if (error == error::eof)
  return; // Connection closed
```

* All Boost.Asio error codes are in namespace `boost::asio::error` Check out the boost/asio/error.hpp header for more details.

* The `io_service` class is thread-safe. Several threads can call `io_service::run()`. If called from multiple threads, all threads will be blocked. All callbacks will be called in the context of any
of the threads that called `io_service::run()`.

* The `socket` classes are not thread-safe. Thus, you should avoid
doing such as reading from a socket in one thread and write to it in a
different thread.

* Boost.Asio, in addition to networking, provides other input/output facilities. Boost.Asio allows waiting for signals, such as **SIGTERM (software terminate)**, **SIGINT (signal interrupt)**, **SIGSEGV (segment violation)**, and so on.

```cpp
void signal_handler(const boost::system::error_code & err, int signal)
{
// log this, and terminate application
}
boost::asio::signal_set sig(service, SIGINT, SIGTERM);
sig.async_wait(signal_handler);
```

* Asynchronous I/O operations can have a deadline to complete.

```cpp
bool read = false;
void deadline_handler(const boost::system::error_code &) {
  std::cout << (read ? "read successfully" : "read failed") <<
  std::endl;
}

void read_handler(const boost::system::error_code &) {
  read = true;
}

ip::tcp::socket sock(service);
...
read = false;
char data[512];
sock.async_read_some(buffer(data, 512), read_handler);
deadline_timer t(service, boost::posix_time::milliseconds(100));
t.async_wait(&deadline_handler);
service.run();
```

* `io_service` class deals with the operating system, waiting for all asynchronous operations to end, and then calling the completion handler for each such operation.

* `.run()` will always end if there are no more operations to monitor.

```cpp
io_service service_;
tcp::socket sock(service_);
sock.async_connect( ep, connect_handler);
service_.run(); // run will complete after a connection
```

* If you want to make sure `service_.run()` continues to run, you have to assign more work to it. There are two ways of accomplishing this. 
* One way is to assign more work inside `connect_handler` by starting another asynchronous operation.

* The other way is to simulate some work for it, by using the following code snippet:

```cpp
typedef boost::shared_ptr<io_service::work> work_ptr;
work_ptr dummy_work(new io_service::work(service_));

service_.stop()
dummy_work.reset(0); // destroy dummy_work
```
The preceding code will make sure that `service_.run()` never stops unless you either use `service_.stop()` or `dummy_work.reset(0); // destroy dummy_work` .

* `boost::asio`: core classes and functions. `io_service`, `streambuf`.
* `boost::asio::ip`: `address`, `endpoing`, `tcp`, `udp`, `icmp`,

* To deal with IP addresses, Boost.Asio provides following classes
1. `ip::address`  
1. `ip::address_v4`
1. `ip::address_v6`

* Some useful methods
1. `ip::address_v4::broadcast([addr, mask])`
1. `ip::address_v4::any()`
1. `ip::address_v4::loopback()` 
1. `ip_address_v6::loopback()`

* Endpoint is an address with a port number. Each different type of socket has its own `endpoint` class.
1. `ip::tcp::endpoint`
1. `ip::udp::endpoint`
1. `ip::icmp::endpoint`

```cpp
// get address, port and IP protocol from end point
std::cout << ep.address().to_string() << ep.port() << ep.protocol()
```

```cpp
io_service service;
ip::udp::socket sock(service)
sock.set_option(ip::udp::socket::reuse_address(true));

// typedef declaration of different types of sockets
ip::tcp::socket = basic_stream_socket<tcp>
ip::udp::socket = basic_datagram_socket<udp>
ip::icmp::socket = basic_raw_socket<icmp>
```

### Connection related functions
```cpp
assign(protocol,socket)
open(protocol)
bind(endpoint)
connect(endpoint)
async_connect(endpoint)
is_open()
close() // Any asynchronous operations on this socket are canceled immediately 
         // and will complete with error::operation_aborted error code.
shutdown(type_of_shutdown) // disables send or receive operations or both
cancel() // Cancel all asynchronous operations
```

### Read/Write functions

```cpp
async_receive(buffer, [flags,] handler)
async_read_some(buffer,handler)
async_receive_from(buffer, endpoint[, flags], handler)
async_send(buffer [, flags], handler)
async_write_some(buffer, handler)
async_send_to(buffer, endpoint, handler)
receive(buffer [, flags])
read_some(buffer)
receive_from(buffer, endpoint [, flags])
send(buffer [, flags])
write_some(buffer) :
send_to(buffer, endpoint [, flags])
available()

// For asynchronous function, signature of the handler is
void handler(const boost::system::error_code& e, size_t bytes)

// Value of flags are

// only peek at the msg, next call to read the msg will re-read this message
ip::socket_type::socket::message_peek 

// OOB data is data that is flagged as more important than normal data
ip::socket_type::socket::message_out_of_band

ip::socket_type::socket::message_do_no_route

ip::socket_type::socket::message_end_of_record
```

* Example of message peek
```cpp
char buff[1024];
sock.receive(buffer(buff), ip::tcp::socket::message_peek );
memset(buff,1024, 0);
// re-reads what was previously read
sock.receive(buffer(buff) );
```

* Read asynchronously from UDP server socket
```cpp
using namespace boost::asio;
io_service service;
ip::udp::socket sock(service);
boost::asio::ip::udp::endpoint sender_ep;
char buff[512];

void on_read(const boost::system::error_code & err, std::size_t read_bytes) {
  std::cout << "read " << read_bytes << std::endl;
  sock.async_receive_from(buffer(buff), sender_ep, on_read);
}

int main(int argc, char* argv[]) {
  ip::udp::endpoint ep( ip::address::from_string("127.0.0.1"), 8001);
  sock.open(ep.protocol());
  sock.set_option(boost::asio::ip::udp::socket::reuse_address(true));
  sock.bind(ep);
  sock.async_receive_from(buffer(buff,512), sender_ep, on_read);
  service.run();
}
```
* A socket instance cannot be copied, as the Copy constructor and operator = are inaccessible:
```cpp
ip::tcp::socket s1(service), s2(service);
s1 = s2; // compile time error
ip::tcp::socket s3(s1); // compile time error

typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;
socket_ptr sock1(new ip::tcp::socket(service));
socket_ptr sock2(sock1); // ok
socket_ptr sock3;
sock3 = sock1; // ok
```
* When reading from or writing to a socket, you'll need a _buffer_, one that will hold the
incoming data or the outgoing data. The memory in the buffer must outlive the I/O operation; you have to make sure if it is not deallocated or goes out of scope as long as the I/O operation lasts.
This is extremely easy for synchronous operations, but not so straightforward for asynchronous operations.

* Boost.Asio buffer instance needs to meet some requirements, namely
`ConstBufferSequence` or `MutableBufferSequence`.

```cpp
struct shared_buffer {
  boost::shared_array<char> buff;
  int size;
  shared_buffer(size_t size) : buff(new char[size]), size(size) {
  }
  mutable_buffers_1 asio_buff() const {
    return buffer(buff.get(), size);
  }
};
```

* Connect a socket to an endpoint
`connect(socket, begin [, end] [, condition])`
`async_connect(socket, begin [, end] [, condition], handler)`

* helper completion function
```
transfer_at_least(n)
transfer_exactly(n)
transfer_all()
```
* Functions that read until a condition is met
```
async_read_until(stream, stream_buffer, delim, handler)
async_read_until(stream, stream_buffer, completion, handler)
read_until(stream, stream_buffer, delim)
read_until(stream, stream_buffer, completion)
```

* Read data from socket only when data is available.
```
if(sock.available())
  read_data()
```
* To implement the asynchronous listening loop, `io_service` class provides four functions. `run()`, `run_one()`, `poll()` and `poll_one()`.

* `io_service::run()` will run as long as there are pending operations to be executed or
you manually call `io_service::stop()`.

* `io_service::strand()`, will orders asynchronous handler calls.

* `dispatch()` will call the handler before it returns, if the current thread has called `service.run()` , while `post()` always returns immediately.


## Boost.ASIO documentation

* I/O execution context (program's link to operating system's IO service)
  * `boost::asio::io_context` object, 
  * `boost::asio::thread_pool` object, or 
  * `boost::asio::system_context`

* I/O objects
  * tcp socket

* The I/O execution context translates any error resulting from the operation into an object of type `boost::system::error_code`

* The I/O object throws an exception of type `boost::system::system_error` if the operation failed. 

```cpp
// asynchronous operation
socket.async_connect(server_endpoint, your_completion_handler);

// handler is a function or function object with signature
void your_completion_handler(const boost::system::error_code& ec);
```

* The asynchronous support is based on the **Proactor design pattern**

* synchronous-only or **Reactor approach**

* `select`, `epoll` or `kqueue`

* Asynchronous completion handlers will only be called from threads that are currently calling io_context::run().

* A strand is defined as a strictly sequential invocation of event handlers (i.e. no concurrent invocation).

* Buffers
  * `mutable_buffer`
  * `const_buffer`
  * `MutableBufferSequence` and 
  * `ConstBufferSequence`