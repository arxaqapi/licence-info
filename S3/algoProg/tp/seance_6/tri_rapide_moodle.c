/**
 * \brief Tests sur les tris avec mesure du temps
 * \brief usage : nom_du_prog nom_du_fichier [limite] o� limite dit de ne consid�rer que les limite premiers nombres du fichier �r d�faut limite = 100
 *
 * \author Jean-Paul Bahsoun, Vincent Dugat, Pierre Piccinini
 * \date septembre 2016, septembre 2017
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define TMAX 300000 // dimension maximale des tableaux

typedef int tableau[TMAX];

void echanger(int *a,int *b) // swap
{
    int aux=*a;
    *a=*b;
    *b=aux;
}

void afficher_tab( tableau t , int dim)
{
    int i;
    for (i=0;i<dim;i++)
        printf("%4d",t[i]);
    printf("\n");
}

/* remplit le tableau avec les dim entiers d'un fichier
 s'il n'y a pas assez d'entiers dans le fichier :  le programme stoppe
*/
void tab_fichier(tableau t,int dim, char *nom)
{
    int i;
    FILE * f_in;
    f_in = fopen(nom,"r") ;
    if (f_in == NULL)
        {  fprintf(stderr,"\n Erreur : Impossible d ouvrir le fichier %s\n",nom) ;    exit(EXIT_FAILURE) ;}
     for (i=0;i<dim;i++)
    {
       fscanf(f_in,"%d",&t[i]) ;
       if (feof(f_in))
         {printf("Erreur: Pas assez d'entiers dans le fichier %s\n",nom);  exit(EXIT_FAILURE);}
    }
     fclose(f_in);
}

// copie de dim �l�ments de T1 dans t2
void initCopieTab(tableau t1, tableau t2, int dim){
    int i;
    for(i=0;i<dim;i++) t2[i]=t1[i]; // copie pour un autre tri
    }

// fonctions et proc�dures de tri

/*renvoie un bool�en vrai ssi t[deb1,fin1]<=val*/
bool inf_eq(tableau t, int deb1, int fin1, int val)
{
  int i;
  for (i=deb1;i<=fin1;++i)
          if (t[i]>val)
              return false;
  return true;
}

/*renvoie un bool�en vrai ssi val<t[deb1,fin1]l*/
bool sup(tableau t, int deb1, int fin1, int val)
{
  int i;
  for (i=deb1;i<=fin1;++i)
         if (t[i]<=val)
              return false;
  return true;
}

int partitionnerInv(tableau tab, int ind_premier, int ind_dernier) {
  //int IPivot = tab[0];
  int ind_pivot = ind_premier;
  int valPivot = tab[ind_pivot];
  int j = ind_dernier;

  //  INV
  assert(inf_eq(tab, ind_premier, ind_pivot, tab[ind_pivot])
          && sup(tab, j + 1, ind_dernier, tab[ind_pivot])
          &&  ind_premier <= ind_pivot && ind_pivot <= j <= ind_dernier);

  // conditiion de sortie, j = i_pivot
  while(j != ind_pivot) {
    //  INV et condition
    assert(inf_eq(tab, ind_premier, ind_pivot, tab[ind_pivot])
            && sup(tab, j + 1, ind_dernier, tab[ind_pivot])
            &&  ind_premier <= ind_pivot && ind_pivot <= j <= ind_dernier
            && j != ind_pivot);


    if (tab[j] > tab[ind_pivot]) {
      j --;
    } else if (tab[j] <= tab[ind_pivot]) {
      echanger(&tab[j], &tab[ind_pivot + 1]);
      echanger(&tab[ind_pivot], &tab[ind_pivot + 1]);
      ind_pivot ++;
    } else {
      printf("/!\\error\n");
    }


    //  INV
    assert(inf_eq(tab, ind_premier, ind_pivot, tab[ind_pivot])
            && sup(tab, j + 1, ind_dernier, tab[ind_pivot])
            &&  ind_premier <= ind_pivot && ind_pivot <= j <= ind_dernier);
  }
  //  INV et non cond
  assert(inf_eq(tab, ind_premier, ind_pivot, tab[ind_pivot])
          && sup(tab, j + 1, ind_dernier, tab[ind_pivot])
          &&  ind_premier <= ind_pivot && ind_pivot <= j <= ind_dernier
          && j == ind_pivot);
  return ind_pivot;
}

/* E: tab tableau de N entiers
    0<=d<N  0<=f<N
 tri rapide
S:  slice tab[d,f] tri�
*/
void triRapide(tableau tab, int d, int f){
    int ind_pivot;
    if (d<f) {
        ind_pivot = partitionnerInv(tab, d, f);
        triRapide(tab, d, ind_pivot-1);
        triRapide(tab, ind_pivot+1, f);
    }
}

// tri bulle : nb de comparaisons de l'ordre de dim^2
void tri_bulle(tableau t,int dim)
{
	int i,j;
	for (i=0;i<dim;i++)
		for(j=i+1;j<dim;j++)
			if (t[i]>t[j])
        echanger(&t[i],&t[j]);
}


// =================== MAIN =================
/* 2 arguments:     le nom du fichier ,   le nombre d'entiers du fichier trait�s*/

int main(int argc,char **argv)
{
    int dim;
    tableau t,t2;
    clock_t now,end; // d�claration de timers
    switch (argc)
    {
      case 1: printf("Usage : commande fichier [dim]\n");return 1;break;
      case 2: dim=100;break;
      case 3: dim=atoi(argv[2]);break;
      default: printf("Erreur ligne de commande: trop d'arguments\n");return 1;break;
    }
    printf("Dim=%d TMAX=%d\n",dim,TMAX);
    tab_fichier(t,dim, argv[1]); // on lit les donn�es dans le 2�me param�tre de la ligne de commande
    //printf("tab 1:");ecriture_tab(t,dim);

    initCopieTab(t,t2,dim); // les tris se feront toujours sur t2 qui sera r�initialis� � chaque fois

    printf("Tri bulles\n");
    now = clock(); // d�part chrono
    tri_bulle(t2,dim);
    end=clock();
    printf("\nTemps CPU : %.2f secondes \n\n",(double) (end-now)/CLOCKS_PER_SEC); // fin chrono
    //printf("tab 1 trie' ");afficher_tab(t2,dim); // pour v�rifier sur un petit vecteur
    printf("-------------------------------\n");

    initCopieTab(t,t2,dim); // r�initialisation de t2

    printf("Tri rapide r�cursif\n");
    now = clock(); // d�part chrono
    triRapide(t2,0,dim-1);
    end =clock();
    printf("\nTemps CPU : %.2f secondes mais l'avez-vous ajoute' ? \n\n",(double) (end - now) / CLOCKS_PER_SEC); // fin chrono
    //printf("tab 1 trie' ");afficher_tab(t2,dim); // pour v�rifier sur un petit vecteur
    printf("-------------------------------\n");

// M�me principe pour le tri fusion

    return 0;
}
