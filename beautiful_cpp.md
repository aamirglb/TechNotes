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