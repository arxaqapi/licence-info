#define _POSIX_C_SOURCE 1

#include "ex.h"

int afficherInfoFichier(char *nom_fichier)
{
    struct stat s;

    if (stat(nom_fichier, &s) == -1)
    {
        perror(nom_fichier);
        return ERROR_STAT;
    }

    /* Nom */
    printf("%-20s: ", nom_fichier);

    /* Type (fichier, repertoire) */
    if (S_ISREG(s.st_mode) != 0)
    {
        printf("fichier");
    }
    else if (S_ISDIR(s.st_mode))
    {
        printf("repertoire");
    }
    else
    {
        printf("ERROR");
    }

    /* taille octets */
    printf("%8ld octets  ", s.st_size);

    /*** DERNIERE MODIFICATION ***/
    /* jour, mois, date, annee */
    printf("%s", ctime(&s.st_mtime));

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Nombre de paramètres insuffisants\n");
    }

    for (int i = 1; i < argc; i++)
    {
        /* affichage des infos du fichier argv[i] */
        afficherInfoFichier(argv[i]);
    }

    return 0;
}

/* use readdir after opendir */