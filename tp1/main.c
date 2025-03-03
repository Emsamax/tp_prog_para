#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[])
{
    int rank, nb_procs;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nb_procs);
    printf("Coucou, je suis le processus %d sur %d processes\n",
    rank,nb_procs);
    MPI_Finalize();
    //return 0;
}