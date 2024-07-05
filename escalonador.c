#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/ipc.h>
#include "readfile.h"

#define KEY 170105067

int main(int argc, char **argv)
{

    int cores = atoi(argv[1]);
    printf("Cores: %d\n", cores);
    int num_processes;
    Process *processes = read_input_file("input.txt", &num_processes);

    int pidTeste15, pidTeste30 = 0;

    struct processo
    {
        int pid;
        int index;
        float time;
    };

    struct processo env;

    int queue = 0;

    if ((queue = msgget(KEY, 0666 | IPC_CREAT)) < 0)
    {
        printf("Erro ao criar fila com ID: %x\n", KEY);
        exit(1);
    }
    else
    {
        printf("Queue: %x\n", queue);
    }

    int pid = 0;

    if ((pid = fork()) < 0)
    {
        printf("Erro: FORK");
        exit(1);
    }

    // msgctl(queue, IPC_RMID, NULL);

    if (pid == 0)
    {
        int ret = execl("./testeXX", "teste15", "15", "1", NULL);
        printf("Ret15: %d\n", ret);
    }
    else
    {
        pidTeste15 = pid;

        if ((pid = fork()) < 0)
        {
            printf("Erro: FORK");
            exit(1);
        }

        if (pid == 0)
        {
            int ret = execl("./testeXX", "teste30", "30", "2", NULL);
            printf("Ret30: %d\n", ret);
        }
        else
        {
            pidTeste30 = pid;

            printf("PidTeste15: %d\n", pidTeste15);
            printf("PidTeste30: %d\n", pidTeste30);
        }
    }
   return 0 ;

}