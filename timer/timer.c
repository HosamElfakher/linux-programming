/*************************************************************************
 * This example demonstrates the basic use of timer functions. Simply, it 
 * creates three types of timers real, virtual and profiling timers. They 
 * all set to the same timeout value and handler.
 * 
 * exercise try to set tm.it_value.tv_usec to 1000000. what did you see? 
 * visit this https://man7.org/linux/man-pages/man3/getitimer.3p.html link to understand the reason.
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>

#include <string.h>
#include <stdlib.h>

#include <signal.h>

#include <sys/time.h>

#include <time.h>

clock_t tm_offset;

void static timer_handler(int sig)
{
    //unsafe sync thread
    printf("%s handler time in ms %ld \n", strsignal(sig) ,((clock()- tm_offset) / 1000));
}

int main(int argc, char *argv[])
{
    struct itimerval tm;
    tm.it_interval.tv_sec = 5;
    tm.it_interval.tv_usec = 0;
    tm.it_value.tv_sec = 5;
    tm.it_value.tv_usec = 0;

    struct sigaction tm_sig;
    sigemptyset(&tm_sig.sa_mask);
    tm_sig.sa_flags = 0;
    tm_sig.sa_handler = timer_handler;
    
    if(-1 == sigaction(SIGVTALRM, &tm_sig, NULL))
    {
        printf("failed to establish a virtual timer signal \n");
    }
    
    if(-1 == sigaction(SIGPROF, &tm_sig, NULL))
    {
        printf("failed to establish a profile timer signal \n");
    }
    
    if(-1 == sigaction(SIGALRM, &tm_sig, NULL))
    {
        printf("failed to establish a real timer signal \n");
    }

    if(-1 == setitimer(ITIMER_VIRTUAL, &tm, NULL))
    {
        printf("failed to set a timer \n");
    }
    
    
    if(-1 == setitimer(ITIMER_REAL, &tm, NULL))
    {
        printf("failed to set a timer \n");
    }
    
    
    if(-1 == setitimer(ITIMER_PROF, &tm, NULL))
    {
        printf("failed to set a timer \n");
    }

    tm_offset = clock();
    
    while(1);

    return 0;

}