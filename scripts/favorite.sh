#!/bin/bash
let number=$RANDOM

if [ $number -gt 25000 ]; then
    echo "What is your favorite topics?"
else
    echo "What is your favorite language?"
fi

read $REPLY
