#include <stdio.h>
#include <assert.h>
#define NMAX 1000

typedef int tab[NMAX];


/**
 * Calcul du poids d'un sous-séquence
 * @param deb indice du début de la sous-séquence
 * @param fin indice de la fin de la sous-séquence
 * @param t tableau t de taille max NMAX
 * @return poids de la sous-séquence
 */
int poids(int deb, int fin, tab t) {
    int poidsSousSeq = 0;
    for(; deb <= fin; deb ++) {
        poidsSousSeq += t[deb];
    }
    return poidsSousSeq;
}

/**
 * Solution naïve O(n³)
 * @param t tableau t de taille max NMAX
 * @param taille taille du tableau
 * @return poids de la sous-séquence de poids max
 */
int f1(tab t, int taille) {
    int max = t[0];

    int maxDeb;
    int maxFin;
    int somme;

    for(int deb = 0; deb < taille; deb ++) {
        for(int fin = deb; fin < taille; fin ++) {
            somme = poids(deb, fin, t);
            if(somme > max) {
                max = somme;
                maxDeb = deb;
                maxFin = fin;
            }
        }
    }
    return max;
}

/**
 * Solution naïve O(n²)
 * @param t tableau t de taille max NMAX
 * @param taille taille du tableau
 * @return poids de la sous-séquence de poids max
 */
int f2(tab t, int taille) {
    int max = t[0];
    int somme;

    for(int deb = 0; deb < taille; deb ++) {
        somme = 0;
        for(int fin = deb; fin < taille; fin ++) {
            somme += t[fin];
            if(somme > max) {
                max = somme;
            }
        }
    }
    return max;
}

int f3(tab t, int taille) {
    // NOT WORKING ERROR
    // Enoncé non compris
    int res = t[0];
    int max = t[0];

    for(int deb = 1; deb < taille; deb ++) {
        if (res > 0) {
            res += t[deb];
        } else {
            res = t[deb];
        }
        if (res > max) {
            max = res;
        }
    }
    return max;
}

int main(void) {
    int max, max2, max3;

    tab testT = {-1, 3, -3, 1, 6};
    tab testT2 = {2,-1,0,-2,3,-4,8,-1,2};

    max = f1(testT, 5);
    max2 = f2(testT, 5);
    max3 = f3(testT, 5);
    printf("f1: %d\n", max);
    printf("f2: %d\n", max2);
    printf("f3: %d\n", max3);
    return 0;
}