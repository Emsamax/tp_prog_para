
#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

int main (int argc, char* argv[]){

  int i,my_id, num_procs,N=50;
  int array[N],array_final_sum[N],array_final_mult[N];
  int r_num,max_value;
  unsigned seed;
  double t0, t1, time;

  // ????

 /*initialization */
  t0 = MPI_Wtime();
  for(i=0;i<N;i++){
    array[i]=my_id +1 ;
  }

/* sum and multiplication */
  // ???
  // ???
  if(my_id == 0) {
    for(i=0;i<N;i++) printf("Final array after sum: %d\n", array_final_sum[i]);
  }
  if(my_id == 0) {
    for(i=0;i<N;i++) printf("Final array after product: %d\n", array_final_mult[i]) ;
  }

/* random number generation */
  seed=my_id+1;
  srand(seed);
  r_num=rand();
  printf("my id is %d and r_num is %d\n", my_id,r_num);

/* calculus of maximum */
   // ???



/*sleep(10); */

/* time calculation */
  t1 = MPI_Wtime();
  time = t1 - t0 ;

  if(my_id == 0) {
  printf("Max_value is (AND THE WINNER IS ....): %d\n", max_value) ;
  printf("Total elapsed time [sec] : %f\n", time);
  }


  MPI_Finalize();
  return 0;
}
