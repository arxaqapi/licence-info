#include "lecture_fichier_tsplib.h"

bool prefix(char *motif, char *buf)
{
    return !strcmp(motif, buf);
}


int lecture_fichier(char *filename, instance_t *instance)
{
    FILE* tsp_prob_file = fopen(filename, "r");
    char buffer[MAXBUF] = "";

    if (tsp_prob_file != NULL)
    {
        while (fgets(buffer, MAXBUF, tsp_prob_file) != NULL)
        {
            analyse_ligne(buffer, instance);
            printf("%s", buffer);
        }        
        
    } else
    {
        printf("Error reading input file\n");
        return NIL;
    }
}


void analyse_ligne(char *ligne, instance_t *instance)
{
    /// \brief Prend une ligne, la découpe et teste a qui ca correspond
    /// \brief (remplace un espace avec un \0)
    char first_word[MAXBUF] = "";

    int i = 0;
    while (ligne[i] != ' ')
    {
        first_word[i] = ligne[i];
        i ++;
    }
    first_word[i] = '\0';
    printf(":: %s\n", first_word);
}
// instance = le problème

// tour = le resultat