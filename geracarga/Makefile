#---------------------------------------------------------------------
# Arquivo	: Makefile
# Conteúdo	: compilar o programa geracarga
# Autor		: Wagner Meira Jr. (meira@dcc.ufmg.br)
# Histórico	: 2021-12-23 - arquivo criado
#---------------------------------------------------------------------
# Opções	: make all - compila tudo
#		: make clean - remove objetos e executável
#---------------------------------------------------------------------

CC = gcc
LIBS = -lm 
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/geracarga.o
HDRS = $(INC)/msgassert.h
CFLAGS = -g -Wall -c -I$(INC)

EXE = $(BIN)/geracarga

all: use

use: $(EXE)
	$(EXE) -o /tmp/geracarga.out 

$(BIN)/geracarga: $(OBJS)
	$(CC) -g -o $(BIN)/geracarga $(OBJS) $(LIBS)

$(OBJ)/geracarga.o: $(HDRS) $(SRC)/geracarga.c
	$(CC) $(CFLAGS) -o $(OBJ)/geracarga.o $(SRC)/geracarga.c 

clean:
	rm -f $(EXE) $(OBJS)  
