############################ -*- Mode: Makefile -*- ###########################
## Makefile --- Cours MPI : TP3.9 : contiguous
##
## Auteur          : MMancini
##
###############################################################################

# Compilateurs, options de compilation et d'�dition de liens
include ../arch/make_inc

OBJS = contiguous.o

# R�gle implicite de compilation
.SUFFIXES: .o .c
.c.o:
	$(CC) -c $(CFLAGS_EX3) $<

all: contiguous

contiguous:$(OBJS)
	$(CC) -o $@ $(LDFLAGS_EX3) $(OBJS)
	$(MPIEXEC_EX3) ./contiguous

clean:
	rm -f $(OBJS) contiguous core
