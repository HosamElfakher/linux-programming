EXE = thread_creation mutex conditional_vars

thread_creation : thread_creation.c
	${CC} -o $@ thread_creation.c
mutex : mutex.c
	${CC} -o $@ mutex.c
conditional_vars: conditional_vars.c
	${CC} -o $@ conditional_vars.c

clean : 
	${RM} ${EXE} *.o