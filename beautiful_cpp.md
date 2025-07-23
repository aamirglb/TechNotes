Beautiful C++

30 core guidelines
1. Write in ISO Standard C++
2. Where there is a choice, prefer default arguments over overloading
3. Don't define a default constructor that only initializes data members; use in-class member initalizers instead
4. Avoid trivial getters and setters
5. Declare one name (only) per declaration

* ISO Standard C++ has a very small library compared to languages like C# and Java.

* Stability over decades is a feature.

* API design is a valuable skill. Naming is hard.

* Overload resolution is a tricky beast to master. Nearly two percent of the C++20 standard is devoted to defining how overload resolution works

* There are three types of implicit conversion sequence:
    * standard conversion sequence 
        * exact match, promotion and conversion. These three ranks are C concepts and are unavoidable if compatibility with C is to be maintained.
    * user-defined conversion sequence
        * nonexplicit constructor, nonexplicit conversion operator
    * ellipsis conversion sequence

* You should make an interface easy to use correctly and hard to use incorrectly.

* The thread-local duration class arrived in C++11 and behaves in much the same way as static duration, except there is a perthread instance of the object rather than a per-program instance.

* If no constructor is defined, then the members of the class are default-initialized. If there are any members of _built-in_ type, then they are _not initialized_ by default.

* Determinism is your ally when it comes to debugging, so ensure determinism with deterministic construction of all objects and initialize every item of member data

```cpp
piano::piano()
{
    number_of_keys = 88;
    mechanical = true;
    manufacturer = "Yamaha";
}
```

* This is **function-body initialization**. However, it is _suboptimal_. Prior to the function body being executed, the members of the class were _default-initialized_. This meant that the `std::string` default constructor was invoked, and then the assignment operator was invoked with a `char const*`. In fact, this is overwriting, not initializing.

* You should prefer initializing in the initializer list to initializing in the function body

```cpp
piano::piano()
    : number_of_keys(88)
    , mechanical(true)
    , manufacturer("Yamaha")
{}
```

* There is a third place you can provide default definitions that is even closer to the action: in the definition of the class itself.

```cpp
class piano
{
public:
    // piano(); // no longer needed
private:
    int number_of_keys = 88;
    bool mechanical = true;
    std::string manufacturer = "Yamaha";
};
```

* There is a cost that cannot be ignored, though, which is that these default values are exposed in a class declaration that is likely to be a dependency of other source files. Making a change to any of these values may require _recompilation of an unknown number of files_.

* A **class invariant** is a condition that must hold for all valid instances of a class. It is established at construction and maintained between calls to public member functions.

* A **pure function** is one that does not refer to _state outside of its scope_. This makes them _parallelizable_, easy to reason about, more amenable to optimization, and likely to be short and simple.

# C++ Brain Teasers

* **Undefined behavior** is the term used when something bad happens during the execution of a program, which the compiler is unable to (not required to) detect. UB allows C++ compilers to **optimize aggressively**.

    * accessing element past the end of the array
    * signed integer overflow

```c++
std::numeric_limits<int>::max() + 1; // signed integer overflow, undefined behavior
```

* **Unspecified and Implementation-Defined behavior**: The C++ standard doesn't specify everything strictly; it leaves some freedom to the implementation.
    * The specific size of the integer types
    * The order of evaluation of function arguments
    * The order of initalization of global variables

* _All class members are initialized before we get to the constructor body_. The members will be default-initialized, if they are not initialized using initialization list.

* When we're calling a function with multiple overloads, the compiler uses a process called _overload resolution_ to figure out which one is the best fit. All the overloads where all arguments can be successfully converted are added to a set of _viable functions_. Then the compiler needs to figure out which overload to select from this set. If an overload has a better conversion for at least one argument and not a worse one for any of the other arguments, this overload is deemed to be the _best viable function_ and is selected by overload resolution.

* The string "hello world" is not a `std::string` but a simple string literal. String literals are plain C-style arrays of `chars` which get baked into the binary by the linker.

* `ponter to cv T` (_cv_ means `const`, `volatile`, `const volatile` or none of these)

