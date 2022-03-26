#!/usr/bin/env bash

# Demonstrate Internal Field Separator (IFS) use

IFS=$' '
items="a b c"

for x in $items; do
	echo "$x"
done

IFS=$'\n'
for y in $items; do
	echo $y
done
