############################ -*- Mode: Makefile -*- ###########################
## Makefile --- Cours MPI : TP8 : Equation de poisson
##
## Auteur          : Dimitri Lecas (CNRS/IDRIS)
##
###############################################################################
SHELL := /bin/bash
# Compilateur et options de compilation et de link
include ../arch/make_inc

OBJS = parallel.o calcul.o poisson.o
OBJS1 = read.o
OBJS2 = calcul_exact.o
OBJS3 = parallel.o calcul.o poisson_non_bloquant.o

# R�gle implicite de compilation
.SUFFIXES: .o .c
%.o : %.c
	$(CC) -c  $(CFLAGS_TP8) $<

default: poisson

all: poisson read calcul_exact

poisson: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS_TP8) -o $@

#poisson_non_bloquant: $(OBJS3)
#	$(CC) $(LDFLAGS_TP8) -o $@ $(OBJS3)

read: $(OBJS1)
	$(CC) $(OBJS1) $(LDFLAGS_TP8) -o $@

calcul_exact: $(OBJS2)
	$(CC) $(OBJS2) $(LDFLAGS_TP8) -o $@

fort.11: read donnees.dat
	$(EXEC_TP8_VERIF) ./read

.PHONY: exe clean verification

exe donnees.dat: poisson poisson.data
	rm -f donnees.dat
	/usr/bin/mpiexec -n 4 ./poisson
#SBATCH	sbatch poisson.slurm

verification: fort.11 calcul_exact
	$(EXEC_TP8_VERIF) ./calcul_exact

clean:
	rm -f $(OBJS) $(OBJS1) $(OBJS2) $(OBJS3) poisson poisson_non_bloquant calcul_exact read *.mod core donnees.dat fort.10 fort.11
