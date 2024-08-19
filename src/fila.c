#include "fila.h"

int retorna_fila(int chave)
{
    int queue = 0;

    if ((queue = msgget(chave, 0666 | IPC_CREAT)) < 0)
    {
        printf("Erro ao criar fila com ID: %x\n", chave);
        return -1;
    }

    // Estrutura para armazenar informações sobre a fila de mensagens
    struct msqid_ds buf;

    // Obtém informações sobre a fila de mensagens
    // IPC_STAT - flag de status
    if (msgctl(queue, IPC_STAT, &buf) < 0)
    {
        printf("Erro ao obter informações sobre a fila de mensagens\n");
        return -1;
    }

    if (buf.msg_qnum > 0)
    {
        printf("LISTA DE MENSAGENS NÃO ESTÁ VAZIA");
        return -1;
    }
    return queue;
}