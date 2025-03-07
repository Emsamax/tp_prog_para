############################ -*- Mode: Makefile -*- ###########################
## Makefile --- Cours MPI : TP3.9 : stride
##
## Auteur          : MMancini
##
###############################################################################

# Compilateurs, options de compilation et d'�dition de liens
include ../arch/make_inc

OBJS = stride.o

# R�gle implicite de compilation
.SUFFIXES: .o .c
.c.o:
	$(CC) -c $(CFLAGS_EX3) $<

all: stride

stride:$(OBJS)
	$(CC) -o $@ $(LDFLAGS_EX3) $(OBJS)
	$(MPIEXEC_EX3) ./stride

clean:
	rm -f $(OBJS) stride core
