#!/bin/sh

DIR_PATH=$1
PATTERN=$2

if [ -z "$DIR_PATH" ] || [ -z "$PATTERN" ]
then 
    echo 'USAGE pathByPattern [PATH] [PATTERN]'
    exit 1
else 
    ls -a "$DIR_PATH" | readlink -f $(grep "$PATTERN") > output.txt
    echo 'Check result in output.txt'
fi
