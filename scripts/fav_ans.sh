#!/usr/bin/expect -f

set timeout -1

spawn ./favorite.sh

expect {
    "*topic?" { send -- "Programming\r" }
    "*language?" { send -- "C++\r" }
}
expect eof
