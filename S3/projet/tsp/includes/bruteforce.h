#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include "tspstat.h"
#include <math.h>

double instance_distance(instance_t *instance);
double euclidean_distance(long x1, long y1, long x2, long y2);
double brute_force_tsp(instance_t instance, tour_t *tournee, tour_t *pire, bool use_mat);
bool nextPermutation(int *array, int dim);


#endif