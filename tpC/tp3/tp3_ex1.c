/*  ## MALLOC a éviter
#include <stdio.h>

int main() {
    int nbrVal;
    printf("Nombre de valeur contenu dans le tableau (doit etre inférieur a 100): ");
    scanf("%d", &nbrVal);

    int tableau[nbrVal];

    for(int i = 0; i < nbrVal; i++)
    {
        scanf("%d", &tableau[i]);
    }
    
    for(int i = 0; i < nbrVal; i++)
    {
        printf("%d\n", tableau[i]);
    }
    
    return 0;
} */
#include <stdio.h>

#define MAX_TAB 100

int main() 
{
    int nbrVal;
    int tableau[MAX_TAB];
    int moyenne = 0;

    printf("Nombre de valeur contenu dans le tableau (doit etre inférieur a 100): ");
    scanf("%d", &nbrVal);

    for(int i = 0; i < nbrVal; i++)
    {
        scanf("%d", &tableau[i]);
    }
    
    for(int i = 0; i < nbrVal; i++)
    {
        moyenne = moyenne + tableau[i];
    }

    moyenne = moyenne/nbrVal;
    printf("Moyenne = %d\n", moyenne);

    for(int i = 0; i < nbrVal; i++)
    {
        if (tableau[i] > moyenne)
        {
            printf("%d\n", tableau[i]);
        }
        
    }
    
    return 0;
}