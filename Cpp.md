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