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