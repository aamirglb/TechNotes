#!/usr/bin/expect -f

proc myfunc { TOTAL } {
    set TOTAL [expr $TOTAL + 1]
    return "$TOTAL"
}

set NUM 0

while {$NUM <= 5} {
    puts "\nNumber $NUM"
    set NUM [myfunc $NUM]
}

puts ""