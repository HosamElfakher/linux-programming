EXE = pipe pipe_shell_cmd

pipe : pipe.c
	${CC} -o $@ pipe.c

pipe_shell_cmd : pipe_shell_cmd.c
	${CC} -o $@ pipe_shell_cmd.c

clean : 
	${RM} ${EXE} *.o