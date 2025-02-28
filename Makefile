############################ -*- Mode: Makefile -*- ###########################
## Makefile --- Cours MPI : TP1 : Environnement
##
## Auteur          : Dimitri Lecas (CNRS/IDRIS) <dimitri.lecas@idris.fr>
###############################################################################

# Compilateurs, options de compilation et d'édition de liens
include ./arch/make_gcc
OBJS = even_odd.o

# Règle implicite de compilation
.SUFFIXES: .o .c
.c.o:
	$(CC) -c $(CFLAGS_TP1) $<

all: even_odd

even_odd:$(OBJS)
	$(CC) -o $@ $(LDFLAGS_TP1) $(OBJS)
	$(MPIEXEC_TP1) ./even_odd

clean:
	rm -f $(OBJS) even_odd core