# Boost C++ Library

C++ GCC get all warnings: gcc -Q --help=warning

* Most of Boost libraries consist solely of header files that can be used directly, some of the libraries require compilation.

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
```
The preceding code will make sure that `service_.run()` never stops unless you either use `service_.stop()` or `dummy_work.reset(0); // destroy dummy_work` .