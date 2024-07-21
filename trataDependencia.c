#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readfile.h"

Process* remove_dependencie(Process *processes, int index) {
    
    for(int i = 0; i < sizeof(processes); i++){
        Process *current_process = &processes[i];

        for (int j = 0; j < current_process -> num_dependencies; j++){
            if(current_process -> dependencies[j] == index){
                if(current_process -> num_dependencies > 1){
                    if((j + 1) < current_process -> num_dependencies){
                        current_process -> dependencies[j] = current_process -> dependencies[j + 1];
                        current_process -> num_dependencies = current_process -> num_dependencies - 1;
                    } else {
                        current_process -> dependencies[j] = current_process -> dependencies[j - 1];
                        current_process -> num_dependencies = current_process -> num_dependencies - 1;
                    }
                } else {
                    current_process -> dependencies[j] = 0;
                }
            }
            // printf("J: %d dependencie: %d\n", j, current_process -> dependencies[j]);
        }
        // printf("ID: %d INDEX: %d\n", current_process -> id, index);
        printf("REMOVENDO\n");
        printf("id:%d comando:%s dependências:", current_process->id, current_process->command);
        for (int j = 0; j < current_process->num_dependencies; ++j) {
            printf(" %d", current_process->dependencies[j]);
        }
        printf("\n");
    }
    printf("\n");
    

    return processes;
}

int getFirstProcessReady(Process *processes) {
    for(int i = 0; i < sizeof(processes); i++){
        Process *current_process = &processes[i];

        if(current_process -> num_dependencies = 1 && current_process -> dependencies[0] == 0){
            return current_process -> id;
        }
    }
    return -1;
}
