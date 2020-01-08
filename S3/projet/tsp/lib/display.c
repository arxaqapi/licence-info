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