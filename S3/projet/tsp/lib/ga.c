#include "ga.h"

tour_t *create_array_tour(int dimension)
{
    return malloc(dimension * sizeof(tour_t));
}

indices_t *create_array_indices(int dimension)
{
    return malloc(dimension * sizeof(indices_t));
}

void two_random_numbers(int *a, int *b, int dimension)
{
    do
    {
        *a = rand() % dimension;
        *b = rand() % dimension;
    } while (*a == *b);
}

void edge_destruction(tour_t *t_parent1, tour_t *t_parent2, tour_t *tfille, int dimension)
{
    copy_array(t_parent1->nodes, tfille->nodes, dimension);
    printf("into the destructor\n");
    sub_tour_t sub_tour;
    sub_tour.dimension = 0;
    sub_tour.tabIndices = create_array_indices(dimension);

    int i = 0;
    int j = i;
    while (i < dimension - 1)
    {
        while (j < dimension - 1)
        {
            /*  (i, i+1)      (j, j+1)                  */

            if (compare_slices(tfille->nodes, i, i + 1, t_parent2->nodes, j, j + 1, dimension) &&
                compare_slices(tfille->nodes, i, i + 1, rev_array(t_parent2->nodes, j, j + 1), j, j + 1, dimension) &&
                compare_slices(rev_array(tfille->nodes, i, i + 1), i, i + 1, rev_array(t_parent2->nodes, j, j + 1), j, j + 1, dimension) &&
                compare_slices(tfille->nodes, i, i + 1, rev_array(t_parent2->nodes, j, j + 1), j, j + 1, dimension))
            {
                sub_tour.tabIndices[i].deb = i;
                sub_tour.tabIndices[i].fin = i;
                sub_tour.dimension ++;
            }
            j++;
        }
        i++;
    }

    for (int i = 0; i < sub_tour.dimension; i++)
    {
        printf("Alors : deb = %d || fin = %d", sub_tour.tabIndices[i].deb, sub_tour.tabIndices[i].deb);
    }
    
}

void mutation()
{
}

void dpx(int *t_parent1, int *t_parent2, int *tfille, int *tfille_fin, int dimension)
{
    // edge_destruction(t_parent1, t_parent2, tfille, tfille_fin, dimension);
}

double ga(instance_t instance, float taux_mut, int n_individus, int n_generations)
{
    double current_distance;
    int dimension = instance.dimension;

    int n_individus_b = 20;
    int n_croisement = 1; // 1 to pop/2
    float taux_mut_b = 0.3;
    int n_generations_b = 200;

    int random_mut;

    pool_t pool;
    pool.pool_size = n_individus_b;
    pool.nodes_dimension = dimension;
    pool.array = create_array_tour(pool.pool_size);

    tour_t fille;
    fille.nodes = create_array_int(dimension);

    int i_par_1;
    int i_par_2;

    

    // create initial population N indiv randomly initialized
    // n_individus * random_walk();
    printf("in the geeeen\n");
    for (int i = 0; i < n_individus_b; i++)
    {
        pool.array[i].length = random_walk(&instance, pool.array[i].nodes);
    }
    printf("je sors?\n");
    

    two_random_numbers(&i_par_1, &i_par_2, n_individus_b);
    printf("rand ok\n");
    edge_destruction(&pool.array[i_par_1], &pool.array[i_par_2], &fille, dimension);


    // do
    // {

    //     while (n_croisement <= n_individus_b / 2)
    //     {
    //         two_random_numbers(&i_par_1, &i_par_2, dimension);
    //         // 2 randomly indiv
    //         // (DPX) faire croisement qui donne tournée fille

    //         // Faire muter fille avec prob p ()
    //         // gen nb al 0 99
    //         random_mut = rand() % 100;
    //         // random_node = rand()%instance->dimension;
    //         if (random_mut < (int)(taux_mut_b * 100))
    //         {
    //             mutation();
    //         }

    //         // remplacement indiv de la pop par la fille (hasard ou moins perf (length))
    //         n_croisement++;
    //     }
    //     n_generations_b--;
    // } while (n_generations_b > 0);

    /*
    repeat
    while (nb croisement voulu non atteint)
        select randomly 2 indiv
        faire croisement qui donne tournée fille (dpx)
        avec une prob p, faire muter la tournée fille (2 arete non consécutive et de faire une 2opt)
        remplacer une indiv de la pop par la fille (au hasard ou le moins performant)
    end
    until: fixed nb de géné OU stabilité atteinte
    */

    // free(pool.array);

    return current_distance;
}