############################ -*- Mode: Makefile -*- ###########################
## Makefile --- Cours MPI : TP4 : Type de donn�es deriv�es (type_transpose)
##
## Auteur          : Dimitri LECAS (CNRS/IDRIS) <dimitri.lecas@idris.fr>
##
###############################################################################

# Compilateurs, options de compilation et d'�dition de liens
include ../arch/make_inc

OBJS = transpose.o

# R�gle implicite de compilation
.SUFFIXES: .o .c
.c.o:
	$(CC) -c $(CFLAGS_TP4) $<

all : transpose

transpose: $(OBJS)
	$(CC) -o $@ $(LDFLAGS_TP4) $(OBJS)
	$(MPIEXEC_TP4) ./transpose

clean :
	rm -f $(OBJS) transpose core
