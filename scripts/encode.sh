#!/bin/bash

# retrieve all converted files
fd . ../sources/extracted/ -t f -e .csv.cvrt > all
cat all | sort > a 
mv a all
touch finished

# only iterate over the files marked as unfinished
for file in $(comm -2 -3 all finished); do

	# apply run length encoding to the file 
	./encoder $file
	
	# mark file as finished
	echo $file >> finished

done

rm all finished
