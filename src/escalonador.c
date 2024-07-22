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
    // Prepara escalonador para desviar quando um sinal chegar
    // Neste caso, servirá para Sync entre escalonador e processos teste
    signal(SIGUSR1, qreader);

    int cores = atoi(argv[1]);
    printf("Cores: %d\n", cores);

    Process *processes = read_input_file("input.txt", &num_processes);
    printf("Num de processos: %i\n", num_processes);

    // Abstração do processo de criação e obtenção da fila de mensagens
    // Programa só roda se a fila estiver vazia
    if ((queue = retorna_fila(KEY)) < 0){
        exit(1);
    }

    int pidTeste15, pidTeste30 = 0;
    int pid = 0;

    if ((pid = fork()) < 0)
    {
        printf("Erro: FORK");
        exit(1);
    }

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

    while (1){
        /* Função do escalonador deve rodar aqui e a condição de parada deve ser o 
        final da execução do último processo */
    }

    // Remove a fila ao final da execução
    msgctl(queue, IPC_RMID, NULL);

    return 0;
}