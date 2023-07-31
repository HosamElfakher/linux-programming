/*************************************************************************
 * This example demonstrates the concept of execve to run different program
 * in a new generated process. The new program is passed as an argument.
 * for example, ./execve_basic ./child_signalling this command will execute
 * child_signalling program in the new generated process by fork.
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>

#include <string.h>
#include <stdlib.h>

#include <errno.h>

int main(int argc, char *argv[])
{
    char *exArgv[2] = {argv[1], NULL};

    __pid_t pid;

    pid = fork();         //after this line 2 different process are created
    if(-1 == pid)
    {
        printf("Failed to create a process child\n");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0)
    {
        execve(argv[1], exArgv , NULL);
        //never comes here
        printf("Exit from child process\n");
        exit(EXIT_SUCCESS);
    }
    else        //default
    {
        printf("Parent process is doing some work and exit\n");
        //do stuff
        exit(EXIT_SUCCESS);
    }
    
    return 0;
}