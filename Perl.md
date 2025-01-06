# Perl

https://www.learning-perl.com/2016/06/watch-regexes-with-regexpdebugger/

* CPAN (The Comprehensive Perl Archive Network). 
*  To start interactive session use
```
perl -de1
```

* Perl is a declarative, interpreted programming language useful for system administration, CGI programming etc. 

* Perl is extermely good at string processing. It is not good for things that require efficiency, such as scientific computation or simulations etc.

* Perl: Practical Extraction and Report Language.

```
# -w turns on warning
#!/usr/bin/perl -w

# force declare all variables
use strict;
```

* Perl is _case-sensitive_. Perl does not require user to declare variables before using them. Every statement must be terminated by a semicolon.

* Use `my` operator to declare variables

```
my $var;

# must use parantheses
my ($v1, $v2, $v3);
```

* Perl has 3 data types
    1. Scalars
    2. Arrays
    3. Hashes

* Scalar variable start with $ sign.

* Double-quoted strings are _interpolated_, any variable name found inside the string will be replaced by their value.

* To compare strings, use the string comparison operators: `eq` (equal), `ne` (not equal), `lt` (less than), `gt` (greater than), `le` (less
or equal), and `ge` (greater or equal). The string concatenation operator is `.` (period).

* Array variables always start with `@` symbol.

* Array can contain only scalars, arrays included in other arrays are **_flattended_**. While indexing an array, the array should be preceded with `$`.

```
my @array = (3, 4, 'five', -0.09876);
print "First element \@array is $array[0].\n"
```
* Negative indices count backward from the end of an array.

* Index of last element of @array is given by special scalar $#array;

* Hash variables always start with %. A hash is a list of key-value pairs. Hash indexing is done with curly braces.

```
my %hash = ('name', 'Aamir', 'age', 30, 'occupation', 'engineer');
my %data = (name => 'Aamir', 
    age => 20,
    occupation => 'engineer');
```

* Built-in string manipulation functions

| Function | Description |
|----------|-------------|
| `chomp`  |             |
| `chop`   |             | 
| `chr`    |             |
| `lc`     |             |
| `uc`     |             |
| `index`  |             |
| `rindex` |             |
| `substr` |             |
| `reverse` |            |
| `split`  |             |

* `<=>` space shift operator
  `x`   string repetition operator

* Array manipulation functions

| Function | Description |
|----------|-------------|
| `push`   |             | 
| `pop`    |             |
| `shift`  |             |
| `unshift`|             |
| `reverse`|             |
| `sort`   |             |
| `join`   |             |
| `splice` |             |
| `grep`   |             |
| `map`    |             |

* Perl has a special **undefined** value, often written **undef**

# Modern Perl

* The `perldoc` utility is part of every complete Perl installation.

```
$ perldoc List::Util
$ perldoc perltoc
$ perldoc Moose::Manual
```

* http://perldoc.perl.org/    http://search.cpan.org/   

* Perl uses context to express how to treat a piece of data.

* The _default scalar variable_ (or _topic variable_), `$_`, is most notable in its absence.

```perl
chomp $_; # same as chomp;
print;    # prints $_
say;      # prints $_
```


# Learning Perl 

* Perl is sometimes called the **Practical Extraction and Report Language**

* Companies such as **ActiveState** provide pre-built and enhanced distributions for several platforms,
including _Windows_. You can also get **Strawberry Perl** for Windows, which
comes with all the same stuff as regular Perl plus extra tools to compile and install
third-party modules.

* ActivePerl from ActiveState has PPM (Perl Package Manager)

* Perl doesn’t require any special kind of filename or extension

* `say` (added in v5.10) adds the newline for us

pragmas
```
use utf8;
use warnings;
perl -w program.pl
#!/usr/bin/perl -w
```

string operators
`.`: concatenation operator
`x`: repeat operator

* A **scalar** variable holds a single scalar value. Scalar variable names begin with a dollar sign ($), called the sigil, followed by a Perl identifier.

* Perl v5.10 adds a slightly better print that it calls say. It automatically puts a newline
on the end

* When a string literal is double-quoted, it is subject to variable interpolation (besides being checked for backslash escapes)

* line-input operator, `<STDIN>`.

* To tell whether a value is `undef` and not the empty string, use the
`defined` function, which returns false for undef, and true for everything else