forask:main.o cli.o command.o sqlite3.o
	cc -o forask main.o cli.o command.o sqlite3.o

sqlite3.o:sqlite3.c
	cc -c sqlite3.c
command.o:command.c sqlite3.h
	cc -c command.c
cli.o:cli.c command.h
	cc -c cli.c
main.o:main.c cli.h
	cc -c main.c
clean:
	rm forask *.o


