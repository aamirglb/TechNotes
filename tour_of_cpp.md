# A Tour of C++

* C++ is a statically typed language. That is, the type of every entity (e.g., object, value, name, and expression) must be known to the compiler at its point of use. The type of an object determines the set of operations applicable to it.

* The operator << ("put to") writes its second argument onto its first.

* A function can be a member of a class. For such a member function, the name of its
class is also part of the function type. For example:

    ```cpp
    char& String::operator[](int index);  // type: char& String::(int)
    ```

* Defining multiple functions with the same name is known as _function overloading_ and is one of the essential parts of generic programming.

* The size of a type is implementation defined (i.e., it can vary among different machines) and can be obtained by the `sizeof` operator

* A `0b` prefix indicates a binary (base 2) integer literal (e.g., 0b10101010). A `0x` prefix indicates a hexadecimal (base 16) integer literal (e.g., 0xBAD1234). A `0` prefix indicates an octal (base 8) integer literal (e.g., 0334).

* To make long literals more readable for humans, we can use a single quote (') as a digit separator. For example, π is about 3.14159'26535'89793'23846'26433'83279'50288 or 0x3.243F'6A88'85A3'08D3

* When defining a variable, you don’t need to state its type explicitly when it can be deduced from the initializer:

    ```cpp
    auto b = true; // a bool
    auto ch = 'x'; // a char
    auto i = 123; // an int
    auto d = 1.2; // a double
    auto z = sqrt(y); // z has the type of whatever sqr t(y) retur ns
    auto bb {true}; // bb is a bool
    ```

* Scope of variables
	* local scope
	* class scope
	* namespace scope

* `const` : The value of a const can be calculated at run time. `constexpr`: to be evaluated at compile time, allows placement of data in read-only memory. The value of `constexpr` must be calculated by the compiler

    ```cpp
    constexpr int dmv = 17;

    int var {17};
    const double sqv = sqrt(var);
    ```

* constant expressions are required by language rules e.g., _array bounds_, _case
labels_, _template value arguments_, and _constants declared using constexpr_.

* compile-time evaluation is important for performance.

* There is no "null reference." A reference must refer to a valid object (and implementations assume that it does).

* the >> operator ("get from") is used for input. The type of the right-hand operand of >> determines what input is accepted, and its right-hand operand is the target of the input operation.

* Like a for-statement, an if-statement can introduce a variable and test it. A name declared in a condition is in scope on both branches of the if-statement.

    ```cpp
    void do_something(vector<int>& v)
    {
    	if (auto n = v.siz e(); n!=0) {
    		// ... we get here if n!=0 ...
    	}
    // ...
    }
    ```

* The new operator allocates memory from an area called the _free store_ (also known as _dynamic memory_ and _heap_).

* Objects allocated on the free store are independent of the scope from which they are created and "live" until they are destroyed using the delete operator.

* Unlike an ordinary function, a _constructor_ is guaranteed to be used to initialize objects of its class. Thus, defining a constructor eliminates the problem of uninitialized variables for a class.

* A `union` is a `struct` in which all members are allocated at the same address so that the union occupies only as much space as its largest member.

    ```cpp
    enum Type { ptr, num };
    union Value {
    		Node *p;
    		int i;
    	};

    struct Entry {
    	string name;
    	Type t;
    	Value v;  // use v.p if t == ptr; use v.i if t == num
    };
    ```

* The standard library type, `variant`, can be used to eliminate most direct uses of unions. A `variant` stores a value of one of a set of alternative types

    ```cpp
    struct Entry {
    	string name;
    	variant<Node *, int> v;
    };

    void f(Entry *pe) {
    	if(holds_alternative<int>(pe->v)) {
    		cout << get<int>(pe->v);
    	}
    }
    ```

* The problem with unions is that they're very simple and crude. You don't have a way to know what's the currently used type and what’s more they won’t call destructors of the underlying types.

* The enumerators from a "plain" enum are entered into the same scope as the name
of their enum and implicitly converts to their integer value.

    ```cpp
    using std::swap;       // using declaration
    using namespace std;   // using directive
    ```

* A function that should never throw an exception can be declared `noexcept`.

    ```cpp
    void user(int sz) noexcept
    {
    	Vector v(sz);
    	iota(&v[0], &v[sz], 1); // fill v with 1,2,3,4...
    	// ...
    }
    ```

* In well-designed code try-blocks are rare. Avoid overuse by systematically using the RAII technique.

* Compilers are optimized to make _returning a value_ much cheaper than throwing the same value as an exception.

* terminating the program (by invoking a function like `terminate()`, `exit()`, or `abort()`).

* do not believe the myth that exception handling is slow; it is often faster than correct handling of complex or rare error conditions, and of repeated tests of error codes.

* The standard library offers the debug macro, `assert()`, to assert that a condition must hold at run time.

* The default behavior for both argument passing and value return is "copy", but some copies can implicitly be optimized to moves.

* if the class representation changes in any significant way, a user must recompile. This is the price to pay for having concrete types behave exactly like built-in types.

* Functions defined in a class are inlined by default. It is possible to explicitly request inlining by preceding a function declaration with the keyword inline.

* A _container_ is an object holding a collection of elements.

* A `static_cast` does not check the value it is converting; the programmer is trusted to use it correctly.

* Other casts are `reinterpret_cast` for **treating an object as simply a sequence of bytes** and `const_cast` for "casting away const."

* The word `virtual` means "may be redefined later in a class derived from this one."

* A class that provides the interface to a variety of other classes is often called a _polymorphic type_.

* We can ask "is this Shape a kind of Smiley?"" using the `dynamic_cast` operator:

    ```cpp
    Shape∗ ps {read_shape(cin)};
    if (Smiley∗ p = dynamic_cast<Smiley∗>(ps)) { // ... does ps point to a Smiley? ...
    	// ... a Smiley; use it
    }
    else {
    	// ... not a Smiley, try something else ...
    }
    ```

* If at run time the object pointed to by the argument of `dynamic_cast` is not of the expected type (here, Smiley) or a class derived from the expected type, `dynamic_cast` returns `nullptr`.

* Assigning the result of new to a ‘‘naked pointer’’ is asking for
trouble.

* If a class X has a destructor that performs a nontrivial task, such as **free-store deallocation** or **lock release**, the class is likely to need the full complement of functions:

    ```cpp
    class X {
    public:
    	X(Sometype);            // "ordinary constructor": create an object
    	X();                    // default constructor
    	X(const X&);            // copy constructor
    	X(X&&);                 // move constructor
    	X& operator=(const X&); // copy assignment: clean up target and copy
    	X& operator=(X&&);      // move assignment: clean up target and move
    	˜X();                   // destructor: clean up
    	// ...
    };
    ```

* When a class has a pointer member, it is usually a good idea to be explicit about copy and move operations.

* `=delete` can be used to suppress any function, not just essential member functions

* A constructor taking a single argument defines a conversion from its argument type.

    ```cpp
    complex z1 = 3.14; // z1 becomes {3.14,0.0}
    complex z2 = z1∗2; // z2 becomes z1*{2.0,0} == {6.28,0.0}
    ```

* Copying of an object of a class is defined by two members: a _copy constructor_ and a _copy assignment_.

    ```cpp
    Vector(const Vector& a);             // copy constr uctor
    Vector& operator=(const Vector& a);  // copy assignment
    ```

* The name `this` is predefined in a member function and points to the object for which the member function is called.

    ```cpp
    class Vector {
    	// ...
    	Vector(const Vector& a);            // copy constructor
    	Vector& operator=(const Vector& a); // copy assignment

    	Vector(Vector&& a);                 // move constructor, no const argument
    	Vector& operator=(Vector&& a);      // move assignment, no const argument
    };
    ```

* The && means "rvalue reference" and is a reference to which we can bind an rvalue.

* The standard-library function `move()` doesn't actually move anything. Instead, it returns a reference to its argument from which we may move – _an rvalue reference_; it is a kind of cast.

* To give _identical treatment to both operands_ of a binary operator, such as ==, it is best defined as a **free-standing function** in the namespace of its class.

* The standard-library `unordered_map<K,V>` is a hash table with `K` as the key type and `V` as the value type. To use a type `X` as a key, we must define `hash<X>`. The standard library does that for us for common types, such as `std::string`.

* A _template_ is a class or a function that we parameterize with a set of types or values.

* Templates are a compile-time mechanism, so their use incurs no run-time overhead compared to hand-crafted code.

* A template argument for which a **concept** is specified is called a _constrained argument_ and a template for which an argument is constrained is called a _constrained
template_.

* In addition to **type arguments**, a template can take **value arguments**. A template value argument must be a constant expression.

    ```cpp
    template <typename T, int N>
    struct Buffer {
    	using value_type = T;
    	constexpr int size() { return N; }
    	T[N];
    };
    ```

* A function template can be a member function, but not a vir tual member.

* The function called `operator()` implements the "function call," "call," or "application" operator `()`.

* Function objects used to specify the meaning of key operations of a general algorithm are often referred to as **policy objects**.

* a lambda with an `auto` parameter makes the lambda a template, or a generic lambda.

* every standard-library container provides `value_type` as the name of its value type

* There is no separate compilation of templates: #include template definitions in every translation unit that uses them.

* Most template arguments must meet specific requirements for the template to compile properly and for the generated code to work properly. That is, most templates must be constrained templates.

* The type-name introducer `typename` is the least constraining, requiring only that the argument be a type.


| #  |  header  filename |  example |
|----|-------------------|----------|
| 1  | `<algorithm>`     | copy(), find(), sort() |
| 2  | `<array>`         | array |
| 3  | `<chrono>`        | duration, time_point |
| 4  | `<cmath>`         | sqrt(), pow() |
| 5  | `<complex>`       | complex, sqrt(), pow() |
| 6  |  `<filesystem>`   | path |
| 7  | `<forward_list>`  | forward_list |
| 8  | `<fstream>`       | fstream, ifstream, ofstream |
| 9  | `<future>`        | future, promise |
| 10 | `<ios>`           | hex, dec, scientific, fixed, defaultfloat |
| 11 | `<iostream>`      | istream, ostream, cin, cout |
| 12 | `<map>`           | map, multimap |
| 13 | `<memory>`        | unique_ptr, shared_ptr, allocator |
| 14 | `<random>`        | default_random_engine, normal_distribution |
| 15 | `<regex>`         | regex, smatch |
| 16 | `<string>`        | string, basic_string |
| 17 | `<set>`           | set, multiset |
| 18 | `<sstream>`       | istringstream, ostringstream |
| 19 | `<stdexcept>`     | length_error, out_of_range, runtime_error |
| 20 | `<thread>`        | thread |
| 21 | `<unordered_map>` | unordered_map, unordered_multimap |
| 22 | `<utility>`       | move(), swap(), pair |
| 23 | `<variant>`       | variant |
| 24 | `<vector>`        | vector |


* The standard string has a move constructor, so returning even long strings by value is efficient.

* These days, `string` is usually implemented using the _short-string optimization_. That is, short string values are kept in the string object itself and only longer strings are placed on free store.

* `string_view` is basically a (pointer,length) pair denoting a sequence of characters.

* In `<reg ex>`, the standard library provides support for regular expressions:
    * `regex_match()`: Match a regular expression against a string (of known size)
    * `regex_search()`: Search for a string that matches a regular expression in an (arbitrarily long) stream of data
    * `regex_replace()`: Search for strings that match a regular expression in an (arbitrarily long) stream of data and replace them
    * `regex_iterator`: Iterate over matches and submatches
    * `regex_token_iterator`: Iterate over non-matches

* The regular expression syntax and semantics are designed so that regular expressions can be compiled into state machines for efficient execution. The regex type performs this compilation at run time.

* A suffix `?` after any of the repetition notations `(?, ∗, +, and { })` makes the pattern matcher **"lazy"** or **"non-greedy."** That is, when looking for a pattern, it will look for the shortest match rather than the longest. By default, the pattern matcher always looks for the longest match; this is known as
the **Max Munch rule**.

* The I/O stream classes all have destructors that free all resources owned (such as buffers and file handles).

* You can read a whole line using the `getline()` function: `std::getline(std::cin, line);`

* For a `list`, `insert(p, elem)` inserts an element with a copy of the value `elem` before the element pointed to by `p`. Here, `p` may be an iterator pointing one-beyond-the-end of the list.

* The standard library offers a **balanced binary search tree** (usually, a **red-black tree**) called **map**.

* The cost of a `map` lookup is `O(log(n))` where `n` is the number of elements in the `map`. However, in many cases, we can do better by using a hashed lookup rather than a comparison using an ordering function, such as <.

    ```cpp
    struct Record {
        string name;
        int product_code;
        // ...
    };

    struct Rhash { // a hash function for Record
        size_t operator()(const Record& r) const
        {
            return hash<string>()(r.name) ˆ hash<int>()(r.product_code);
        }
    };

    unordered_set<Record,Rhash> my_set; // set of Records using Rhash for lookup
    ```

* _Designing good hash functions is an art_ and sometimes requires knowledge of the data to which it will be applied. Creating a new hash function by combining existing hash functions using exclusive-or (ˆ) is simple and often very effective.

* An empty `forward_list` occupies just one word, whereas an empty `vector` occupy three.

* Use `reserve()` to avoid invalidating pointers and iterators to elements.

* An iterator is an object of some type.

* A predicate should not modify the elements to which it is applied.

* `std::move()` doesn't move anything. Instead, it casts its argument to an rvalue reference, thereby saying that its argument will not be used again and therefore may be moved.

    ```cpp
    template <typename T>
    void swap(T& a, T& b)
    {
        T tmp {move(a)};   // the T constructor sees an rvalue and moves
        a = move(b);       // the T assignment sees an rvalue and moves
        b = move(tmp);     // the T assignment sees an rvalue and moves
    }
    ```

* an `array` can be allocated with its elements on the stack, in an object, or in static storage.

* If we try to access an `optional` that does not hold a value, the result is _undefined_; an exception is _not_ thrown. Thus, `optional` is not guaranteed type safe.

* Use `std::mem_fn()` to make a function object from a member function.

* The standard-library `function` is a type that can hold any object you can invoke using the call operator `()`. That is, an object of type `function` is a function object.

* A random number generator consists of two parts:
    * An engine that produces a sequence of random or pseudo-random values
    * A distribution that maps those values into a mathematical distribution in a range

* The standard library directly supports concurrent execution of multiple threads in a single
address space.

* We call a computation that can potentially be executed concurrently with other computations a _task_.
A _thread_ is the system-level representation of a _task_ in a program.

* A _task_ is a function or a function object.

* To "join" a thread means to "wait for the thread to terminate."

* This `scoped_lock` will proceed only after acquiring all its mutexes arguments and will never block
("go to sleep") while holding a mutex.

* The basic `mutex` allows one thread at a time to access data. One of the most common ways of
sharing data is among many readers and a single writer. This **"reader-writer lock" idiom** is supported
be `shared_mutex`. A reader will acquire the mutex "shared" so that other readers can still
gain access, whereas a writer will demand exclusive access.

    ```cpp
    shared_mutex mx; // a mutex that can be shared
    void reader()
    {
        shared_lock lck {mx}; // willing to share access with other readers
        // ... read ...
    }

    void writer()
    {
        unique_lock lck {mx}; // needs exclusive (unique) access
        // ... write ...
    }
    ```

* The basic support for communicating using external events is provided by `condition_variables`. A `condition_variable` is a mechanism allowing one thread to wait for another. In particular, it allows a thread to wait for some condition (often called an event) to occur as the result of work done by other threads.