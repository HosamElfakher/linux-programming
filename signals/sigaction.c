/*************************************************************************
 * This example demonstrates the basic use of sigaction function. This 
 * functions address the portablity issue of using signal(). Additionally,
 * it has more control on signal handlers.
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>

#include <string.h>
#include <stdlib.h>

#include <signal.h>

static void sig_handler(int sig, siginfo_t *info, void *ucontext)
{
    //unsafe-thread sync
    printf("\ncougth signal\nnumber (%d)  code (%d) value(%d)\n", info->si_signo, info->si_code, info->si_value.sival_int);
}

int main (int argc, char *argv[])
{
    struct sigaction sig;

    sigemptyset(&sig.sa_mask);
    sig.sa_flags = SA_SIGINFO;            //to carry more info for handler

    sig.sa_handler = sig_handler;

    if( -1 == sigaction(SIGINT, &sig, NULL)) //alternative for signal function 
    {
        printf("Failed to create disposition signal\n");
    }

    pause();         //wait for a signal

    return 0;
}