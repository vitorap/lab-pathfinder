CC = gcc
EXE = trabalho
LIB = -lm -g3

HDIR = ./header
SDIR = ./src
ODIR = ./src/obj

_OBJ = grafo.o fila.o global.o labirinto.o pilha.o listaOrd.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))

all: $(EXE)

$(ODIR)/%.o: $(SDIR)/%.c $(HDIR)/%.h
	$(CC) -c $< -o $@ $(LIB)

$(EXE): $(SDIR)/main.c $(OBJ)
	$(CC) $< -o $@ $(OBJ) $(LIB)

run:
	./$(EXE)
run-valgrind:
	valgrind ./$(EXE)
run-gdb:
	gdb ./$(EXE)

.PHONY: clear
clear:
	rm $(OBJ)