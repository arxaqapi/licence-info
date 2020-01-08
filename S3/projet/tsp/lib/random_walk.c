#include "random_walk.h"



int next_random(instance_t *instance, int *nodes, int zeiger)
{   

    int random_node;
    do
    {
        random_node = rand()%instance->dimension;
    } while (is_in_array(random_node, nodes, instance->dimension) && random_node != nodes[zeiger]);
    
    return random_node;
}

double random_walk(instance_t *inst)
{
    int dimension = inst->dimension;
    int current_nodes[dimension];
    
    double current_distance;

    current_nodes[0] = 0;
    for (int i = 0; i < dimension - 1; i++)
    {
        current_nodes[i + 1] = next_random(inst, current_nodes, i);        
    }

    current_distance = array_distance(current_nodes, *inst);
    

    return current_distance;
}