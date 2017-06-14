DIR_INC = ./include
DIR_SRC = ./src
DIR_OBJ = ./obj
DIR_BIN = ./bin

OBJS = $(DIR_OBJ)/main.o $(DIR_OBJ)/cli.o $(DIR_OBJ)/command.o $(DIR_OBJ)/sqlite3.o

CC = cc
CFLAGS = -I$(DIR_INC)
CCF = $(CC) $(CFLAGS)

RM = rm
RMF = rm -rvf

forask:$(OBJS)
	$(CC) $(OBJS) -o $(DIR_BIN)/forask

$(DIR_OBJ)/sqlite3.o : $(DIR_SRC)/sqlite3.c
	$(CCF) -c $(DIR_SRC)/sqlite3.c -o $(DIR_OBJ)/sqlite3.o
$(DIR_OBJ)/command.o : $(DIR_SRC)/command.c $(DIR_INC)/sqlite3.h
	$(CCF) -c $(DIR_SRC)/command.c -o $(DIR_OBJ)/command.o
$(DIR_OBJ)/cli.o : $(DIR_SRC)/cli.c $(DIR_INC)/command.h
	$(CCF) -c $(DIR_SRC)/cli.c -o $(DIR_OBJ)/cli.o
$(DIR_OBJ)/main.o : $(DIR_SRC)/main.c $(DIR_INC)/cli.h
	$(CCF) -c $(DIR_SRC)/main.c -o $(DIR_OBJ)/main.o

.PHONY : clean
clean:
	$(RMF) $(DIR_OBJ)/*
	$(RMF) $(DIR_BIN)/*


