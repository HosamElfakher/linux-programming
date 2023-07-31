EXE = fork_basic orphans Zombie_process child_signalling execve_basic

fork_basic : fork_basic.c
	${CC} -o $@ fork_basic.c

orphans : orphans.c
	${CC} -o $@ orphans.c

Zombie_process: Zombie_process.c
	${CC} -o $@ Zombie_process.c

child_signalling: child_signalling.c
	${CC} -o $@ child_signalling.c

execve_basic: execve_basic.c
	${CC} -o $@ execve_basic.c

clean : 
	${RM} ${EXE} *.o