#include "sudoku.h"

/* Implanter les fonctions de sudoku.h ici */
T_coordonnees obtenirCoords(int indice) {
    T_coordonnees caseSudoku;
    caseSudoku.ligne = indice / 9;
    caseSudoku.colonne = indice % 9;
    return caseSudoku;
}

int obtenirIndice(T_coordonnees coords) {
    return 9 * (coords.ligne + coords.colonne);
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


int main(void) {


    return 0;
}