#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <time.h>
#include <signal.h>

#define KEY 170105067

#define CLI_TEST 0
// #define CLI_TEST 1

struct processo
{
    long mtype; // Campo necessário para mensagens
    int pid;
    int index;
    float time;
};

int queue = 0;

int main(int argc, char **argv)
{
    // Verificando requisitos de execução do código
    //************************************************
    if (argc < 2 || (CLI_TEST && (argc < 2))) // Verifica se há pelo menos 3 argumentos
    {
        printf("ERRO: Número errado de parâmetros\n");
        exit(-1);
    }


    int time_param = atoi(argv[1]);

    int index_param = 0;

    if (!CLI_TEST)
    {
        index_param = atoi(argv[2]); // Converte argv[2], o índice
        if ((queue = msgget(KEY, 0666)) < 0)
        {
            perror("Erro ao obter fila com ID");
            exit(1);
        }
    }
    //************************************************

    clock_t start, end;
    double cpu_time_used;
    long i;

    start = clock();

    struct processo env;

    while (1)
    {
        for (i = 0; i < 8000000000; i++)
            ;
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        if (cpu_time_used >= time_param)
        {
            break;
        }
    }

    // escolha de programação. 
    // Iamos utilizar para diferenciar a mensagem do filho e a mensagem do escalonador, mas não precisou
    // Lemos a mensagem sequencialmente
    env.mtype = 1; // Define o tipo de mensagem
    env.pid = getpid();
    env.index = index_param;

    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    env.time = cpu_time_used;

    if (!CLI_TEST)
    {
        if (msgsnd(queue, &env, sizeof(env) - sizeof(long), 0) == -1)
        { // Exclui o campo mtype do tamanho
            perror("Erro ao enviar mensagem");
            exit(1);
        }
    } else {
        printf("Turnaround: %.3f segundos do index %d\n", cpu_time_used, env.index);
    }
    return 0;
}
