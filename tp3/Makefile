############################ -*- Mode: Makefile -*- ###########################
## Makefile --- Cours MPI : TP3 : Communications collectives
##
## Auteur          : Dimitri Lecas (CNRS/IDRIS) <dimitri.lecas@idris.fr>
## 
###############################################################################

# Compilateurs, options de compilation et d'�dition de liens
include ../arch/make_inc

OBJS  = pi.o

# R�gle implicite de compilation
.SUFFIXES: .o .c
.c.o:
	$(CC) -c $(CFLAGS_TP3) $<

all: pi

pi: $(OBJS)
	$(CC) -o $@ $(LDFLAGS_TP3) $(OBJS)
	$(MPIEXEC_EX1) ./pi

clean:
	rm -f $(OBJS) pi core
