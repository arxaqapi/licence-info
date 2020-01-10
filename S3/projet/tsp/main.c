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

// extern bool sans_zero;
bool sans_zero = false;

int main(int argc, char *argv[])
{
    srand(time(NULL));

    bool file_opened = false;
    bool m_written = false;
    bool b_rw = false;
    bool b_ppv = false;

    
    
    int balises[NB_BALISES];

    init_balises(balises);

    int *nodes;
    int *ppv_nodes;
    int *rw_nodes;

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

    if (argc <= 1)
    {
        printf("Erreur, paramètres manquant, utiliser l'option -h pour afficher l'aide\n");
        return 1;
    }

    int i = 0;

    while (i < NB_BALISES)
    {
        if (balises[BAL_ZERO] != NIL)
        {
            sans_zero = true;
        }
        if (!file_opened && balises[BAL_F] != NIL)
        {
            if (lecture_fichier(argv[balises[BAL_F] + 1], &inst) != NIL)
            {
                file_opened = true;
                nodes = create_array_int(inst.dimension);
                ppv_nodes = create_array_int(inst.dimension);
                rw_nodes = create_array_int(inst.dimension);

                print_entete(&inst, argv[balises[BAL_F] + 1]);
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
                print_methode(&m_written, "Bruteforce", meuilleureDistance, duration, nodes, inst.dimension);
                free(nodes);
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
            start = clock();
            meuilleureDistance = ppv(&inst, ppv_nodes);
            end = clock();
            duration = (double)(end - start) / CLOCKS_PER_SEC;
            print_methode(&m_written, "PPV", meuilleureDistance, duration, ppv_nodes, inst.dimension);

            // free(ppv_nodes);
            b_ppv = true;
            anhiliation_bal(BAL_PPV, balises);
        }
        else if (file_opened && balises[BAL_RW] != NIL)
        {
            start = clock();
            meuilleureDistance = random_walk(&inst, rw_nodes);
            end = clock();
            duration = (double)(end - start) / CLOCKS_PER_SEC;
            print_methode(&m_written, "Random walk", meuilleureDistance, duration, rw_nodes, inst.dimension);
            // free(rw_nodes);

            b_rw = true;
            anhiliation_bal(BAL_RW, balises);
        }
        else if (file_opened && balises[BAL_2OPT] != NIL)
        {
            if (balises[BAL_PPV] != NIL || b_ppv)
            {
                start = clock();
                meuilleureDistance = two_opt(ppv_nodes, inst);
                end = clock();
                duration = (double)(end - start) / CLOCKS_PER_SEC;
                print_methode(&m_written, "2OPT ppv", meuilleureDistance, duration, ppv_nodes, inst.dimension);
                // free(ppv_nodes);
                b_ppv = false;
            }
            if (balises[BAL_RW] != NIL || b_rw)
            {
                start = clock();
                meuilleureDistance = two_opt(rw_nodes, inst);
                end = clock();
                duration = (double)(end - start) / CLOCKS_PER_SEC;
                print_methode(&m_written, "2OPT random walk", meuilleureDistance, duration, rw_nodes, inst.dimension);
                // free(rw_nodes);
                b_rw = false;
            }
            anhiliation_bal(BAL_2OPT, balises);
        }
        else if (file_opened && balises[BAL_GA] != NIL)
        {
            printf("Implementation de l'algo génétique non terminée\n");
            anhiliation_bal(BAL_GA, balises);
        }
        else if (file_opened && balises[BAL_H] != NIL)
        {
            print_help();
            anhiliation_bal(BAL_H, balises);
        }

        i++;
    }

    // meuilleureDistance = ga(inst, 0.1, 1, 1);

    return 0;
}