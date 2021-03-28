# Perl

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
