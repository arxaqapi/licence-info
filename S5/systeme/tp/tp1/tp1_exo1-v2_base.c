/**-------------------------------------------------------------------------
  TP1 - Squelette code exercice 1-V2
  Compilation : gcc tp1_exo1-v2_base.c -o exo1b -lpthread
--------------------------------------------------------------------------**/

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define NB_THREADS_MAX 10
#define NB_FOIS 10

/*------------------------------------------------------------------------
 * Affichage de l'identite de l'appelant 
  ------------------------------------------------------------------------*/
void afficher(int rang, pthread_t thdId)
{
	printf("Je suis le thread de rang %d, mon identificateur est %lu\n", rang, thdId);
}

/*------------------------------------------------------------------------
 Fonction d'affichage d'une erreur selon la cause de l'echec d'une primitive
 Arret du thread si arret positionne a 1
  ------------------------------------------------------------------------*/
void thdErreur(char *msg, int cause, int arret)
{
	printf("%s : %s \n", msg, strerror(cause));
	if (arret)
		pthread_exit(NULL);
}

/*------------------------------------------------------------------------
	Code execute par chaque thread 
-----------------------------------------------------------------------*/

void *thd_afficher(void *arg)
{
	/* A compl�ter */
	int nbAffichages = (int) (arg + 1);
	int rang = (int) (arg);

	for (int i = 0; i < nbAffichages; i++)
		afficher(rang, pthread_self());

	pthread_exit(NULL);
}

/*------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
	int i, nbThreads, etat, nbAffichages;
	pthread_t idThreads[NB_THREADS_MAX];
	/* A compl�ter */

	if (argc != 2)
	{
		printf("Usage : %s <Nb Threads>\n", argv[0]);
		exit(1);
	}
	nbThreads = atoi(argv[1]);
	if (nbThreads > NB_THREADS_MAX)
	{
		nbThreads = NB_THREADS_MAX;
	}

	printf("Combien d'affichages du message ?\n");
	scanf("%d", &nbAffichages);

	int arr[2] = {nbAffichages, 0};

	/* Creation des threads */
	for (i = 0; i < nbThreads; i++)
	{
		arr[1] = i;
		if ((etat = pthread_create(&idThreads[i], NULL, thd_afficher, arr)) != 0)
		{
			thdErreur("Echec create", etat, 0);
		}
	}
	/* Attendre la fin des threads  */
	for (i = 0; i < nbThreads; i++)
	{
		if ((etat = pthread_join(/* A compl�ter */)) != 0)
		{
			thdErreur("Echec join", etat, 0);
		}
	}
	return 0;
}
