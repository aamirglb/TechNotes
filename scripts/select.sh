#!/bin/bash

# select option in Add Remove Append
# do
#     echo "Your selection is: $option"
# done

PS3="Enter your choice: "
select option in Add Remove Append 
do
    echo "Your selection is: $option"
    break
done
