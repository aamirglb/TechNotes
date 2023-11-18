# C++ Complete Reference

* The version of C defined by the 1989 standard is commonly referred to as **C89**.

* The **C99** standardization committee focused on two main areas: the addition of several _numeric libraries_ and the development of some special-use, but highly innovative, new features, such as _variable-length arrays_ and there _strict pointer qualifier_.

* In a few cases, features originally from C++, such as single-line comments, were also incorporated into C99.

* Because the standard for C++ was finalized before C99 was created, none of the C99 innovations are found in Standard C++.

* **Portability** means that it is easy to adapt software written for one type of computer or operating system to another. For example, if you can easily convert a program written for UNIX so that it runs under Windows, that program is portable.

* A data type defines a set of values that a variable can store along with a set of operations that can be performed on that variable. Common data types are integer, character, and real.

* Although **C** has five basic built-in data types, it is not a strongly typed language, as are **Pascal** and **Ada**. C permits almost all type conversions.

* For example, you may freely intermix character and integer types in an expression.

* Unlike a high-level language, C performs almost _no run-time error checking_. For example, no check is performed to ensure that array boundaries are not overrun. These types of checks are the responsibility of the programmer.

* C is special in that it allows the direct manipulation of bits, bytes, words, and pointers. This makes it well suited for system-level programming, where these operations are common.

* Another important aspect of C is that it has only a _few keywords_, which are the commands that make up the C language. For example, **C89** defines only **32** keywords, with **C99** adding just another **5**.

* C's main structural component is the function - C's stand-alone subroutine.

### const

* Variables of type const may not be changed by your program. (A const variable can be given an initial value, however.) The compiler is free to place variables of this type into read-only memory (ROM).

* A const variable will receive its value either from an explicit initialization or by some hardware-dependent means.

* `const char *str` - can update the pointer but not the value pointed to by pointer, `str++` is allowed but *str = '-'` is not allowed.

### volatile

* The modifier `volatile` tells the compiler that a variable's value may be changed in ways not explicitly specified by the program.

* C/C++ compilers automatically optimize certain expressions by assuming that a variable's content is unchanging if it does not occur on the left side of an assignment statement; thus, it might not be reexamined each time it is referenced. Also, some compilers change the order of evaluation of an expression during the compilation process. The volatile modifier _prevents these changes_.

* if 0x30 is assumed to be the value of a port that is changed by external conditions only

`const volatile char *port = (const volatile char *) 0x30;`

### Storage Class Specifiers

    * extern
    * static
    * register
    * auto
    * mutable -- only c++

#### extern

* extern allows you to declare a variable without defining it. However, if you give that variable an initialization, then the extern declaration becomes a definition.

```c
extern int outside_temp; // only declration
extern int outside_temp = 10; // variable is defined here
```

* The extern specifier tells the compiler that the variable types and names that follow it have been defined elsewhere extern can also be applied to a function declaration, but doing so is redundant.

#### static variable

* static variables are permanent variables within their own function or file. Unlike global variables, they are not known outside their function or file, but they maintain their values between calls.

* a static local variable is a local variable that retains its value between function calls.

* You can give a static local variable an initialization value. This value is assigned only once, at program start-up - not each time the block of code is entered, as with normal local variables.

#### static global variable

* Applying the specifier static to a global variable instructs the compiler to create a global variable that is known only to the file in which you declared it

* static variables enable you to hide portions of your program from other portions

static use in C++
-----------------

* In C++, the preceding use of staticis still supported, but deprecated. This means that it is not recommended for new code. Instead, you should use a namespace.

register variable
-----------------

* The `register` storage specifier originally applied only to variables of type `int`, `char`, or `pointer` types. However,register's definition has been broadened so that it applies to any type of variable.

* You can only apply the `register` specifier to local variables and to the formal parameters in a function. Global register variables are not allowed.

* In C, you cannot find the address of a register variable using the & operator.

* But this restriction does not apply to C++. However, taking the address of a register variable in C++ may prevent it from being fully optimized.

* Global and static local variables are initialized only at the start of the program.

`wchar_t`
-------

* Both C and C++ define _wide characters_ (used mostly in non-English language environments), which are 16 bits long. To specify a wide character constant, precede the character with a L. For example,

```cpp
  wchar_t wc;
  wc = L'A';
```

* In C, `wchar_t` type is defined in a header file and is not a built-in type. In C++, `wchar_t` is built in.

* C allows you to define string constants, it does not formally have a string data type. C++ does define a string class, however.

* There is, a difference between the _prefix_ and _postfix_ forms when you use these operators in an expression. When an increment or decrement operator precedes its operand, the increment or decrement operation is performed before obtaining the value of the operand for use in the expression. If the operator follows its operand, the value of the operand is obtained before incrementing or decrementing it.

```cpp
x = 10;
y = ++x; // x is 11, y is 11

