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

int main(int argc, char *argv[])
{
    __pid_t pid;

    pid = fork();         //after this line 2 different process are created
    if(-1 == pid)
    {
        printf("Failed to create a process child\n");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0)
    {
        printf("Immediate child exit\n");
        exit(EXIT_SUCCESS);
    }
    else        //default
    {
        sleep(1);
        printf("Run ps -au command to list a zombie process\n");
        sleep(20);
        printf("Exiting Parent PID (%d) \n", getpid());
        exit(EXIT_SUCCESS);
    }

    return 0;
}