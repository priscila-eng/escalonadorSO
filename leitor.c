#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define KEY 170105067

struct processo
{
    long mtype;
    int pid;
    int index;
    float time;
};

int main()
{
    int queue;
    struct processo msg;

    // Obtendo a fila de mensagens existente
    if ((queue = msgget(KEY, 0666)) == -1)
    {
        perror("msgget");
        exit(1);
    }

    // Lendo todas as mensagens da fila 
    while (1)
    {
        if (msgrcv(queue, &msg, sizeof(struct processo) - sizeof(long), 0, 0) == -1)
        {
            perror("msgrcv");
            exit(1);
        }

        // Processando a mensagem recebida
        printf("Mensagem recebida:\n");
        printf("PID: %d\n", msg.pid);
        printf("Índice: %d\n", msg.index);
        printf("Tempo: %f segundos\n", msg.time);
        printf("\n");
    }

    return 0;
}
