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

| Flag | Desciption |
|------|------------|
| `/g` | Global replacement |


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
