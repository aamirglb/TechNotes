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

* The `turtle` module allows you to create images using turtle graphics. On Ubuntu `turtle` required tkinter module.

```shell
$ sudo apt-get install python3-tk
```

* Turtle methods

|  fun  |  Description            |
|-------|-------------------------|
|  `fd` | Forward                 |
|  `bk` | Backward                |
|  `lt` | Left turn (in angle)    |
|  `rt` | Right turn (in angle)   |

# Learning Python

* Jython - Based on Java
  IronPython - Based on .NET-based Python
  Stackless and 
  PyPy

* Python can interact over networks with interfaces like SOAP, XML-RPC, and CORBA.

* Python includes tools such as modules and OOP that naturally promote code reusability

* Python is a general-purpose programming language that blends procedural, functional, and object-oriented paradigms.

* Python’s standard library comes with POSIX bindings and support for all the usual OS tools: 
    * environment variables, 
    * files, 
    * sockets, 
    * pipes, 
    * processes, 
    * multiple threads, 
    * regular expression pattern matching, 
    * command-line arguments, 
    * standard stream interfaces,
    * shell-command launchers, 
    * filename expansion, 
    * zip file utilities, 
    * XML and JSON parsers,
    * CSV file handlers, and more.

* Python comes with a standard object-oriented
interface to the Tk GUI API called tkinter (Tkinter in 2.X)

* Higher-level toolkits such as **Dabo** are built on top of base APIs such as _wxPython_ and
_tkinter_. With the proper library, you can also use GUI support in other toolkits in
Python, such as Qt with PyQt, GTK with PyGTK, MFC with PyWin32, .NET with
IronPython, and Swing with Jython (the Java version of Python, described in Chapter
2) or JPype

* integrating a C library into Python enables Python to
test and launch the library’s components, and embedding Python in a product enables
onsite customizations to be coded without having to recompile the entire product

* The in-process _SQLite_ embedded SQL database engine
is a standard part of Python itself since 2.5, supporting both prototyping and basic
program storage needs.

* Python’s standard _pickle_ module provides a simple object
persistence system—it allows programs to easily save and restore entire Python objects
to files and file-like objects.

* _PyMongo_, an interface to **MongoDB**, a high-performance, non-SQL, open source
JSON-style document database, which stores data in structures very similar to Python’s
own lists and dictionaries, and whose text may be parsed and created with Python’s
own standard library json module.

* Image processing with PIL and its newer Pillow fork

* PEP (Python Enhancement Proposal)

* Main things found in Python's toolbox
    * Dynamic typing
    * Automatic memory management
    * Built-in object types
    * Built-in tools
    * Library utilities
    * Third-party utilities

* Python script is first compiled to **byte code** and then routed to **virtual machine**. Byte code of the program is stored in files that end with a _.pyc_ extension (compiled .py)

* In 3.2 and later, .pyc files are stored in __pycache__ directory.

* byte code is saved in files only for files that are imported, not
for the top-level files of a program that are only run as scripts

* Python Virtual Machine (PVM) is just a big code loop that iterates through
your byte code instructions, one by one, to carry out their operations. The PVM is the
runtime engine of Python;

* there are at least five implementations
of the Python language—CPython, Jython, IronPython, Stackless, and
PyPy. Other potential candidates here include the Cython and Shed Skin systems

* Frozen binaries bundle together the byte code of your program files, along with the
PVM (interpreter) and any Python support files your program needs, into a single
package.

* In Python `*` means multiply for numbers but repeat for strings.

* In Python, using a variable before it has been _assigned a value_ is always an error

* Python files are usually knows as _modules_. Modules are simply text files containing Python statements.

```python
import sys
print(sys.platform)
```

* Scripts usually start with a line that begins with the
characters #! (often called “hash bang” or “shebang”), followed by the path to the
Python interpreter on your machine.

* On some Unix systems, you can avoid hardcoding the path to the Python interpreter
in your script file by writing the special first-line comment like this:
`#!/usr/bin/env python`

* In simple terms, every file of Python source code whose name ends in a .py extension is a module. Other files can access the items a module defines by importing that module — import operations essentially load another file and grant access to that file’s contents

* One of the modules is designated as the main or
top-level file, or “script”—the file launched to start the entire program,

* import operations _run_ the code in a file that is being
loaded as a final step. Because of this, importing a file is yet another way to launch it.

* `import script1` This works, but only once per session by default. After the first import, later imports do nothing, even if you change and save the module’s source file again in another window. This is by design because import is an expensive operation.

* To reload python module without stopping and restarting the session use `reload` function available in `imp` standard library module.

```python
from imp import reload
reload(script1)

DeprecationWarning: the imp module is deprecated in favour of importlib; see the module's documentation for alternative uses
```
* A module is mostly just a package of variable names, known as a
_namespace_, and the names within that package are called _attributes_. An attribute is simply a variable name that is attached to a specific object (like a module).

```python

# myfile.py
title = "The Meaning of Life"

import myfile
myfile.title

from myfile import title
title
```

* The `dir()` function fetches a list of all the names avaialble inside a module.

```python
import sys
dir(sys)

for i, name in enumerate(dir(sys)):
	print("{} => {}".format(i, name))
```

Page 71: Modules and namespaces