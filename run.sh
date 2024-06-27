#!/bin/bash

mkdir -p temp

# only iterate over the files marked as unfinished
for file in $(comm -2 -3 all finished); do

	# convert the file
	./converter $file

	# concatenate the agent results
	cat $(fd . temp/ | sort -n -t/ -k2) > "$file".out

	# clear agent files for next iteration
	rm -rf temp
    mkdir temp

	# mark file as finished
	echo $file >> finished

done
