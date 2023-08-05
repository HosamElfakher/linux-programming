/*************************************************************************
 * This example demonstrates creation of, changing its stack size. a thread
 * and monitoring thread by join function(like wait in process)
 ************************************************************************/

#define _GNU_SOURCE 

#include <stdio.h>
#include <unistd.h>

#include <string.h>
#include <stdlib.h>

#include <errno.h>

#include <pthread.h>

void *thread1(void *arg)
{
    int i;
    for(i = 0; i < 3; i++)
    {
        printf("Thread 1 count %d\n", i);
        sleep(1);
    }

    //Using pthread_detach() function and commenting exit function if you aren't interested
    //in thread monitoring termination status

    //pthread_detach(pthread_self()); 
    pthread_exit((void *)1);
}

int main(int argc, char *argv[])
{
    pthread_t th1;
    pthread_attr_t th1_attr;

    pthread_attr_init(&th1_attr);

    void *ps;
    int r = 
    r = posix_memalign(&ps, sysconf(_SC_PAGESIZE), 1024);
    if(0 != r)
    {
        printf("failed to allocate stack\n");
        exit(EXIT_FAILURE);
    }
    printf("allocated stack address is %p\n", ps);

    pthread_attr_setstack(&th1_attr, ps, 1024);

    r = pthread_create(&th1, NULL, thread1, NULL);
    if(0 != r)
    {
        printf("failed to create a new thread\n");
        exit(EXIT_FAILURE);
    }

    void *res;
    while (!pthread_join(th1, &res))
    {
        printf("Returned value from thread1 is %ld\n", (long)res);
    }
    
    return 0;
}