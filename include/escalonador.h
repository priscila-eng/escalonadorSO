#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include "readfile.h"
#include <errno.h>
#include <signal.h>

#define KEY 170105067

struct processo
{
    long mtype;
    int pid;
    int index;
    float time;
};
