#!/usr/bin/expect -f

set name [lindex $argv 0]
set favorite [lindex $argv 1]

# disable timeout
set timeout -1
spawn ./questions.sh
expect "Hello, who are you?\r"
send -- "$name\r"

expect "Can I ash you some questions?\r"
send -- "Sure\r"

expect "What is your favorite topic?\r"
send -- "$favorite\r"

expect eof