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
    long **mat = malloc(nbRows * sizeof(long *));
    if (mat == NULL)
    {
        printf("Problème d'allocation create_long_mat !");
        exit(1);
    }
    int j;
    for (int i = 0; i < nbRows; i++)
    {
        mat[i] = malloc(nbCol * sizeof(long));
        if (mat[i] == NULL)
        {
            printf("Problème d'allocation create_long_mat !");
            exit(1);
        }
    }
    return mat;
}

void copy_array(int *array_source, int *array_destination, int dimension)
{
    for (int i = 0; i < dimension; i++)
    {
        array_destination[i] = array_source[i];
    }
}

void init_array(int *array, int dimension)
{
    for (int i = 0; i < dimension; i++)
    {
        array[i] = i;
    }
}

double array_distance(int *node_array, instance_t reference_instance)
{
    int taille = reference_instance.dimension;
    double distance = 0;
    for (int i = 0; i < taille; i++)
    {
        // printf("indice i: %d | indice in node_array: %d\n", i, node_array[i]);
        // printf("long: %ld\n", reference_instance.tabCoord[node_array[i]][0]);
    }

    for (int i = 0; i < taille - 1; i++)
    {

        distance += euclidean_distance(reference_instance.tabCoord[node_array[i]][0], reference_instance.tabCoord[node_array[i]][1],
                                       reference_instance.tabCoord[node_array[i + 1]][0], reference_instance.tabCoord[node_array[i + 1]][1]);
        // printf("i %d\n", i);
    }
    distance += euclidean_distance(reference_instance.tabCoord[node_array[0]][0], reference_instance.tabCoord[node_array[0]][1],
                                   reference_instance.tabCoord[node_array[taille - 1]][0], reference_instance.tabCoord[node_array[taille - 1]][1]);
    return distance;
}

double instance_distance(instance_t *instance)
{
    instance->length = 0;
    for (int i = 0; i < instance->dimension - 1; i++)
    {
        instance->length += euclidean_distance(instance->tabCoord[i][0], instance->tabCoord[i][1], instance->tabCoord[i + 1][0], instance->tabCoord[i + 1][1]);
    }
    instance->length += euclidean_distance(instance->tabCoord[0][0], instance->tabCoord[0][1], instance->tabCoord[instance->dimension - 1][0], instance->tabCoord[instance->dimension - 1][1]);

    return instance->length;
}

double euclidean_distance(long x1, long y1, long x2, long y2)
{
    return sqrt((double)((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

int is_in_array(int nb, int *array, int dimension)
{
    for (int i = 0; i < dimension; i++)
    {
        if (array[i] == nb)
        {
            return 1;
        }
    }
    return 0;
}

////////////////

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
