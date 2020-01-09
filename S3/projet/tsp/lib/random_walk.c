#include "random_walk.h"



int next_random(instance_t *instance, int *nodes, int zeiger)
{   

    int random_node;
    do
    {
        random_node = rand()%instance->dimension;
    } while (is_in_array(random_node, nodes, instance->dimension) && random_node/* == nodes[zeiger]*/);
    
    return random_node;
}

double random_walk(instance_t *inst, int *nodes)
{
    int dimension = inst->dimension;
    
    double current_distance;

    nodes[0] = 0;
    for (int i = 0; i < dimension - 1; i++)
    {
        nodes[i + 1] = next_random(inst, nodes, i);        
    }

    current_distance = array_distance(nodes, *inst);
    
    return current_distance;
}