/* INTEGRANTES
- Matrícula - Nome
- 170105067 - Hyago Gabriel Oliveira Figueiredo
- 180076272 - Jonas de Souza Fagundes
- 190113219 - Maria Eduarda Alves de Sousa
- 190094699 - Priscila Angel Rodrigues Silva
*/
/* INFORMAÇÕES DE AMBIENTE
- Compilador: GCC - versão 11.4.0
- Sistema Operacional: Unix - Ubuntu 22.04
- Ambiente utilizado para programar: Visual Studio Code
*/
/* COMO EXECUTAR
1) Makefile:
    a) executar comando make
    b) em seguida, make exec
    c) para mudar o número de cores:
        i)  alterar o makefile (regra exec)
        ii) após executar o make, executar o comando ./escalona <cores>
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
    // nessa struct tem os atributos da mensagem (tipo, pid, index e time)
    struct processo msg;

    // declaração do final do temporizador
    clock_t end;

    // Obtendo a fila de mensagens existente
    // KEY é a chave da fila e 0666 está em octal e é a permissão de acesso da fila. 
    // significa que o dono, o grupo e os outros usuários podem ler e escrever.
    if ((queue = msgget(KEY, 0666)) == -1)
    {
        perror("msgget");
        exit(1);
    }

    // id, ponteiro para armazenar a mensagem, tamanho da mensagem, flag de execução
    if (msgrcv(queue, &msg, sizeof(struct processo) - sizeof(long), 0, 0) == -1)
    {
        perror("msgrcv");
        exit(1);
    }

    // Processando a mensagem recebida
    finishProcess[posArray] = msg;

    // ponteiro da lista de processos, index do processo que terminou
    remove_dependencie(processes, finishProcess[posArray].index);
    --num_processes_running;
    posArray++;

    // finaliza o temporizador de turnaround do processo filho
    end = clock();

    // transforma a contagem para segundos
    double turnaround = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Turnaround do processo %d: %.3f segundos.\n", msg.index, turnaround);

    // coleta o status de morte, para não ficar zombie
    int status;
    wait(&status);
}

// J é o index do processo pronto que vai ser executado
int executa(int j){
    int pid = 0;

    if ((pid = fork()) < 0)
    {
        printf("Erro: FORK");
        return -1;
    }
    // verifica se é o processo filho
    if (pid == 0)
    {
        // tamanho da string testeXX
        int len = strlen(processes[j].command);

        // pega o XX da string testeXX (tempo do processo)
        char time[] = {processes[j].command[len - 2], processes[j].command[len - 1], '\0'};

        // transformando um inteiro em string, porque no execl precisa que todos os argumentos sejam string
        char str[10];
        sprintf(str, "%d", processes[j].id);
        
        printf("Processo número %d executando.\n", processes[j].id);

        // testeXX, 15 ou 30, index do processo
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

    // converte a string em inteiro o argumento de número de cores
    int cores = atoi(argv[1]);
    if (cores <= 0){
        printf("Número de cores inválido");
        return 0;
    }

    // declaração de variáveis do temporizador
    double cpu_time_used;
    clock_t end;

    // inicia a contagem do tempo de turnaround e do makespan
    start = clock();

    // Prepara escalonador para desviar quando um sinal chegar
    // Neste caso, servirá para Sync entre escalonador e processos teste
    signal(SIGCHLD, qreader);

    processes = read_input_file("input.txt", &num_processes);

    struct processo finishAux[num_processes];

    // criamos esse for para zerar a lista de processos finalizados,
    // pois quando criamos o array, percebemos que foi criada com lixo de memória ao invés de zero
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

        // evitar que um processo pronto seja executado quando todos os cores estiverem ocupados
        if(num_processes_running == cores){
            continue;
        }

        // se não tiver nenhum processo rodando e nenhum processo pronto, o escalonador para de executar
        // porque ou todos processos já rodaram ou algum processo depende dele mesmo ou de uma dependência que nunca vai rodar
        if(num_processes_running == 0){
            int index = getProcessReady(processes);
            if(index == -1){
                break;
            }
        }

        // se o número de processos rodando for menor que o numero de cores, ele verifica se tem algum processo pronto
        if (num_processes_running < cores){
            int index = getProcessReady(processes);
            if(index == -1){
                continue;
            }
            int ret = executa(index);

            // significa que o filho está rodando
            if(ret == 10){
                /* atualiza a dependência para -1, número escolhido para indicar que o processo já etá sendo ou já foi executado
                   com isso, o escalonador não precisa executá-lo novamente
                */
                processes[index].dependencies[0] = -1;
                ++num_processes_running;
            } else {
                printf("DEU RUIM NO FORK\n");
            }
        }
    }

    // Remove a fila ao final da execução
    msgctl(queue, IPC_RMID, NULL);

    // finaliza o temporizador do makespan
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("MAKESPAN: %.3f segundos\n", cpu_time_used);

    return 0;
}