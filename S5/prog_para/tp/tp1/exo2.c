#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#define SIZE 20000
#define THREAD_NUMB 8

int main(int argc, char **argv) {
  int i, j, tid;
  double t, start, stop;
  double *matrice_A;

  double somme[THREAD_NUMB] = {0, 0, 0, 0, 0, 0, 0, 0};
  double somme_finale = 0;
  // Allocations
  matrice_A = (double *)malloc(SIZE * SIZE * sizeof(double));

  // Initialisations
  for (i = 0; i < SIZE; i++) {
    for (j = 0; j < SIZE; j++) {
      matrice_A[i * SIZE + j] = 0.0000001;
    }
  }
  // ------------------------------------------------------//
  //                        1) sequentiel
  // ------------------------------------------------------//
  start = omp_get_wtime();
  for (i = 0; i < SIZE; i++) {
    for (j = 0; j < SIZE; j++) {
      somme_finale += matrice_A[i * SIZE + j];
    }
  }
  stop = omp_get_wtime();
  t = stop - start;
  printf("1) Temps ex1: %f\n", t);
  printf("1) somme finale = %f\n\n", somme_finale);

  // ------------------------------------------------------//
  //              2) somme des sommes partielles
  // ------------------------------------------------------//
  somme_finale = 0;
  start = omp_get_wtime();
#pragma omp parallel num_threads(THREAD_NUMB) private(j, tid)
  {
    tid = omp_get_thread_num();
#pragma omp for
    for (i = 0; i < SIZE; i++) {
      for (j = 0; j < SIZE; j++) {
        somme[tid] += matrice_A[i * SIZE + j];
      }
    }

#pragma omp single
    {
      for (int i = 0; i < THREAD_NUMB; i++) {
        somme_finale += somme[i];
      }
    }
  }
  stop = omp_get_wtime();
  t = stop - start;
  printf("2) Temps ex2: %f\n", t);
  // main thread
  printf("2) somme finale = %f\n\n", somme_finale);

  // ------------------------------------------------------//
  //        3) somme des sommes partielles par thread
  // ------------------------------------------------------//
  // reset
  somme_finale = 0;
  for (int i = 0; i < THREAD_NUMB; i++) {
    somme[i] = 0;
  }
  start = omp_get_wtime();
#pragma omp parallel num_threads(THREAD_NUMB) private(j, tid)
  {
    tid = omp_get_thread_num();
#pragma omp for
    for (i = 0; i < SIZE; i++) {
      for (j = 0; j < SIZE; j++) {
        somme[tid] += matrice_A[i * SIZE + j];
      }
    }
// add to somme_finale
#pragma omp critical
    { somme_finale += somme[tid]; }
  }

  stop = omp_get_wtime();
  t = stop - start;
  printf("3) Temps ex3: %f\n", t);
  printf("3) somme finale = %f\n\n", somme_finale);

  // ------------------------------------------------------//
  //              4) réduction
  // ------------------------------------------------------//
  // reset
  somme_finale = 0;
  start = omp_get_wtime();
#pragma omp parallel num_threads(THREAD_NUMB) private(j) reduction(+:somme_finale)
  {
#pragma omp for
    for (i = 0; i < SIZE; i++) {
      for (j = 0; j < SIZE; j++) {
        somme_finale += matrice_A[i * SIZE + j];
      }
    }
  }
  stop = omp_get_wtime();
  t = stop - start;
  printf("4) Temps ex4: %f\n", t);
  printf("4) somme finale = %f\n\n", somme_finale);

  // Liberations
  free(matrice_A);
  return EXIT_SUCCESS;
}
