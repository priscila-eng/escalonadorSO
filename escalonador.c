#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/ipc.h>

int main(int argc, char **argv){

    int cores = atoi(argv[1]);
    printf("Cores: %d\n", cores);

    int pidTeste15, pidTeste30 = 0;

    struct processo
    {
        int pid;
        int index;
        float time;
    };
    
    struct processo env;


    int queue = msgget(0x1900, IPC_CREAT | 0x1FF);
    printf("Queue: %x\n", queue);

    int pid = fork();

    

    // msgctl(queue, IPC_RMID, NULL);

    if(pid == 0){
        int ret = execl("./teste15", "teste15", queue, 0, NULL);
        printf("ret teste15");
    } else {
        pidTeste15 = pid;

        pid = fork();

        if(pid == 0){
            int ret = execl("./teste30", "teste30", NULL);
            printf("%d", ret);
        } else {
            pidTeste30 = pid;

            printf("%d\n", pidTeste15);
            printf("%d\n", pidTeste30);
        }
    }

    return 0;

}