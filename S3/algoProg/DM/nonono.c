#include "sudoku.h"

//-------------------------------------------------------------------------------

//--------------------------------------------------------------------------------

/* Implanter les fonctions de sudoku.h ici */

T_coordonnees obtenirCoords(int indice)
{
  T_coordonnees x = {indice / 9, indice % 9};
  return x;
}

int obtenirIndice(T_coordonnees coords)
{
  if (coords.ligne == 0)
  {
    return coords.colonne;
  }
  else
  {
    return ((coords.ligne * 9) + coords.colonne);
  }
}

T_coordonnees debutRegion(int indiceRegion)
{
  T_coordonnees x = {(3 * (indiceRegion / 3)), (3 * (indiceRegion % 3))};
  return x;
}

int indiceRegion(T_coordonnees coords)
{
  return (3 * (coords.ligne / 3) + (coords.colonne / 3));
}

T_sudoku lireSudoku(char *chemin)
{
  FILE *sudokuFile;
  sudokuFile = fopen(chemin, 'r');
  T_sudoku s;
  if (sudokuFile != NULL)
  {
    for (int i = 0; i < 9; i++)
    {
      fscanf(sudokuFile, "%d %d %d %d %d %d %d %d %d", &s.grille[i * 9].val, &s.grille[i * 9 + 1].val, &s.grille[i * 9 + 2].val, &s.grille[i * 9 + 3].val, &s.grille[i * 9 + 4].val, &s.grille[i * 9 + 5].val, &s.grille[i * 9 + 6].val, &s.grille[i * 9 + 7].val, &s.grille[i * 9 + 8].val);
    }
    fclose(sudokuFile);
  }
  else
  {
    printf("fichier introuvalbe\n");
  }
  return s;
}

void initialiserSudoku(T_sudoku *s)
{
  for (int i = 0; i < 81; i++)
  {
    if (s->grille[i].val == 0)
    {
      s->grille[i].n_candidats = 9;
      for (int j = 1; j < 10; j++)
      {
        s->grille[i].candidats[j - 1] = j;
      }
    }
    else
    {
      s->grille[i].n_candidats = 0;
    }
  }
}

void afficherSudoku(T_sudoku s)
{
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      printf("%d\t", s.grille[j + (9 * i)].val);
    }
    printf("\n");
  }
}

int rechercherValeur(int val, T_case c)
{
  for (int i = 0; i < c.n_candidats; i++)
  {
    if (c.candidats[i] == val)
    {
      return i;
    }
  }
  return c.n_candidats;
}

void supprimerValeur(int ival, T_case *pc)
{
  pc->candidats[ival] = 0;
  pc->n_candidats -= 1;
  if (ival != pc->n_candidats)
  {
    for (int i = ival; i < pc->n_candidats; i++)
    {
      pc->candidats[i] = pc->candidats[i + 1];
      pc->candidats[i + 1] = 0;
    }
  }
}

// R1

int R1_case(T_case *pc)
{
  //si la case n'as plus qu'un seul candidat dans sa liste de candidats
  if (pc->n_candidats == 1)
  {
    pc->val = pc->candidats[0];
    supprimerValeur(0, pc);
    return 1;
  }
  return 0;
}

