#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FILE_MAX (2 << 7) - 2 // ext4 file path max size
#define HEADER_MAX 1000
#define LINE_MAX 290000
#define NUM_TOKS 6

int main(int argc, char const *argv[]) {
    int num_agents, i, j;
    char file_path[FILE_MAX], 
         header[HEADER_MAX], 
         record[LINE_MAX], 
         first_half[HEADER_MAX],
         second_half[LINE_MAX];
    
    if (argc < 2) {
        fprintf(stderr, "specify file to impute");
        return EXIT_FAILURE;
    }

    // safely create new file

    strncpy(file_path, argv[1], sizeof(file_path));
    strncat(file_path, ".imp", sizeof(file_path) - strlen(file_path));

    FILE *in = fopen(argv[1], "r"), *out = fopen(file_path, "w");

    // skip over header

    fgets(header, sizeof(header), in);
    fprintf(out, "%s", header);

    // retrieve relevant fields

    fgets(record, sizeof(record), in);
    sscanf(record, "%*[^,],%*[^,],%*[^,],%d", &num_agents);
    rewind(in);
    fgets(header, sizeof(header), in);

    for (i = 1; i <= num_agents; i++) {
        for (j = 0; j < i; j++) {
            fgets(record, sizeof(record), in);
            // extract data before num_agents
            sscanf(record, "%[^,],%[^,],%[^,],", first_half, 
                                                first_half + strlen(first_half),
                                                first_half + strlen(first_half));
            // extract data after
            sscanf(record, "%*[^,],%*[^,],%*[^,],%*[^,],%s", second_half);
            fprintf(out, "%s%d%s", first_half, i, second_half);
        }
        rewind(in);
        fgets(header, sizeof(header), in);
    }

    fclose(in);
    fclose(out);

    return EXIT_SUCCESS;
}
