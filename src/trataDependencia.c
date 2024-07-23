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
        }
    }
    

    return processes;
}

int getFirstProcessReady(Process *processes) {
    for(int i = 0; i < sizeof(processes); i++){
        Process *current_process = &processes[i];

        if((current_process -> num_dependencies == 1) && (current_process -> dependencies[0] == 0)){
            printf("NUM_DEPENDECIES %d\n", current_process -> num_dependencies);
            return i;
        }
    }
    return -1;
}
