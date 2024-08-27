# Functional Programming

* FP provides
    * Power
    * Safety
    * Clarity

* Changing the way you think is the hard part; once that's
achieved, learning the syntax of any particular language is relatively easy.

* `System.Linq` is a **functional library**

* `System.Collections.Immutable` `System.Interactive` and `System.Reactive`

* `language-ext`, is a library written by Paul Louth to improve the C# developer's experience when coding functionally.

* functional programming (FP)? At a high level, is a
programming style that emphasizes functions while avoiding state mutation.

* Two folds: Functions as first-class values and Avoiding state mutation

* `Select` (an extension method on IEnumerable)

* Prior to C# 10, you need to explicitly declare delegate type
Func<int, int> triple = x => x * 3;  // Before C# 10
var triple = (int x) => x * 3;  // C# 10

* Purely functional languages don't allow in-place updates at all

```c#
var triple = (int x) => x * 3;
var range = Enumerable.Range(1, 10);
var triples = range.Select(triple);
WriteLine(triples);

var isOdd = (int x) => x % 2 == 1;
var sorted = range.OrderBy(x => x);
var filtered = range.Where(isOdd);
```

* The difficult art of structuring a complex
application relies on the following principles
* Modularity - Software should be composed of discrete, reusable components
* Separation of concerns - Each component should only do one thing
* Layering - High-level components can depend on low-level components but not vice versa
* Loose coupling - A component shouldn't know about the internal details of the components it depends on; therefore changes to a component shouldn't affect components that depends on it.

https://github.com/papers-we-love/papers-we-love/

* introduction of records in C# 9. records allow you to define custom immutable types
without any boilerplate

* LINQ is indeed a functional library

* LINQ offers implementations for many common operations on lists, mapping, sorting, and filtering

* **Mapping** - Given a sequence and a function, mapping yields a new sequence
whose elements are obtained by applying the given function to each element in
the original sequence (in LINQ, this is done with the `Select` method)

* **Filtering** - Given a sequence and a predicate, filtering yields a new sequence
including all the elements from the original sequence that satisfy the predicate
(in LINQ, this is done with `Where`)

* **Sorting** - Given a sequence and a key-selector function, sorting yields a
sequence where the elements of the original sequence are ordered by the key (in
LINQ, this is done with `OrderBy` and `OrderByDescending`)

* `using static System.Math`: using static enables unqualified access to the static members of `System.Math`, like `PI` and `Pow`

```c#
public record Circle(double Radius) {
	public double Circumference => PI * 2 * Radius;  // An expression-bodied property
	public double Area { get {
        double Square(double d) => Pow(d, 2);  // local method
        return PI * Square(Radius); }}
}
```

* a functional library in C# consists mainly of static methods

* C# 7 introduced new lightweight syntax for creating and consuming `tuples`

* A record without a body ends with a semicolon.

```c#
// a record without a body ends with a semicolon
record Product(string Name, decimal Price, bool IsFood);

record Order(Product Product, int Quantity) {
    public decimal NetPrice => Product.Price * Quantity;
}
```

* Notice how with a single line, you can define the Product type! The compiler
generates a constructor, property getters, and several convenience methods such
as Equals, GetHashCode, and ToString for you

* Records in C# 9 are _reference types_, but C# 10 allows you to use
record syntax to define value types by simply writing _record struct_ rather
than just record. Somewhat surprisingly, _record structs_ are **mutable**, and
you have to declare your struct as _readonly record struct_ if you want it to be
**immutable**.

* FP differs from object-oriented programming (OOP) by focusing on functions
rather than objects, and on data transformations rather than state mutations.

up the ante

* higher-order functions (HOFs) raise the level of abstraction in our programs,
allowing us to do more with less code.

* Delegates are type-safe function pointers. Type-safe here means that a delegate
is strongly typed.

* `Func<R>` - Represents a function that takes no arguments and returns a result of type R
* `Func<T1,R>` - Represents a function that takes an argument of type T1 and
returns a result of type R

* There's a similar delegate family to represent **actions**, _functions that have no return value_, such as void methods:
* `Action` - Represents an action with no input arguments
* `Action<T1>` - Represents an action with an input argument of type T1
* `Action<T1,T2>` - and so on - Represent an action with several input arguments

* Arity is a funny word that refers to the number of arguments that a function accepts. For instance
* A **nullary** function takes no arguments.
* A **unary** function takes one argument.
* A **binary** function takes two arguments.
* A **ternary** function takes three arguments.

* Lambda expressions, called lambdas for short, are used to declare a function
inline.

* The fact that functions can be represented with dictionaries also makes it
possible to optimize computationally expensive functions by storing their
computed results in a dictionary instead of recomputing them every time. This
technique is called memoization.

* higher-order functions (HOFs) are functions that take other functions as inputs or return a function as
output or both.

* The code uses `Dapper` (https://github.com/StackExchange/dapper-dot-net), a thin layer on top of
ADO.NET, allowing you to interact with the database through a simple API: 
Query,
Execute