############################ -*- Mode: Makefile -*- ###########################
## Makefile --- Cours MPI : TP1 : Environnement
##
## Auteur          : Dimitri Lecas (CNRS/IDRIS) <dimitri.lecas@idris.fr>
###############################################################################

# Compilateurs, options de compilation et d'édition de liens
include ./arch/make_gcc
OBJS = exemple_03.o

# Règle implicite de compilation
.SUFFIXES: .o .c
.c.o:
	$(CC) -c $(CFLAGS_TP1) $<

all: exemple_03

exemple_03:$(OBJS)
	$(CC) -o $@ $(LDFLAGS_TP1) $(OBJS)
	$(MPIEXEC_TP1) -n 2 ./exemple_03

clean:
	rm -f $(OBJS) exemple_03 core