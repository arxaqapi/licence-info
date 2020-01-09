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
#include "display.h"
#include "ga.h"

int main(int argc, char *argv[])
{
    srand(time(NULL));

    bool file_opened = false;
    bool csv_written = false;
    int balises[NB_BALISES];
    int *nodes;
    int n_lignes = 0;

    instance_t inst;
    double meuilleureDistance;

    clock_t start;
    clock_t end;
    double duration;

    analyse_balises(argc, argv, balises);
    // for (int i = 0; i < NB_BALISES; i++)
    // {
    //     printf("B = %d\n", balises[i]);
    // }

    int i = 0;

    while (i < NB_BALISES)
    {
        if (!file_opened && balises[BAL_F] != NIL)
        {
            if (lecture_fichier(argv[balises[BAL_F] + 1], &inst, &n_lignes) != NIL)
            {
                file_opened = true;
                nodes = create_array_int(inst.dimension);

                print_entete(&inst, argv[balises[BAL_F] + 1], n_lignes);
                print_instance_csv(&inst);
            }
            else
            {
                printf("Erreur lecture du fichier de -f\n");
                return NIL;
            }
            anhiliation_bal(BAL_F, balises);
        }
        else if (file_opened && balises[BAL_O] != NIL)
        {

            to_csv_file(argv[balises[BAL_O] + 1], inst);
            // csv_written = true;

            anhiliation_bal(BAL_O, balises);
        }
        else if (file_opened && balises[BAL_BF] != NIL)
        {
            if (inst.dimension <= 11)
            {
                start = clock();
                meuilleureDistance = brute_force_tsp(&inst, false, nodes);
                end = clock();
                duration = (double)(end - start) / CLOCKS_PER_SEC;
                print_methode(false, "Bruteforce", meuilleureDistance, duration, nodes, inst.dimension);
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
            meuilleureDistance = random_walk(&inst, nodes);
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

    //meuilleureDistance = ga(inst, 0.1, 1, 1);

    return 0;
}