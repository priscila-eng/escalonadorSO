#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/ipc.h>

int main(int argc, char **argv){

    int cores = atoi(argv[1]);
    printf("Cores: %d\n", cores);
    int pid = fork();

    if(pid == 0){
        int ret = execl("./teste15", "teste15", NULL);
        printf("%d", ret);
    }

    pid = fork();

    if(pid == 0){
        int ret = execl("./teste30", "teste30", NULL);
        printf("%d", ret);
    }
    return 0;

}