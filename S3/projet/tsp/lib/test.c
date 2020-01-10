#include "test.h"

bool is_array_random(int *nodes, int dimension)
{
    for (int i = 0; i < dimension - 1; i++)
    {
        for (int j = i + 1; j < dimension; j++)
        {
            if (i != j && nodes[i] == nodes[j])
            {
                return false;
            }
        }
    }
    return true;
}

// void test_rand()
// {
//     int pool_size = 100;
//     int nodes_mat[pool_size][dimension];
//     for (int i = 0; i < count; i++)
//     {
//         /* code */
//     }
    
// }