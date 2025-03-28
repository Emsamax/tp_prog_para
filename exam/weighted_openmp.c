#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "omp_repair.h"

#define N 100000

int main() {
    double result = 0.0;
    double *matrix = malloc(N * sizeof(double));
    double *weights= malloc(N * sizeof(double));

    // Capture du temps initial avant le calcul
    clock_t t0 = clock();

    // Initialisation de la matrice avec des valeurs de 1 à N
    // Initialisation de weights avec des valeurs de 0.1 à 1.6 (selon le nombre d'éléments)
    #pragma omp parallel for
    for (long int i = 0; i < N; i++) {
        weights[i] = 0.1 * (i + 1);  // Initialise les poids
        matrix[i] = i + 1;  // Initialise la matrice avec les valeurs de 1 à N
    }

    // Calcul de la somme pondérée
    #pragma omp parallel for reduction(+:result)
        for (long int i = 0; i < N; i++) {
            result += matrix[i] * weights[i]; // Additionne le produit des éléments correspondants
        }
    
    // Capture du temps final après le calcul
    clock_t t1 = clock();

    // Affichage du résultat de la somme pondérée et du temps écoulé
    printf("Somme pondérée : %f calculée en %f secondes\n", result, (double)(t1 - t0) / CLOCKS_PER_SEC );
    
    free(matrix);
    free(weights);

    return 0;
}