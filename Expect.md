# Expect Scripting Language

* Expect is a tool that help in automating scripts.

* Expect scripting language works by expecting input, then the Expect script will send the response without any user interaction.

```bash
$ apt-get install expect
```
### Expect commands

| Command   | Description |
| --------- | ----------- |
| spawn     | Starts a script or a program       |
| expect    | Waits for program output   |
| send      | Sends a reply to your program   |
| interact  | Allows to interact with the program   |

```bash
# disable timeout
set timeout -1
```

* Use `spawn` to run any program 

* To build an expect script automatically, use `autoexpect` command.

```
autoexpect ./questions.sh
```

* Use `set` command to define variables in expect scripts
```bash
set NAME Aamir
set COUNT 4
```

* To use command line arguments in expect scripts
```bash
set MYVAR [lindex $argv 0]
```

* Use conditional tests using braces
```bash
expect {

    "something" { send -- "send this\r" }

    "*another" { send -- "send another\r" }

}
```

### if else conditions
```bash
#!/usr/bin/expect -f

set NUM 1

if { $NUM < 5 } {

    puts "\Smaller than 5\n"

} elseif { $NUM > 5 } {

    puts "\Bigger than 5\n"

} else {

    puts "\Equals 5\n"

}
```

* NOTE: Opening brace must be on same line.

### while loops
```bash
#!/usr/bin/expect -f

set NUM 0

while { $NUM <= 5 } {

    puts "\nNumber is $NUM"

    set NUM [ expr $NUM + 1 ]

}

puts ""
```

### for loop
```bash
#!/usr/bin/expect -f

for {set NUM 0} {$NUM <= 5} {incr NUM} {

    puts "\nNUM = $NUM"

}

puts ""
```

### User-defined Functions

You can define a function using proc like this:

```bash
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
```

### Interact Command
* The interact command reverts the control to the keyboard.