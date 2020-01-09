#include "display.h"

int to_csv_file(char *filename, instance_t instance)
{
    FILE *csv_file;
    csv_file = fopen(filename, "w");
    if (csv_file != NULL)
    {
        fprintf(csv_file, "%s\n", "*** Instance ***");
        fprintf(csv_file, "%s %s\n", "Nom de l'instance ;", instance.name);
        fprintf(csv_file, "%s %d\n", "Nombre de villes (avec (0,0)) ;", instance.dimension);
        fprintf(csv_file, "%s %s\n", "Type", instance.type);
        fprintf(csv_file, "%s\n", "Point ; Abscisse ; Ordonnée");
        for (int i = 0; i < instance.dimension; i++)
        {
            fprintf(csv_file, "%6d ; %6ld ; %6ld\n", i, instance.tabCoord[i][0], instance.tabCoord[i][1]);
        }
    }
    else
    {
        printf("Erreur dans la création du fichier: %s", filename);
        return NIL;
    }

    return 1;
}

void print_entete(instance_t *instance, char *filename)
{
    printf("J'ouvre le fichier : %s\n", filename);
    printf("Commentaire : %s\n", instance->comment);
    printf("%d lignes lues\n", instance->dimension + 7);
    printf("EOF\n");
}

void print_instance_csv(instance_t *instance)
{
    printf("\n*** Instance ***\n");
    printf("Nom de l'instance ; %s\n", instance->name);
    printf("Nombre de villes (avec (0,0)) ; %d\n", instance->dimension);
    printf("Type %s\n", instance->type);
    printf("Point ; Abscisse ; Ordonnée\n");
    for (int i = 0; i < instance->dimension; i++)
    {
        printf("%6d ; %6ld ; %6ld\n", i, instance->tabCoord[i][0], instance->tabCoord[i][1]);
    }
    printf("\n");
}

void print_methode(bool al_an, char *m_name, double final_length, double time, int *final_nodes, int dimension)
{
    if (!al_an)
    {
        printf("Méthode ; longueur ; Temps CPU (sec) ; Tour\n");
        al_an = true;
    }
    printf("%s ; %.2f ; %.2f ; ", m_name, final_length, time);

    printf("[");
    for (int i = 0; i < dimension; i++)
    {
        printf("%d", final_nodes[i]);
        if (i < dimension - 1)
        {
            printf(",");
        }
    }
    printf("]\n");
}