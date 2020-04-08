/*************************************************************
* proto_tdd_v1 -  émetteur                                   *
* TRANSFERT DE DONNEES  v1                                   *
*                                                            *
* Transfert de donnée avec détection d'erreur et contrôle de *
* flux et reprise sur erreur   < Stop-and-wait >             *
* T. KUNZE - Univ. de Toulouse III - Paul Sabatier           *
**************************************************************/

#include <stdio.h>
#include "application.h"
#include "couche_transport.h"
#include "services_reseau.h"

/* =============================== */
/* Programme principal - émetteur  */
/* =============================== */
int main(int argc, char *argv[])
{
    unsigned char message[MAX_INFO]; /* message de l'application */
    int taille_msg;                  /* taille du message */
    paquet_t paquet;                 /* paquet utilisé par le protocole */
    paquet_t p_controle;             /* paquet de controle */

    int n_tempo;
    int codeRetour;

    init_reseau(EMISSION);

    printf("[TRP] Initialisation reseau : OK.\n");
    printf("[TRP] Debut execution protocole transport.\n");

    /* lecture de donnees provenant de la couche application */
    de_application(message, &taille_msg);

    /* tant que l'émetteur a des données à envoyer */
    while (taille_msg != 0)
    {

        /* construction paquet */
        for (int i = 0; i < taille_msg; i++)
        {
            paquet.info[i] = message[i];
        }
        paquet.lg_info = taille_msg;
        paquet.type = DATA;

        /* generation du controle */
        paquet.somme_ctrl = generer_controle(paquet);
        /* remise à la couche reseau */
        /* // on envoie le paquet au recepteur
        vers_reseau(&paquet);
        // on lance un temporisateur 
        n_tempo = 0;
        depart_temporisateur(n_tempo, 200);
        // puis on attend un code de retour
        if((codeRetour = attendre()) == -1)
        {
            // si reception == -1 on passe au paquet suivant, ack recut
            arreter_temporisateur(n_tempo);
        } else
        {
            // sinon on arrete le tempo n° de retour 
            // et on renvoie le paquet
            if
        } */
        //////////////////////////////////////////////////////////////////////
        n_tempo = 0;
        do
        {
            vers_reseau(&paquet);
            // on lance un temporisateur
            depart_temporisateur(n_tempo, 200);
            // puis on attend un code de retour
            do
            {
                // on traite le cas ou le n° de tempo expiré
                // est différent au n° de tempo lancé
                codeRetour = attendre();
            } while (codeRetour != n_tempo && codeRetour != PAQUET_RECU);

            n_tempo++;
            // si reception == -1 on passe au paquet suivant, ack recut
            // sinon on renvoie le paquet
        } while (codeRetour != PAQUET_RECU && n_tempo <= 31);
        arreter_temporisateur(n_tempo);

        /* lecture des donnees suivantes de la couche application */
        de_application(message, &taille_msg);
    }

    printf("[TRP] Fin execution protocole transfert de donnees (TDD).\n");
    return 0;
}
