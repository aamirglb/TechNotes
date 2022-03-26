#!/usr/bin/env bash

# Demonstrate Internal Field Separator (IFS) use
names=(
     "Mohammad Aamir Ali"
     "Mohammad Adam Ali"
     "Mohammad Umar"
     "Farooq Aadil"
)
  
echo "With default IFS value..."
for name in ${names[@]}; do
	echo "$name"
done

echo ""
echo "With strict-mode IFS value..."
IFS=$'\n\t'
for name in ${names[@]}; do
	echo "$name"
done

