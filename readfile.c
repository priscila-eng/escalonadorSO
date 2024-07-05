#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readfile.h"

#define MAX_LINE_LENGTH 100

Process* read_input_file(const char *filename, int *num_processes) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erro ao abrir arquivo");
        return NULL;
    }

    char line[MAX_LINE_LENGTH];
    Process *processes = NULL;
    *num_processes = 0;

    while (fgets(line, sizeof(line), file)) {
        (*num_processes)++;
        processes = realloc(processes, (*num_processes) * sizeof(Process));
        if (!processes) {
            perror("Erro ao realocar memória");
            exit(EXIT_FAILURE);
        }


        Process *current_process = &processes[*num_processes - 1];
        // lendo id comando e dependencias
        char dependencies_str[MAX_LINE_LENGTH];
        sscanf(line, "%d %s %s", &current_process->id, current_process->command, dependencies_str);

        // tirando a virgula e #
        current_process->num_dependencies = 0;
        char *token = strtok(dependencies_str, ",");
        while (token && strcmp(token, "#") != 0) {
            current_process->dependencies[current_process->num_dependencies++] = atoi(token);
            token = strtok(NULL, ",");
        }
        // printando para testar se esta lendo corretamente
        printf("id:%d comando:%s dependências:", current_process->id, current_process->command);
        for (int j = 0; j < current_process->num_dependencies; ++j) {
            printf(" %d", current_process->dependencies[j]);
        }
        printf("\n");
    }

    fclose(file);
    return processes;
}
