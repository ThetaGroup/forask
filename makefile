DIR_INC = ./include
DIR_SRC = ./src
DIR_OBJ = ./obj
DIR_BIN = ./bin

OBJS = $(DIR_OBJ)/main.o $(DIR_OBJ)/cli.o $(DIR_OBJ)/command.o $(DIR_OBJ)/sqlite3.o

CC = cc
CFLAGS = -I$(DIR_INC) -Wall
CCF = $(CC) $(CFLAGS)

RM = rm
RMF = rm -rvf
MD = mkdir -p

forask:$(OBJS) obj_bin
	$(CC) $(OBJS) -o $(DIR_BIN)/forask

$(DIR_OBJ)/sqlite3.o : $(DIR_SRC)/sqlite3.c obj_dir
	$(CCF) -c $(DIR_SRC)/sqlite3.c -o $(DIR_OBJ)/sqlite3.o

$(DIR_OBJ)/command.o : $(DIR_SRC)/command.c $(DIR_INC)/sqlite3.h obj_dir
	$(CCF) -c $(DIR_SRC)/command.c -o $(DIR_OBJ)/command.o

$(DIR_OBJ)/cli.o : $(DIR_SRC)/cli.c $(DIR_INC)/command.h obj_dir
	$(CCF) -c $(DIR_SRC)/cli.c -o $(DIR_OBJ)/cli.o

$(DIR_OBJ)/main.o : $(DIR_SRC)/main.c $(DIR_INC)/cli.h obj_dir
	$(CCF) -c $(DIR_SRC)/main.c -o $(DIR_OBJ)/main.o

obj_dir : 
	$(MD) $(DIR_OBJ)

obj_bin :
	$(MD) $(DIR_BIN)

.PHONY : clean
clean:
	$(RMF) $(DIR_OBJ)/*
	$(RMF) $(DIR_BIN)/*


