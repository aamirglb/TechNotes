#!/usr/bin/expect -f
set timeout -1

spawn ./ques2.sh
expect "Hello, who are you?\r"
send -- "Aamir Ali\r"

expect "*password?\r"
interact ++ return
send "\r"

expect "*topic?\r"
send -- "Technology\r"

expect eof
