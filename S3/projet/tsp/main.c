/// \file main.c
/// \author Tarek Kunze
/// \date december 2019
/// \brief Main C file

#include <stdio.h>
#include "balises.h"
#include "tspstat.h"
#include "lecture_fichier_tsplib.h"
#include "bruteforce.h"

int main(int argc, char *argv[])
{
    // char chemin_fichier_tsp[TAILLENOM];

    // FINAL
    // int tab_balises[NB_BALISES];

    //      analyse_balises(argc, argv, tab_balises);

    instance_t inst;
    double meuilleureDistance = 5;
    //      test = lecture_fichier("./res/att10.tsp", &inst);
    if (lecture_fichier(argv[recherche_chaine(argc, argv, "-f") + 1], &inst) != NIL)
    {
        printf("%d\n", inst.dimension);
        printf("x : %ld| y : %ld|\n", inst.tabCoord[0][0], inst.tabCoord[0][1]);
        printf("\n---- OK ----\n");
        meuilleureDistance = brute_force_tsp(&inst, false);
        printf("?\n");

        printf("BF Distance : %f\n", meuilleureDistance);
    }

    return 0;
}

// instance = le problème

// tour = le resultat