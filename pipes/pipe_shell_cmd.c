/*************************************************************************
 * This example demonstrates using pipes to execute shell commands. The
 * usage of this example is restricted by executing a command without
 * spaces, For example "ls" command will be executed but "ls -al"
 * the "ls" only will be executed.
 ************************************************************************/
#include <stdio.h>
#include <unistd.h>

#include <string.h>
#include <stdlib.h>

#include <sys/wait.h>
#include <signal.h>

#include <errno.h>

#define MAX_CMD_BUFFER_SIZE          (50)

int main(int argc, char *argv[])
{
    
    char cmd[MAX_CMD_BUFFER_SIZE], ch;
    FILE* fpr;

    while(1)
    {
        scanf("%s",cmd);
            
        fpr = popen(cmd, "r");     //open pipe to shell to execute the command
        if(fpr == NULL)
        {
            printf("cant open pipe to shell \n");
        }
        while( (ch = fgetc(fpr)) != EOF)
        {
            putchar(ch);
        }
        
        pclose(fpr);
    }

    exit(EXIT_SUCCESS);
}