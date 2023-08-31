/*************************************************************************
 * This example demonstrates the data exchange between threads using 
 * message queue IPC. 
 ************************************************************************/

#define _GNU_SOURCE 

#include <stdio.h>
#include <unistd.h>

#include <string.h>
#include <stdlib.h>

#include <errno.h>

#include <pthread.h>

#include <mqueue.h>

mqd_t mq_id;

void *thread1(void *arg)
{
   unsigned char txBuf[3], i = 1;
   while (i++ < 4)
   {
      printf("Thread 1 send data\n");
      
      txBuf[0] = i;   
      txBuf[1] = i+1;
      txBuf[2] = i+2;
      mq_send(mq_id, txBuf, 3, 0);
      
      sleep(1);
   }

    printf("Thread 1 send last data\n");
    
    txBuf[0] = txBuf[1] = txBuf[2] = 0;   
    mq_send(mq_id, txBuf, 3, 0);
    
    pthread_exit((void *)1);
}

void *thread2(void *arg)
{
    unsigned char rxBuf[50];
    int rxNum;

    struct mq_attr at;

    mq_getattr(mq_id, &at);

    while (1)
    {
        rxNum = mq_receive(mq_id, rxBuf, at.mq_msgsize, NULL);

        if(rxNum == -1)
        {
            printf("error mq queue reading\n");
            pthread_exit((void*)55);
        }
        else
        {
            printf("Thread received: \n");
            unsigned char i , ext = 0;
            for( i = 0; i < 3; i++)
            {
                printf("%d ", rxBuf[i]);

                if(rxBuf[i] == 0)
                    ext++;
            }
            printf("\n");
            if(ext == 3)
                break;
        }
    }
    
    pthread_exit((void *)2);
}

int main(int argc, char *argv[])
{
    char mq_name[] = "/loc_MQ";

    mq_id = mq_open(mq_name, O_RDWR | O_CREAT, 0x700 ,NULL);
    if(-1 == mq_id)
    {
        printf("Failed to create a message queue\n");
        exit(EXIT_FAILURE);
    }

    pthread_t th1, th2;
    int r;

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

    mq_close(mq_id);
    mq_unlink(mq_name);

    return 0;
}