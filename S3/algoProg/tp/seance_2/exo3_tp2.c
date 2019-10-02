/*  dynamique
* int N;
* int P;
* int **m = malloc(N*sizeof(int*));
* int i = 0;
* for(i = 0; i < N; i++) {
*   int* m[i] = malloc(P*sizeof(int));
* }
*for(i=0; i < N; i++) {
* free(m[i]);
* }
* free(m);
*/

// probleme de fuite de mémoire: pas de free lors de malloc, prog stoppe instant
// /!\ faire attention lors du free de matrices, pour éviter la perte d'adresse des zones mémoires contenant les tableaux
#include <stdlib.h>
#include <stdio.h>

int main(void) {
  return 0;
}
