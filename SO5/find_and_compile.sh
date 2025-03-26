#!/bin/bash


if [ $# -eq 1 ]; then
    max_depth=$1
else
    echo "Introduceți adâncimea maximă :"
    read max_depth
fi

if ! [[ "$max_depth" =~ ^[0-9]+$ ]]; then
    echo "Adâncimea trebuie să fie un nr."
    exit 1
fi


find ~/ -maxdepth $max_depth -type f -mtime -28d > file_list.txt


if [ $? -ne 0 ]; then
    echo "Command find has failed!" >&2
    exit 1
fi


while IFS= read -r file; do
  
    if file "$file" | grep -q "C source"; then
      
        gcc "$file" -o "${file%.*}"
        if [ $? -eq 0 ]; then
            echo "$file -> Compilat ok!"
        else
            echo "$file -> Eroare la compilare!"
        fi
    else
        
        last_modified=$(stat -c %y "$file")
        echo "$last_modified $file"
    fi
done < file_list.txt

