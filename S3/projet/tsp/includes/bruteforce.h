#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include "tspstat.h"
#include <math.h>
#include "tools.h"

void init_tour_bf(tour_t *tour_a_init, instance_t instance);
double array_distance(int *node_array, instance_t reference_instance);
double instance_distance(instance_t *instance);
double euclidean_distance(long x1, long y1, long x2, long y2);
double brute_force_tsp(instance_t instance, tour_t *tournee, tour_t *pire, bool use_mat);
bool next_permutation(int *array, int dim);


#endif