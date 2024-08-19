#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readfile.h"

Process* remove_dependencie(Process *processes, int index) {
    
    // percorre todos os processos
    for(int i = 0; i < sizeof(processes); i++){
        Process *current_process = &processes[i];

        // percorre a lista de dependencia do processo, substituindo a posição que tem o indice do processo finalizado
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

    // retorna a lista com as dependencias removidas
    return processes;
}

/* Método de escalonamento:
    Shortest Job First
    Dá preferência para executar primeiro os processos de 15 segundos. 
    Se entre os prontos não tiver processos de 15 segundos, o primeiro processo ready de 30 segundos é executado.
    Para verificar se o processo está pronto, verificamos se ele tem, apenas, uma dependência e se essa dependência é 0.
*/
int getProcessReady(Process *processes) {
    int indexFirst = -1;

    for(int i = 0; i < sizeof(processes); i++){
        Process *current_process = &processes[i];

        if((current_process -> num_dependencies == 1) && (current_process -> dependencies[0] == 0)){
        
            if(strcmp("teste15", current_process -> command) == 0){
                return i;
            } else {
                if (indexFirst == -1){
                    indexFirst = i;
                }
            }
        }
    }

    return indexFirst;
}
