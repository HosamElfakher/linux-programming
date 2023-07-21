/*************************************************************************
 * This example demonstrates the basic use of signals. The control flow of 
 * the program is controlled by supplied command lines as the following.
 * 1- It sends an immediate signal to itself if no arguments are supplied.
 * 2- It sends a delayed signal to itself by the delayed mount of time that is 
 *    supplied as argument eg, ./signal_basics -s 10 to delay for 10 sec.
 * 3- It sends an immediate signal to specified process which its pid is 
 *    provided as an argument eg, ./signal_basics -i 22541 (PID = 22541).
 * 4- It sends a delayed signal to specific process. where the delay time 
 *    and process ID are supplied as an arguments eg, ./signal basic -s 10 -t 22541  
 ************************************************************************/
#include <stdio.h>
#include <unistd.h>

#include <string.h>
#include <stdlib.h>

#include <signal.h>

static void sigHandle(int sig)
{
	//unsafe sync function
	printf("signal name (%s)  signal number (%d)\n", strsignal(sig), sig);
}

int main (int argc, char *argv[])
{
	int opt, slp = 0;
	pid_t pid = 0;

	while((opt = getopt(argc, argv, "s:i:")) != -1)
	{
		switch (opt)
		{
		case 's': slp = atoi(optarg);
			break;
		case 'i': pid = atoi(optarg);
		default:

			break;
		}
	}
	if(signal(SIGINT, sigHandle) == SIG_ERR)    //signal function is not prefered for signals due to portabilty issues
	{
		printf("failed to create a signal\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		if(pid == 0)
		{
			pid = getpid();
			printf("Process PID (%d) \n", pid);
			sleep(slp);
			if(raise(SIGINT) != 0)                       //raise (SIGINT) = kill(getpid(), SIGINT))
			{
				printf("failed to send a signal\n");
				exit(EXIT_FAILURE);
			}
			else
				printf("raised signal to pid (%d) after (%d) sec\n", pid, slp);
		}
		else if(pid != 0)
		{
			sleep(slp);
			if(0 != kill(pid, SIGINT))
			{
				printf("failed to send a signal\n");
				exit(EXIT_FAILURE);
			}
			else
				printf("sent signal to pid (%d) after (%d) sec\n", pid, slp);
		}
		else
		{
			printf("undefined command\n");
		}
	}
	return 0;
}
