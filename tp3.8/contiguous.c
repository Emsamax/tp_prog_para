/**
 * contiguous.c --- TP3.9 :
 *                         line
 *
 * @author MMancini
 **/


#include <stdio.h>
#include <mpi.h>

/**
 * @brief Line type
 **/
int main(int argc, char* argv[])
{
    int num_lin = 5, num_col = 7;
    float a[num_lin][num_col];
    int tag = 1, rank;
    MPI_Datatype type_line;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    for(int i=0;i<num_lin;i++)
        for(int j=0;j<num_col;j++) 
            a[i][j] = rank;

    // ???
    MPI_Type_contiguous(num_col, MPI_FLOAT, &type_line);
    MPI_Type_commit(&type_line);
    

    if(rank==0) {
        // sending the first line
        //MPI_Send(&a[0][0],num_col,MPI_FLOAT,1,tag,MPI_COMM_WORLD);

        // ???
        MPI_Send(&a[0][0], 1, type_line, 1, tag, MPI_COMM_WORLD);
    }
    else if(rank==1) {
        // receiving the last line
        //MPI_Recv(&a[num_lin-1][0],num_col,MPI_FLOAT,0,tag,MPI_COMM_WORLD,&status);
        printf("test");
        // ???
        MPI_Recv(&a[num_lin-1][0], 1, type_line, 0, tag, MPI_COMM_WORLD, &status);

        for(int i = 0; i < num_lin; i++) {
            for(int j = 0; j < num_col; j++) {
                printf("%f ", a[i][j]);
            } 
        printf("\n");}
    }


    // ???
    MPI_Type_free(&type_line);
    MPI_Finalize();
}
