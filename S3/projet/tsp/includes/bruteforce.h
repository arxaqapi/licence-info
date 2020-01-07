#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include "tspstat.h"
#include <math.h>
#include "tools.h"

double brute_force_tsp(instance_t *instance, bool use_mat);
bool next_permutation(int *array, int dim);


#endif