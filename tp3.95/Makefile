############################ -*- Mode: Makefile -*- ###########################
## Makefile --- Cours MPI : TP3.95 : block
##
## Auteur          : MMancini
##
###############################################################################

# Compilateurs, options de compilation et d'�dition de liens
include ../arch/make_inc

OBJS = block.o

# R�gle implicite de compilation
.SUFFIXES: .o .c
.c.o:
	$(CC) -c $(CFLAGS_EX3) $<

all: block

block:$(OBJS)
	$(CC) -o $@ $(LDFLAGS_EX3) $(OBJS)
	$(MPIEXEC_EX3) ./block

clean:
	rm -f $(OBJS) block core
