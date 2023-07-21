EXE = signal_basics signal_masking

signal_basics : signal_basics.c
	${CC} -o $@ signal_basics.c

signal_masking : signal_masking.c
	${CC} -o $@ signal_masking.c 

clean : 
	${RM} ${EXE} *.o