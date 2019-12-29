/// \file bruteforce.c
/// \author Tarek Kunze
/// \date december 2019
/// \brief Bruteforce implementation lib

#include <math.h>
#include "bruteforce.h"

double instance_distance(instance_t *instance)
{
    instance->length = 0;
    for (int i = 0; i < instance->dimension - 1; i++)
    {
        instance->length += euclidean_distance(instance->tabCoord[i][0], instance->tabCoord[i][1], instance->tabCoord[i + 1][0], instance->tabCoord[i + 1][1]);
    }
}

double euclidean_distance(long x1, long y1, long x2, long y2)
{
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

double brute_force_tsp(instance_t instance, tour_t *tournee, tour_t *pire, bool use_mat)
{
    /// \brief considère toute les permutations de la tournée initiale et garde la plus courte
    /// \brief et la pire, le point n°1 est fixe
    /// \param [in] instance : pour les points et coordonées
    /// \param [out] tournee : la meuilleure tournee
    /// \param [out] pire : la pire tournee
    /// \param [in] use_mat : flag pour indiquer si on veut utiliser la matrices des distances
    if (use_mat)
    {
        printf("Matrices des distances:\n");
    }
    else
    {
        printf("Bf normal");
    }
}

bool nextPermutation(int *array, int dim)
{
    /// \brief
}