x = 10;
y = x++;  // x is 11, y is 10
```

* Most C/C++ compilers produce very fast, efficient object code for increment and decrement operations—code that is better than that generated by using the equivalent assignment statement. For this reason, you should use the increment and decrement operators when you can

* bitwise operations cannot be used on `float`, `double`,` long double`, `void`,
`bool`, or other, more complex types.

The exclusive OR has the truth table shown here:

| p  |   q  |   p^q |
|----|------|-------|
| 0  |   0  |   0   |
| 1  |   0  |   1   |
| 1  |   1  |   0   |
| 0  |   1  |   1   |

* relational and logical operators always produce a result that is either true or false, whereas the similar bitwise operations may produce any arbitrary value in accordance with the specific operation.

* A shift right effectively divides a number by 2 and a shift left multiplies it by 2.

* The one's complement operator, `~`, reverses the state of each bit in its operand. That is, all 1's are set to 0, and all 0's are set to 1.

The ? Operator
--------------

* The ternary operator ? takes the general form
`Exp1 ? Exp2 : Exp3;`
where Exp1, Exp2, and Exp3 are expressions.

The & and * Pointer Operators
------------------------------

* A pointer is the memory address of some object.
pointers have three main functions in C/C++.
    i)  They can provide a fast means of referencing array elements.
    ii) They allow functions to modify their calling parameters.
    iii) they support linked lists and other dynamic data structures.

The Compile-Time Operator `sizeof`
---------------------------------

* sizeof is a unary compile-time operator that returns the length, in bytes, of the variable or parenthesized type-specifier that it precedes.

```c
double f;
printf("%d ", sizeof f);  // for variables parenthesis is not required
printf("%d", sizeof(int));
```

* to compute the size of a type, you must enclose the type name in parentheses. This is not necessary for variable names, although there is no harm done if you do so. `sizeof` is evaluated at compile time, and the value it produces is treated as a constant within your program.

The Comma Operator
------------------

* The comma operator strings together several expressions. The left side of the comma operator is always evaluated as void. This means that the expression on the right side becomes the value of the total comma-separated expression. For example,

```c
x = (y=3, y+1);
```

first assigns y the value 3 and then assigns x the value 4. The parentheses are necessary because the comma operator has a lower precedence than the assignment operator.

The Dot (.) and Arrow (->) Operators
------------------------------------

* The dot operator is used when working with a structure or union directly. The arrow operator is used when a pointer to a structure or union is used.

Order of Evaluation
-------------------

* Neither C nor C++ specifies the order in which the sub expressions of an expression are evaluated. This leaves the compiler free to rearrange an expression to produce more optimal code. However, it also means that your code should never rely upon the order in which subexpressions are evaluated.

For example, the expression
`x = f1() + f2();`
does not ensure that f1( ) will be called before f2().

Casts
------

* You can force an expression to be of a specific type by using a cast. The general form of a cast is (type) expression

True and False in C and C++
----------------------------

* In C, a true value is any nonzero value, including negative numbers. A false value is 0. This approach to true and false allows a wide range of routines to be coded extremely efficiently.

* C++ also defines a Boolean data type called `bool`, which can have only the values true and false.

* C99 has added a Boolean type called _Bool, but it is incompatible with C++.

* The C language guarantees at least _15 levels of nesting_. In practice, most compilers allow substantially more. More importantly, Standard C++ suggests that at least _256 levels of nested_ ifs be allowed in a C++ program.

```c
/* print proper message */
t ? f1(t) + f2() : printf("zero entered.\n");
```

* Some C++ compilers rearrange the order of evaluation of an expression in an attempt to optimize the object code. This could cause functions that form the operands of the ? operator to execute in an unintended sequence.

switch
-------

* C/C++ has a built-in multiple-branch selection statement, called `switch`, which successively tests the value of an expression against a list of integer or character constan. When a match is found, the statements associated with that constant are executed.

* Floating-point expressions are not allowed.
/* gcc error */
error: switch quantity not an integer

* Although case is a label statement, it cannot exist by itself, outside of switch

* In C, a switch can have at least _257 case statements_. Standard C++ recommends that at least _16,384 case statements_ be supported!!

* There are three important things to know about the switch statement:
    1. The switch differs from the if in that switch can only test for equality, whereas if can evaluate any type of relational or logical expression.

    1. No two case constants in the same switch can have identical values. Of course, a switch statement enclosed by an outer switch may have case constants that are the same.

    1. If character constants are used in the switch statement, they are automatically converted to integers.

* In C++ (but not C89), it is possible to declare a variable within the conditional expression of an if or switch, within the conditional expression of a while loop, or within the initialization portion of a for loop.

* A variable declared in one of these places has its scope limited to the block of code controlled by that statement.

* In C89, a non-void function does not technically have to return a value. If no return value is specified, a garbage value is returned. However, in C++ (and in C99), a non-void function must return a value.

* Most programmers' chief concern about the goto is its tendency to render programs unreadable.

* You can generate a pointer to the first element of an array by simply specifying the array name, without any index.

* In C/C++, you cannot pass an entire array as an argument to a function. You can, however, pass to the function a pointer to an array by specifying the array's name without an index.

* If a function receives a single-dimension array, you may declare its formal parameter in one of three ways: as a pointer, as a sized array, or as an unsized array.

```c
void func1(int *x) /* pointer */
void func1(int x[10]) /* sized array */
void func1(int x[]) /* unsized array */
```

* When declaring a character array that will hold a null-terminated string, you need to declare it to be one character longer than the largest string that it is to hold (to accomodate null character).

| Name  | Function |
|-------|----------|
| strcpy(s1, s2) | Copies s2 into s1. |
| strcat(s1, s2) | Concatenates s2 onto the end of s1. |
| strlen(s1) | Returns the length of s1. |
| strcmp(s1, s2) | Returns 0 if s1 and s2 are the same; less than 0 if s1<s2; greater than 0 if s1>s2. |
| strchr(s1, ch) | Returns a pointer to the first occurrence of ch in s1. |
| strstr(s1, s2) | Returns a pointer to the first occurrence of s2 in s1. |

* When a two-dimensional array is used as an argument to a function, only a pointer to the first element is actually passed. However, the parameter receiving a two-dimensional array must define at least the size of the rightmost dimension. The rightmost dimension is needed because the compiler must know the length of each row if it is to index the array correctly.
`void func1(int x[][10])`

* To create an array of null-terminated strings, use a two-dimensional character array. The size of the left index determines the number of strings and the size of the right index specifies the maximum length of each string.

* The following code declares an array of 30 strings, each with a maximum length of 79 characters, plus the null terminator.

```c
char str_array[30][80];
```

* It is easy to access an individual string: You simply specify only the left index. `gets(str_array[4])`

* C/C++ allows arrays of more than two dimensions. The exact limit, if any, is determined by your compiler.

/* gcc gives error for more than 11 dimensions */
error: size of array 'array' is too large

* Arrays of more than three dimensions are not often used because of the amount of memory they require.

* In multidimensional arrays, it takes the computer time to compute each index. This means that accessing an element in a multidimensional array can be slower than accessing an element in a single-dimension array.

* When passing multidimensional arrays into functions, you must declare all but the leftmost dimension.

```c
int m[4][3][6][5];
void func1(int d[][3][6][5])
```

* When you use the string constant, the compiler automatically supplies the null terminator.

Pointers
---------

    1. pointers provide the means by which functions can modify their calling arguments.
    1. pointers support dynamic allocation.
    1. pointers can improve the efficiency of certain routines.

* any type of pointer can point anywhere in memory. However, all pointer arithmetic is done relative to its base type, so it is important to declare the pointer correctly.

* In C++, it is illegal to convert one type of pointer into another without the use of an explicit type cast. In C, casts should be used for most pointer conversions.

* `%p` - causes `printf( )` to display an address in the format used by the host computer

Pointer Arithmetic
-------------------

* There are only two arithmetic operations that you may use on pointers: addition and subtraction. you may add or subtract integers to or from pointers.

* Besides addition and subtraction of a pointer and an integer, only one other arithmetic operation is allowed: You may subtract one pointer from another in order to find the number of objects of their base type that separate the two.

* All other arithmetic operations are prohibited. Specifically, you may not multiply or divide pointers; you may not add two pointers; you may not apply the bitwise operators to them; and you may not add or subtract type float or double to or from pointers.

* The following rules govern pointer arithmetic. Each time a pointer is incremented, it points to the memory location of the next element of its base type. Each time it is decremented, it points to the location of the previous element.

* Global and static local pointers are automatically initialized to null.

```c
char *p = "hello world";
```

* The reason this sort of initialization works is because of the way the compiler operates. All C/C++ compilers create what is called a string table, which is used to store the string constants used by the program. Therefore, the preceding declaration statement places the address of "*hello world*", as stored in the string table, into the pointer p.

* In Standard C++, the type of a string literal is technically `const char *`. But C++ provides an automatic conversion to `char *`.

* However, this automatic conversion is a deprecated feature, which means that you should not rely upon it for new code. For new programs, you should assume that string literals are indeed constants and the declaration of `p` in the preceding program should be written like this.
`const char *p = "hello world";`

Pointers to Functions
---------------------

* A particularly confusing yet powerful feature of C++ is the function pointer. Even though a function is not a variable, it still has a physical location in memory that can be assigned to a pointer. This address is the entry point of the function and it is the address used when the function is called. Once a pointer points to a function, the function can be called through that pointer. Function pointers also allow functions to be passed as arguments to other functions. (callback function)

* You obtain the address of a function by using the function's name without any parentheses or arguments.

* Both of the following statements are same.

```c
(*cmp)(a, b)
cmp(a, b);
```

* The reason that you will frequently see the first style is that it tips off anyone reading your code that a function is being called through a pointer. (That is, that cmp is a function pointer, not the name of a function.) Other than that, the two expressions are equivalent.

* Dynamic allocation is the means by which a program can obtain memory while it is running. As you know, global variables are allocated storage at compile time. Local variables use the stack. However, neither global nor local variables can be added during program execution.

```c
#include <stdlib.h>
void *malloc(size_t number_of_bytes);
void free(void *p);
```

* The `malloc( )` function returns a pointer of type `void *`, which means that you
can assign it to any type of pointer. After a successful call, `malloc( )` returns
a pointer to the first byte of the region of memory allocated from the heap.
If there is not enough available memory to satisfy the `malloc( )` request, an
allocation failure occurs and `malloc( )` returns a `null`.

* In C, a `void *` pointer is automatically converted to the type of the pointer on
the left side of an assignment. However, it is important to understand that this
automatic conversion does not occur in C++. In C++, an explicit type cast is
needed when a `void *` pointer is assigned to another type of pointer.

* It is critical that you never call `free( )` with an invalid argument; otherwise,
you will destroy the free list.

* In C (and C++) you _cannot define a function within a function_. This is why
neither C nor C++ are technically block-structured languages.

* There are two special built-in arguments, `argv` and `argc`, that are used to
receive command line arguments. The `argc` parameter holds the number of arguments
on the command line and is an integer. It is always at least 1 because the name
of the program qualifies as the first argument. The `argv` parameter is a pointer
to an array of character pointers. Each element in this array points to a
command line argument.
All command line arguments are strings

* In theory, you can have up to **32,767 arguments**, but most operating systems do
not allow more than a few.

* In C++, the use of void to indicate an empty parameter list is allowed, but
redundant.

* In C89, if a non-void function does not explicitly return a value via
a return statement, then a garbage value is returned. In C++ (and C99),
a non-void function must contain a return statement that returns a value.

Recursion
----------

* In C/C++, a function can call itself. A function is said to be recursive if a
statement in the body of the function calls itself. Recursion is the process of
defining something in terms of itself, and is sometimes called circular
definition.

* The main advantage to recursive functions is that you can use them to create
_clearer and simpler versions of several algorithms_. For example, the Quicksort
algorithm is difficult to implement in an iterative way.

* Prototypes enable both C and C++ to provide stronger type checking, somewhat
like that provided by languages such as Pascal. When you use prototypes, the
compiler can find and report any illegal type conversions between the type of
arguments used to call a function and the type definition of its parameters.

* The compiler will also catch differences between the number of arguments used to
call a function and the number of parameters in the function.

* The old-style form of parameter declaration is designated as obsolete by the C
languag and is not supported by C++.

* The C language gives you five ways to create a custom data type:

    1. The **structure**, which is a grouping of variables under one name and is called
   an aggregate data type. (The terms compound or conglomerate are also commonly
   used.)

    1. The **bit-field**, which is a variation on the structure and allows easy access to
   individual bits.

    1. The **union**, which enables the same piece of memory to be defined as two or
   more different types of variables.

    1. The **enumeration**, which is a list of named integer constants.

    1. The `typedef` keyword, which defines a new name for an existing type.

* C++ supports all of the above and adds classes.

* In C, to declare a structure variable (i.e., a physical object) of type addr,
write
`struct addr addr_info;`

In C++, you may use this shorter form.
`addr addr_info; //    keyword struct is not needed.`

