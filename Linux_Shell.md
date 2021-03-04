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
### Secure Shell (SSH) server installation
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
### Secure Transfer Files using SCP
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
