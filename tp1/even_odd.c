#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[])
{
    int rank, nb_procs;
    char* rank_desc;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nb_procs);
    if(rank % 2 == 0){
        rank_desc = "even";
    }else{
        rank_desc = "odd";
    }
    printf("Coucou, je suis le processus %d my rank is %s \n",
    rank,rank_desc);
    MPI_Finalize();
    //return 0;
}