/*************************************************************************
 * This example demonstrates the basic use of shared variables synchronization
 * between threads. To demonstrate the importance of mutex try to run this 
 * code by commenting this line #define MUTEX and try again with #define MUTEX
 ************************************************************************/

#define _GNU_SOURCE 

#include <stdio.h>
#include <unistd.h>

#include <string.h>
#include <stdlib.h>

#include <errno.h>

#include <pthread.h>

#define MUTEX

#ifdef MUTEX
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
#endif

volatile int shared_var;

void *thread1(void *arg)
{
    int i;
    for(i = 0; i < 50000; i++)
    {
        #ifdef MUTEX
        pthread_mutex_lock(&mtx);
        #endif
        shared_var++;
        #ifdef MUTEX
        pthread_mutex_unlock(&mtx);
        #endif
    }
    printf("In thread 1 shared variable count is %d\n", shared_var);
    pthread_exit((void *)1);
}

void *thread2(void *arg)
{
    int i;
    for(i = 0; i < 50000; i++)
    {

        #ifdef MUTEX
        pthread_mutex_lock(&mtx);
        #endif
        shared_var++;
        #ifdef MUTEX
        pthread_mutex_unlock(&mtx);
        #endif
    }
    printf("In thread 2 shared variable count is %d\n", shared_var);
    pthread_exit((void *)2);
}

int main(int argc, char *argv[])
{
    pthread_t th1, th2;
    int r;

    shared_var = 0;
    printf("inital value for shared variable is %d \n", shared_var);

    r = pthread_create(&th1, NULL, thread1, NULL);
    if(0 != r)
    {
        printf("failed to create a thread 1\n");
        exit(EXIT_FAILURE);
    }

    r = pthread_create(&th2, NULL, thread2, NULL);
    if(0 != r)
    {
        printf("failed to create a thread 2\n");
        exit(EXIT_FAILURE);
    }


    void *res;
    if(!pthread_join(th1, &res))
    {
        printf("Returned value from thread1 is %ld\n", (long)res);
    }
    
    if(!pthread_join(th2, &res))
    {
        printf("Returned value from thread2 is %ld\n", (long)res);
    }

    return 0;
}