int R1_sudoku(T_sudoku *ps)
{
  int count = 0;
  for (int i = 0; i < 81; i++)
  {
    if (R1_case(&ps->grille[i]) == 1)
    {
      T_coordonnees coords = obtenirCoords(i);
      int valeur = ps->grille[i].val;
      //parcours les 9 cases de la ligne
      for (int j = (9 * coords.ligne); j < ((9 * coords.ligne) + 9); j++)
      {
        //sauf la case i
        if (j != i)
        {
          // passe seulement dans les cases qui sont a 0
          if (ps->grille[j].val == 0)
          {
            int indiceValeur = rechercherValeur(valeur, ps->grille[j]);
            // conditions qui verifie que la valeur se trouve bien dans le tableau des candidats
            if (indiceValeur != ps->grille[j].n_candidats)
            {
              supprimerValeur(indiceValeur, &ps->grille[j]);
              count += 1;
            }
          }
        }
      }
      //parcours les 9 cases de la colonne
      for (int j1 = 0; j1 < 9; j1++)
      {
        //simplification de l'indice j
        int j = ((9 * j1) + coords.colonne);
        //sauf la case i
        if (j != i)
        {
          //passe seulement dans les cases qui sont a 0
          if (ps->grille[j].val == 0)
          {
            int indiceValeur = rechercherValeur(valeur, ps->grille[j]);
            // conditions qui verifie que la valeur se trouve bien dans le tableau des candidats
            if (indiceValeur != ps->grille[j].n_candidats)
            {
              supprimerValeur(indiceValeur, &ps->grille[j]);
              count += 1;
            }
          }
        }
      }
      T_coordonnees deb_region = debutRegion(indiceRegion(coords));
      //parcours des 9 cases de la region
      for (int k = deb_region.ligne; k < deb_region.ligne + 3; k++)
      {
        for (int j = deb_region.colonne; j < deb_region.colonne + 3; j++)
        {
          T_coordonnees coords_actuel = {k, j};
          // on passe dans toutes les cases sauf la case d'indice i
          if (obtenirIndice(coords) != obtenirIndice(coords_actuel))
          {
            //indice de la case a verifier
            int indice = obtenirIndice(coords_actuel);
            //on verifie que la case n'as pas encore de valeur attribue
            if (ps->grille[indice].val == 0)
            {
              int indiceValeur = rechercherValeur(valeur, ps->grille[indice]);
              // conditions qui verifie que la valeur se trouve bien dans le tableau des candidats
              if (indiceValeur != ps->grille[indice].n_candidats)
              {
                supprimerValeur(indiceValeur, &ps->grille[indice]);
                count += 1;
              }
            }
          }
        }
      }
    }
  }
  if (count == 0)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

//R2

int R2_case(int indCase, T_sudoku *ps)
{
  //conteur pour le retrun 1
  int count = 0;
  //si la case est un 0 :
  if (ps->grille[indCase].val == 0)
  {
    T_coordonnees coords = obtenirCoords(indCase);
    //parcours les 9 cases de la ligne
    for (int j = (9 * coords.ligne); j < ((9 * coords.ligne) + 9); j++)
    {
      //sauf la case i
      if (j != indCase)
      {
        //si la case a une valeur affectee
        if (ps->grille[j].val != 0)
        {
          //on verifie que la valeur soit dans les candidats de la case passee en parametre
          int indiceVal = rechercherValeur(ps->grille[j].val, ps->grille[indCase]);
          if (indiceVal != ps->grille[indCase].n_candidats)
          {
            //la valeur se situe bien les candidats de la case, on la supprime donc des candiddats
            supprimerValeur(indiceVal, &ps->grille[indCase]);
            count += 1;
          }
        }
      }
    }
    //parcours les 9 cases de la colonne
    for (int j1 = 0; j1 < 9; j1++)
    {
      //simplification de l'indice j
      int j = ((9 * j1) + coords.colonne);
      //si la case a une valeur affectee
      if (ps->grille[j].val != 0)
      {
        //on verifie que la valeur soit dans les candidats de la case passee en parametre
        int indiceVal = rechercherValeur(ps->grille[j].val, ps->grille[indCase]);
        if (indiceVal != ps->grille[indCase].n_candidats)
        {
          //la valeur se situe bien les candidats de la case, on la supprime donc des candiddats
          supprimerValeur(indiceVal, &ps->grille[indCase]);
          count += 1;
        }
      }
    }
    T_coordonnees deb_region = debutRegion(indiceRegion(coords));
    //parcours des 9 cases de la region
    for (int k = deb_region.ligne; k < deb_region.ligne + 3; k++)
    {
      for (int j = deb_region.colonne; j < deb_region.colonne + 3; j++)
      {
        T_coordonnees coords_actuel = {k, j};
        // on passe dans toutes les cases sauf la case passee en parametre d'indice indCase
        if (obtenirIndice(coords) != obtenirIndice(coords_actuel))
        {
          //indice de la case a verifier
          int indice = obtenirIndice(coords_actuel);
          //on verifie que la case a une valeur deja affectee
          if (ps->grille[indice].val != 0)
          {
            int indiceValeur = rechercherValeur(ps->grille[indice].val, ps->grille[indCase]);
            // conditions qui verifie que la valeur se trouve bien dans le tableau des candidats
            if (indiceValeur != ps->grille[indCase].n_candidats)
            {
              supprimerValeur(indiceValeur, &ps->grille[indCase]);
              count += 1;
            }
          }
        }
      }
    }
    if (count == 0)
    {
      return 0;
    }
    else
    {
      return 1;
    }
  }
  return 0;
}

int R2_sudoku(T_sudoku *ps)
{
  int c = 0;
  for (int i = 0; i < 81; i++)
  {
    if (R2_case(i, ps) == 1)
    {
      c += 1;
    }
  }
  if (c == 0)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

//R3

int R3_case(int indCase, T_sudoku *ps)
{
  if (ps->grille[indCase].val == 0)
  {
    T_coordonnees coords = obtenirCoords(indCase);
    //parcours tous les candidats de la case
    for (int i = 0; i < ps->grille[indCase].n_candidats; i++)
    {
      //trouve = 0 tant quon a pas trouve de candidats
      int trouve = 0;
      //on recupere la valeur du candidat
      int valeurCandidat = ps->grille[indCase].candidats[i];
      //parcours les 9 cases de la ligne
      for (int j = (9 * coords.ligne); j < ((9 * coords.ligne) + 9); j++)
      {
        //sauf la case dindice indCase
        if (j != indCase)
        {
          //parcours tous les candidats de la case dindice j
          for (int k = 0; k < ps->grille[j].n_candidats; k++)
          {
            if (ps->grille[j].candidats[k] == valeurCandidat)
            {
              trouve = 1;
            }
          }
        }
      }
      //cas ou le candidat "valeurCandidat" est seul sur la ligne
      if (trouve == 0)
      {
        while (ps->grille[indCase].n_candidats > 0)
        {
          supprimerValeur(0, &ps->grille[indCase]);
        }
        ps->grille[indCase].val = valeurCandidat;
        return 1;
      }
    }
    //parcours tous les candidats de la case
    for (int i = 0; i < ps->grille[indCase].n_candidats; i++)
    {
      //trouve = 0 tant quon a pas trouve de candidats
      int trouve = 0;
      //on recupere la valeur du candidat
      int valeurCandidat = ps->grille[indCase].candidats[i];
      //parcours les 9 cases de la colonne
      for (int j1 = 0; j1 < 9; j1++)
      {
        //simplification de l'indice j
        int j = ((9 * j1) + coords.colonne);
        //sauf la case dindice indCase
        if (j != indCase)
        {
          //parcours tous les candidats de la case dindice j
          for (int k = 0; k < ps->grille[j].n_candidats; k++)
          {
            if (ps->grille[j].candidats[k] == valeurCandidat)
            {
              trouve = 1;
            }
          }
        }
      }
      //cas ou le candidat "valeurCandidat" est seul sur la colonne
      if (trouve == 0)
      {
        while (ps->grille[indCase].n_candidats > 0)
        {
          supprimerValeur(0, &ps->grille[indCase]);
        }
        ps->grille[indCase].val = valeurCandidat;
        return 1;
      }
    }
    //parcours tous les candidats de la case
    for (int i = 0; i < ps->grille[indCase].n_candidats; i++)
    {
      //trouve = 0 tant quon a pas trouve de candidats
      int trouve = 0;
      //on recupere la valeur du candidat
      int valeurCandidat = ps->grille[indCase].candidats[i];
      T_coordonnees deb_region = debutRegion(indiceRegion(coords));
      //parcours des 9 cases de la region
      for (int k = deb_region.ligne; k < deb_region.ligne + 3; k++)
      {
        for (int j = deb_region.colonne; j < deb_region.colonne + 3; j++)
        {
          T_coordonnees coords_actuel = {k, j};
          // on passe dans toutes les cases sauf la case passee en parametre d'indice indCase
          if (obtenirIndice(coords) != obtenirIndice(coords_actuel))
          {
            //indice de la case a verifier
            int indice = obtenirIndice(coords_actuel);
            //parcours tous les candidats de la case d'indice indice
            for (int z = 0; z < ps->grille[indice].n_candidats; z++)
            {
              if (ps->grille[indice].candidats[z] == valeurCandidat)
              {
                trouve = 1;
              }
            }
          }
        }
      }
      //cas ou le candidat "valeurCandidat" est seul sur la region
      if (trouve == 0)
      {
        while (ps->grille[indCase].n_candidats > 0)
        {
          supprimerValeur(0, &ps->grille[indCase]);
        }
        ps->grille[indCase].val = valeurCandidat;
        return 1;
      }
    }
    return 0;
  }
  return 0;
}

int R3_sudoku(T_sudoku *ps)
{
  int count = 0;
  for (int i = 0; i < 81; i++)
  {
    if (R3_case(i, ps) == 1)
    {
      T_coordonnees coords = obtenirCoords(i);
      int valeur = ps->grille[i].val;
      //parcours les 9 cases de la ligne
      for (int j = (9 * coords.ligne); j < ((9 * coords.ligne) + 9); j++)
      {
        //sauf la case i
        if (j != i)
        {
          // passe seulement dans les cases qui sont a 0
          if (ps->grille[j].val == 0)
          {
            int indiceValeur = rechercherValeur(valeur, ps->grille[j]);
            // conditions qui verifie que la valeur se trouve bien dans le tableau des candidats
            if (indiceValeur != ps->grille[j].n_candidats)
            {
              supprimerValeur(indiceValeur, &ps->grille[j]);
              count += 1;
            }
          }
        }
      }
      //parcours les 9 cases de la colonne
      for (int j1 = 0; j1 < 9; j1++)
      {
        //simplification de l'indice j
        int j = ((9 * j1) + coords.colonne);
        //sauf la case i
        if (j != i)
        {
          //passe seulement dans les cases qui sot a 0
          if (ps->grille[j].val == 0)
          {
            int indiceValeur = rechercherValeur(valeur, ps->grille[j]);
            // conditions qui verifie que la valeur se trouve bien dans le tableau des candidats
            if (indiceValeur != ps->grille[j].n_candidats)
            {
              supprimerValeur(indiceValeur, &ps->grille[j]);
              count += 1;
            }
          }
        }
      }
      T_coordonnees deb_region = debutRegion(indiceRegion(coords));
      //parcours des 9 cases de la region
      for (int k = deb_region.ligne; k < deb_region.ligne + 3; k++)
      {
        for (int j = deb_region.colonne; j < deb_region.colonne + 3; j++)
        {
          T_coordonnees coords_actuel = {k, j};
          // on passe dans toutes les cases sauf la case d'indice i
          if (obtenirIndice(coords) != obtenirIndice(coords_actuel))
          {
            //indice de la case a verifier
            int indice = obtenirIndice(coords_actuel);
            //on verifie que la case n'as pas encore de valeur attribue
            if (ps->grille[indice].val == 0)
            {
              int indiceValeur = rechercherValeur(valeur, ps->grille[indice]);
              // conditions qui verifie que la valeur se trouve bien dans le tableau des candidats
              if (indiceValeur != ps->grille[indice].n_candidats)
              {
                supprimerValeur(indiceValeur, &ps->grille[indice]);
                count += 1;
              }
            }
          }
        }
      }
    }
  }
  if (count == 0)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

int valide(T_sudoku ps)
{
  for (int i = 0; i < 81; i++)
  {
    if (ps.grille[i].val == 0)
    {
      return 0;
    }
  }
  return 1;
}

int cases_restantes(T_sudoku ps)
{
  int count = 0;
  for (int i = 0; i < 81; i++)
  {
    if (ps.grille[i].val == 0)
    {
      count += 1;
    }
  }
  return count;
}

void resoudreSudoku(char *chemin)
{
  T_sudoku s = lireSudoku(chemin);
  R2_sudoku(&s);
  while (R1_sudoku(&s) == 1 || R3_sudoku(&s) == 1)
  {
  }
  afficherSudoku(s);
}














/////////////////////////////////
//oim



int retireCandidatGroupement(T_sudoku *ps, int indDeComparaison)
{
  T_coordonnees coordDebutRegion = debutRegion(indiceRegion(obtenirCoords(indDeComparaison)));
  T_coordonnees coordValeur;
  int modif = 0;
  int valeurARetirer = ps->grille[indDeComparaison].val;
  int idVal;
  int idValARetirer;
  for (int x = coordDebutRegion.ligne; x < coordDebutRegion.ligne + 3; x++)
  {
    for (int y = coordDebutRegion.colonne; y < coordDebutRegion.colonne + 3; y++)
    {
      coordValeur.ligne = x;
      coordValeur.colonne = y;
      idVal = obtenirIndice(coordValeur);
      if (idVal != indDeComparaison && ps->grille[idVal].val == 0)
      {
        idValARetirer = rechercherValeur(valeurARetirer, ps->grille[idVal]);
        if (idValARetirer != ps->grille[idVal].n_candidats)
        {
          supprimerValeur(idValARetirer, &ps->grille[idVal]);
          modif = 1;
        }
      }
    }
  }
  return modif;
}

int retireCandidatLigne(T_sudoku *ps, int indDeComparaison)
{
  T_coordonnees coordValeur = obtenirCoords(indDeComparaison);
  int modif = 0;
  int valeurARetirer = ps->grille[indDeComparaison].val;
  int idVal;
  for (int x = (9 * coordValeur.ligne); x < ((9 * coordValeur.ligne) + 9); x++)
  {
    if (x != indDeComparaison && ps->grille[x].val == 0)
    {
      idVal = rechercherValeur(valeurARetirer, ps->grille[x]);

      if (idVal != ps->grille[x].n_candidats)
      {
        supprimerValeur(idVal, &ps->grille[x]);
        modif = 1;
      }
    }
  }
  return modif;
}

int retireCandidatColonne(T_sudoku *ps, int indDeComparaison)
{
  T_coordonnees coordValeur = obtenirCoords(indDeComparaison);
  int modif = 0;
  int valeurARetirer = ps->grille[indDeComparaison].val;
  int indElementColonne;
  int idVal;

  for (size_t x = 0; x < 9; x++)
  {
    indElementColonne = 9 * x + coordValeur.colonne;

    if (indElementColonne != indDeComparaison && ps->grille[indDeComparaison].val != 0)
    {
      idVal = rechercherValeur(valeurARetirer, ps->grille[indElementColonne]);

      if (idVal != ps->grille[indElementColonne].n_candidats)
      {
        supprimerValeur(idVal, &ps->grille[indElementColonne]);
        modif = 1;
      }
    }
  }
  return modif;
}

/**
 * @param idValeur indice de la valeur qui sera affecter
 * @param pc pointeur sur une case
 */
void affectationValeurACase(int idValeur, T_case *pc)
{
  if (pc->candidats[idValeur] != 0)
  {
    /* code */
    // n_candidats => 0
    // tt cases de candidiats du tableau doivent être mises a 0
    pc->val = pc->candidats[idValeur];
    for (int i = 0; i < pc->n_candidats; i++)
    {
      pc->candidats[i] = 0;
    }
    pc->n_candidats = 0;
  }
}

/** Afficher un sudoku: 9 lignes de 9 entiers
 * separes par des tabulations (\t)
 * @param pc un pointeur sur une case
 */
int R1_case(T_case *pc)
{
  if (pc->n_candidats == 1)
  {
    affectationValeurACase(0, pc);
    pc->val = pc->candidats[0];
    //supprimerValeur(0, pc);
    //return 1;
  }
  return 0;
}

/** Applique R1 sur la case
 * @param ps pointeur sur le sudoku
 * @return 1 si il y a eu une modification, 0 sinon
 */
int R1_sudoku(T_sudoku *ps)
{
  int verifSiModification = 0;
  for (int id = 0; id < 81; id++)
  {
    //  Si R1 a été appliqué
    if (R1_case(&ps->grille[id]))
    {
      if (retireCandidatLigne(ps, id) || retireCandidatGroupement(ps, id) || retireCandidatColonne(ps, id))
      {
        verifSiModification = 1;
      }
    }
  }
  return verifSiModification;
}

/** Applique R2 sur la case

/**
 * @param indCase indice de la case sur laquelle on applique R2
 * @param ps poiteur sur un sudoku
 * @return 1 si la regle a ete appliqué, 0 sinon
 */
/*
int R2_case(int indCase, T_sudoku *ps)
{
  //  return 1 si au moins 1 candid retiré de la case
}

/** Applique R2 sur toutes les cases du sudoku,
 * renvoie 1 si une modification a eu lieu, 0 sinon
 * @param ps pointeur sur un sudoku
 * @return renvoie 1 si une modification a eu lieu, 0 sinon
*/
/*
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
*/