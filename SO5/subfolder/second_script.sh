#!/bin/bash


if [ ! -d "$1" ]; then
    echo "directorul nu este valid." >&2
    exit 1
fi


total_bash_scripts=0


for file in "$1"/*; do
    if [ -d "$file" ]; then
       
        ./subfolder/second_script.sh "$file"
    elif [ -f "$file" ]; then
       
        if file "$file" | grep -q "Bourne-Again shell script"; then
           
            sha256sum "$file"
            let total_bash_scripts+=1
        else
           
            num_newlines=$(grep -o $'\n' "$file" | wc -l)
            echo "$file: $num_newlines"
        fi
    fi
done


if [ $total_bash_scripts -gt 0 ]; then
    echo "Nr total de scripturi găsite: $total_bash_scripts"
    exit 0
else
    exit -1
fi

