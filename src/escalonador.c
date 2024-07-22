#include "escalonador.h"

int queue = 0;
int num_processes;

void qreader()
{
    struct processo msg;

    // Obtendo a fila de mensagens existente
    if ((queue = msgget(KEY, 0666)) == -1)
    {
        perror("msgget");
        exit(1);
    }

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

int main(int argc, char **argv)
{
    signal(SIGUSR1, qreader);

    int cores = atoi(argv[1]);
    printf("Cores: %d\n", cores);
    Process *processes = read_input_file("input.txt", &num_processes);

    printf("Num de processos: %i\n", num_processes);

    int pidTeste15, pidTeste30 = 0;

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

        // o 1 é o indice do processo, após conectar com a fila, passamos dinamicamente
        remove_dependencie(processes, 1);
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

            // o 2 é o indice do processo, após conectar com a fila, passamos dinamicamente
            remove_dependencie(processes, 2);
            printf("PidTeste15: %d\n", pidTeste15);
            printf("PidTeste30: %d\n", pidTeste30);
        }
    }

    printf("Indice processo ready: %d\n", getFirstProcessReady(processes));

    while (1)
        ;

    return 0;
}