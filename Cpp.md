# C++ Concurrency in Action

* With C++11 it is possible to write multithreaded C++ programs without relying on platform-specific extensions and enabled you to write portable multithreaded code with guaranteed behavior.

* Technical Specifications for **Concurrency extensions** and **Parallelism** to be incorporated into C++17.

* Concurrency is about two or more separate activities happening at the same time.

* Separate processes can pass messages to each other through all the normal inter-
communication channels (signals, sockets, files, pipes, and so on).

* It is easier to write safe concurrent code with processes rather than threads.

* Threads are much like light-weight processes: each thread runs independently of the others, and each may run a different sequence of instructions. But all threads in a process _share the same address space_, and most of the data can be accessed directly from all threads, global variables remain global, and pointers or references to objects or data can be passed around among threads.

* Application frameworks, such as MFC, and general-purpose C++ libraries, such as Boost and ACE.

* C++ Standard Library was extended to include classes for managing threads, protecting shared data, synchronizing operations between threads, and low-level atomic operations.

```cpp
#include <thread>
void do_some_work();
std::thread t(do_some_work);

struct background_task {
    void operator()() const {
        do_work();
        do_more_work();
    }
}
background_task f;
std::thread t2(f); // functor is copied into storge belonging to thread
```

* `std::thread` works with any callable type.

* _**C++ most vexing parse**_, passing a temporary rather than a named variable

```cpp
std::thread my_thread(background_task()); // WRONG !!
// Declare my_thread function taking single parameter and return thread object

std::thread my_thread( (background_task()) ); // extra set of parentheses
std::thread my_thread{background_task()};
```

* `std::thread` destructor calls `std::terminate()` if thread terminate without join.

* `join()` is a simple and brute-force technique. For more fine-grained control use _condition variable_ and _futures_.

* The call to `join()` is liable to be skipped if an exception is thrown after the thread has been started but before the call to `join()`.

* Thread guard using Resource Acquisition Is Initialization (RAII) idiom

```cpp
class thread_guard {
    std::thread& t;
public:
    explicit thread_guard(std::thread& t_) : t{t_} {}
    ~thread_guard() { 
        if(t.joinable()) {
            t.join(); // can be called only once for a given thread
        }
    }
    thread_guard(const thread_gurad&) = delete;
    thread_guard& operator=(const thread_guard&) = delete;
};

std::thread t(func);
thread_guard g(t);
```
* If a thread becomes detached, it isn’t possible to obtain a std::thread object that references it, so it can no longer be joined. Ownership and control of detached threads are passed over to C++ Runtime Library.

```cpp
char buffer[1024];
sprintf(buffer, "%i", some_param);
```

```cpp
struct X {
    void do_lengthy_work();
};
X my_x;
// Supply object pointer as first argument for class member functions
std::thread t(&X::do_lengthy_work, &my_x); 
```

* `std::unique_ptr`, provides automatic memory management for dynamically
allocated objects. The _move constructor_ and _move assignment_ operator allow the ownership of an object to be transferred around between `std::unique_ptr` instances 

* This moving of values allows objects of this type to be accepted as function
parameters or returned from functions. Where the source object is _temporary_, the
move is automatic, but where the source is a _named value_, the transfer must be
requested directly by invoking std::move().

* It is not possible to just drop a thread by assigning a new value to the std::thread object that manages it.

```cpp
std::thread t1(some_function);
std::thread t2(some_other_function);
t1 = std::move(t2); // Program will be terminated
```

```cpp
// Ownership is transferred
std::thread f() { 
    return std::thread(some_function);
 }

 void f(std::thread t);
```

* `std::thread::hardware_concurrency()` function returns an indication of the number of threads that can truly run concurrently for a given execution of a program.

* Thread identifiers are of type `std::thread::id` and can be retrieved in two:  ways. `get_id()` member function or `std::this_thread:: get_id()`.

* _invariants_ (never changing)

* One of the most common cause of bugs in concurrent code is a _race condition_. A race condition is anything where the outcome depends on the relative ordering of execution of operations on tow or more threads.

* A great deal of complexity in writing software that uses concurrency comes from avoiding problematic race conditions.

* The most basic mechanism for protecting shared data is to use synchronization primitive called _mutex_ (mutual exclusion).


* The Thread Library ensures that once one thread has locked a specific mutex, all other threads that try to lock the same mutex have to wait until the thread that successfully locked the mutex unlocks it.

* Mutexes come with their own problems in the form of a _deadlock_.

# C++17

### Structure Binding

```cpp
struct MyStruct {
int i = 0;
std::string s;
};
MyStruct ms;

// structured bindings
auto [u,v] = ms;
```
### if and switch with Initialization

```cpp
if (status s = check(); s != status::success) {
    return s;
}

// s is valid for whole if statement
```

```cpp
using namespace std::filesystem;
...
switch (path p(name); status(p).type()) {
```

One strength of C++ is its ability to support the development of header-only libraries. However, up
to C++17, this was only possible if no global variables/objects were needed or provided by such a
library. 

Since C++17 you can define a variable/object in a header file as inline and if this definition is
used by multiple translation units, they all refer to the same unique object

According to the **one definition rule** (ODR), a variable or entity had to be defined in exactly one
translation unit.

variable templates (since C++14):
```cpp
template<typename T = std::string>
T myGlobalObject = "initial value";
```

```cpp
class MyClass {
static inline std::string name = ""; // OK since C++17
...
};
inline MyClass myGlobalObj;
// OK even if included/defined by multiple CPP files
```