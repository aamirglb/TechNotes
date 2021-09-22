# The Rust Programming Language

* `rustup`, is a command line tool for managing Rust versions and associated tools.

* `rustup doc` to open the local documentation in your browser.

* Rust files always end with the `.rs` extension.

```rust
fn main() {
}
```

* println! calls a Rust macro. If it called a function instead, it
would be entered as println (without the ! ).

* Rust is an _ahead-of-time compiled language_, meaning you can
compile a program and give the executable to someone else, and they can
run it even without having Rust installed.

* **Cargo** is Rust’s build system and package manager.

* Cargo handles a lot of tasks
for you, such as building your code, downloading the libraries your code
depends on, and building those libraries. (We call libraries your code needs
dependencies.)

```shell
$ cargo new hello_cargo
$ cd hello_cargo

$ cargo build
$ cargo run

$ cargo check # to check if the code compiles, doesn't produce executable

$ cargo build --release
```

* `cargo.toml` file is in the **TOML (Tom’s Obvious, Minimal Language)** format, which is Cargo’s configuration format.

* In Rust, packages of code are referred to as **crates**.

* Cargo expects your source files to live inside the src directory. The top-
level project directory is just for README files, license information, config-
uration files, and anything else not related to your code.

* Running
cargo build for the first time also causes Cargo to create a new file at the top
level: Cargo.lock. This file keeps track of the exact versions of dependencies
in your project.

* To obtain user input and then print the result as output, we need to bring
the io (input/output) library into scope. The io library comes from the
standard library (which is known as std )

* By default, Rust brings only a few types into the scope of every program
in the prelude.

* let statement is used to create a variable. In Rust, variables are **immutable** by default.

* use `mut` before the variable name to make a variable mutable:

```rust
let foo = 5; // immutable
let mut bar = 5; // mutable
```

* `String::new` function returns a new instance of a String. String
is a string type provided by the standard library that is a growable, UTF-8
encoded bit of text.

* The :: syntax in the ::new line indicates that new is an _associated function_
of the String type. An associated function is implemented on a type, in this
case String , rather than on a particular instance of a String . Some languages
call this a _static method_.

* Rust
has a number of types named `Result` in its standard library: a generic `Result`
as well as specific versions for submodules, such as `io::Result` .

* The number 0.3.14 is actually shorthand for ^0.3.14 , which means “any ver-
sion that has a public API compatible with version 0.3.14.”

* https://crates.io/. Crates.io is where people in the Rust ecosystem post their open
source Rust projects for others to use.

* Crates are installed globally for the current user, not per project. Currently, they are stored in <user directory>/.cargo/registry.

* `cargo update` will ignore the `Cargo.lock` file and figure out all the latest versions that fit your specifications in Cargo.toml. If that works, Cargo will write those versions to the `Cargo.lock` file.

* The `Rng` trait defines methods
that random number generators implement, and this trait must be in scope
for us to use those methods.

* **Monty Hall Problem**

* Another neat feature of Cargo is that you can run the cargo doc --open command,
which will build documentation provided by all of your dependencies locally and
open it in your browser.

* Rust has
a strong, static type system. However, it also has type inference. When we
wrote let mut guess = String::new() , Rust was able to infer that guess should
be a String and didn’t make us write the type.

* Rust allows us to shadow
the previous value of guess with a new one. This feature is often used in
situations in which you want to convert a value from one type to another
type.

* The `loop` keyword creates an infinite loop.

* Switching from an expect call to a match expression is how you generally
move from crashing on an error to handling the error.

* In Err(_) pattern underscore, _ , is a catchall value

* In Rust, the compiler guarantees that when you state that a value won’t
change, it really won’t change.

* you aren’t allowed to use `mut` with `constants`. Constants aren’t just
immutable by default—they’re always immutable.
You declare constants using the `const` keyword instead of the `let` keyword,
and the type of the value must be annotated.

* We can shadow a variable by using the same variable’s name and
repeating the use of the let keyword

* Rust has four primary scalar types: **integers**, **floating-point numbers**, **Booleans**, and **characters**.

Integer Types in Rust

| Length  | Signed | Unsigned |
|---------|--------|----------|
| 8-bit   | i8     | u8  |
| 16-bit  | i16    | u16 |
| 32-bit  | i32    | u32 |
| 64-bit  | i64    | u64 |
| 128-bit | i128   | u128 |
| arch    | isize  | usize |

