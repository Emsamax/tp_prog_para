#include "mpi.h"
#include <stdio.h>
int main(int argc, char *argv[]) {
    int rank, num_proc, send_val ,recv_val;
    int tag = 100;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    recv_val = 0;
    send_val = rank+1000;
    // We define the process we'll communicate with (we suppose that we have exactly 2 processes)
    num_proc = (rank+1)%2;
    MPI_Sendrecv(&send_val,1,MPI_INT,num_proc,tag,&recv_val,1,MPI_INT,
        num_proc,tag,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    printf("Coucou, I process %d, I received %d from preocess %d \n",
    rank,recv_val,num_proc);
    MPI_Finalize();
    return 0;
}