/*************************************************************************
 * This example demonstrates the basic use of task creation using fork
 * and exit function. It also shows that the parent stack is copied 
 * to the child process. Since there is no determinant way to know 
 * which process will run first so a blocking function is added to
 * parent process to let child runs first.
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>

#include <string.h>
#include <stdlib.h>

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
        if(0 != atexit(exit_handler))
        {
            printf("Failed to create exit handler\n");
        }
        exit(EXIT_SUCCESS);
    }
    else        //default
    {
        sleep(1);
        printf("Parent PID (%d) \nParent local var (%d)\n", getpid(), local_var*2);
        exit(EXIT_SUCCESS);
    }

    return 0;
}