/*************************************************************************
 * This example demonstrates the concept of orphan process. Basically,The
 * parent process die before the child so the child PPID will be changed. 
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

    printf("Starting Parent PID (%d)\n", getpid());

    pid = fork();         //after this line 2 different process are created
    if(-1 == pid)
    {
        printf("Failed to create a process child\n");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0)
    {
        printf("starting Child Execution\nChild parent PID (%d)\n", getppid());
        sleep(1);
        printf("Exiting Child parent PID (%d)\n", getppid());
        exit(EXIT_SUCCESS);
    }
    else        //default
    {
        printf("Exiting Parent PID (%d) \n", getpid());
        exit(EXIT_SUCCESS);
    }

    return 0;
}