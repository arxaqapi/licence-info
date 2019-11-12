#include "sudoku.h"
#include <stdlib.h>
#include <stdio.h>


/* Implanter les fonctions de sudoku.h ici */

/* Retourne les coordonnees de la case a 
partir de son indice dans le sudoku */
T_coordonnees obtenirCoords(int indice) {
    T_coordonnees caseSudoku;
    caseSudoku.ligne = indice / 9;
    caseSudoku.colonne = indice % 9;
    return caseSudoku;
}

/* Retourne l'indice d'une case dans 
le sudoku a partir de ses coordonnees */
int obtenirIndice(T_coordonnees coords) {
    return 9 * coords.ligne + coords.colonne;
}

T_coordonnees debutRegion(int indiceRegion) {
    T_coordonnees coordPremiereCaseRegion;
    coordPremiereCaseRegion.ligne = 3 * (indiceRegion / 3);
    coordPremiereCaseRegion.colonne = 3 * (indiceRegion % 3);
    return coordPremiereCaseRegion;
}

int indiceRegion(T_coordonnees coords) {
    return 3 * (coords.ligne / 3) + (coords.colonne / 3);
}

/* Lire une grille et initialiser un sudoku */
T_sudoku lireSudoku(char* chemin) {
    FILE* fichierSudoku;
    T_sudoku sudokuNonInit;

    int caractereActuel = 0;
    int conteur = 0;

    fichierSudoku = fopen(chemin, "r");

    if (fichierSudoku == NULL) {
        printf("Fichier Introuvable");
    } else {

        do {
            caractereActuel = fgetc(fichierSudoku);
            if (caractereActuel == '\n' 
            || caractereActuel == ' ' 
            || caractereActuel == EOF) {
                continue;
            }
            sudokuNonInit.grille[conteur].val = (int)(caractereActuel - '0')/*(int)caractereActuel*/;
            conteur ++;

        } while(caractereActuel != EOF);

        fclose(fichierSudoku);
    }
    
    return sudokuNonInit;//sudok
}

/*
si val affecté a une case (val != 0):
le nombre de n_candidats de la case doit-être mis à 0
toute case les cases du tableau de candidats doivent 
être mis à 0
*/
void initialiserSudoku(T_sudoku* s) {
    for(int i = 0; i < 81; i++) {
        if (s->grille[i].val != 0) {
            s->grille[i].n_candidats = 0;
            for(int idCaseCandidats = 0; idCaseCandidats < 9; idCaseCandidats ++) {
                s->grille[i].candidats[idCaseCandidats] = 0;
            }
        } else {
            s->grille[i].n_candidats = 9;
            for(int idCaseCandidats = 0; idCaseCandidats < 9; idCaseCandidats ++) {
                s->grille[i].candidats[idCaseCandidats] = idCaseCandidats + 1;
            }
        }
    }
}

/* Recherche et suppression de candidats dans une case */
int rechercherValeur(int val, T_case c){
/* Renvoie l'indice de val dans le tableau de candidats de c.
Si l'indice n'est pas present, renvoie c.n_candidats */
    int indiceDeValDansCandidats;
    for(int i = 0; i < c.n_candidats; i++) {
        if (c.candidats[i] == val) {
            indiceDeValDansCandidats = i;
            return indiceDeValDansCandidats;
        }
    }
    return c.n_candidats;

}
void supprimerValeur(int ival, T_case* pc) {
/* ival est l'indice de la valeur a supprimer,
on considere que la valeur a supprimer est presente dans les candidats de la case */
    //sup and décale??
    for(int i = ival; i < pc->n_candidats - 1; i++) {
        pc->candidats[i + 1] = pc->candidats[i];
    }
    pc->n_candidats --;
    for(int i = pc->n_candidats; i < 9; i++) {
        pc->candidats[i] = 0;
    }
}


/* Affichage de grilles */
/* Afficher un sudoku: 9 lignes de 9 entiers separes par des tabulations (\t)*/
void afficherSudoku(T_sudoku s) {
    for(int i = 1; i <= 81; i ++) {
        printf("%d\t", s.grille[i - 1].val);
        if(i % 9 == 0) {
            printf("\n");
        }
    }
}

/* Implementation des regles */

int R1_case(T_case* pc) {
    /* Applique R1 sur la case */
    //return 1; si règle appliqué
    //return 0; si non appliqué
    if (pc->n_candidats == 1) {
        pc->val = pc->candidats[0];
        //supprimerValeur(pc->candidats[0], pc);
        return 1;
    }
    return 0;
}

int R1_sudoku(T_sudoku* ps) {
    /* Applique R1 sur toutes les cases du sudoku,
renvoie 1 si une modification a eu lieu, 0 sinon */
    for(int i = 0; i < 81; i++) {
        if(R1_case(&ps->grille[i])) {
            supprimerValeur(ps->grille[i].candidats[0], &ps->grille[i]);
        }
        R1_case(&ps->grille[i]);
    }
}

//int main(void) {
    /*
    T_sudoku sudo;
    
    int arr[] = { 0, 3, 5, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8};
    for(int i = 0; i < 20; i++) {
        sudo.grille[i].val = arr[i];
    }

    afficherSudoku(sudo);
    */
    //lireSudoku("one.txt");

//    return 0;
//}