* A standard conversino sequence is always _better_ than a user-defined conversion sequence.

```
const char[12] -> const char * -> const void * // standard conversion
const char[12] -> const char * -> std::string  // user defined conversion
```

* Different sanitizers exist for different purposes, but all monitor the code at runtime in various ways to detect problems that can't be detected at compile time.

* Clang compiler supports the following sanitizers:
    * Address Sanitizer (ASan) -fsanitize=address: use-after-free, heap/stack/global buffer overflows, memory leaks
    * Leak Sanitizer (LSan) -fsanitize=leak 
    * Memory Sanitizer (MSan) -fsanitize=memory (require Clang + libc++, special runtime; not supported on Windows or macOS)
    * Thread Sanitizer (TSan) -fsanitize=thread: data races and race conditions
    * Undefined Behavior Sanitizer (UBSan) -fsanitize=undefined
    * Control Flow Integrity (CFI) -fsanitizer=cfi: detects indirect call violations (eg: type confusion in virtual calls)

* A sanitizer can only detect an issue if that issue actually occurs at runtime.

* A common technique for dynamic polymorphism is using _virtual functions_.

* When you call a virtual function on a base class pointer pointing to an object of derived class, the object's dynamic type is used and the overrideen function from derived class is called.

* If base class destructor is non-virtual, deleting a derived class object through base class pointer is an undefined behavior.

* C++ always initializes members in the order they are declared in the class, not in the order they are listed in the constructor's initializer list.

* The C++ standard doesn't require dynamic initialization to happen before `main`, it merely allows it. However, the standard require dynamic initialization of global bariables to happen before any function defined in the same translation unit (TU) are called.

* A translation unit (TU) is just a single .cpp file after all the #include files have been included.

* Unlike global variables, local static variables are not initialized when the program starts but rather the first time control passes through their declarations.

* Global variables in different translation units can be initialized in any order.

* This problem of _unknown initialization order_ between globals in different translation units is often referred to as **Static Initialization Order Fiasco**.

* Instead of global variables, use functions with local static variables to control lifetimes.

* `std::move` turns an _lvalue_ into an _rvalue_ and is the way we tell the type system that "this is fine, you can go ahead and move from this lvalue; I won't be using it anymore."

* Unnamed return value optimization (URVO) and Named return value optimization (NRVO)

* A functino call is a _prvalue_ (pure rvalue)

* One popular ABI is the **Itanium C++ ABI**, used on Linux. GCC and Clang both conform to this ABI, so you can freely call a function compiled with one from a function compiled by the other.

* The `T` in `template <typename T>` is called the _template parameter_. The goal of template argument deduction is to find `T`.

* `char` type is a bit special in that the implementation can choose whether to back it by signed char or `unsigned char`. In either case, `char` is a distinct type. So `char`, `signed char` and `unsigned char` are actually three different types and whether or not a plain `char` is signed is implementation defined.

* A data race results in a undefined behavior.

* Whether or not `std::atomic<char>` is lock-free is implementation defined, but it typically is.

* Single parameter constructor not marked as `explicit` are known as _converting constructors_.

* When a virtual function is called from a constructor or destructor, the function called is the one in that particular class and not one overriding it in a more-derived class.

* **Curiously Recurring Template Pattern (CRTP) idiom:** The idea is to make the base class a template and then use the derived class as a template parameter for its own base class. Now the base class knows, statically even, which derived class is being instantiated simply by looking at its template parameter.

* The **CRTP** is a C++ idiom in which a class `Derived` inherits from a base class that is templated on the derived class itself. It looks "curious" because a class appears to refer to itself as a template parameter before it is fully defined.

```c++
class Derived : public Base<Derived> {};
```

```c++
struct GameObject {
    virtual void render() const = 0;
};

template <typename Derived>
struct LoggingGameObject : public GameObject {
    LoggingGameObject() { std::cout << "Created a " << Derived::typeName << '\n'; }
    void render() const override { std::cout << "Rendered a " << Derived::typeName << '\n'; }
};
```

