#!/bin/bash

#Assignment #1 part 2.

writefile=$1
writestr=$2

# Handle arguments missing, print out information about them

if [ -z $writefile ] || [ -z $writestr ]
then
    echo You did not provide a path to a file, or a string to write to said path
    exit 1
fi 

# Change from -d to -f since we are looking for filepath validation not directory
if [ ! -f $writefile ]
then
    echo File "$writefile" does not exist, creating and writing to it...
    mkdir -p "$(dirname "$writefile")"
    echo "$writestr" > "$writefile"
fi

# Write/overwrite to existing path with the intended string.
# NOTE: echo is used to produce the string, using the raw variable will not work.
# > Overwrites to that file path, it also implicitly creates the file, which may make the code from lines 16-20 duplicated code, but at least I notify the user.

echo "$writestr" > "$writefile"

# Most tests create a file, in case the file already exists but needs overwriting this one will write.

