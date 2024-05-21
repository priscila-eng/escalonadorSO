#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <time.h>

int main(int argc, char **argv){
    clock_t start, end;
    double cpu_time_used;
    long i;

    start = clock();
    struct processo
    {
        int pid;
        int index;
        float time;
    };
    
    struct processo env;

    int queue = atoi(argv[1]);

    printf("%d\n", queue);

    while (1) {
        for (i=0; i<8000000000; i++);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        if (cpu_time_used >= 15.0) {
            break;
        }
    }
    msgget(queue, 0x1ff);

    env.pid = getpid();
    env.index = atoi(argv[2]);

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    env.time = cpu_time_used;

    msgsnd(queue, &env, sizeof(env), 0);

    printf("Tempo de execução: %f segundos\n", cpu_time_used);

    return 0;
}