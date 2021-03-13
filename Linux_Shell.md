# Bash Shell

<font size=4>
Table Of Contents <br>

[1. Symbolic Links](#<font-color="orange">-1.-symbolic-links-</font>) <br>
[2. Secure Shell (SSH)](#<font-color="orange">-2.-secure-shell-(ssh)-server-installation</font>) <br>
[3. Using SCP](#<font-color="orange">-3.-secure-transfer-files-using-scp-</font>) <br>
[4. find Command](#<font-color="orange">4.-find-command</font>) <br>
</font>

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

Search command history by pressing **Ctrl+R**
Repeat previous command: **!!** or **!-1**
In emacs mode, press **Ctlr+P**
Execute command that starts with specific word: **!<word-start>**
Clear history: **history -c**
Get command from previous argument to current command: **!!:$**
Get first argument from previous command: **!^**
Substitue specific argument: **!cp:2**

```bash
# display timestamp with history command
$ export HISTTIMEFORMAT='%F %T '
$ history | more

# control history size is HISTSIZE in ~/.bash_profile
HISTSIZE=450
HISTFILESIZE=450

# change history file name using HISTFILE in ~/.bash_profile
HISTFILE=/root/.mycommands

# Eliminate consecutive repeated history entires
$ export HISTCONTROL=ignoredups

# Erase duplicate across history
$ export HISTCONTROL=erasedups

# force history not to remember command
$ export HISTCONTROL=ignorespace

# Ignore specific command from history
$ export HISTIGNORE="pwd:ls:ls -ltr:"

# disable history
$ export HISTSIZE=0
```

By default history is stored in `~/.bash_history`

| Command       | Description |
| ------------- | ----------- |
| !!            | Repeats the previous command       |
| !10           | Repeat the 10 th command from the history        |
| !-2           | Repeat the 2 nd command (from the last) from the history        |
| !string       | Repeat the command that starts with “string” from the history        |
| !?string      | Repeat the command that contains the word “string” from the history        |
| ^str1^str2^   | Substitute str1 in the previous command with str2 and execute it        |
| !!:$          | Gets the last argument from the previous command        |
| !string:n     | Gets the nth argument from the command that starts with “string” from the history.        |

```bash
# find all files that changed within last 24 hours
$ find / -ctime -1 > /tmp/changed-file-list.txt &

# suspend current job
$ find / -ctime -1 > /tmp/changed-file-list.txt
$ bg
$ %2 &

# view all background jobs
$ jobs

# move background job to foreground
$ fg

# kill background job using kill %job-number
$ kill %2

# username - hostname - full path of CWD
$ export PS1="\u@\h \w$ "

$ export PS2="continue-> "
```

```bash
# dark blue prompt
$ export PS1="\e[1;34m\u@\h \w$ \e[m"
```
* \e[ - indicates begining of color prompt
* x;ym - indicate color code
* \e[m - indicate end of color prompt

Color codes:
* Black 0;30
* Blue  0;34
* Green 0;32
* Cyan  0;36
* Red   0;31
* Purple 0;35
* Brown  0;33
Replace 0 with 1 for dark color

Another way is to use following color codes:
* Black \033[30m
* Blue \033[34m
* Green \033[32m
* Cyan \033[36m
* Red \033[31m
* Purple \033[35m
* Brown \033[33m

Sequence of execution of bash startup files
* `/etc/profile` -> execute next step
* `~/.bash_profile` -> end
* `~/.bash_login` -> end
* `~/.profile` -> end

`~/.bashrc` is not directly executed by bash. However, `~/.bash_profile` typically execute `~/.bashrc`.

```bash
if [ -f ~/.bashrc ]; then
    . ~/.bashrc
fi
```

when concatenate the value of a variable with another value, use the `${}` referencing form.

`/etc/profile` checks all `*.sh` file under `/etc/profile.d` and executes them.

"$VAR" - If quoted, it is considered as one word
 $VAR  - iF not quoted, it will be split into multiple words

```bash
states="CA NY UT TX"
for i in $states; do
    echo $i
done
Output
------
CA
NY
UT

for i in "$states"; do
    echo $i
done
Output
------
CA NY UT TX
 ``` 

 * Executing a shell script like `./script.sh` will spawn a new bash shell and it executes the script.

 * Positional parameters are of the form `$1` to `$N`. When N is more than single digit, it must be enclosed in braces like `${N}`.
 $1, $2 ... ${10}, ${11}

| Command   | Description |
| --------- | ----------- |
| $0        | Script Name       |
| $1        | First parameter   |
| $2        | Second parameter  |
| $*        | All parameters    |
| $@        | All parameters    |
| $#        | Total number of parameters |
| $$        | PID of the shell |
| $!        | PID of most recently executed background process |
| $?        | Exit status of most recently executed command |
| $-        | All options set using bash set builtin command |
| $_        | Gives last argument to previous command. At the shell startup, it gives absolute filename of the shell script being executed. |

```bash
# display all parameters using following single line code-snippet
printf '"%b"\n' "$@" | cat -n
```

`$*` and `$@` are same except when double quoted.
"$*" is converted to "${1}x${2}x${3}x..."

```bash
# get range of parameters ${@:$start:$count}
$ start=2
$ count=3
$ ${@:$start:$count}
$ for i in "${@:$start:$count}"; do
$    echo $i
$ done
```

* `shift` command moves the arguments (positional parameters) to the left by n positions. If no argument is specified, the argument will be moved by 1.

* `echo -n` Do not output trailing newline
* `echo -e` Enable interpretation of backslash escapes

* single quotes '', will not expand variable values, i.e $ symbol will be treated as a literal value.

* Declare variables using `typeset` and `declare` builtins. `typeset` is deprecated.

```bash
# declare integer
$ declare -i variablename

# readonly variable
$ declare -r variablename

# array
$ declare -a array

# associative array
$ declare -A array
```

* Inside shell script use `let` for arithmetic expressions.
```bash
# both are same, no need to have $ on RHS
let total=total+3
let total=$total+3
```

* `((expression))` tells bash to evaluate contents as an expression. This is very much like `let`. However within (()), you can use spaces. (()) allows pre- and post- increment/decrement:
```bash
$ ((total++))
$ ((total--))
$ ((++total))
```

* `expr` is a unix command (not a bash builtin) which can be used to evaluate an expression.

* Bash does not understand floating point arithmetic. It treats numbers containing a decimal point as strings.

### Number Comparison

| Operator   | Description |
| ---------  | ----------- |
| -eq        | Equal to       |
| -ne        | Not Equal to   |
| -gt        | Greater than       |
| -ge        | Greater than or equal to   |
| -lt        | Less than       |
| -le        | Less than or equal to   |

### String Comparison
| Operator   | Description |
| ---------  | ----------- |
| =        | Equal to       |
| ==        | Equal to   |
| !=        | Not Equal to       |
| <        |    |
| >        |        |
| -z        | Zero byte? Is string empty?   |
| -n        | Not empty?   |


```
if [ conditional express ]; then
    statement1
    statement2
else
    statement3
fi

if [ conditional express ]; then
    statement1
    statement2
elif [ conditional expression2 ]; then
    statement3
else
    statement4
fi
```

* In a shell
    * 0 means last command executed successfully
    * 1 means last command execution failed

### File Test Operators
| Operator   | Description |
| ---------  | ----------- |
| -e        | File exists       |
| -f        | It's a regular file   |
| -d        | It's a directory       |
| -b        | It's a block device   |
| -c        | It's a character device       |
| -s        | File is not empty   |
| -p        | It's a pipe   |
| -S        | It's a socket      |
| -h        | It's a symbolic link   |
| -t        | Check if FD is opened in terminal       |
| -r        | File read permission   |
| -w        |        |
| -x        |  |
| -u        | suid set on the file   |
| -g        | sgid set on the file       |
| -k        |  Sticky bit set on file  |
| -O        | You own the file       |
| -G        | File group id and my group id are same   |
| -N        | fiel got modified since last read   |
| f1 -nt f2        | f1 newer than f2       |
| f1 -ot f2        | f1 is older than f2   |
| f1 -ef f2        | Both files are hard linked to same file       |

* **-a** does 'and' comparison inside conditional expression
* **-o** does 'or' comparison inside conditional expression
* **!** is a logical NOT
* **&&** is used to execute sequence of commands only when previous command is successfully executed with a return status of zero.
* **||** execute exactly one command in a sequence of commands.

```bash
if [ $total -ge 50 -a $total -le 100 ]; then
if [ "$input" == "apple" -o "$input" == "orange" ]; then

passwd=/etc/passwd
group=/etc/group

if [ -f $passwd ] && x=`wc -l $passwd|awk '{print $1}'` && \
   [ -f $group ] && y=`wc -l $group|awk '{print $1}'` && let total=$x+$y
then 
    echo "Total Lines in $passwd and $group files are: $total"
fi

[ -f /.datafile ] || touch /.datafile
```

* [[]] - Extended Test Command is an advanced variation of []
    * Allows pattern matching
    * =~ regular expresison matching
```bash
    if [[ $name ~= ^b ]]; 
```

```bash
for varname in list
do
    commands ##Body of the loop
done

# loop through files and directories
cd ~
for item in *
do
    echo "Item $((i++)) : $item"
done
```

* If list is missing from for statement, bash uses positional parameters that were passed into the shell.

```bash
# Use range of numbers using brace expansion
for num in {1..10}

# Range of number with increment
for num in {1..10..2}

# Bash for loop using C syntax
for (( expr1; expr2; expr3 ))
do
    commands
done
```

```bash
# While loop
while expression
do
    commands
done

# until loop
until expression
do
    commands #body of the loop
done
```

* bash until loop is useful as a way of waiting for certain events to occur.

```bash
case var in
pattern1 )
    command1
    command2
    ...
    ;;
pattern2 )
    command3
    command4
    ...
    ;;
esac
```
* Each set of command in case statement should end with two semi-colons (;;)

* case terminator can be `;;`, `;&` and `;;&`

* Bash has a formatted print command `printf`

```bash
read -a arrayname
read -p prompt
read -s # This doesn't echo the value as you enter
read -t 10 # read waits for 10 sec and times out
read -N 5  # return after reading exactly 5 char
read -r    # read \ literally 
read       # if no variable, store value in $REPLY internal variable
```

* The bash shell has a hash table where the commands you execute are stored. When you execute the same command next time, bash won't search the PATH variable, instead it will pick up the command from the hash table and run it.

* Use `type` command to identify the type of a particular command. A command can be an alias, a shell builtin, a shell keyword, or an external program.

```bash
type lw
type pwd
```

* `ulimit` control the amount of resources that can be assigned to processes that are started by bash shell.
```bash
# view all current limits
ulimit -a
```

* `shopt` stands for shell options. View all shell options and their current status.

---
## <font color="orange"> 1. Symbolic Links </font>
---

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
---
## <font color="orange"> 2. Secure Shell (SSH) Server Installation</font>
---

SSH is a cryptographic network protocol used for a secure connection between a client and a server.

```bash
$ sudo apt update
$ sudo apt install openssh-server -y

# verify that installation is successful
$ sudo systemctl status ssh

# Allow Uncomplicated Firewall(UFW) firewall 
$ sudo ufw allow ssh

# connect to ssh server
$ ssh user_name@ip_address
```

To determine the public IP address of the machine you’re trying to SSH to, simply visit the following URL: `https://api.ipify.org`

```bash
# To disable SSH
$ sudo systemctl stop ssh

# To start again
$ sudo systemctl start ssh
```
OpenSSH client-side configuration file is `config` is stored in `.ssh` directory under user's home directory.
The `config` file must be readable and writable only by the user and not accessible by others:

```bash
$ touch ~/.ssh/config
$ chmod 600 ~/.ssh/config
```
---
## <font color="orange"> 3. Secure Transfer Files Using SCP </font>
---

SCP (secure copy) allows to securely copy files and directories between two locations.

```bash
scp [options] source destination
```

SCP options <br>
`-P`: Remote host ssh port
`-p`: Preserve file modification and access time
`-q`: Suppress progress meter and non-error messages
`-C`: Force `scp` to compress the data
`-r`: copy directories recursively

```bash
# Copy local file to remote
$ scp file.txt remote_username@10.10.0.2:/remote/directory

# Save file with different name
$ scp file.txt remote_username@10.10.0.2:/remote/directory/newfilename.txt

# if remote is listening on different port
$ scp -P 2322 file.txt remote_username@10.10.0.2:/remote/directory

# Copy dirctory
$ scp -r /local/directory remote_username@10.10.0.2:/remote/directory

# Copy remote file to local system
$ scp remote_username@10.10.0.2:/remote/file.txt /local/directory

# Copy file between two remote systems
$ scp user1@host1.com:/files/file.txt user2@host2.com:/files
```

---
## <font color="orange">4. find command</font>
---

* `find` command can be used to find files by **permission, users, groups, file type, date, size** and other possible criteria.

```bash
# find files in current working directory
$ find . -name test.txt
$ find /home -name test.txt

# ignore case
$ find /home -iname test.txt

# find directories
$ find / -type d -name Test

# find files
$ find . -type f -name test.cpp

# find all cpp files
$ find . -type f -name "*.cpp"

# find file with 777 permission
$ find . -type f -perm 0777 -print

# without 777 permission 
$ find / -type f ! -perm 777

# find read only files
$ find . -perm /u=r

# find all executable file
$ find . -perm /a=x

# find all 777 and chmod to 644
$ find / -type f -perm 0777 -print -exec chmod 644 {} \;
```
TBD: https://www.tecmint.com/35-practical-examples-of-linux-find-command/
What are files with SGID bit and Sticky bit?? SUID files