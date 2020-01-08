/// \file main.c
/// \author Tarek Kunze
/// \date december 2019
/// \brief Main C file

#include <stdio.h>
#include <time.h>
#include "balises.h"
#include "tspstat.h"
#include "lecture_fichier_tsplib.h"
#include "bruteforce.h"
#include "ppv.h"
#include "random_walk.h"
#include "tools.h"
#include "2opt.h"

int main(int argc, char *argv[])
{
    srand(time(NULL));

    bool file_opened = false;
    int balises[NB_BALISES];
    int *nodes;

    instance_t inst;
    double meuilleureDistance;

    analyse_balises(argc, argv, balises);
    int i = 0;

    while (i < NB_BALISES)
    {
        if (balises[BAL_F] != NIL && !file_opened)
        {
            if (lecture_fichier(argv[balises[BAL_F] + 1], &inst) != NIL)
                file_opened = true;
                nodes = creer_tab_int(inst.dimension);
        }
        else if (file_opened && balises[BAL_BF] != NIL)
        {
            if (inst.dimension <= 11)
            {
                //  bf ...
                printf("\n---- OK ----\n");
                meuilleureDistance = brute_force_tsp(&inst, false);
                printf("BF Distance : %f\n", meuilleureDistance);
            }
            else
            {
                printf("La fonction bruteforce ne sera pas exécutée, nombre de noeuds supérieur à 10\n");
            }
            anhiliation_bal(BAL_BF, balises);
        }
        else if (file_opened && balises[BAL_BFM] != NIL)
        {
            if (inst.dimension <= 11)
            {
                //  bfm ...
            }
            else
            {
                printf("La fonction bruteforce ne sera pas exécutée, nombre de noeuds supérieur à 10\n");
            }

            anhiliation_bal(BAL_BFM, balises);
        }
        else if (file_opened && balises[BAL_PPV] != NIL)
        {
            meuilleureDistance = ppv(&inst, nodes);
            printf("----------- PPV -----------\n ppv = %f\n", meuilleureDistance);
            meuilleureDistance = two_opt(nodes, inst);
            printf("----------- 2OPT -----------\n 2OPT = %f\n", meuilleureDistance);

            anhiliation_bal(BAL_PPV, balises);
        }
        else if (file_opened && balises[BAL_RW] != NIL)
        {
            meuilleureDistance = random_walk(&inst);
            printf("----------- random -----------\n random = %f\n", meuilleureDistance);

            anhiliation_bal(BAL_RW, balises);
        }
        else if (file_opened && balises[BAL_H] != NIL)
        {
            print_help();
            anhiliation_bal(BAL_H, balises);
        }

        i++;
    }

    return 0;
}