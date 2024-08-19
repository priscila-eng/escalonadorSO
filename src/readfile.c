#include <stdio.h>  
#include <stdlib.h> 
#include <string.h> 

#define MAX_LINE_LENGTH 100 // Define um tamanho máximo de 100 caracteres para uma linha do arquivo de entrada.

Process* read_input_file(const char *filename, int *num_processes) {
    // Esta função lê o arquivo de entrada e retorna um array de estruturas `Process`.
    // `filename` é o nome do arquivo, e `num_processes` é um ponteiro para armazenar o número de processos lidos.

    FILE *file = fopen(filename, "r");
    // Abre o arquivo especificado por `filename` em modo de leitura ("r").
    // Se a abertura do arquivo falhar, a função `fopen` retornará NULL.

    if (!file) {
        perror("Erro ao abrir arquivo");
        // Se `file` for NULL, imprime uma mensagem de erro e retorna NULL.
        return NULL;
    }

    char line[MAX_LINE_LENGTH];
    // Declara um array de caracteres para armazenar cada linha do arquivo lida.

    Process *processes = NULL;
    // Inicializa um ponteiro para `Process` com NULL. Este será o array que armazenará todos os processos lidos.

    *num_processes = 0;
    // Inicializa o número de processos para 0. `*num_processes` é atualizado diretamente no endereço passado.

    while (fgets(line, sizeof(line), file)) {
        // Lê cada linha do arquivo até o final.
        // `fgets` lê uma linha do arquivo e armazena em `line`.

        (*num_processes)++;
        // Incrementa o contador de processos a cada linha lida.

        processes = realloc(processes, (*num_processes) * sizeof(Process));
        // Realoca memória para o array de processos. Cada vez que um novo processo é lido, o array é expandido.
        // Se `realloc` falhar, retorna NULL, o que causaria um erro crítico.

        if (!processes) {
            perror("Erro ao realocar memória");
            // Se a realocação de memória falhar, imprime uma mensagem de erro e encerra o programa.
            exit(EXIT_FAILURE);
        }

        Process *current_process = &processes[*num_processes - 1];
        // Aponta para o último elemento do array de processos, que é onde o novo processo será armazenado.

        char dependencies_str[MAX_LINE_LENGTH];
        // Declara um array de caracteres para armazenar a string de dependências lida do arquivo.

        sscanf(line, "%d %s %s", &current_process->id, current_process->command, dependencies_str);
        // Usa `sscanf` para extrair os valores da linha lida:
        // - O ID do processo (`%d`) é armazenado em `current_process->id`.
        // - O comando (`%s`) é armazenado em `current_process->command`.
        // - A string de dependências (`%s`) é armazenada em `dependencies_str`.

        current_process->num_dependencies = 0;
        // Inicializa o número de dependências do processo atual para 0.

        char *token = strtok(dependencies_str, ",");
        // Usa `strtok` para dividir a string de dependências usando a vírgula como delimitador.
        // O primeiro token (parte da string antes da primeira vírgula) é retornado.

        while (token && strcmp(token, "#") != 0) {
            // Enquanto houver tokens e o token atual não for o caractere '#':
            current_process->dependencies[current_process->num_dependencies++] = atoi(token);
            // Converte o token para um número inteiro (que é o ID de um processo do qual o processo atual depende) 
            // e o armazena no array de dependências do processo atual.
            // Incrementa o número de dependências.

            token = strtok(NULL, ",");
            // Obtém o próximo token, continuando a dividir a string original.
        }
    }

    fclose(file);
    // Fecha o arquivo após terminar a leitura.

    return processes;
    // Retorna o array de processos lidos.
}