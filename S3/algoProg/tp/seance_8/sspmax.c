#include <stdio.h>
#include <assert.h>
#include  <time.h>
#define NMAX 100000

typedef long tab[NMAX];

/**
 * Calcul du poids d'un sous-séquence
 * @param deb indice du début de la sous-séquence
 * @param fin indice de la fin de la sous-séquence
 * @param t tableau t de taille max NMAX
 * @return poids de la sous-séquence
 */
long poids(long deb, long fin, tab t) {
    long poidsSousSeq = 0;
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
long f1(tab t, long taille) {
    long max = t[0];

    long maxDeb;
    long maxFin;
    long somme;

    for(long deb = 0; deb < taille; deb ++) {
        for(long fin = deb; fin < taille; fin ++) {
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
long f2(tab t, long taille) {
    long max = t[0];
    long somme;

    for(long deb = 0; deb < taille; deb ++) {
        somme = 0;
        for(long fin = deb; fin < taille; fin ++) {
            somme += t[fin];
            if(somme > max) {
                max = somme;
            }
        }
    }
    return max;
}

long f3(tab t, long taille) {
    // NOT WORKING ERROR
    // Enoncé non compris
    long res = t[0];
    long max = t[0];

    for(long deb = 1; deb < taille; deb ++) {
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

long main(void) {
    srand(time(NULL));
    //  long x = rand()%21-10;
    long max, max2, max3;

    clock_t debut = clock();
    clock_t fin = clock();


    tab testT = {-1, 3, -3, 1, 6};
    tab testT2 = {2, -1, 0, -2, 3, -4, 8, -1, 2};

    tab tableau;
    for(long i = 0; i < 100000; i++) {
        tableau[i] = rand()%21-10;
    }

    

    debut = clock();
    max2 = f2(tableau, 100000);
    fin = clock();
    printf("F2: Temps CPU:%.2fsecondes\n",(double)(fin-debut)/CLOCKS_PER_SEC);
    printf("f2: %li\n", max2);

    debut = clock();
    max3 = f3(tableau, 100000);
    fin = clock();
    printf("F3: Temps CPU:%.2fsecondes\n",(double)(fin-debut)/CLOCKS_PER_SEC);
    printf("f3: %li\n", max3);

    debut = clock();
    max = f1(tableau, 100000);
    fin = clock();
    printf("F1: Temps CPU:%.2fsecondes\n",(double)(fin-debut)/CLOCKS_PER_SEC);
    printf("f1: %li\n", max);

    return 0;
}