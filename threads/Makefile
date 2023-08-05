EXE = thread_creation mutex

thread_creation : thread_creation.c
	${CC} -o $@ thread_creation.c
mutex : mutex.c
	${CC} -o $@ mutex.c

clean : 
	${RM} ${EXE} *.o