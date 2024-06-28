#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define FILE_MAX 255 // specified by ext4 filesystem
#define LINE_MAX 470000


/*
    run-length encodes input `str`
    appends to `outfile`
*/
void encode(char *str, FILE *outfile);


int main(int argc, char **argv) {

    // ensure filepath is specified
    if (argc < 2) {
        fprintf(stderr, "Specify a filepath as $1");
        return EXIT_FAILURE;
    }

    char *infile_path = argv[1];

    // open i/o files
    FILE *infile = fopen(infile_path, "r");

    char outfile_path[FILE_MAX];
    strcat(outfile_path, infile_path);
    strcat(outfile_path, ".e");

    FILE *outfile = fopen(outfile_path, "w");

    // iterate over lines

    char line[LINE_MAX + 1];

    while ((fgets(line, LINE_MAX + 1, infile)) != NULL) {
        encode(line, outfile);
    }

    // close files to write

    fclose(infile);
    fclose(outfile);

    return EXIT_SUCCESS;
}


void encode(char *str, FILE *outfile) {
    int i = 0;
    char c;
    while ((c = str[i]) != '\0') {
        
        // waits (w) are pre-encoded
        if (isdigit(c)) {
            fputc(c, outfile);
            i++;
            continue;
        }

        // find number of consecutive actions
        int j = 0;
        while (c == str[i + j]) {
            j++;
        }

        // based on "number of chars seen"
        switch (j) {
            // only one, just write char
            case 1:
                fputc(c, outfile);
                break;
            // two or more, write {num}{char}
            default:
                fprintf(outfile, "%d%c", j, c);
                break;
        }

        // jump over processed chars
        i += j;

    }
}
