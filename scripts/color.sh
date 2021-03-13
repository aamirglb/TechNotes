#!/bin/bash
# color codes
BLUE="\033[0;34m"
DARK_RED="\033[1;31m"
GREEN="\033[0;32m"
NO_COLOR="\033[0m"

shell="Bash"
echo -e "The best shell is: $shell"
echo -e "The best shell is: $BLUE$shell$NO_COLOR"
echo -e "The best shell is: $DARK_RED$shell$NO_COLOR"
echo -e "The best shell is: $GREEN$shell$NO_COLOR"

echo ""
echo "tput Example"

echo -e "The best shell is [normal]: $shell"
echo -e "The best shell is [bold]  : `tput bold`$shell`tput sgr0`"
echo -e "The best shell is [background]: `tput setb 4`$shell`tput setb 0`"
echo -e "The best shell is [underline]: `tput smul`$shell`tput rmul`"