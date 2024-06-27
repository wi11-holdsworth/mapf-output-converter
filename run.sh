#!/bin/bash

# the file we want to run this on
if [ -z "$1" ]; then
  echo "Usage: $0 directory"
  exit 1
fi

# where the results are going
mkdir -p outputs

# for each file in a directory
for file in "$1"*
do
    # create a folder to store all the outputs
    mkdir temp

    # run the script to generate the outputs
    ./converter "$file"

    # combine all the files in the output folder into one file of the same name
    # https://unix.stackexchange.com/questions/118244/fastest-way-to-concatenate-files
    cd outputs
    fd . -d 1 -t f '*' |
        sort -z |
        xargs -0 cat -- >> "$(basename "$file").out"
    mv "$(basename $file).out" ../
    cd ..

    # delete the intermediate folder
    rm -rf outputs
done 
