/*************************************************************
* proto_tdd_v1 -  recepteur                                  *
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
/* Programme principal - récepteur */
/* =============================== */
int main(int argc, char *argv[])
{
    unsigned char message[MAX_INFO]; /* message pour l'application */
    paquet_t paquet;                 /* paquet utilisé par le protocole */
    paquet_t p_controle;             /* paquet de controle */
    int fin = 0;                     /* condition d'arrêt */

    uint8_t seq_num_checker;

    init_reseau(RECEPTION);

    printf("[TRP] Initialisation reseau : OK.\n");
    printf("[TRP] Debut execution protocole transport.\n");

    /* tant que le récepteur reçoit des données */
    while (!fin)
    {
        de_reseau(&paquet);

        if (verifier_controle(paquet) == DATA)
        {
            /* extraction des donnees du paquet recu */
            for (int i = 0; i < paquet.lg_info; i++)
            {
                message[i] = paquet.info[i];
            }
            p_controle.type = ACK;

            vers_reseau(&p_controle);
            // NUM DE SEQ
            if (seq_num_checker != paquet.num_seq)
            {
                fin = vers_application(message, paquet.lg_info);
            }
            seq_num_checker = paquet.num_seq;
            
            /* remise des données à la couche application */
        }
    }

    printf("[TRP] Fin execution protocole transport.\n");
    return 0;
}