* The information contained in one structure may be assigned to another structure
of the same type using a single assignment statement. That is, you do not need
to assign the value of each member separately.

* There is one major drawback to passing all but the simplest structures to
functions: the overhead needed to push the structure onto the stack when the
function call is executed. If the structure contains many members, however, or
if some of its members are arrays, run-time performance may degrade to
unacceptable levels. The solution to this problem is to pass only a
pointer to the structure.

* C guarantees that structures can be nested to at least 15 levels. Standard
C++ suggests that at least 256 levels of nesting be allowed.

* Bit-fields can be useful for a number of reasons,
such as:
    1. If storage is limited, you can store several Boolean (true/false) variables in one byte.
    1. Certain devices transmit status information encoded into one or more bits within a byte.
    1. Certain encryption routines need to access the bits within a byte.

* To access individual bits, C/C++ uses a method based on the structure. In fact,
a bit-field is really just a special type of structure member that defines how
long, in bits, the field is to be.

* A bit-field must be declared as an integral or enumeration type. Bit-fields of
length 1 should be declared as unsigned, because a single bit cannot have a sign

Bit-fields restrictions
-----------------------

1. You cannot take the address of a bit-field.
1. Bit-fields cannot be arrayed.
1. They cannot be declared as static.
1. You cannot know, from machine to machine, whether the fields will run from
   right to left or from left to right; this implies that any code using
   bit-fields may have some machine dependencies.

