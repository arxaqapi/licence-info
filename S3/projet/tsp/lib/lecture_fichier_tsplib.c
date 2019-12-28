#include "lecture_fichier_tsplib.h"

bool prefix(char *motif, char *buf)
{
    return !strcmp(motif, buf);
}

void get_first_word(char *line, char *first_word)
{

    int i = 0;
    while (line[i] != ' ' && line[i] != '\n')
    {
        first_word[i] = line[i];
        i++;
    }
    first_word[i] = '\0';
}

void get_field_value(char *line, char *field_value)
{
    int i = 0;
    while (line[i] != ':')
    {
        i++;
    }
    i += 2;
    int j = 0;
    while (line[i] != '\0' && line[i] != '\n' && j < i)
    {
        field_value[j] = line[i];
        i++;
        j++;
    }
    field_value[j] = '\0';
}

int lecture_fichier(char *filename, instance_t *instance)
{
    FILE *tsp_prob_file = fopen(filename, "r");
    int c = 0;
    int dim = 0;
    char buffer[MAXBUF] = "";

    int poubelle;

    if (tsp_prob_file != NULL)
    {
        while (fgets(buffer, MAXBUF, tsp_prob_file) != NULL)
        {
            c++;
            if (c > 5 && dim < instance->dimension)
            {
                instance->tabCoord = create_long_mat(instance->dimension, 2);
                for (int i = 0; i < instance->dimension; i++)
                {
                    fscanf(tsp_prob_file, "%d %ld %ld ", &poubelle, &instance->tabCoord[i][0], &instance->tabCoord[i][1]);
                }
                fclose(tsp_prob_file);
                dim++;
            }
            else
            {
                analyse_ligne(buffer, instance);
            }
        }
        fclose(tsp_prob_file);
    }
    else
    {
        printf("Error reading input file\n");
        return NIL;
    }
    // for (int i = 0; i < instance->dimension; i++)
    // {
    //     printf("i : %d | x : %ld| y : %ld|\n", i+1, instance->tabCoord[i][0], instance->tabCoord[i][1]);
    // }

    return 0;
}

void analyse_ligne(char *ligne, instance_t *instance)
{
    /// \brief Prend une ligne, la découpe et teste a qui ca correspond
    /// \brief (remplace un espace avec un \0)

    char field_type[TAILLENOM];
    char field_value[MAXBUF];

    get_first_word(ligne, field_type);

    if (prefix(field_type, "NAME"))
    {
        // get field value
        get_field_value(ligne, field_value);
        // fill struct with it
        strcpy(instance->name, field_value);
    }
    else if (prefix(field_type, "COMMENT"))
    {
        // get field value
        get_field_value(ligne, field_value);
        // fill struct with it
    }
    else if (prefix(field_type, "TYPE"))
    {
        // get field value
        get_field_value(ligne, field_value);
        // fill struct with it
        strcpy(instance->type, field_value);
    }
    else if (prefix(field_type, "DIMENSION"))
    {
        // get field value
        get_field_value(ligne, field_value);
        // fill struct with it
        //strcpy(instance->dimension, field_value);
        instance->dimension = atoi(field_value);
    }
    else if (prefix(field_type, "EDGE_WEIGHT_TYPE"))
    {
        // get field value
        get_field_value(ligne, field_value);
        // fill struct with it
        strcpy(instance->EDGE_TYPE, field_value);
    }
}
// instance = le problème

// tour = le resultat