#include <stdio.h>
#include <stdlib.h>
#include "balises.h"

void print_help()
{
    FILE* help_file = fopen("./res/help.txt", "r");
    char buffer[MAXBUF] = "";
    if (help_file != NULL)
    {
        while (fgets(buffer, MAXBUF, help_file) != NULL)
        {
            printf("%s", buffer);
        }
        fclose(help_file);
    } else
    {
        printf("Erreur d'ouverture du fichier help.txt\n");
    }
};

//  void analyse_balises(int argc, char **argv, int tab_arg[NB_BALISES]);
//  int recherche_chaine (int argc, char **argv, char *ch);