#!/bin/bash

if [ $# -eq 0 ]; then
    # echo -n "Enter a number: "
    read -p "Enter a number: " num
else 
    num=$@
    echo "setting number to ${num}, ${1}"
fi

for n in $@
do
    echo "****** Table of $n ****** "
    for i in {1..10}
    do
        echo "$n x $i = $((n * i ))"
    done
    echo "##########################"
    echo ""
done

