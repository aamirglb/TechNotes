# Python Notes

## Think Python

* The single most important skill for a computer scientist is **problem solving**.

* Two kinds of programs process high-level languages into low-level languages: **interpreters** and **compilers**. An interpreter reads a high-level program and executes it line by line. A compiler reads the program and translates it completely before the program starts run-
ning.

* When you have eliminated the impossible, whatever remains, however im-
probable, must be the truth. - Sherlock Holmes

```python
type(3.2)       # <type 'float'>
type('hello')   # <type 'str'>
type(17)        # <type 'int'>
```

* Python 2 has 31 keywords. In Python 3, `exec` is no longer a keyword, but `nonlocal` is.

* In the context of programming, a function is a named sequence of statements that performs a computation.

* Python provides built-in functions that convert values from one type to another.

```python
int(3.2)
float(32)
str(32)
```

* A **module** is a file that contains a collection of related functions.
Before we can use the module, we have to import it using `import math`.

* `def` is a keyword that indicates that this is a function definition.
```python
def say_hello():
    echo "Hello"
    
def add_numbers(a, b):
    return a+b
```