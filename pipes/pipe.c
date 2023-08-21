/*************************************************************************
 * This example demonstrates using pipes for unidirectional data exchange
 * between the child process and parent.
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
    int PipeListFD[2];


    if( -1 == pipe(PipeListFD))
    {
        printf("Cant create pipe\n");
    }

    switch(fork())
    {
       case -1: return (EXIT_FAILURE);
       case 0:
            if(-1 == close(PipeListFD[0]))       //Child only sends data so it should close write pipe fd
            {
                printf("child failed to close read FD\n");
            }
            int Tdata = 48;
            for(;;)
            {
                write(PipeListFD[1], &Tdata, 1);
                if(Tdata++ > 100)
                    Tdata = 48;

                sleep(1);
            }
            exit(EXIT_SUCCESS);

       default:
            if(-1 == close(PipeListFD[1])) //parent only reads data so it should close read pipe fd
            {
                printf("parent failed to close write FD\n");
            }

            int Rdata;
            while (1)
            {
                read(PipeListFD[0], &Rdata, 1);
                //write data to standard ouput (terminal)
                write(STDOUT_FILENO, &Rdata, 1);
                write(STDOUT_FILENO, "\n", 1);
            }
            
    }

    exit(EXIT_SUCCESS);
}