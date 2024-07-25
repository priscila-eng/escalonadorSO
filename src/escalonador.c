/* INTEGRANTES
- Matrícula - Nome
- 170105067 - Hyago Gabriel Oliveira Figueiredo
- 180076272 - Jonas de Souza Fagundes
- 190113219 - Maria Eduarda Alves de Sousa
- 190094699 - Priscila Angel Rodrigues Silva
*/
/* INFORMAÇÕES DE AMBIENTE
- Compilador: GCC
- Sistema Operacional: Unix
- Ambiente utilizado para programar: Visual Studio Code
*/
/* COMO EXECUTAR
1) Makefile:
    a) executar comando make
    b) em seguida, make exec
    c) para mudar o número de cores, pode alterar o makefile (regra exec) ou após executar o make, executar o comando ./escalonador <cores>
2) ./escalonador 2
*/
/* INPUT.TXT
1 teste15 0,#
2 teste15 1,#
3 teste30 1,#
4 teste15 1,#
5 teste30 2,3,#
6 teste15 4,5,#
7 teste30 7,#
8 teste15 6,7,#
*/

#include "escalonador.h"

int queue = 0;
int num_processes = 0;
int posArray = 0;
int num_processes_running;

struct processo* finishProcess;
Process *processes;
clock_t start;

void qreader()
{
    struct processo msg;
    clock_t end;

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
    finishProcess[posArray] = msg;
    remove_dependencie(processes, finishProcess[posArray].index);
    --num_processes_running;
    posArray++;
    end = clock();
    double turnaround = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Turnaround: %.3f segundos do index %d\n", turnaround, msg.index);
    int status;
    wait(&status);
}

int executa(int j){
    int pid = 0;

    if ((pid = fork()) < 0)
    {
        printf("Erro: FORK");
        return -1;
    }
    if (pid == 0)
    {
        int len = strlen(processes[j].command);
        char time[] = {processes[j].command[len - 2], processes[j].command[len - 1], '\0'};

        char str[10];
        sprintf(str, "%d", processes[j].id);
        
        int ret = execl("./testeXX", processes[j].command, time, str, NULL);
        printf("Ret15: %d\n", ret);
        return -1;
    } else {
        return 10;
    }
}

int main(int argc, char **argv)
{
    if (argc < 2) // Verifica se há pelo menos 3 argumentos
    {
        printf("ERRO: Número errado de parâmetros\n");
        exit(-1);
    }
    int cores = atoi(argv[1]);
    if (cores <= 0){
        printf("Número de cores inválido");
        return 0;
    }

    double cpu_time_used;
    clock_t end;

    start = clock();
    // Prepara escalonador para desviar quando um sinal chegar
    // Neste caso, servirá para Sync entre escalonador e processos teste
    signal(SIGCHLD, qreader);


    printf("Cores: %d\n", cores);

    processes = read_input_file("input.txt", &num_processes);

    struct processo finishAux[num_processes];
    for(int i = 0; i < num_processes; i++){
        finishAux[i].index = 0;
        finishAux[i].mtype = 0;
        finishAux[i].pid = 0;
        finishAux[i].time = 0;
    }
    finishProcess = finishAux;
    
    // Abstração do processo de criação e obtenção da fila de mensagens
    // Programa só roda se a fila estiver vazia
    if ((queue = retorna_fila(KEY)) < 0){
        exit(1);
    }

    while (1){
        if(num_processes_running == cores){
            continue;
        }
        if(num_processes_running == 0){
            int index = getFirstProcessReady(processes);
            if(index == -1){
                break;
            }
        }
        if (num_processes_running < cores){
            int index = getFirstProcessReady(processes);
            if(index == -1){
                continue;
            }
            int ret = executa(index);
            if(ret == 10){
                processes[index].dependencies[0] = -1;
                ++num_processes_running;
            } else {
                printf("DEU RUIM NO FORK\n");
            }
        }
        /* Função do escalonador deve rodar aqui e a condição de parada deve ser o 
        final da execução do último processo */
    }

    // Remove a fila ao final da execução
    msgctl(queue, IPC_RMID, NULL);

    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("MAKESPAN: %.3f segundos\n", cpu_time_used);

    return 0;
}