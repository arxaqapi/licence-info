/// \file main.c
/// \author Tarek Kunze
/// \date december 2019
/// \brief Main C file

#include <stdio.h>
#include "balises.h"
#include "tspstat.h"
#include "lecture_fichier_tsplib.h"
#include "bruteforce.h"

int main(int argc, char *argv[]) {
    char chemin_fichier_tsp[TAILLENOM];


    // FINAL
    int tab_balises[NB_BALISES];
    
    //      analyse_balises(argc, argv, tab_balises);
    
    instance_t inst;
    int test;
    //      test = lecture_fichier("./res/att10.tsp", &inst);
    test = lecture_fichier(argv[recherche_chaine(argc, argv, "-f") + 1], &inst);

    printf("Distance : %f\n", instance_distance(&inst));
    return 0;
}


// instance = le problème

// tour = le resultat