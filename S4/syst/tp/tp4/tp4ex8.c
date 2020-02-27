#define _POSIX_C_SOURCE 1

#include "ex.h"

void close_file(int desc)
{
    int status = close(desc);
    if (status == -1)
    {
        perror("Error closing file");
        exit(ERROR_CLOSING);
    }
}


void saisirFiche(Infos *i)
{
    int age;
    int nbEnf;
    char nom[LONG_MAX_NOM + 1];

    printf("Le nom: \n");
    scanf("%s", nom);

    printf("L'age: \n");
    scanf("%d", &age);

    printf("Le nombre d'enfants: \n");
    scanf("%d", &nbEnf);

    i->Age = age;
    i->nbEnfants = nbEnf;
    strcpy(i->Nom, nom);

}

void printFiche(Infos i)
{
    printf("le nom: %s\n", i.Nom);
    printf("l'age': %d\n", i.Age);
    printf("le nombre d'enfants: %d\n", i.nbEnfants);
}

int creation(char *NomFichier)
{
    int desc;

    Infos fiche1;
    ssize_t s;


    desc = open(NomFichier, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

    if (desc == -1)
    {
        perror(NomFichier);
        return ERROR_READING;
    }

    /* Saisie et affichage DEBUG de la fiche */
    saisirFiche(&fiche1);
    printFiche(fiche1);

    /* Ecriture dans le fichier */
    s = write(desc, &fiche1, sizeof(Infos));
    /* retourne nb d'octets effectif écrits */

    if (s == -1)
    {
        /* Erreur tout court */
        perror("Erreur ecriture fichier");
        close_file(desc);
    } else if (sizeof(Infos) != s)
    {
        /* Erreur, pas toute la structure a été écrite */
        perror("Erreur ecriture structure");
        close_file(desc);
    }
    printf("Nb octets écrits = %ld\n", s);

    close_file(desc);
    
    return 0;
}


int consultation(char *NomFichier)
{
    int desc;
    int n_fiche;
    int nb_fiches;
    printf("Numero de la fiche a consulter: ");
    scanf("%d", n_fiche);
    printf("\n");

    /* Ouverture du fichier */
    desc = open(NomFichier, O_RDONLY);
    if (desc == -1)
    {
        perror(NomFichier);
        exit(ERROR_READING + 10);
    }

    /* Affichage nombre de fiches dans le ficher */

    /*
        while not end
            
            avancer de sizeof(Infos);
            nb_diches ++;
    */
    fscanf();
    

    /* consultation en boucle :
    (saisie numéro fiche, positionnement début fiche,lecture fiche, affichage contenu fiche) */


    /* Fermeture fichier */

    return 0;
}


/*
reagrder partie cours raite des fichier, primitives décrites.
On ouvre et on ferme un fichier
*/


int main (void)
{
    creation("lol");
    return 0;
}