Unions
-------

* A union is a memory location that is shared by two or more different types of
variables. A union provides a way of interpreting the same bit pattern in two
or more different ways.

```c
enum coin { penny, nickel, dime, quarter,
            half_dollar, dollar};
enum coin money;
money = dime;
if(money==quarter) printf("Money is a quarter.\n");
```

* You can define new data type names by using the keyword `typedef`. You are not
actually creating a new data type, but rather defining a new name for an
existing type. This process can help make machine-dependent programs more
portable.

Console IO
----------

* In C, input and output are accomplished through library functions. There are
both console and file I/O functions.

* Standard C++ does not define any functions that perform various screen control
operations (such as cursor positioning) or that display graphics, because these
operations vary widely between machines. Nor does it define any functions that
write to a window or dialog box under Windows. Instead, the console I/O
functions perform only TTY-based output. However, most compilers include in
their libraries screen control and graphics functions that apply to the specific
environment in which the compiler is designed to run. And, of course, you may
use C++ to write Windows programs, but keep in mind that the C++ language does
not directly define functions that perform these tasks.

Reading and Writing Characters
-------------------------------

```c
#include <stdio.h>
int getchar(void);  // reads a character from the keyboard,
int putchar(int c); // prints a character to the screen
```

* The `getchar()` function waits until a key is pressed and then returns its value.
The key pressed is also automatically echoed to the screen.

* The `putchar()` function writes a character to the screen at the current cursor
position.

