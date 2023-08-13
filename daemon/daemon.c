/*************************************************************************
 * This example demonstrates the know how to create a daemon, signal
 * handling for daemon killing and demonstrates the basic of system 
 * logs. This program will behave as expected when virtual terminal.
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>

#include <string.h>
#include <stdlib.h>

#include <sys/wait.h>
#include <signal.h>

#include <sys/stat.h>
#include <fcntl.h>

#include <syslog.h>

#include <errno.h>

static void dhandler(int sig)
{
    syslog(LOG_ALERT, "%s", "HUP killing signal\n");
    
    closelog();
}

int main(int argc, char *argv[])
{
    __pid_t pid;

    struct sigaction dsig;

    sigemptyset(&dsig.sa_mask);
    dsig.sa_flags = SA_RESTART;
    dsig.sa_handler = dhandler;

    if(-1 == sigaction(SIGHUP, &dsig, NULL))
    {
        printf("Failed to create a daemon kill signal\n");
    }

    pid = fork();         //after this line 2 different process are created
    if(-1 == pid)
    {
        printf("Failed to create a process child\n");
        
        exit(EXIT_FAILURE);
    }
    if(0 == pid)
    {
        if(-1 == setsid())
        {
            printf("failed to change process session id \n");
        }
        openlog("**********Local daemon", LOG_PID, LOG_DAEMON);


        umask(0);            //change permission
        
        if(0 != chdir("/"))  //change mount point
            printf("Failed to change mounting point\n");
            
        int fd = sysconf(_SC_OPEN_MAX);
        
        while(fd >= 0)
        {
            close(fd);
        }

        int cnt = 0;
        while(1)
        {
            syslog(LOG_ALERT, "%d %s", cnt++, "count for local daemon\n");
            sleep(60);
        }
    }

    return 0;
}