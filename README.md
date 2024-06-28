## Purpose

Convert files of format 0:u;0:l;1:u;1:d etc into:

ul\n
ud\n

## Steps

1. pre-process files using `./preprocess.sh` in working directory 
    1. removes " quotes
    2. adds a space between consecutive delimiters (,, -> , ,) to ensure `strtok` outputs something for every token
2. touch files `all` and `finished`
3. run `fd . $INPUT_DIR/ -t f -e .csv > all` so that the below script can be stopped and started as needed
4. run `./run.sh` which runs `./converter` $file for all files in `all` and not `finished`
5. RUN LENGTH ENCODE
6. ADD HEADERS BACK
7. 
