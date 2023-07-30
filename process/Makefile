EXE = fork_basic orphans Zombie_process

fork_basic : fork_basic.c
	${CC} -o $@ fork_basic.c

orphans : orphans.c
	${CC} -o $@ orphans.c

Zombie_process: Zombie_process.c
	${CC} -o $@ Zombie_process.c
	
clean : 
	${RM} ${EXE} *.o