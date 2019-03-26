#include <stdio.h>

#define VAL 30
#define VOY 6

int main() // ex2.1
{
    char phrase[VAL];
    char voyelles[VOY] = {'a', 'e', 'i', 'o', 'u', 'y'};
    int compteur = 0, compteurVoyelles = 0, i = 0, testLow, testInte = 0;

    printf("Enter character array: ");
    scanf("%s", &phrase);

    while((phrase[i] != '#') && (testInte == 0))
    {
        compteur ++;
        for(int y = 0; y < VOY; y++)
        {
            if (phrase[i] == voyelles[y])
            {
                compteurVoyelles ++;
            }
        }
        
        testLow = isupper(phrase[i]);
        if(testLow != 0)
        {
            testInte = 1;
        }
        i ++;
    }
    if(testInte == 1)
    {
        printf("Erreur charac n°: %d", i);
    }else {
        printf("Total count of elements is : %d and the total count of vowels is : %d\n", compteur, compteurVoyelles);
    }
    return 0;
}  
/*
int main()
{
    char phrase[VAL];
    char voyelles[VOY] = {'a', 'e', 'i', 'o', 'u', 'y'};
    int compteur = 0, compteurVoyelles = 0, i = 0;

    printf("Enter character array: ");
    scanf("%s", &phrase);

    while(phrase[i] != '#')
    {
        compteur ++;
        for(int y = 0; y < VOY; y++)
        {
            if (phrase[i] == voyelles[y])
            {
                compteurVoyelles ++;
            }
        }
        i ++;
    }
    printf("Total count of elements is : %d and the total count of vowels is : %d\n", compteur, compteurVoyelles);
    return 0;
}*/