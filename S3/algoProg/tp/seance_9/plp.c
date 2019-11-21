#include <stdio.h>
#include <stdbool.h>

#define NMAX 100000

typedef int tab[NMAX];

bool est_palin(tab t, int taille_t, int d, int f)
{
    int k = 0;
    while (t[d + k] == t[f - k] && (k <= (f - d) / 2))
    {
        k++;
    }
    return (k > (f - d) / 2);
}

int plp_brute_force(tab t, int taille)
{
    int plp = 0;
    int taille_pal = 0;

    for (int d = 0; d < taille; d++)
    {
        for (int f = d; f < taille; f++)
        {
            ;
            if (est_palin(t, taille, d, f))
            {
                taille_pal = ((f + 1) - d);
                if (taille_pal > plp)
                {
                    plp = taille_pal;
                }
            }
        }
    }
    return plp;
}

int plp_dynamique(tab t, int taille)
{
    int mat[taille][taille];
    for (int i = 0; i < taille; i++)
    {
        //  diagonale de la matrice
        mat[i][i] = 1;
    }
    for (int i = 0; i < taille - 1; i++)
    {
        //  diagonale
        if (t[i] == t[i + 1])
        {
            mat[i][i + 1] = 1;
        }
        else
        {
            mat[i][i + 1] = 0;
        }
    }
}

int main(void)
{
    tab t1 = {0, 0, 0, 0, 0, 0, 0, 0, 1};
    int maxBF;

    maxBF = plp_brute_force(t1, 9);
    printf("Plp = %d", maxBF);
    return 0;
}