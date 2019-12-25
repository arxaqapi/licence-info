/// \file main.c
/// \author Tarek Kunze
/// \date december 2019
/// \brief Main C file

#include <stdio.h>
#include "balises.h"
#include "tspstat.h"


int main(int argc, char *argv[]) {
    //  char chemin_fichier_tsp[TAILLENOM];
    /*
    if (argc < 3)
    {
        printf("Vous devez au moins entrez le nom du fichier tsp avec -f\n");
        return NIL;
    } else if (!strcmp(argv[1], "-f"))
    {
        printf("Chemin fichier entré: %s\n", args[2]);
    } else {
        printf("uncaugth error\n");
    }
    */


    // FINAL
    int tab_balises[NB_BALISES];
    
    analyse_balises(argc, argv, tab_balises);
    for (int i = 0; i < NB_BALISES; i++)
    {
        printf("tab_balises: id = %d | ele = %d\n", i, tab_balises[i]);
    }
    
    return 0;
}