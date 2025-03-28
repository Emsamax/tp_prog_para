#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"

#define N 100000000

// Fonction pour calculer la somme pondérée
void compute_weighted_sum(double matrix[], double weights[], double *result, long int tailleBlock) {
    *result = 0.0;
    /* Les processus font (N / nbProc) calculs */
    for (long int i = 0; i < tailleBlock; i++) {
        *result += matrix[i] * weights[i]; // Additionne le produit des éléments correspondants
    }
}

int main(int argc, char *argv[]) {
    int rank;
    int nbProc = 0;
    double* matrix = malloc(N * sizeof(double));
    double* weights = malloc(N * sizeof(double));;
    double result;
    double resFinal;

    /* Initialisation de MPI */
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nbProc);

    /* Vérifier qu'il y a bien 4 processus */
    if (nbProc != 4) {
        printf("Le nombre de processus doit etre egale a 4.");
        MPI_Finalize();
        return 1;
    }

    // Capture du temps initial avant le calcul
    clock_t t0 = clock();

    /* Le processus 0 initialise la matrice et les poids */
    if (rank == 0) {
        // Initialisation de la matrice avec des valeurs de 1 à N
        for (long int i = 0; i < N; i++) {
            matrix[i] = i + 1;  // Initialise la matrice avec les valeurs de 1 à N
        }

        // Initialisation de weights avec des valeurs de 0.1 à 1.6 (selon le nombre d'éléments)
        for (long int i = 0; i < N; i++) {
            weights[i] = 0.1 * (i + 1);  // Initialise les poids
        }
    }

    /* On envoie une partie de chaque vecteur à chaque processus */
    const long int tailleBlock = N / nbProc;
    double* matriceLocal = malloc(tailleBlock * sizeof(double));
    double* weightsLocal = malloc(tailleBlock * sizeof(double));
    MPI_Scatter(matrix, tailleBlock, MPI_DOUBLE, weightsLocal, tailleBlock, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(weights, tailleBlock, MPI_DOUBLE, matriceLocal, tailleBlock, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Calcul de la somme pondérée
    compute_weighted_sum(matriceLocal, weightsLocal, &result, tailleBlock);
    //printf("Valeur calcule par proc %d : %f\n", rank, result);

    /* On récupère chaque résultats dans le processus 0 */
    MPI_Reduce(&result, &resFinal, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    
    // Capture du temps final après le calcul
    clock_t t1 = clock();

    // Affichage du résultat de la somme pondérée et du temps écoulé
    if (rank == 0) {
        printf("Somme pondérée : %f\n", resFinal );
        printf("Calculée en %f secondes\n", (double)(t1 - t0) / CLOCKS_PER_SEC );
    }

    /* Sortie de MPI */
    free(matrix);
    free(weights);
    free(matriceLocal);
    free(weightsLocal);
    MPI_Finalize();
    
    return 0;
}
