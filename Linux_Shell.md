# Bash Shell

* Bash is "Bourne Again Shell". Bourne shell is developed by GNU.
* Different shells
    1. **sh** - Bourne Shell
    1. **bash** - Bourne Again Shell
    1. **csh** - C shell
    1. **tcsh** - Turbo C shell
    1. **ksh** - Korn shell

* `/etc/shells` file lists all available shells on the systems

```bash
$ cat /etc/shells
# /etc/shells: valid login shells
/bin/sh
/bin/bash
/bin/rbash
/bin/dash
```

* Last filed of every user record in `/etc/passwd` indicates default shell for that user.

* "#!" is called sha bang.

* `/bin/sh` is a symbolic link to `bash` shell in Linux.

* shell command line provides two modes to edit the commands in command line. 
    1. emacs mode
    1. vi mode

```bash
# show current options, default is emac mode
$ set | grep SHELLOPTS
SHELLOPTS=braceexpand:emacs:hashall:histexpand:history:interactive-comments:monitor

# change to vi mode
$ set -o vi
$ set | grep SHELLOPTS
SHELLOPTS=braceexpand:hashall:histexpand:history:interactive-comments:monitor:vi

# go back to emacs mode
$ set -o emacs
```

customize the readline default key bindings by adding your own
bindings in a `~/.inputrc` File. Global default file is `/etc/inputrc`.

### Symlink in Linux
* A symlink (also called a symbolic link) is a type of file in Linux that points to another file or a folder on your computer.

* A **hard link** cannot be created for a folder or file in a different file system.

* A symlink can be created using `ln` link command. By default `ln` create hard link. `-s` flag specifies that the link should be soft link.

```bash
ln -s <path to file/folder TO BE LINKED> <path to link TO BE CREATED>

# example
ln -s /home/aamir/flight_test_report.txt tp.txt
ln -s /home/aamir/flight_test_report.txt flight_reports/tp.txt

# symlink for folder
ln -s /home/aamir/workspace ws

# check if a file is symlink
$ ls -l host_ws
lrwxrwxrwx 1 aamir aamir 22 Mar  3 10:09 host_ws -> /home/aamir/workspace/

# Remove symlink
unlink <path-to-symlink>

# Can also use rm
rm <path-to-symlink>
```

The main benefit of `rm` over `unlink` is that we can remove multiple links at once.

```bash
# find broken symlink
find /home/aamir -xtype l

# delete broken symlink
find /home/aamir -xtype l -delete
```
