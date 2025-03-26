#!/bin/bash


if [ ! -d "$1" ]; then
    echo "Directorul $1 nu există." >&2
    exit 1
elif [ ! -r "$1" ] || [ ! -x "$1" ]; then
    echo "Nu ai permisiuni ." >&2
    exit 2
else
 
    ./subfolder/second_script.sh "$1"
    exit_code=$?
    exit $exit_code
fi

