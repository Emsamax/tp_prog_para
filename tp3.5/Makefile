############################ -*- Mode: Makefile -*- ###########################
## Makefile --- Cours MPI : TP3.5 : reduction ex
##
## Auteur          : CINECA
##
###############################################################################

# Compilateurs, options de compilation et d'édition de liens
include ../../arch/make_inc

OBJS  = reduce.o

# Règle implicite de compilation
.SUFFIXES: .o .c
.c.o:
	$(CC) -c $(CFLAGS_TP3) $<

all: reduce

reduce: $(OBJS)
	$(CC) -o $@ $(LDFLAGS_TP3) $(OBJS)
	$(MPIEXEC_TP3) ./reduce

clean:
	rm -f $(OBJS) reduce core
