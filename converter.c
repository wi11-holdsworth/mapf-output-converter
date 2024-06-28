#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define CMD_LEN 1000
#define COMMAND "/usr/bin/wc -m "

#define HEADER_LEN 1000
#define AGENT_I 3
#define SOLUTION_I 6

#define ACTION_LEN 10

// required by -Werror/-Wpedantic

FILE *popen(const char *command, const char *mode);

int main(int argc, char **argv) {

    // ensure path to csv file is specified
    
    if (argc < 2) {
        fprintf(stderr, "Missing file path\n");
        return EXIT_FAILURE;
    }
    
    // now get it from argv and open for reading

    char *file = argv[1];
    FILE *fp = fopen(file, "r");

    // we need number of chars in file to know how much
    // memory to allocate for the record
    
    char cmd[CMD_LEN + 1];
    strcpy(cmd, COMMAND);
    strcat(cmd, file);

    FILE *fp_wc = popen(cmd, "r");

    int len;
    fscanf(fp_wc, "%d", &len);

    // skip over the header

    char header[HEADER_LEN + 1];
    fgets(header, HEADER_LEN, fp);

    // allocate memory for the record 

    char *record = (char *) malloc(len * sizeof(char) + 1);
    fgets(record, len, fp);

    // initialise tokeniser and ignore instance name

    char *token;
    int num_agents = 0;
    strtok(record, ",");
    
    // extract number of agents and solution string from the record

    for (int i = 1; i <= SOLUTION_I; i++) {
        token = strtok(NULL, ",");

        if (i == AGENT_I) {
            num_agents = atoi(token);
        }
    }

    // open the same number of files as there are agents in results folder for
    // writing to

    FILE **agent_files = (FILE **) malloc(sizeof(FILE*) * num_agents);
    assert(agent_files);
    int *time_of_last_move = (int *) malloc(sizeof(int) * num_agents);
    assert(time_of_last_move);
    char file_path[FILENAME_MAX]; 

    for (int i = 0; i < num_agents; i++) {
        sprintf(file_path, "temp/%d", i);
        agent_files[i] = fopen(file_path, "w");
    }

    // iterate through the solution and write to the file containing the correct
    // agent

    // initialise action tokeniser and extract first action...
    
    char *first_action = strtok(token, ";"), move;
    int agent_num;

    sscanf(first_action, "%d:%c", &agent_num, &move);
    fprintf(agent_files[agent_num], "%c", move);

    // ...now extract the rest of them...

    char *action;
    int t = 1, num_waits = 1;
    while ((action = strtok(NULL, ";")) != NULL) {
        sscanf(action, "%d:%c", &agent_num, &move);

        num_waits = t - time_of_last_move[agent_num] - 1;
        
        switch (num_waits) {
            // moved last timestep
            case 0:
                fprintf(agent_files[agent_num], "%c", move);
                break;
            // moved one timestep ago, store w not 1w
            case 1:
                fprintf(agent_files[agent_num], "w%c", move);
                break;
            // moved some number of timesteps ago, store the number of them
            default:
                fprintf(agent_files[agent_num], "%dw%c", num_waits, move);
                break;
        }

        fprintf(agent_files[agent_num], "%c", move);

        time_of_last_move[agent_num] = t;
        t++;
    }

    // ...and close all the files

    for (int i = 0; i < num_agents; i++) {
        fprintf(agent_files[i], "%c", '\n');
        fclose(agent_files[i]);
    }

    fclose(fp);

    return EXIT_SUCCESS;
}
