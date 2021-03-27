# Sed and Awk Tools

* Sed **Stream Editor** is very powerful tool to manipulate, filter and transform text.

* Basic Syntax
```
sed [options] {sed-commands} {input-file}

sed [options] -f {sed-cmd-in-a-file} {input-file}
# print all lines
$ sed -n 'p' /etc/passed
```

* sed reads one line at a time from input-file and executes the command on that particular line.

* sed substitute command: s. The substitute command changes all occurrences of regular expression into a new value.

```
echo "day" | sed 's/day/night/'
sed 's/day/night' <old >new
```

* The character after substitute command `s` is the delimiter. It can be anything.

```
sed 's:day:night:' <old >new
sed 's|day|night|' file
```

* The special character `&` corresponds to the pattern found

```
sed 's/[a-z]*/(&)/'

echo "abc 123" | sed 's/[a-z]*/(&)/'
output: (abc) 123

echo "abc 123" | sed 's/[0-9][0-9]*/(&)/'
output: abc (123)

```

* `+` is a meta-character when using "extended regular expressions". To enable extended regular expression, use `-r` command line argument.

```
echo "123 abc" | sed -r 's/[0-9]+/(&)/'
```

* The escaped parentheses (that is, parentheses with backslashes before them) remember a substring of the characters matched by the regular expression. You can use this to exclude part of the characters matched by the regular expression. The "\1" is the first remembered pattern, and the "\2" is the second remembered pattern. Sed has up to nine remembered patterns.


```
echo "hello world" | sed 's/\([a-z]*\).*/\1/'
output: hello

# switch words around, to use \1, \2 you should use escaped parentheses \(...\)
sed 's/\([a-z]*\) \([a-z]*\)/\2 \1/'
```

* With extended regular expressions '(' and ')' no longer need to have a backslash.
```
echo "hello world" | sed -r 's/([a-z]+) ([a-z]+)/\2 \1/'
output: world hello
```

* `'1` can be used in search pattern as well.
```
# remove duplicate words
sed -r 's/([a-z]+) \1/\1/'

echo "hello hello world world" | sed -r 's/([a-z]+) \1/\1/g'
output: hello world
```

* sed -n, -quiet, --silent : suppress automatic printing of pattern space

## sed pattern flags
```
sed s/pattern/str/flags
```

| Command | Description |
|---------|-------------|
| `p`  | Print lines |
| `d`  | Delete lines |
| `w`  | Write to file |

* [^]*: matches everything except a space.

* The `s` command will not scan the newly created output.

* use "\(" and "\)" to mark each pattern, and use "\1" "\2" for matched patterns.

* Add a number after the substitution command to indicate you only want to match that particular pattern.

```
# delete second word /2
echo "one two three four" | sed -r 's/([a-z])* //2'
output: one three four

echo "one two three four" | sed -r 's/([a-z])* //2g'
output: one four
```

* The number flag can be any number from 1 to 512.

```
#Add a colon after 80th character in each line.
sed 's/./&:/80' <file >new
```
* Sed scripting follows Read, Execute, Print, Repeat (REPR) acronum.

* Usually when p is used you will use the -n option to suppress the the default printing that happens as part of the standard sed flow.

```
$ sed -n '2 p' /etc/passwd
$ sed -n '1, 4 p' /etc/passwd
$ sed -n '4, $ p' /etc/passwd
```

* `n,m` indicatates n through m lines
* `n,+m` means m lines starting with n
* `n~m` indicates that sed should start at nth line and pick up every mth line from there.

```
# print only odd numbered lines
$ sed -n '1~2 p' /etc/passwd

# print lines matching pattern "star"
$ sed -n '/star/ p' notes.txt

# print line matching "star" and 2 lines immediately
$ sed -n '/star/,+2 p' notes.txt

# delete only 2nd line
$ sed '2 d' news.txt

# delete 1 through 4
$ sed '1, 4 d' news.txt

# delete all empty lines from a file
$ sed '/^$/ d' test.txt

# delete all comment lines
$ sed '/^#/ d' test.txt
```

* sed's most powerful command is substitute command `s`.

```
# replace Manager with Director only on lines that contain 'Sales'
$ sed '/Sales/s/Manager/Director/' employee.txt

$ echo "aamir" | sed 's/a/A/'
output: Aamir
$ echo "aamir" | sed 's/a/A/g'
output: AAmir
```

| Substitute Flag | Desciption |
|-----------------|------------|
| `/g` | Global replacement |
| `/1, /2, /3` | Number Flags |
| `/p` | print flag |
| `/w` | write flag |
| `/i` | ignore case  (only GNU) |
| `/e` | execute command (only GNU) |

* Use number flag to specify occurence of original string. Only the n-th instance of original string will trigger the substitution. /11 will replace only the 11th occurrence of original string in a line.

```
echo "aamir" | sed 's/a/A/2'
output: aAmir
```

```
# print only line that was changed by substitute cmd
$ sed -n 's/aamir/Aamir/p' /etc/passwd
```

* `&` replaces it with whatever text matched the original-string or regular-expression.

## Regular Expression

| Meta-Character | Description |
|----------------|-------------|
| `^`            | Matches at the start of a line |
| `$`            | Matches the end of line |
| `.`            | Matches any character except the end of line char |
| '*`            | Zero or more occurrences of previous char |
| `\+`           | Matches one or more occurrence of previous char |
| `\?`           | Zero or one occurrences of previous char |
| `\`            | Search for special chac (ex: *, .) |
| [0-9]          | character class, Match only one out of several char |
| `|`            | Match either of two whole subexpressions |


```
$ sed -n '/101\|102/ p' test.txt
```

