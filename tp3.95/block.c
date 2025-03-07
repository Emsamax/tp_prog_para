/**
 * block.c --- TP3.95 :
 *                         block
 *
 * @author MMancini
 **/


#include <stdio.h>
#include <mpi.h>
/**
 * @brief block type
 **/
int main(int argc, char* argv[])
{
    int num_lin = 19, num_col = 17;
    int blk_lin = 5, blk_col = 7;
    float a[num_lin][num_col];
    int tag = 1, rank;
    MPI_Datatype type_blk;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    for(int i=0;i<num_lin;i++){for(int j=0;j<num_col;j++) a[i][j] = rank;}

    MPI_Type_vector(blk_lin, blk_col, num_col, MPI_FLOAT, &type_blk);
    MPI_Type_commit(&type_blk);

    // ???
    if(rank==0){
        // sending the first line
        // ???
        MPI_Send(&a[0][0], 1, type_blk, 1, tag, MPI_COMM_WORLD);
    }
    else if(rank==1){
        // receiving the last line
        // ???
        MPI_Recv(&a[0][0], 1, type_blk, 0, tag, MPI_COMM_WORLD, &status);

        for(int i = 0; i < num_lin; i++) {
            for(int j = 0; j < num_col; j++) {
            printf("%f ", a[i][j]);
            } printf("\n");}
    }

    MPI_Type_free(&type_blk);
    MPI_Finalize();
}
