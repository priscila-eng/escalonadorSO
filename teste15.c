#include <stdio.h>
#include <time.h>

int main(){
    clock_t start, end;
    double cpu_time_used;
    long i;

    start = clock();

    while (1) {
        for (i=0; i<8000000000; i++);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        if (cpu_time_used >= 15.0) {
            break;
        }
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Tempo de execução: %f segundos\n", cpu_time_used);

    return 0;
}