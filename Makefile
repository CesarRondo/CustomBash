
#Make exec in the commandline to execute
$(CC) = gcc
exec:
		$(CC) main.c functs1.c functs2.c -o exec
Clean:
		rm*.o exec