* the isize and usize types depend on the kind of computer
your program is running on: 64 bits if you’re on a 64-bit architecture and
32 bits if you’re on a 32-bit architecture.

* all number literals except the byte literal allow a type suffix, such as 57u8 ,
and _ as a visual separator, such as 1_000 .

* Rust uses the term _panicking_ when a program exits with an error;

* Rust’s floating-point types are `f32` and `f64` ,
which are 32 bits and 64 bits in size, respectively. The default type is `f64`
because on modern CPUs it’s roughly the same speed as f32 but is capable
of more precision.

* a Boolean type in Rust has two
possible values: true and false . Booleans are one byte in size. The Boolean
type in Rust is specified using bool .

* Rust’s
char type is the language’s most primitive alphabetic type. Rust’s char type is four bytes in size and represents a Unicode Scalar
Value.

* Compound types can group multiple values into one type. Rust has two
primitive compound types: _tuples_ and _arrays_.

* We create a tuple by writing a comma-separated list of values inside
parentheses.

```rust
let tup: (i32, f64, u8) = (500, 6.4, 1);
```

* In addition to destructuring through pattern matching, we can access
a tuple element directly by using a period ( . ) followed by the index of the
value we want to access.

* Unlike a
tuple, every element of an array must have the same type. Arrays in Rust are
different from arrays in some other languages because arrays in Rust have a
fixed length, like tuples.

* Arrays are useful when you want your data allocated on the stack rather
than the heap

```rust
// element type and number of elements
let a: [i32; 5] = [1, 2, 3, 4, 5];
```

* In function signatures, you must declare the type of each parameter.
This is a deliberate decision in Rust’s design: requiring type annotations
in function definitions means the compiler almost never needs you to use
them elsewhere in the code to figure out what you mean.

* _Statements_ are
instructions that perform some action and do not return a value. _Expressions_
evaluate to a resulting value. Let’s look at some examples.

* In Rust,
the return value of the function is synonymous with the value of the final
expression in the block of the body of a function.

* Blocks of code associated with the conditions in if expres-
sions are sometimes called arms, just like the arms in match expressions.
the condition in this code _must_ be a bool .

* you can add the value you want returned after the break expression you use
to stop the loop; that value will be returned out of the loop so you can use
it

* The `Range`, type provided by the standard library that generates all numbers in sequence starting from one num-
ber and ending before another number.

* **Ownership** is Rust’s most unique feature,
and it enables Rust to make memory safety
guarantees without needing a garbage col-
lector.

* memory is managed through a system of ownership with
a set of rules that the compiler checks at compile time.

* Ownership Rules
    * Each value in Rust has a variable that’s called its owner.
    * There can be only one owner at a time.
    * When the owner goes out of scope, the value will be dropped.

* The double colon ( :: ) is an operator that allows us to namespace this
particular from function under the String type

* When a variable
goes out of scope, Rust calls a special function for us. This function is
called `drop` , and it’s where the author of String can put the code to return
the memory. Rust calls drop automatically at the closing curly bracket.

```rust
let s1 = String::from("hello");
let s2 = s1;
println!("{}, world!", s1); // this won't work
```

* If we do want to deeply copy the heap data of the String , not just the stack
data, we can use a common method called `clone`.

* If a type has the Copy trait, an older variable is still usable
after assignment. Rust won’t let us annotate a type with the Copy trait if the
type, or any of its parts, has implemented the Drop trait.

* We call having references as function parameters _borrowing_.

* mutable references have one big restriction: you can have only _one mutable reference_ to a particular piece of data in a particular scope. 

```rust
let mut s = String::from("hello");
let r1 = &mut s;
let r2 = &mut s;   // Error
```

* The benefit of having this restriction is that Rust can prevent _data races_
at compile time. A _data race_ is similar to a race condition and happens when
these three behaviors occur:
    * Two or more pointers access the same data at the same time.
    * At least one of the pointers is being used to write to the data.
    * There’s no mechanism being used to synchronize access to the data.

* A string slice is a reference to part of a `String` , and it looks like this:
```rust
let s = String::from("hello world");
let hello = &s[0..5];
let world = &s[6..11];
```

* To define a `struct`, we enter the keyword struct and name the entire struct.

```rust
struct User {
    username: String,
    email: String,
    sign_in_count: u64,
    active: bool,
}

let user1 = User {
                email: String::from("someone@example.com"),
                username: String::from("someusername123"),
                active: true,
                sign_in_count: 1,
};
```