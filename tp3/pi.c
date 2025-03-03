/*
 * pi.c --- TP3 : Diffusions globales et réductions
 *
 * Auteur          : Dimitri LECAS (CNRS/IDRIS - France) <dimitri.lecas@idris.fr>
 *
 */

#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]) {
  long long nbbloc,i;
  double largeur, somme, x;
  int rank;
  double pi;
  int nbProc = 0;
  double temps_debut,temps_fin;

  /* Initialisation de MPI */
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &nbProc);

  temps_debut=MPI_Wtime();

  /* Nombre d'intervalles */
  nbbloc = 1000*1000*1000LL*100;
  /* largeur des intervalles */
  largeur = 1.0/nbbloc;

  somme = 0;

  for (i=(nbbloc/nbProc)*rank; i< (nbbloc/nbProc)*(rank+1); i++) {
    /* Point au milieu de l'intervalle */
    x = largeur*(i+0.5);
    /* Calcul de l'aire */
    somme += largeur*(4.0 / (1.0 + x*x));
  }

  //printf("Rank: %d, somme: %f", rank, somme);

  MPI_Reduce(&somme, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

  temps_fin=MPI_Wtime();

  if (rank == 0)
    printf("Pi = %.20lf\nTemps: %lf\n", pi, temps_fin-temps_debut);

  /* Sortie de MPI */
  MPI_Finalize();
  
  return 0;
}