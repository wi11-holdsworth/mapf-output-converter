#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_MAX (2 << 7) - 2 // ext4 file path max size
#define HEADER_MAX 1000
#define RECORD_MAX 260000000 // wc -c over all csvs
#define NUM_TOKS 5
#define LINE_MAX 290000

int main(int argc, char **argv) {

    if (argc < 3) {
        fprintf(stderr, "expect ./formatter {CSV_PATH} {RLE_PATH}");
        return EXIT_FAILURE;
    }

    // get input file names
    char *in_csv_path = argv[1], *in_rle_path = argv[2];
    
    // open csv file as i1, rle as i2, and new file as o

    FILE *in_csv = fopen(in_csv_path, "r");
    
    char out_file_path[FILE_MAX];
    strcpy(out_file_path, in_csv_path);
    strcat(out_file_path, ".fmt");
    FILE *out = fopen(out_file_path, "w");

    // write header line of i1 to o

    char header[HEADER_MAX];
    fgets(header, HEADER_MAX, in_csv);
    fprintf(out, header);

    // read first 5 tokens of i1 and write to o

    char *record = (char *) malloc(sizeof(char) * RECORD_MAX + 1);
    fgets(record, RECORD_MAX, in_csv);
    fprintf(out, "%s,", strtok(record, ","));

    for (int i = 0; i < NUM_TOKS; i++) {
        fprintf(out, "%s,", strtok(NULL, ","));
    }

    fclose(in_csv);

    // read first line of i2 and append to o

    FILE *in_rle = fopen(in_rle_path, "r");

    char line[LINE_MAX];

    while ((fgets(line, LINE_MAX, in_rle) != NULL)) {
        fprintf(out, "%s", line);
    }

    // read all lines of i2 and append to o

    fclose(in_rle);
    fclose(out);

    return EXIT_SUCCESS;
}