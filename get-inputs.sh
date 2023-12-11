#! /usr/bin/bash

if [ ! -v INPUTS_DIR ]; then 
    INPUTS_DIR="inputs"
fi

if [ -z "$1" ]; then
cat <<-EOF
Fetch AoC input for DAYNUMBER using COOKIES
Usage: ./get-inputs.sh DAYNUMBER COOKIES
Note: COOKIES are stored to cookies.txt once inputted

EOF
exit 1
fi

COOKIES=
if [ -n "$2" ]; then
    echo "$2"
    COOKIES="$2"
    echo "$2" > "cookies.txt"
elif [ -r "cookies.txt" ]; then
    COOKIES=$(cat "cookies.txt")
    echo "$COOKIES"
else
cat <<-EOF
Fetch AoC input for DAYNUMBER using COOKIES
Usage: ./get-inputs.sh DAYNUMBER COOKIES
Note: COOKIES are stored to cookies.txt once inputted

EOF
exit 1
fi

wget --no-cookies --header="$COOKIES" "https://adventofcode.com/2023/day/$1/input" -O "$INPUTS_DIR/input$1.txt"
