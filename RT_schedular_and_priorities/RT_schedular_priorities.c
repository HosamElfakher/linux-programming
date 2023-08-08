/*************************************************************************
 * This example demonstrates the usage of schedulers policies and 
 * priorities of process. In this example ranges of real time schedulers
 * priorites is displayed, Get the current schedular policy/priority of
 * the running process and changing them. Since changing the process 
 * priority and policy is privileged this program should run under 
 * privileged mode (sudo). Finally, it displays the CPUs number in which
 * process can run and tie it to one CPU.
 ************************************************************************/

#define _GNU_SOURCE 

#include <stdio.h>
#include <unistd.h>

#include <string.h>
#include <stdlib.h>

#include <errno.h>

#include <sched.h>


int main(int argc, char *argv[])
{
    printf("Priority info for real time schedulers\n");
    
    printf("Min priority for RR sched is %d\n", sched_get_priority_min(SCHED_RR));
    printf("Max priority for RR sched is %d\n", sched_get_priority_max(SCHED_RR));

    printf("Min priority for FIFO sched is %d\n", sched_get_priority_min(SCHED_FIFO));
    printf("Max priority for FIFO sched is %d\n", sched_get_priority_max(SCHED_FIFO));

    printf("Get running process sched policy %d\n", sched_getscheduler(getpid()));
    
    struct sched_param SchPars;
    sched_getparam(getpid(), &SchPars);
    printf("Get running process sched priority %d\n", SchPars.sched_priority);
    
    printf("Modify process schedular to RR Sched (2) and priority to 10 \n");
    
    SchPars.sched_priority = 10;
    sched_setscheduler(getpid(), SCHED_RR, &SchPars);
    sched_getparam(getpid(), &SchPars);

    printf("Get modified process sched policy %d with priority of %d\n", sched_getscheduler(getpid()), SchPars.sched_priority);


    printf("Current CPU affinity info \n");
    
    cpu_set_t cpuSet;
    sched_getaffinity(getpid(), sizeof(cpuSet), &cpuSet);
    for(int i = 0; i < CPU_SETSIZE; i++) //it depends on the system cores number
    {
        if(CPU_ISSET(i, &cpuSet))
        {
            printf("CPU (%d) is used for this process \n", i);
        }
    }

    printf("Set process to one core\n");
    CPU_ZERO(&cpuSet);
    CPU_SET(0, &cpuSet);
    sched_setaffinity(0, sizeof(cpuSet), &cpuSet);

    sched_getaffinity(getpid(), sizeof(cpuSet), &cpuSet);
    for(int i = 0; i < CPU_SETSIZE; i++) //it depends on the system cores number
    {
        if(CPU_ISSET(i, &cpuSet))
        {
            printf("Modified CPU (%d) is used only for this process \n", i);
        }
    }

    return 0;
}