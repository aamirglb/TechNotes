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

