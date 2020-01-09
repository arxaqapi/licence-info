#include "ppv.h"



int next_v(instance_t *instance, int *nodes, int zeiger)
{
    int best_node = -1;
    double dist = 100000000;
    double best_dist = dist;
    for (int i = 0; i < instance->dimension; i++)
    {
        if (!is_in_array(i, nodes, instance->dimension) && i != nodes[zeiger])
        {
            dist = euclidean_distance(instance->tabCoord[nodes[zeiger]][0], instance->tabCoord[nodes[zeiger]][1], instance->tabCoord[i][0], instance->tabCoord[i][1]);
            if (dist < best_dist)
            {
                best_dist = dist;
                best_node = i;
            }
        }
    }
    return best_node;
}


double ppv(instance_t *inst, int *nodes)
{
    int dimension = inst->dimension;
    double current_distance = 0;

    nodes[0] = 0;

    for (int i = 0; i < dimension - 1; i++)
    {
        nodes[i + 1] = next_v(inst, nodes, i);        
    }

    current_distance = array_distance(nodes, *inst);


    return current_distance;
}