#!/usr/bin/expect -f

# disable timeout
set timeout -1
spawn ./questions.sh
expect "Hello, who are you?\r"
send -- "Aamir Ali\r"

expect "Can I ash you some questions?\r"
send -- "Sure\r"

expect "What is your favorite topic?\r"
send -- "Technology\r"

expect eof