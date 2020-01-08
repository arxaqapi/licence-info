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


double ppv(instance_t *inst)
{
    int dimension = inst->dimension;
    // int best_nodes[dimension];    // best arr
    // int worst_nodes[dimension];   // worst arr
    int current_nodes[dimension];
    // init_array(best_nodes, dimension);
    // init_array(worst_nodes, dimension);
    // init_array(current_nodes, dimension);

    double current_distance = 0;
    // double best_distance = current_distance;
    // double worst_distance = current_distance;

    // on choisit un somet de départ = (0, 0)
    // on visite le ppv de ce sommet
    // on continue de proche en proche

    // we need to construct an array with the points
    // for each point -1 (not the current one) :
    // calc dist and keep pointer of the shortest

    // for 10 points = 10 * 10 operations

    // init point 00 in array
    current_nodes[0] = 0;
    for (int i = 0; i < dimension - 1; i++)
    {
        // calc and keep best dist and ind
        // Do not calc dist with himself
        /************* Attention c'est une boucle!! ***********/
        //      We need to skip the current one and the noes already visited

        // 
        current_nodes[i + 1] = next_v(inst, current_nodes, i);        
    }

    current_distance = array_distance(current_nodes, *inst);
    

    return current_distance;
}