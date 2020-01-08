#ifndef OPT_H
#define OPT_H

#include "tspstat.h"
#include "tools.h"

bool does_it_cross(int *nodes, int n_1, int n_2, instance_t instance, bool cyclic);
double two_opt(int *nodes, instance_t instance);

#endif