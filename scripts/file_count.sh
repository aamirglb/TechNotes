#!/bin/bash
cd ~
files=0
dir=0
for i in *
do
    if [ -f $i ]; then
        ((files++))
    elif [ -d $i ]; then
        ((dir++))
    fi
done

echo "Total Files: ${files}" 
echo "Total Directories: ${dir}" 