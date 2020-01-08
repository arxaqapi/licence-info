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

int main(int argc, char *argv[])
{
    srand(time(NULL));
    // char chemin_fichier_tsp[TAILLENOM];

    // FINAL
    // int tab_balises[NB_BALISES];

    //      analyse_balises(argc, argv, tab_balises);

    instance_t inst;
    double meuilleureDistance;
    //      test = lecture_fichier("./res/att10.tsp", &inst);
    if (lecture_fichier(argv[recherche_chaine(argc, argv, "-f") + 1], &inst) != NIL)
    {
        if (inst.dimension <= 11)
        {
            printf("\n---- OK ----\n");
            meuilleureDistance = brute_force_tsp(&inst, false);
            printf("BF Distance : %f\n", meuilleureDistance);
        }

        meuilleureDistance = ppv(&inst);
        printf("----------- PPV -----------\n ppv = %f\n", meuilleureDistance);

        meuilleureDistance = random_walk(&inst);
        printf("----------- random -----------\n random = %f\n", meuilleureDistance);
        meuilleureDistance = random_walk(&inst);
        printf("----------- random -----------\n random = %f\n", meuilleureDistance);
    }

    return 0;
}