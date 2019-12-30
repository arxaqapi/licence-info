/// \file bruteforce.c
/// \author Tarek Kunze
/// \date december 2019
/// \brief Bruteforce implementation lib

#include <math.h>
#include "bruteforce.h"

void init_tour_bf(tour_t *tour_a_init, instance_t instance)
{
    strcpy(tour_a_init->name, instance.name);
    tour_a_init->dimension = instance.dimension;
    tour_a_init->tour = creer_tab_int(tour_a_init->dimension);
    for (int i = 0; i < instance.dimension; i++)
    {
        tour_a_init->tour[i] = i + 1;
    }
}

double array_distance(int *node_array, instance_t reference_instance)
{
    int taille = reference_instance.dimension;
    double distance = 0;
    for (int i = 0; i < taille; i++)
    {
        distance += euclidean_distance(reference_instance.tabCoord[node_array[i]][0], reference_instance.tabCoord[node_array[i]][1], reference_instance.tabCoord[node_array[i] + 1][0], reference_instance.tabCoord[node_array[i] + 1][1]);
    }
    return distance;
}

double instance_distance(instance_t *instance)
{
    instance->length = 0;
    for (int i = 0; i < instance->dimension - 1; i++)
    {
        instance->length += euclidean_distance(instance->tabCoord[i][0], instance->tabCoord[i][1], instance->tabCoord[i + 1][0], instance->tabCoord[i + 1][1]);
    }
    return instance->length;
}

double euclidean_distance(long x1, long y1, long x2, long y2)
{
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

double brute_force_tsp(instance_t instance, tour_t *best_tour, tour_t *worst_tour, bool use_mat)
{
    /// \brief considère toute les permutations de la tournée initiale et garde la plus courte
    /// \brief et la pire, le point n°1 est fixe
    /// \param [in] instance : pour les points et coordonées
    /// \param [out] tournee : la meuilleure tournee
    /// \param [out] pire : la pire tournee
    /// \param [in] use_mat : flag pour indiquer si on veut utiliser la matrices des distances

    // init tour
    tour_t bf_tour;
    bf_tour.tour = creer_tab_int(bf_tour.dimension);
    init_tour_bf(&bf_tour, instance);

    if (use_mat)
    {
        printf("Matrices des distances:\n");
    }
    else
    {
        printf("Bf normal\n");
        do
        {
            // calcul de la longeur du nvx segments
            // mise a jour de bf_tour
            bf_tour.length = array_distance(bf_tour.tour, instance);
            // maj de >+ et >-
            if (bf_tour.length > worst_tour->length)
            {
                for (int i = 0; i < bf_tour.dimension; i++)
                {
                    worst_tour->tour[i] = bf_tour.tour[i];
                }
            }
            else if (bf_tour.length < best_tour->length)
            {
                for (int i = 0; i < bf_tour.dimension; i++)
                {
                    best_tour->tour[i] = bf_tour.tour[i];
                }
            }
        } while (next_permutation(bf_tour.tour, bf_tour.dimension));
    }
    return best_tour->length;
}

bool next_permutation(int *array, int dim)
{
    /// \brief Computes the next lexicographical permutation of the specified
    /// \brief array of integers in place, returning a Boolean to indicate
    /// \brief whether a next permutation existed. (Returns false when the
    /// \brief argument is already the last possible permutation.)
    // Find non-increasing suffix
    if (dim == 0)
    {
        return false;
    }
    size_t i = dim - 1;
    while (i > 0 && array[i - 1] >= array[i])
    {
        i--;
    }
    if (i == 0)
    {
        return false;
    }

    // Find successor to pivot
    size_t j = dim - 1;
    while (array[j] <= array[i - 1])
    {
        j--;
    }
    int temp = array[i - 1];
    array[i - 1] = array[j];
    array[j] = temp;

    // Reverse suffix
    j = dim - 1;
    while (i < j)
    {
        temp = array[i];
        array[i] = array[j];
        array[j] = temp;
        i++;
        j--;
    }
    return true;
}