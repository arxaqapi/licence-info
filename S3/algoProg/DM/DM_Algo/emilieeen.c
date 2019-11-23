//  Implementation R2

/** Mets a jours les n_candidats et candidats de la case
 * correspondant a l'indice passée en parametre, en fonction
 * des valeurs des cases des groupements
 * @param indCase indice de la case sur laquelle on applique R2
 * @param ps poiteur sur un sudoku
 * @return 1 si la regle a ete appliqué, 0 sinon
 */
int R2_case(int indCase, T_sudoku *ps)
{
    //  Ligne : construction du tableau depuis les elements de la ligne
    int verifSiModification = 0;
    if (ps->grille[indCase].val == 0)
    {

        T_coordonnees coordCase = obtenirCoords(indCase);
        int ind_valeur;
        int val;

        //  parcours la ligne de indCase(9*coordCase.ligne à ...+9)
        for (int x = (9 * coordCase.ligne); x < ((9 * coordCase.ligne) + 9); x++)
        {
            // x: indice de la case de la ligne
            val = ps->grille[x].val;
            if (indCase != x && val != 0)
            {
                ind_valeur = rechercherValeur(val, ps->grille[indCase]);
                if (ps->grille[indCase].n_candidats > ind_valeur)
                {
                    supprimerValeur(ind_valeur, &ps->grille[indCase]);
                    verifSiModification = 1;
                }
            }
        }

        //  Colonne : construction du tableau depuis les elements de la colonne

        for (int ind_ele_colonne = coordCase.colonne; ind_ele_colonne <= 72 + coordCase.colonne; ind_ele_colonne += 9)
        {
            // ind_ele_colonne: indice de la case de la colonne
            val = ps->grille[ind_ele_colonne].val;
            if (indCase != ind_ele_colonne && val != 0)
            {
                ind_valeur = rechercherValeur(val, ps->grille[indCase]);
                if (ps->grille[indCase].n_candidats > ind_valeur)
                {
                    //  ajoutValeurACase(val, &tableauTemporaire);
                    supprimerValeur(ind_valeur, &ps->grille[indCase]);
                    verifSiModification = 1;
                }
            }
        }

        // Groupement : construction du tableau depuis les elements du groupement
        T_coordonnees coord_debut_region = debutRegion(indiceRegion(coordCase));
        T_coordonnees coordValeur;
        int indElementGroupement;
        for (int x = coord_debut_region.ligne; x < (coord_debut_region.ligne + 3); x++)
        {
            for (int y = coord_debut_region.colonne; y < (coord_debut_region.colonne + 3); y++)
            {
                coordValeur.ligne = x;
                coordValeur.colonne = y;
                indElementGroupement = obtenirIndice(coordValeur);
                val = ps->grille[indElementGroupement].val;

                if (indCase != indElementGroupement && val != 0)
                {
                    ind_valeur = rechercherValeur(val, ps->grille[indCase]);
                    if (ps->grille[indCase].n_candidats > ind_valeur)
                    {
                        //  ajoutValeurACase(val, &tableauTemporaire);
                        supprimerValeur(ind_valeur, &ps->grille[indCase]);
                        verifSiModification = 1;
                    }
                }
            }
        }
    }
    return verifSiModification;
}

/** Applique R2 sur toutes les cases du sudoku,
 * renvoie 1 si une modification a eu lieu, 0 sinon
 * @param ps pointeur sur un sudoku
 * @return renvoie 1 si une modification a eu lieu, 0 sinon
*/
int R2_sudoku(T_sudoku *ps)
{
    int verifSiModification = 0;
    for (int i = 0; i < 81; i++)
    {
        if (R2_case(i, ps))
        {
            verifSiModification = 1;
        }
    }
    return verifSiModification;
}