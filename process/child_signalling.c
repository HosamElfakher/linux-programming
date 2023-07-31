/*************************************************************************
 * This example demonstrates the concept of zombie process. Basically,The
 * child finished its work however the parent didn't monitor it by wait
 * function. 
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>

#include <string.h>
#include <stdlib.h>

#include <sys/wait.h>
#include <signal.h>

#include <errno.h>

volatile int RxSig = 0;
static void child_handler(int sig)
{
    RxSig = 1;
    //unsafe thread call
    printf("caught signal name (%s)  signal number (%d)\n", strsignal(sig), sig);
}

int main(int argc, char *argv[])
{
    
    struct sigaction sig;
    
    sigemptyset(&sig.sa_mask);
    sig.sa_flags = 0;
    sig.sa_handler = child_handler;

    if(-1 == sigaction(SIGCHLD, &sig, NULL))
    {
        printf("Failed to create child signal disposition\n");
    }

    __pid_t pid;

    pid = fork();         //after this line 2 different process are created
    if(-1 == pid)
    {
        printf("Failed to create a process child\n");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0)
    {
        printf("child sleeps for a while\n");
        sleep(3);
        exit(EXIT_SUCCESS);
    }
    else        //default
    {
        while(1)
        {
            if(RxSig)
            {
                printf("child sent termination signal\n");
                exit(EXIT_SUCCESS);
            }
        }
    }

    return 0;
}