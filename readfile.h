#ifndef READFILE_H
#define READFILE_H

#define MAX_DEPENDENCIES 50

typedef struct {
    int id;
    char command[50];
    int dependencies[MAX_DEPENDENCIES];
    int num_dependencies;
} Process;

Process* read_input_file(const char *filename, int *num_processes);

Process* remove_dependencie(Process *processes, int index);

#endif /* READFILE_H */
