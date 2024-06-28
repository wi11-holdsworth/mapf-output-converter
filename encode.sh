#!/bin/bash

# only iterate over the files marked as unfinished
for file in $(comm -2 -3 all finished); do

	# convert the file
	./encoder $file
    
    # and get rid of the old one
    rm $file
	
	# mark file as finished
	echo $file >> finished

done
