/*************************************************************************
 * This example demonstrates the basic use of conditional variables
 * signalling. In this example there is a producer thread signal a consumer
 * thread using conditional variable signal. The commented part of the code
 * is the best practice to have a full control over the program behavior.
 * However, I preferred to comment them out to illustrate the internal
 * behavior of siganl_wait function.
 ************************************************************************/

#define _GNU_SOURCE 

#include <stdio.h>
#include <unistd.h>

#include <string.h>
#include <stdlib.h>

#include <errno.h>

#include <pthread.h>


pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t CondVar = PTHREAD_COND_INITIALIZER;

volatile int shared_var;

void *producer_thread(void *arg)
{
    int ret;
    while(1)
    {
        sleep(1);// to allow the other thread to run to unlock the mutex
        ret = pthread_mutex_lock(&mtx);
        if(0 != ret)
            exit(EXIT_FAILURE);
        shared_var++;
        ret = pthread_mutex_unlock(&mtx);
        if(0 != ret)
            exit(EXIT_FAILURE);

        printf("Produced signal of shared var %d\n", shared_var);
        
        ret = pthread_cond_signal(&CondVar);
        if(0 != ret)
            exit(EXIT_FAILURE);

    }
    pthread_exit((void *)1);
}

void *consumer_thread(void *arg)
{
    int ret;
    while(1)
    {
        // ret = pthread_mutex_lock(&mtx);
        // if(0 != ret)
        //     exit(EXIT_FAILURE);
        //while(!shared_var)
        {
            /*
            pthread_cond_wait() internally perform the following:
            1- unlock the Mutex
            2- block the current thread till signalled by another thread
            3- lock mutex
            */
            ret = pthread_cond_wait(&CondVar, &mtx);
            if(0 != ret)
                exit(EXIT_FAILURE);
        }

        //while(shared_var)
        {
            shared_var--;
            printf("Consumed signal of shared var %d\n", shared_var);
        }
        // ret = pthread_mutex_unlock(&mtx);
        // if(0 != ret)
        //     exit(EXIT_FAILURE);
        
    }
    pthread_exit((void *)2);
}

int main(int argc, char *argv[])
{
    pthread_t th1, th2;
    int r;

    shared_var = 0;
    printf("inital value for shared variable is %d \n\n\n", shared_var);

    r = pthread_create(&th1, NULL, producer_thread, NULL);
    if(0 != r)
    {
        printf("failed to create a thread 1\n");
        exit(EXIT_FAILURE);
    }

    r = pthread_create(&th2, NULL, consumer_thread, NULL);
    if(0 != r)
    {
        printf("failed to create a thread 2\n");
        exit(EXIT_FAILURE);
    }


    void *res;
    if(!pthread_join(th1, &res))
    {
        printf("Returned value from producer_thread is %ld\n", (long)res);
    }
    
    if(!pthread_join(th2, &res))
    {
        printf("Returned value from consumer_thread is %ld\n", (long)res);
    }

    return 0;
}