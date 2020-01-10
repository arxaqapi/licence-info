#include "2opt.h"

bool onSegment(int p, int q, int r, instance_t inst, int *nodes)
{
    if (inst.tabCoord[nodes[q]][0] <= max(inst.tabCoord[nodes[p]][0], inst.tabCoord[nodes[r]][0]) && inst.tabCoord[nodes[q]][0] >= min(inst.tabCoord[nodes[p]][0], inst.tabCoord[nodes[r]][0]) &&
        inst.tabCoord[nodes[q]][1] <= max(inst.tabCoord[nodes[p]][1], inst.tabCoord[nodes[r]][1]) && inst.tabCoord[nodes[q]][1] >= min(inst.tabCoord[nodes[p]][1], inst.tabCoord[nodes[r]][1]))
        return true;

    return false;
}

long orientation(int p, int q, int r, instance_t inst, int *nodes)
{
    long val = (inst.tabCoord[nodes[q]][1] - inst.tabCoord[nodes[p]][1]) * (inst.tabCoord[nodes[r]][0] - inst.tabCoord[nodes[q]][0]) -
               (inst.tabCoord[nodes[q]][0] - inst.tabCoord[nodes[p]][0]) * (inst.tabCoord[nodes[r]][1] - inst.tabCoord[nodes[q]][1]);

    if (val == 0)
        return 0; // colinear

    return (val > 0) ? 1 : 2; // clock or counterclock wise
}

bool do_intersect(int p1, int q1, int p2, int q2, instance_t instance, int *nodes)
{
    int o1 = orientation(p1, q1, p2, instance, nodes);
    int o2 = orientation(p1, q1, q2, instance, nodes);
    int o3 = orientation(p2, q2, p1, instance, nodes);
    int o4 = orientation(p2, q2, q1, instance, nodes);

    // General case
    if (o1 != o2 && o3 != o4)
        return true;

    // Special Cases
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1, instance, nodes))
        return true;

    // p1, q1 and q2 are colinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1, instance, nodes))
        return true;

    // p2, q2 and p1 are colinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2, instance, nodes))
        return true;

    // p2, q2 and q1 are colinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2, instance, nodes))
        return true;

    return false;
}

double two_opt(int *nodes, instance_t instance)
{
    int dimension = instance.dimension;

    double distance;
    double new_distance;

    for (int x = 0; x < dimension - 1; x++)
    {
        for (int y = x + 2; y < dimension - 1; y++)
        {
            if (do_intersect(x, x + 1, y, y + 1, instance, nodes))
            {

                distance = array_distance(nodes, instance);

                swap_2opt(nodes, x + 1, y);

                new_distance = array_distance(nodes, instance);

                if (new_distance > distance)
                {
                    swap_2opt(nodes, x + 1, y);
                }
            }
        }
    }

    return array_distance(nodes, instance);
}