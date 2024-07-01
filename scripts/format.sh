#!/bin/sh

touch finished
fd . raw/unzipped/ -t f -e .csv > all
cat all | sort > a 
mv a all

for file in $(cat all) ; do 

    echo "$file"
    
    # extract from csv file and paste RLE data in
    # output is .csv.fmt file
    ./bin/formatter $file "$file.out.e"

    # show diff 
    diff "$file.csv.fmt" "$file"

done
