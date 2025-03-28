#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 64

// Fonction pour calculer la somme pondérée
void compute_weighted_sum(double matrix[N], double weights[N], double *result) {
    *result = 0.0;
    for (long int i = 0; i < N; i++) {
        *result += matrix[i] * weights[i]; // Additionne le produit des éléments correspondants
    }
}

int main() {
    double result;
    double *matrix = malloc(N * sizeof(double));
    double *weights= malloc(N * sizeof(double));

    // Capture du temps initial avant le calcul
    clock_t t0 = clock();

    // Initialisation de la matrice avec des valeurs de 1 à N
    for (long int i = 0; i < N; i++) {
        matrix[i] = i + 1;  // Initialise la matrice avec les valeurs de 1 à N
    }

    // Initialisation de weights avec des valeurs de 0.1 à 1.6 (selon le nombre d'éléments)
    for (long int i = 0; i < N; i++) {
        weights[i] = 0.1 * (i + 1);  // Initialise les poids
    }

    // Calcul de la somme pondérée
    compute_weighted_sum(matrix, weights, &result);
    
    // Capture du temps final après le calcul
    clock_t t1 = clock();

    // Affichage du résultat de la somme pondérée et du temps écoulé
    printf("Somme pondérée : %f calculée en %f secondes\n", result, (double)(t1 - t0) / CLOCKS_PER_SEC );
    
    free(matrix);
    free(weights);

    return 0;
}