/// \file bruteforce.c
/// \author Tarek Kunze
/// \date december 2019
/// \brief Bruteforce implementation lib

#include <math.h>
#include "bruteforce.h"

//
// 0 Ne BOUGE PAS
//
/////////

double brute_force_tsp(instance_t *instance, bool use_mat)
{
    /// \brief considère toute les permutations de la tournée initiale et garde la plus courte
    /// \brief et la pire, le point n°1 est fixe
    /// \param [in] instance : pour les points et coordonées
    /// \param [in] use_mat : flag pour indiquer si on veut utiliser la matrices des distances

    //  Variables
    int dimension = instance->dimension;

    int best_nodes[dimension];    // best arr
    int worst_nodes[dimension];   // worst arr
    int current_nodes[dimension]; // tour en cour
    init_array(best_nodes, dimension);
    init_array(worst_nodes, dimension);
    init_array(current_nodes, dimension);

    double current_distance = array_distance(current_nodes, *instance);
    
    double best_distance = current_distance;
    double worst_distance = current_distance;

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
            current_distance = array_distance(current_nodes, *instance);

            // maj de >+ et >-
            if (current_distance <= best_distance)
            {
                copy_array(current_nodes, best_nodes, dimension);
                best_distance = current_distance;
            }
            if (current_distance > worst_distance)
            {
                copy_array(current_nodes, worst_nodes, dimension);
                worst_distance = current_distance;
            }
            // length a recalc * 2 || Pas besoin !
        } while (next_permutation(current_nodes + 1, dimension));
    }
    printf("best array : [");
    for (int i = 0; i < dimension; i++)
    {
        printf("%d,", best_nodes[i]);
    }
    printf("]\n");
    return best_distance;
}

bool next_permutation(int *array, int dim)
{
    /// \brief Computes the next lexicographical permutation of the specified
    /// \brief array of integers in place, returning a Boolean to indicate
    /// \brief whether a next permutation existed. (Returns false when the
    /// \brief argument is already the last possible permutation.)
    // Find non-increasing suffix
    dim--;
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