#!/bin/bash

# retrieve all raw csv files
fd . ../sources/extracted/ -t f -e .csv > all
cat all | sort > a 
mv a all

touch finished

mkdir -p temp

# only iterate over the files marked as unfinished
for file in $(comm -2 -3 all finished); do

	# convert the file
	./converter $file

	# concatenate the agent results
	cat $(fd . temp/ | sort -n -t/ -k2) > "$file".converted

	# clear agent files for next iteration
	rm temp/*
	
	# mark file as finished
	echo $file >> finished

done

# clean up working dir
rm -rf temp
rm all finished
