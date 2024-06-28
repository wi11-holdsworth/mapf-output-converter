import sys


def decode(line: str, outfile) -> str:
    num = ""
    for char in line:
        if char.isdigit():
            num += str(char)
            continue

        if num == "":
            outfile.write(char)
            continue

        if char == "w":
            outfile.write(num + char)
        else:
            outfile.write(char * int(num))
        
        num = ""
        

with open(sys.argv[1], "r") as infile, open(sys.argv[1] + '.pyout', "w") as outfile:
    for line in infile.readlines():
        decode(line, outfile)

