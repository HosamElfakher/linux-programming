/*************************************************************************
 * This example demonstrates the basic use of task creation using fork
 * , exit function and monitoring child process by wait. It also shows
 * that the parent stack is copied to the child process. Since there 
 * is no determinant way to know which process will run first so a
 * blocking function is added to parent process to let child runs first.
 * To demonstrate the usage of this program successfully,
 * 1- run the program in background mode as ./fork_basic &
 * 2- run ps command to list running process
 * 3- run fg command to restore the process into foreground 
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>

#include <string.h>
#include <stdlib.h>

#include <sys/wait.h>
#include <signal.h>

#include <errno.h>

void exit_handler(void)
{
    printf("Terminated child process\n");
}

int main(int argc, char *argv[])
{
    __pid_t pid;

    int local_var = 100;
    printf("Parent PID (%d)\n", getpid());

    pid = fork();         //after this line 2 different process are created
    if(-1 == pid)
    {
        printf("Failed to create a process child\n");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0)
    {
        printf("Child PID (%d)\nChild local var (%d)\n", getpid(), local_var*2);
        sleep(15);
        if(0 != atexit(exit_handler))
        {
            printf("Failed to create exit handler\n");
        }
        exit(EXIT_SUCCESS);
    }
    else        //default
    {
        // sleep(1);
        __pid_t ch_pid;
        if(-1 != (ch_pid = wait(NULL)))
        {
            if(ch_pid != ECHILD)
            {
               printf("Monitored terminated child PID (%d)", ch_pid); 
            }
        }
        printf("Parent PID (%d) \nParent local var (%d)\n", getpid(), local_var*2);
        exit(EXIT_SUCCESS);
    }

    return 0;
}