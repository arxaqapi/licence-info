#include "display.h"


void instance_to_csv(instance_t *instance)
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