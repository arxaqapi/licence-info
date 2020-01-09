#include "2opt.h"

bool does_it_cross(int *nodes, int n_1, int n_2, instance_t instance, bool cyclic)
{
    int back_to_basics = n_2 + 1;
    if (cyclic)
    {
        back_to_basics = 0;
    }

    if (euclidean_distance(instance.tabCoord[nodes[n_1]][0], instance.tabCoord[nodes[n_1]][1], instance.tabCoord[nodes[n_1 + 1]][0], instance.tabCoord[nodes[n_1 + 1]][1]) +
            euclidean_distance(instance.tabCoord[nodes[n_2]][0], instance.tabCoord[nodes[n_2]][1], instance.tabCoord[nodes[back_to_basics]][0], instance.tabCoord[nodes[back_to_basics]][1]) >
        euclidean_distance(instance.tabCoord[nodes[n_1]][0], instance.tabCoord[nodes[n_1]][1], instance.tabCoord[nodes[n_2]][0], instance.tabCoord[nodes[n_2]][1]) +
            euclidean_distance(instance.tabCoord[nodes[n_1 + 1]][0], instance.tabCoord[nodes[n_1 + 1]][1], instance.tabCoord[nodes[back_to_basics]][0], instance.tabCoord[nodes[back_to_basics]][1]))
    {
        return true;
    }

    return false;
}

double two_opt(int *nodes, instance_t instance)
{
    int dimension = instance.dimension;
    bool upgrade = true;
    bool temp_bool;

    int i = 0;
    int j = i;
    while (upgrade)
    {
        upgrade = false;
        while (i < dimension)
        {
            j = i + 1;
            //j != i - 1 && j != i && j != i + 1 && j < dimension
            while (j < dimension)
            {
                if (j == dimension - 1)
                {
                    temp_bool = does_it_cross(nodes, i, j, instance, true);
                }
                else
                {
                    temp_bool = does_it_cross(nodes, i, j, instance, false);
                }
                if (temp_bool)
                {
                    swap_2opt(nodes, i + 1, j);
                    upgrade = true;
                }
                j++;
            }
            i++;
        }
    }

    return array_distance(nodes, instance);
}