/*
 * transpose.f90  --- Utilisation de alltoall
 *
 *
 * Auteur          : Marco Mancini (CNRS/IDP - France)
 *                   <marco.mancini@univ-tours.fr>
 *
 */

#include "mpi.h"
#include <stdlib.h>
#include <stdio.h>

void trans (double *a, int n) {
/* transpose square matrix a, dimension nxn
 * Consider this as a black box for the MPI course
 */
    int i, j, ij , ji, l;
    double tmp;
    ij = 0;
    for(i=0;i<n;i++){
	ij = i*n;
	for(j=i+1;j<n;j++){
	    ij +=  j;
	    ji = j * n + i;
	    tmp = a[ij];
	    a[ij] = a[ji];
	    a[ji] = tmp;
	}
    }
}



#define N_LIG 4
#define N_PROC 2
#define N_COL N_LIG/N_PROC

int main(int argc, char *argv[]) {
    double a[N_LIG][N_COL];
    double b[N_LIG][N_COL];

    int rank,iterl,iterc,taille_reel, nb_proc, i,j;
    MPI_Status statut;

    /* Initialisation de MPI */
    MPI_Init(&argc, & argv);
  	MPI_Comm_rank(MPI_COMM_WORLD, &rank);


    if(nb_proc!=N_PROC){
	if (rank == 0) {
	    printf("Number of procs has to be equal to %d\n",N_PROC);
	}
	MPI_Abort(MPI_COMM_WORLD,1);
	return 1;
    }

    // init of matrix a.
    // the matrix is separated on the procs in blocks
	int *a= malloc(sizeof(double)* N_LIG * N_COL);
	int *b= malloc(sizeof(double)* N_LIG * N_COL);
	
	//MPI_Scatter(void * A, N_LIG * N_COL, M);
    for(int k=0;k<N_PROC;k++){
		if(k==rank){
			printf("rank %d : a[ij]=\n",rank);
			for(i=0;i<N_LIG;i++){
				for(j=0;j<N_COL;j++){
					a[i][j] = j+ i*N_LIG + rank *N_COL;
					printf("%05.0f ",a[i][j]);
				}
			printf("\n");
			}
		}
	MPI_Barrier(MPI_COMM_WORLD);
    }


	// Communication to transpose the blocks
	int MPI_Alltoall(
		void *a, int 8, MPI_Datatype int,
		void *b, int 8, MPI_Datatype int,
		PI_COMM_WORLD
		);
    

    // Now we have to transpose the blocks:
    for(int i=0; i< N_PROC; i++){
	trans(&b[i*N_COL][0],N_COL);
    }

    // print the transpose
    for(int k=0;k<N_PROC;k++){
	if(k==rank){

	    printf("rank %d : b[ij]=\n",rank);
	    for(i=0;i<N_LIG;i++){
		for(j=0;j<N_COL;j++){
		    printf("%05.0f ",b[i][j]);
		}
		printf("\n");
	    }
	}
	MPI_Barrier(MPI_COMM_WORLD);
    }



    /* Sortie de MPI */
    MPI_Finalize();
    return 0;
}
