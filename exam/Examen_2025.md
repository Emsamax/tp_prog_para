<!-- Examen_2025.md -->
# Examen MPI/OpenMP <a id="exo_1"></a>

## 1) Exercice de parallélisation avec MPI

### Objectifs

1. L'objectif de cet exercice est de prendre un code séquentiel (***weigthed_seq.c***) calculant une **somme pondérée** d'un **vecteur** et de le paralléliser en utilisant **MPI (Message Passing Interface)**. Vous devrez diviser les données entre plusieurs processus et effectuer des communications entre ces processus pour calculer la somme pondérée de manière parallèle.

2. Une fois le code parallélisé, il faudrait varier la taille des tableaux \( N \) (64,128,256,512,1024,2048,4000,20000,40000,100000) et faire un graphique du temps de calcul \( T \)  en fonction du valeur de \( N \)  pour les deux codes, séquentiel et parallèle.
Expliquer les résultats.

#### Description du code séquentiel

Le programme séquentiel *weigthed_seq.c* effectue les opérations suivantes :

1. **Initialisation du vecteur et des poids** :
    - Un vecteur `matrix` de taille \( N \) est initialisé avec des valeurs allant de 1 à \( N \).
    - Un autre vecteur `weights` est également initialisé avec des valeurs croissantes.

2. **Calcul de la somme pondérée** :
    - Le produit de chaque élément du vecteur `matrix` et du vecteur `weights` est effectué.
    - La somme de ces produits est calculée pour obtenir la somme pondérée finale.

3. **Temps d'exécution** :
    - Le temps d'exécution du calcul est mesuré et affiché.

#### Objectifs de la parallélisation

Vous devez transformer ce code séquentiel en un programme parallèle ***weigthed_mpi.c*** en utilisant MPI. Voici les étapes à suivre pour y parvenir.

#### Étapes à suivre

1. **Initialisation de MPI** :
   - Initialiser MPI et faire une introspection. 

2. **Vérification du nombre de processus** :
   - Le programme doit être exécuté avec exactement 4 processus. Si le nombre de processus est différent, affichez un message d'erreur et terminez le programme.

3. **Initialisation des données** :
   - Le processus 0 initialise les vecteurs `matrix` et `weights`.

4. **Diffusion des données** :
   - Le processus 0 distribue les vecteurs `matrix` et `weights` aux différents processus. Chaque processus recevra une portion des vecteurs à traiter.

5. **Calcul de la somme pondérée locale** :
   - Chaque processus calcule la somme pondérée locale en multipliant les éléments locaux des vecteurs `matrix` et `weights`.
   - Conservez la somme locale dans une variable.

6. **Recuperation du résultat par processus 0** :
   - Les résultats des différents processus et obtenir la somme totale de la matrice pondérée. La somme totale sera envoyée au processus 0.

7. **Affichage du résultat et du temps d'exécution** :
   - Le processus 0 doit afficher le résultat final (la somme pondérée totale) ainsi que le temps d'exécution du calcul (utiliser le bon outil pour mesurer le temps de calcul).

8. **Finalisation de MPI**

#### Structure du programme parallèle

Le programme parallèle ***weigthed_mpi.c*** doit être structuré de la manière suivante :

- **Initialisation**.
- **Introspection**.
- **Initialisation des données** : Le processus 0 initialise les vecteurs `matrix` et `weights`.
- **Diffusion des données**.
- **Calcul de la somme pondérée locale** : Chaque processus effectue la somme locale.
- **Réduction** : Accumuler les sommes locales.
- **Affichage du résultat** : Le processus 0 affiche la somme totale et le temps d'exécution.
- **Finalisation**.

#### Code de base

Le code séquentiel de départ est le suivant (en C) :

```c
// weigthed.c
#include <stdio.h>
#include <time.h>

#define N 64

int main() {
    double result = 0.0;
    double matrix[N], weights[N];

    clock_t t0 = clock();

    for (int i = 0; i < N; i++) {
        matrix[i] = i + 1;  // Remplir le vecteur avec des valeurs de 1 à N
    }

    for (int i = 0; i < N; i++) {
        weights[i] = 0.1 * (i + 1);  // Remplir les poids
    }

    // Calcul de la somme pondérée
    for (int i = 0; i < N; i++) {
        result += matrix[i] * weights[i];
    }

    clock_t t1 = clock();

    printf("Somme pondérée : %f calculée en %f secondes\n", result, (double)(t1 - t0) / CLOCKS_PER_SEC);
    
    return 0;
}
```

---
---

## 2) Exercice : OpenMP

### Objectif

En utilisant le code séquentiel ***weigthed_seq.c*** de l'exercice précèdent ([Exercice 1](#exo_1)), écrire sa version parallèle en utilisant OpenMP ***weigthed_omp.c*** .
Répondre aux mêmes questions.

---
---

## 3) Exercice : Simulation thermique parallèle

### Objectif

Prendre le programme ***thermique_seq.c*** (qui simule une diffusion thérmique) et le paralléliser ***thermique_mpi.c*** sur une plaque 2D en utilisant :

- Allocation dynamique de mémoire

- Communicateur cartésien

- Échanges de halo avec MPI_Sendrecv

---

```c
// thermique_seq.c
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
    // Dimensions globales
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
```

### Tâches à effectuer:

- Initialisation MPI et dimensions
- Création du communicateur cartésien
- Allocation dynamique locale
- Échanges de halo avec `Sendrecv`
- Calcul parallèle

#### Validation:

- Vérifier la conservation de la température aux bords
- Comparer les résultats avec la version séquentielle
- Tester avec différentes configurations de processus

#### Bonus:

- Implémenter des conditions aux limites périodiques
- Gérer les cas où les dimensions ne sont pas parfaitement divisibles

Cet exercice combine les concepts clés de MPI : décomposition de domaine, communications non-bloquantes avec `Sendrecv`, et gestion avancée des communicateurs. Les étudiants devront gérer soigneusement l'allocation dynamique et les décalages dans les tableaux pour les couches de halo.



## 4) Exercice Bonus

### Objectif

Parallelisation Hybride d'un code avec MPI + OpenMP.

### Tâche:
Prendre le code MPI que vous avez fait dans l'[Exercice 1](#exo_1) (***weighted_mpi.c***) et y ajouter une parallelisation OpenMP pour obtenir le code ***weighted_mpi_omp.c***

#### Compilation
La compilaition d'un code hybride se fait en combianant les deux methodes vues :

```bash
mpicc -c weighted_mpi_omp.c -fopenmp -o weighted_mpi_omp
```