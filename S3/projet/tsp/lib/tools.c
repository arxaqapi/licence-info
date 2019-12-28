/// \file tools.c
/// \author Vincent Dugat
/// \date summer 2019
/// \brief fonctions diverses

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "tools.h"






long **create_long_mat(int nbRows, int nbCol)
{
    long **tab = (long **)malloc(nbRows * sizeof(long *));
    for (int i = 0; i < nbRows; i++)
        tab[i] = (long *)malloc(nbCol * sizeof(long));
    return tab;
}








void erreur(char *message)
{
    /// \brief imprime à l'écran un message d'erreur (chaîne de caractères)
    /// \brief le message est sensé être composé du nom du sous-programme+" : "+message d'erreur
    /// \param[in] message : le message à imprimer
    printf("*** ERREUR : %s ***\n", message);
    exit(1);
}

int random_node(int min, int max)
{
    /// \brief crée un nombre aléatoire entre min et max
    /// \returns le nombre
    return (rand() % (max - min)) + min;
}

int *creer_tab_int(int dim)
{
    /// \brief crée un tableau dynamique d'entiers de dim cases
    /// \param[in] dim : la dimension du tableau voulu
    /// \returns adresse du tableau
    return (int *)malloc(dim * sizeof(int));
}

char *creer_tab_char(int dim)
{
    /// \brief crée un tableau dynamique de char de dim cases
    return (char *)malloc(dim * sizeof(char));
}

void affiche_tab_int(int *tab, int dim, FILE *logfp)
{
    fprintf(logfp, "[");
    for (int i = 0; i < dim - 1; i++)
        fprintf(logfp, "%d,", tab[i]);
    fprintf(logfp, "%d]\n", tab[dim - 1]);
}

void affiche_tab_char_hex(char *tab, int dim, FILE *logfp)
{
    for (int i = 0; i < dim; i++)
        fprintf(logfp, "%x", tab[i]);
    fprintf(logfp, "\n");
}

void affiche_tab_char(char *tab, int dim, FILE *logfp)
{
    for (int i = 0; i < dim; i++)
        fprintf(logfp, "%c", tab[i]);
    fprintf(logfp, "\n");
}

int **creer_mat_int(int nbRows, int nbCol)
{
    int **tab = (int **)malloc(nbRows * sizeof(int *));
    for (int i = 0; i < nbRows; i++)
        tab[i] = (int *)malloc(nbCol * sizeof(int));
    return tab;
}

double **creer_mat_dist(int dimension)
{
    /// \brief crée la matrice carrées des distances = tab dynamique triangulaire
    /// \brief chaque ligne a une case de moins que la précédente
    double **tab = (double **)malloc(dimension * sizeof(double *));
    for (int i = 0; i < dimension; i++)
        tab[i] = (double *)malloc(dimension * sizeof(double));
    dimension--;
    return tab;
}

void swap(int *tab, int ind1, int ind2)
/// \brief inverse le contenu des cases ind1 et ind2 dans tab
/// \param[in,out] tab : le tableau
/// \param[in] ind1 : premier indice
/// \param[in] ind2 : deuxième indice
/// \post *tab[ind1]=*TAB[ind2] && *tab[ind2]=*TAB[ind1]
{
    int temp;
    temp = tab[ind1];
    tab[ind1] = tab[ind2];
    tab[ind2] = temp;
}

void renverse_tab(int *tab, int prem, int der)
{
    /// \brief reverse le contenu du tableau entre les indices prem et der
    /// \param[in,out] tab : le tableau à modifier
    /// \param[in] prem : indice de début
    /// \param[in] der : indice de fin
    int ind;
    int dim = der - prem + 1;

    for (ind = 0; ind < dim / 2; ind++)
        swap(tab, prem + ind, der - ind);
}
