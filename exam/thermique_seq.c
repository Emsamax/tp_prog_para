#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define ITER_MAX 100
#define TOL 1e-6

void init_matrix(double **plate, int M, int N) {
    // Initialisation des bords
    for(int i=0; i<M; i++) {
        plate[i][0] = 100.0; // Bord gauche
        plate[i][N-1] = 0.0; // Bord droit
    }
}

int main(int argc, char *argv[]) {
    int M = atoi(argv[1]);
    int N = atoi(argv[2]);
    double diff;
    int iter;
    double t0 = clock();

    // Allocation dynamique
    double **plate = malloc(M * sizeof(double*));
    for(int i=0; i<M; i++)
        plate[i] = malloc(N * sizeof(double));
    
    init_matrix(plate, M, N);
    
    // Simulation séquentielle
    for(iter=0; iter<ITER_MAX; iter++) {
        diff = 0.0;
        
        for(int i=1; i<M-1; i++) {
            for(int j=1; j<N-1; j++) {
                double temp = plate[i][j];
                plate[i][j] = (plate[i-1][j] + plate[i+1][j] +
                              plate[i][j-1] + plate[i][j+1]) / 4.0;
                diff += fabs(temp - plate[i][j]);
            }
        }
        
        if(diff < TOL) break;
    }

    // Nettoyage mémoire
    for(int i=0; i<M; i++) free(plate[i]);
    free(plate);

    printf("NxM : %d, Iterations : %d, Temps : %f secondes\n", N*M,iter,(double)(clock() - t0) / CLOCKS_PER_SEC);

    return 0;
}
