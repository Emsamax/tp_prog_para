############################ -*- Mode: Makefile -*- ###########################
## Makefile --- Cours MPI : TP3 : Communications collectives
##
## Auteur          : Dimitri Lecas (CNRS/IDRIS) <dimitri.lecas@idris.fr>
## 
###############################################################################

# Compilateurs, options de compilation et d'�dition de liens
include ../arch/make_inc

OBJS  = weighted_openmpi.o

# R�gle implicite de compilation
.SUFFIXES: .o .c
.c.o:
	$(CC) -c $(CFLAGS_TP3) $<

all: weighted_openmpi

weighted_openmpi: $(OBJS)
	$(CC) -o $@ $(LDFLAGS_TP3) $(OBJS)
	$(MPIEXEC_EX1) ./weighted_openmpi

clean:
	rm -f $(OBJS) weighted_openmpi core
