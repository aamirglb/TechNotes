# Linux System Programming

* Typical services of any operating system are executing a new program, opening a file, reading a file, allocating a region of memory, getting the current time of day, and so on.

* The interface to the kernel is a layer of software called the _system calls_. Libraries of common functions are built on top of the system call interface.

* Linux is the kernel used by the GNU operating system.

* /etc/passwd. composed of seven colon-separated fields: 
`sar:x:205:105:Stephen Rago:/home/sar:/bin/ksh`

1. the login name, 
1. encrypted password, 
1. numeric user ID (205), 
1. numeric group ID (105), 
1. a comment field, 
1. home directory (/home/sar), and 
1. shell program (/bin/ksh).

* A `shell` is a command-line interpreter that reads user input and executes commands.

* The Bourne-again shell is the GNU shell provided with all Linux systems.

* A directory is a file that contains directory entries.

* The `stat` and `fstat` functions return a structure of information containing all the attributes of a file.

* The only two characters that cannot appear in a filename are the _slash character_ (/) and the _null_ character.

* In the root directory, (..) dot-dot is the same as dot.

* A process can change its working directory with the chdir function.

* Unbuffered I/O is provided by the functions `open`, `read`, `write`, `lseek`, and `close`.

* The standard I/O functions such as `printf`, `fgets` provide a buffered interface to the unbuffered I/O functions. Using standard I/O relieves us from having to choose optimal buffer sizes.

* The `fgets` function reads an entire line. The `read` function, in contrast, reads a specified number of bytes.

* An executing instance of a program is called a `process`. The UNIX System guarantees that every process has a unique numeric identifier
called the process ID.

* There are three primary functions for process control: `fork`, `exec`, and `waitpid`. The exec function has seven variants.

* each line returned by `fgets` is terminated with a newline character,
followed by a null byte.
```c
if (buf[strlen(buf) - 1] == '\n')
    buf[strlen(buf) - 1] = 0;
```

* `execlp` function wants a null-terminated argument, not a newline-terminated argument.

* `fork` returns the non-negative process ID of the new child process to the parent, and returns 0 to the child.

* The combination of fork followed by exec is called spawning a new process on some operating systems.

* All threads within a process share the same address space, file descriptors, stacks, and process-related attributes. Each thread executes on its own stack, although any thread can access the stacks of other threads in the same process.

* The file `<errno.h>` defines the symbol errno and constants for each value that errno can assume.

* Two functions are defined by the C standard to help with printing error messages.

```c
#include <string.h>
// map errnum to error message
char *strerror(int errnum);

#include <stdio.h>
// produce error message based on current errno
void perror(const char *msg);
```

* Groups are normally used to collect users together into projects or departments. This allows the sharing of resources, such as files, among members of the same group.

* `/etc/group` file maps group names into numeric group IDs.

* functions `getuid` and `getgid` return the user ID and the group ID.

* Signals are a technique used to notify a process that some condition has occurred. The process has three choices for dealing with the
signal.
1. Ignore the signal
1. Let the default action occur
1. Provide a function that is called when the signal occurs 