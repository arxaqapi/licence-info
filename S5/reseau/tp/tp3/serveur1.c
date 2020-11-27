/* =================================================================== */
// Progrmame Serveur qui calcule le résultat d'un coup joué à partir
// des coordonnées reçues de la part d'un client "joueur".
// Version ITERATIVE : 1 seul client/joueur à la fois
/* =================================================================== */

#include <stdio.h>

/* =================================================================== */
/* FONCTION PRINCIPALE : SERVEUR ITERATIF                              */
/* =================================================================== */
int main(int argc, char **argv) {

    // create socket
    // bind adn listen
    // loop:
    //      accept comm
    //      loop:
    //          <- receive_data <- "lig col\0"
    //          | init treasure position x, y
    //          | result = recherche_tresor(N, x_tresor, y_tresor, lig, col)
    //          -> send_data -> result
    //      :end
    //      close comm
    // :end
    return 0;
} // end main