* Both functions return `EOF` if an error occurs. The E`OF macro is defined in `stdio.h` and is generally equal to -1.

A Problem with getchar()
--------------------------

* Normally, `getchar()` is implemented in such away that it buffers input until
ENTER is pressed. This is called line-buffered input; you have to press ENTER
before anything you typed is actually sent to your program. Also, since
`getchar()` inputs only one character each time it is called, line-buffering may
leave one or more characters waiting in the input queue, which is annoying in
interactive environments.

* These functions are not defined in Standard C++ but these functions are always
provided by the compiler.

```c
#include <conio.h>
int getch(void);
int getche(void);
```

* The `getch()` function waits for a keypress, after which it returns immediately.
It does not echo the character to the screen. The `getche( )` function is the same
as `getch()`, but the key is echoed.

Reading and Writing Strings
---------------------------

gets()
------

* The `gets()` function reads a string of characters entered at the keyboard and
places them at the address pointed to by its argument. You may type characters
at the keyboard until you press ENTER. _The carriage return does not become part
of the string_; instead, a _null terminator is placed at the end and gets() returns_.

```c
#include <stdio.h>
char *gets(char *str);
```

where str is a character array that receives the characters input by the user.
gets() also returns str.

puts()
------

* The `puts()` function writes its string argument to the screen followed by a
newline. Its prototype is:

```c
#include <stdio.h>
int puts(const char *str);
```

* `puts()` recognizes the same backslash codes as `printf()`, such as '\t' for tab.

* A call to `puts()` requires far less overhead than the same call to `printf()`
because `puts()` can only output a string of characters it cannot output numbers
or do format conversions. Therefore, `puts()` takes up less space and runs faster
than `printf()`. For this reason, the `puts()` function is often used when it is
important to have highly optimized code. The `puts()` function returns EOF if an
error occurs. Otherwise, it returns a nonnegative value.

Formatted Console I/O
---------------------

* The functions `printf()` and `scanf()` perform formatted output and input that is,
they can read and write data in various formats that are under your control.
Both functions can operate on any of the built-in data types, including
characters, strings, and numbers.

printf()
--------

```c
#include <stdio.h>
int printf(const char *control_string, ...);
```
returns the number of characters written or a negative value if an error occurs.

* The control_string consists of two types of items. The first type is composed of
characters that will be printed on the screen. The second type contains format
specifiers that define the way the subsequent arguments are displayed. A format
specifier begins with a percent sign and is followed by the format code.
There must be exactly the same number of arguments as there are format
specifiers, and the format specifiers and the arguments are matched in order
from left to right.


| Code  |  Format  |
| ------|--------- |
| %c    |  Character |
| %d    |  Signed decimal integers |
| %i    |  Signed decimal integers |
| %e    |  Scientific notation (lowercase e) |
| %E    |  Scientific notation (uppercase E) |
| %f    |  Decimal floating point |
| %g    |  Uses %e or %f, whichever is shorter |
| %G    |  Uses %E or %F, whichever is shorter |
| %o    |  Unsigned octal |
| %s    |  String of characters |
| %u    |  Unsigned decimal integers |
| %x    |  Unsigned hexadecimal (lowercase letters) |
| %X    |  Unsigned hexadecimal (uppercase letters) |
| %p    |  Displays a pointer |
| %n    |  The associated argument must be a pointer to an integer. This specifier causes the number of         characters written so far to be put into that integer. |
| %%    |  Prints a % sign |

* You can tell `printf()` to use either `%f` or `%e` by using the `%g` or `%G` format
specifiers. This causes `printf()` to select the format specifier that produces
the shortest output.

* `%n` specifier causes `printf()` to load the variable pointed to by its corresponding
argument with a value equal to the number of characters that have been output.

```c
printf("this%n is a test\n", &count);
On Linux: this printfs
This is a test 4
On Windows (with gcc 4.7.0)
This 2 --> looks some problem here
```

* %n is used primarily to enable your program to perform dynamic formatting.

Format Modifiers
-----------------

* The format modifier goes between the percent sign and the format code.
`%05d` -- An integer placed between the % sign and the format code acts as a
minimum field width specifier.

* The minimum field width modifier is most commonly used to produce tables in
which the columns line up.

The Precision Specifier
------------------------

* It consists of a period followed by an integer. Its exact meaning depends upon
the type of data it is applied to.

* for floating-point data using the `%f`, `%e`, or `%E` specifiers, it determines the
number of decimal places displayed.

* `%10.4f` displays a number at least ten characters wide with four decimal places.

* When applied to `%g` or `%G`, it specifies the number of significant digits.

* Applied to strings, the precision specifier specifies the maximum field length.
`%5.7s` displays a string at least five and not exceeding seven characters long.

* If the string is longer than the maximum field width, the end characters will
be truncated.

* When applied to integer types, the precision specifier determines the minimum
number of digits that will appear for each number. Leading zeros are added to
achieve the required number of digits.

Justifying Output
-----------------

* By default, all output is right-justified. That is, if the field width is larger
than the data printed, the data will be placed on the right edge of the field.
You can force output to be left-justified by placing a minus sign directly after
the %. For example, %-10.2f left-justifies a floating-point number with two
decimal places in a 10-character field.

* %ld means that a long int is to be displayed. The h modifier instructs printf()
to display a short integer. For instance, %hu indicates that the data is of
type short unsigned int.

* The l and h modifiers can also be applied to the n specifier, to indicate that
the corresponding argument is a pointer to a long or short integer, respectively.

* If your compiler fully complies with Standard C++, then you can use the l
modifier with the c format to indicate a wide-character. You can also use the l
modifier with the s format to indicate a wide-character string.

* The L modifier may prefix the floating-point specifierse,f, and g, and indicates
that a long double follows.

The * and # Modifiers
---------------------

* Preceding g, G, f, E,or e specifiers with a # ensures that there will be a
decimal point even if there are no decimal digits.

* If you precede the x or X format specifier with a #, the hexadecimal number will
be printed with a 0x prefix. Preceding the o specifier with # causes the number
to be printed with a leading zero.
You cannot apply # to any other format specifiers.

* Instead of constants, the minimum field width and precision specifiers may be
provided by arguments to printf(). To accomplish this, use an * as a placeholder.
When the format string is scanned, printf() will match the * to an argument in
the order in which they occur.

printf("%*.*f", 10 , 4 , 123.4 );

scanf()
--------

* scanf() is the general-purpose console input routine. It can read all the
built-in data types and automatically convert numbers into the proper internal
format.

```c
int scanf(const char *control_string, ...);
```

* The scanf() function returns the number of data items successfully assigned a
value. If an error occurs, scanf( ) returns EOF.

| Code | Meaning |
|------|-------- |
| %c | Read a single character. |
| %d  | Read a decimal integer. |
| %i | Read an integer in either decimal, octa hexadecimal format. |
| %e  | Read a floating-point number. |
| %f  | Read a floating-point number. |
| %g  | Read a floating-point number. |
| %o  | Read an octal number. |
| %s  | Read a string. |
| %x  | Read a hexadecimal number. |
| %p  | Read a pointer. |
| %n  | Receives an integer value equal to the value of characters read so far. |
| %u  | Read an unsigned decimal integer. |
| %[ ] | Scan for a set of characters. |
| %% | Read a percent sign. |

* The scanf() function stops reading a number when the first nonnumeric character
is encountered.

* like most implementations of getchar(), scanf() will generally line-buffer input
when the %c specifier is used. This makes it somewhat troublesome in an
interactive environment.

* Although spaces, tabs, and newlines are used as field separators when reading
other types of data, when reading a single character, white-space characters are
read like any other character.

* Using %s causes scanf() to read characters until it encounters a white-space
character.

* Unlike gets(), which reads a string until a carriage return is typed, scanf()
reads a string until the first white space is entered.

Using a Scanset
---------------

* The scanf() function supports a general-purpose format specifier called a
scanset. A scanset defines a set of characters. When scanf() processes a
scanset, it will input characters as long as those characters are part of the
set defined by the scanset. The characters read will be assigned to the
character array that is pointed to by the scanset's corresponding argument.
You define a scanset by putting the characters to scan for inside square
brackets. The beginning square bracket must be prefixed by a percent sign.
	%[XYZ] read only the characters X, Y, and Z.

```c
char str[80];
scanf("%[abcdefg]", str);
```

* You can specify an inverted set if the first character in the set is a ^.
The ^ instructs scanf() to accept any character that is not defined by the
scanset.

* In most implementations you can specify a range using a hyphen. For example,
this tells scanf() to accept the characters A through Z:
%[A-Z]

* One important point to remember is that the scanset is case sensitive.

* "%d,%d" causes scanf() to read an integer, read and discard a comma, and then
read another integer.

Format Modifiers
-----------------

* The format specifiers can include a maximum field length modifier. This is an
integer, placed between the % and the format specifier, that limits the number
of characters read for that field. to read no more than 20 characters into
str, write
`scanf("%20s", str);`

Suppressing Input
------------------

* You can tell scanf() to read a field but not assign it to any variable by
preceding that field's format code with an *. For example, given

```c
scanf("%d%*c%d", &x, &y);
```

* you could enter the coordinate pair 10,10. The comma would be correctly read,
but not assigned to anything. Assignment suppression is especially useful when
you need to process only a part of what is being entered.

File IO
--------

* The C I/O system supplies a consistent interface to the programmer independent
of the actual device being accessed. That is, the C I/O system provides a level
of abstraction between the programmer and the device. This abstraction is called
a stream and the actual device is called a file.

Streams
--------

* The C file system is designed to work with a wide variety of devices, including
terminals, disk drives, and tape drives. Even though each device is very
different, the file system transforms each into a logical device called a
stream. All streams behave similarly. Because streams are largely device
independent, the same function that can write to a disk file can also be used to
write to another type of device, such as the console.
There are two types of streams: text and binary.

Text Streams
-------------

* A text stream is a sequence of characters. Standard C allows (but does not
require) a text stream to be organized into lines terminated by a newline
character. However, the newline character is optional on the last line.
(Actually, most C/C++ compilers do not terminate text streams with newline
characters.)

* In a text stream, certain character translations may occur as required by the
host environment. For example, a newline may be converted to a carriage return/
linefeed pair. Therefore, there may not be a one-to-one relationship between the
characters that are written (or read) and those on the external device. Also,
because of possible translations, the number of characters written (or read)
may not be the same as those on the external device.

Binary Streams
--------------

* A binary stream is a sequence of bytes that have a one-to-one correspondence to
those in the external device.

Files
------

* In C/C++, a file may be anything from a disk file to a terminal or printer.
Not all files have the same capabilities. For example, a disk file can support
random access while some printers cannot.

* If you close a file opened for output, the contents, if any, of its associated
stream are written to the external device. This process is generally referred to
as "flushing" the stream, and guarantees that no information is accidentally
left in the disk buffer.

* All files are closed automatically when your program terminates normally, either
by main()returning to the operating system or by a call to exit().
Files are not closed when a program terminates abnormally, such as when it
crashes or when it calls abort().

```c
#include <stdio.h>
```

| Name       |   Function |
| -----------|------------|
| fopen()    |   Opens a file. |
| fclose()   |   Closes a file. |
| putc()     |   Writes a character to a file. |
| fputc()    |   Same as putc(). |
| getc()     |   Reads a character from a file. |
| fgetc()    |   Same as getc(). |
| fgets()    |   Reads a string from a file. |
| fputs()    |   Writes a string to a file. |
| fseek()    |   Seeks to a specified byte in a file. |
| ftell()    |   Returns the current file position. |
| fprintf()  |   Is to a file what printf() is to the console. |
| fscanf()   |   Is to a file what scanf() is to the console. |
| feof()     |   Returns true if end-of-file is reached. |
| ferror()   |   Returns true if an error has occurred. |
| rewind()   |   Resets the file position indicator to the beginning of the file. |
| remove()   |   Erases a file. |
| fflush()   |   Flushes a file. |

three types: `size_t`, `fpos_t`, and `FILE`

Macros as defined in gcc
------
NULL
EOF              (-1)
FOPEN_MAX        (20)
SEEK_SET          0
SEEK_CUR and      1
SEEK_END          2

fopen()
-------

FILE *fopen(const char *filename, const char *mode);

| Mode |  Meaning  |
| -----|---------- |
| r    |  Open a text file for reading. |
| w    |  Create a text file for writing. |
| a    |  Append to a text file. |
| rb   |  Open a binary file for reading. |
| wb   |  Create a binary file for writing. |
| ab   |  Append to a binary file. |
| r+   |  Open a text file for read/write. |
| w+   |  Create a text file for read/write. |
| a+   |  Append or create a text file for read/write. |
| r+b  |  Open a binary file for read/write. |
| w+b  |  Create a binary file for read/write. |
| a+b  |  Append or create a binary file for read/write. |


| Mode       |    File            |     fopen() |
| -----------|--------------------|---------------------------------- |
| read (r)   |    does not exist  |     return error |
| append (a) |    does not exist  |     creat a new file |
| append (a) |    exist           |     all data will be appended at the end |
| write (w)  |    does not exist  |     create a new file |
| write (w)  |    exist           |     create a new file and contents of original file will be destroyed |
| r+         |    does not exist  |     not create a new file |
| w+         |    does not exist  |     create a new file |
| r+         |    exist           |     doesn't destroy content |
| w+         |    exist           |     destroys its contents |

int fclose(FILE *fp);
fclose() also frees the file control block associated with the stream, making it
available for reuse.
return value of zero signifies a successful close operation.
on erro retuns EOF

The C I/O system defines two equivalent functions that output a character:putc()
and fputc(). (Actually, putc() is usually implemented as a macro.)
There are two identical functions simply to preserve compatibility with older
versions of C.

int putc(int ch, FILE *fp);
on success returns the character written else return EOF.

int getc(FILE *fp);
do {
  ch = getc(fp);
} while(ch!=EOF);

feof()
------
First, the file system can operate on both text and binary files. When a file is
opened for binary input, an integer value that will test equal to EOF may be
read. This would cause the input routine to indicate an end-of-file
condition even though the physical end of the file had not been reached.
Second, getc() returns EOF when it fails and when it reaches the end of the
file. Using only the return value of getc(), it is impossible to know which
occurred. To solve these problems, the C file system includes the function
feof(), which determines when the end of the file has been encountered.

int feof(FILE *fp);
feof() returns true if the end of the file has been reached; otherwise, it
returns 0.

fputs() and fgets()
---------------------
int fputs(const char *str, FILE *fp);
char *fgets(char *str, int length, FILE *fp);

The fgets() function reads a string from the specified stream until either a
newline character is read or length -1 characters have been read.

rewind()
----------
The rewind() function resets the file position indicator to the beginning of the
file specified as its argument.
void rewind(FILE *fp);

ferror()
----------
The ferror() function determines whether a file operation has produced an error.
int ferror(FILE *fp);
It returns true if an error has occurred during the last file operation;
otherwise, it returns false. Because each file operation sets the error
condition, ferror() should be called immediately after each file operation;
otherwise, an error may be lost.

Erasing Files
--------------
The remove() function erases the specified file.
int remove(const char *filename);
It returns zero if successful; otherwise, it returns a nonzero value.

Flushing a Stream
-----------------
int fflush(FILE *fp);
flush the contents of an output stream
If you call fflush() with fp being null, all files opened for output are flushed.
The fflush( ) function returns 0 if successful; otherwise, it returns EOF.

// TODO PAGE 261  ==> To be continued till the end of chapter...

The Preprocessor
-----------------
various instructions to the compiler in the source code of a C/C++ program.
These are called preprocessor directives, and although not actually part of the
C or C++ language per se, they expand the scope of the programming environment.

In C, each preprocessor directive is necessary. In C++, some features have been
rendered redundant by newer and better C++ language elements. In fact,
one of the long-term design goals of C++ is the elimination of the preprocessor
altogether.

The preprocessor contains the following directives:
1) #define 		2) #elif 		3) #else 		4) #endif
5) #error 		6) #if 			7) #ifdef 		8) #ifndef
9) #include 	10) #line 		11) #pragma 	12) #undef

all preprocessor directives begin with a # sign.
each preprocessing directive must be on its own line.
#include <stdio.h>  #include <stdlib.h>    // will not work

C++ provides a better way of defining constants, which uses the const keyword.

The #define directive has another powerful feature: the macro name can have
arguments. Each time the macro name is encountered, the arguments used in its
definition are replaced by the actual arguments found in the program.

one major benefit: It increases the execution speed of the code because there is
no function call overhead. However, if the size of the function-like macro is
very large, this increased speed may be paid for with an increase in the size of
the program because of duplicated code.

Although parameterized macros are a valuable feature, C++ has a better way of
creating inline code, which uses the inline keyword.

#error
-------
The #error directive forces the compiler to stop compilation. It is used
primarily for debugging.
#error error-message
The error-message is not between double quotes

#include
--------
The number of levels of nesting allowed varies between compilers. However,
Standard C stipulates that at least eight nested inclusions will be available.
Standard C++ recommends that at least 256 levels of nesting be supported.

#include "stdio.h" --> file is looked for in another implementation-defined
                       manner
#include <stdio.h> --> file is searched for in a manner defined by the creator
                       of the compiler

The expression that follows the #if is evaluated at compile time. Therefore, it
must contain only previously defined identifiers and constants—no variables may
be used.

Standard C states that #ifs and #elifs may be nested at least eight levels.
Standard C++ suggests that at least 256 levels of nesting be allowed.

You may nest #ifdefs and #ifndefs to at least eight levels in Standard C.
Standard C++ suggests that at least 256 levels of nesting be supported.

Using defined
--------------
In addition to #ifdef, there is a second way to determine if a macro name is
defined. You can use the #if directive in conjunction with the defined
compile-time operator.
#if defined MYFILE
#if !defined DEBUG
One reason for using defined is that it allows the existence of a macro name to
be determined by a #elif statement.

#line
------
The #line directive changes the contents of __LINE__ and __FILE__
#line number "filename"
number is any positive integer and becomes the new value of __LINE__ ,
and the optional filename is any valid file identifier, which becomes the new
value of __FILE__ #line is primarily used for debugging and special applications

#pragma
--------
#pragma is an implementation-defined directive that allows various instructions
to be given to the compiler.

The # and ## Preprocessor Operators
------------------------------------
There are two preprocessor operators: # and ##. These operators are used with
the #define statement.

The # operator, which is generally called the "stringize" operator, turns the
argument it precedes into a quoted string.

The ## operator, called the "pasting" operator, concatenates two tokens.

//TODO check Test your c skills for clear understanding

Predefined Macro Names
-----------------------
C++ specifies six built-in predefined macro names. They are
__LINE__
__FILE__
__DATE__
__TIME__
__STDC__
__cplusplus
The C language defines the first five of these.

The meaning of __STDC__ is implementation-defined. Generally, if __STDC__ is
defined, the compiler will accept only standard C/C++ code that does not contain
any nonstandard extensions.

A compiler conforming to Standard C++ will define __cplusplus as a value
containing at least six digits. Nonconforming compilers will use a value with
five or less digits.

C++
=====
Using only structured programming techniques, programs are typically organized
around code. This approach can be thought of as "code acting on data."
Object-oriented programs work the other way around. They are organized
around data, with the key principle being "data controlling access to code."

Encapsulation
--------------
Encapsulation is the mechanism that binds together code and the data it
manipulates, and keeps both safe from outside interference and misuse.

Polymorphism
-------------
polymorphism is the attribute that allows one interface to control access to a
general class of actions. The specific action selected is determined by the
exact nature of the situation.

C++ is a compiled language. Therefore, in C++, both run-time and compile-time
polymorphism are supported.

Inheritance
------------
Inheritance is the process by which one object can acquire the properties of
another object.

<iostream> is one of the modern-style headers defined by Standard C++.
Modern C++ headers do not use the .h extension.

A namespace creates a declarative region in which various program elements can
be placed. Namespaces help in the organization of large programs.
std namespace is the namespace in which the entire Standard C++ library is
declared. C library functions are available in the default, global namespace.

the >> operator stops reading input when the first white-space character is
encountered.

The reason that C99 specifies _Bool rather than bool as a keyword is that many
preexisting C programs have aleady defined their own custom versions of bool. By
defining the Boolean type as _Bool, C99 avoids breaking this preexisting code.
However, it is possible to achieve compatibility between C++ and C99 on this
point because C99 adds the header <stdbool.h> which defines the macros
bool, true, and false. By including this header, you can create code that is
compatible with both C99 and C++.

Function Overloading
---------------------
One way that C++ achieves polymorphism is through the use of function
overloading. In C++, two or more functions can share the same name as long as
their parameter declarations are different. In this situation, the functions
that share the same name are said to be "overloaded", and the process is
referred to as "function overloading".

// house is derived from building
class house : public building {
class derived-class : access base-class {

constructor
------------
A constructor is a special function that is a member of a class and has
the same name as that class.
In C++, constructors cannot return values and, thus, have no return type.

The C++ Keywords
----------------
There are 63 keywords currently defined for Standard C++.
early versions of C++ defined the overload keyword, but it is obsolete.

Class and object
----------------
By default, functions and data declared within a class are private to that class
and may be accessed only by other members of the class. The public access
specifier allows functions or data to be accessible to other parts of your
program.

restrictions that apply to class members.
1) A non-static member variable cannot have an initializer.
2) No member can be an object of the class that is being declared. (Although a
   member can be a pointer to the class that is being declared.)
3) No member can be declared as auto, extern, or register.

In C++, the role of the structure was expanded, making it an alternative way to
specify a class. In fact, the only difference between a class and a struct is
that by default all members are public in a struct and private in a class.

acronym POD is used to describe a C-style structure—one that does not contain
member functions, constructors, or destructors. It stands for Plain Old Data.

In C++, unions may contain both member functions and variables. They may also
include constructors and destructors. A union in C++ retains all of its C-like
features, the most important being that all data elements share the same
location in memory.

restrictions when you use C++ unions
------------------------------------
1) a union cannot inherit any other classes of any type.
2) a union cannot be a base class.
3) A union cannot have virtual member functions.
4) No static variables can be members of a union.
5) A reference member cannot be used.
6) A union cannot have as a member any object that overloads the = operator.
7) no object can be a member of a union if the object has an explicit
   constructor or destructor function.

Anonymous Unions (only C++)
-----------------
An anonymous union does not include a type name, and no objects  of the union
can be declared. Instead, an anonymous union tells the compiler that its member
variables are to share the same location. However, the variables themselves are
referred to directly, without the normal dot operator syntax.

  // define anonymous union
  union {
    long l;
    double d;
    char s[4];
  } ;
  // now, reference union elements directly
  l = 100000;
  d = 123.2342;

All restrictions involving unions apply to anonymous ones, with these additions.
1) the only elements contained within an anonymous union must be data. No
   member functions are allowed.
2) Anonymous unions cannot contain private or protected elements.
3) global anonymous unions must be specified as static.

Friend Functions
-----------------
It is possible to grant a non-member function access to the private members of
a class by using a friend. A friend function has access to all private and
protected members of the class for which it is a friend.

To declare a friend function, include its prototype within the class, preceding
it with the keyword friend.

Use of friend function
----------------------
1) friends can be useful when you are overloading certain types of operators
2) friend functions make the creation of some types of I/O functions easier
3) friend functions may be desirable is that in some cases, two or more classes
   may contain members that are interrelated relative to other parts of program.

A friend of one class may be a member of another.
restrictions to friend functions.
1) a derived class does not inherit friend functions.
2) friend functions may not have a storage-class specifier. That is, they may
   not be declared as static or extern.

Friend Classes
--------------
It is possible for one class to be a friend of another class. When this is the
case, the friend class and all of its member functions have access to the
private members defined within the other class.

Inline Functions
----------------
In C++, you can create short functions that are not actually called; rather,
their code is expanded in line at the point of each invocation. This process is
similar to using a function-like macro. To cause a function to be expanded in
line rather than called, precede its definition with the inline keyword.

Like the register specifier, inline is actually just a request, not a command,
to the compiler. The compiler can choose to ignore it.

I is possible to define short functions completely within a class declaration.
When a function is defined inside a class declaration, it is automatically made
into an inline function (if possible). It is not necessary (but not an error)
to precede its declaration with the inline keyword.

myclass ob(3, 4);
myclass ob = myclass(3, 4);

If a constructor only has one parameter, there is a third way to pass an initial
value to that constructor.
X ob = 99; // passes 99 to constructor

Static Class Members
---------------------
Both function and data members of a class can be made static.

Static Data Members
--------------------
When you precede a member variable's declaration with static, you are telling
the compiler that only one copy of that variable will exist and that all objects
of the class will share that variable.

When you declare a static data member within a class, you are not defining it.
(That is, you are not allocating storage for it.) Instead, you must provide a
global definition for it elsewhere, outside the class. This is done by
redeclaring the static variable using the scope resolution operator to identify
the class to which it belongs.
int class::static_Var;

Static Member Functions
------------------------
Member functions may also be declared as static.
restrictions on static member functions
1) They may only directly refer to other static members of the class.
   (Of course, global functions and data may be accessed by static member
   functions.)
2) A static member function does not have a this pointer.
3) There cannot be a static and a non-static version of the same function.
4) A static member function may not be virtual.
5) They cannot be declared as const or volatile.

static member functions have limited applications, but one good use for them is
to "preinitialize" private static data before any object is actually created.

A class may be defined within a function.
restrictions to local classes.
1) all member functions must be defined within the class declaration.
2) The local class may not use or access local variables of the function in
   which it is declared (except that a local class has access to static local
   variables declared within the function or those declared as extern).
3) It may access type names and enumerators defined by the enclosing function,
4) No static variables may be declared inside a local class.

When a copy of an argument is made during a function call, the normal
constructor is not called. Instead, the object's copy constructor is called.
The default copy constructor creates a bitwise (that is, identical) copy of the
object.

A function may return an object to the caller.
By default, all data from one object is assigned to the other by use of a
bit-by-bit copy. However, it is possible to overload the assignment operator and
define some other assignment procedure.
