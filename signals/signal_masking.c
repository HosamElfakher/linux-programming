/*************************************************************************
 * This example demonstrates the basic use of signal initialization, blocking 
 * and pending functionality. Simply, it blocks Interrupt signal (ctrl+c) 
 * signal and enable quit signal (ctrl+\). The program runs indefinitely till
 * receiving Quit signal. Once received, it displays pended signal if it was
 * sent and terminate the program.
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>

#include <string.h>
#include <stdlib.h>

#include <signal.h>

static volatile int ext = 0;
static void sig_handler(int sig)
{
    //unsafe sync function
    printf("cought signal (%s) of number (%d)\n", strsignal(sig), sig );

    if(sig == SIGQUIT)
    {
        ext = 1;
    }
}

int main (int argc, char *argv[])
{
    sigset_t sig_msk, pend_sig;
    
    if(0 != sigemptyset(&sig_msk))
    {
        printf("fail to init signals \n");
        exit(EXIT_FAILURE);
    }

    if(0 != sigaddset(&sig_msk, SIGINT))
    {
        printf("fail to add signal to sig set \n");
        exit(EXIT_FAILURE);       
    }

    if(0 != sigprocmask(SIG_BLOCK, &sig_msk, NULL))
    {
        printf("fail to block signal set \n");
        exit(EXIT_FAILURE);         
    }

    if(SIG_ERR == signal(SIGINT, sig_handler))
    {
        printf("fail to create signal \n");
        exit(EXIT_FAILURE);         
    }

    if(SIG_ERR == signal(SIGQUIT, sig_handler))
    {
        printf("fail to create signal \n");
        exit(EXIT_FAILURE);         
    }
    
    while(1)
    {
        /*Note: sigset_t implementation is different across linux/posix standards 
                so the printf function may not work on other hosting environment */
        ext == 1? sigpending(&pend_sig),
            pend_sig.__val[0] != 0 ? printf("pended signal mask (%s) \n", strsignal(pend_sig.__val[0])) : printf("No pended siganls \n"),
            exit(EXIT_SUCCESS): 0;
    }


    return 0;
}