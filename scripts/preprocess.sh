#!/bin/bash

# Use find command to recursively list all files
find "$1" -type f | while IFS= read -r file; do
    echo "$file"
    
    # remove all double quotes
    sd "\"" "" "$file"
    
    # put an empty space between consecutive delimiters
    sd ",," ", ," "$file"

done
