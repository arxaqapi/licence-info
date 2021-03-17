#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "limace.h"
#include "tai.h"

#define DEBOGAGE

#ifdef DEBOGAGE
#define DEBUG fprintf(stderr,"Fichier %s, ligne %d\n",__FILE__,__LINE__);
#else
#define DEBUG
#endif

#define AFAIRE(fonction) fprintf(stderr,"Corps de la fonction " #fonction \
                                        " à écrire.\n" ); \
												 return NULL;


/*
 * Inversion d'une image
 * Entrée : image initiale (binaire, niveaux de gris ou couleur)
 * Sortie : image résultat
 */
Image Inversion(Image Im)
{
  AFAIRE(Inversion);
  // binaire
  // niveaux de gris
  // couleur
  Im
}

 /*
  * Étalement de la dynamique d'une image de niveaux de gris
  * Entrée : image initiale en niveaux de gris
  * Sortie : image résultat
  */
Image Etalement(Image Im)
{
  AFAIRE(Etalement);
}

/*
 * Binarisation d'une image de niveaux de gris par seuillage global
 * Entrées : image de niveaux de gris initiale et seuil
 * Sortie : image binaire
 */
Image Binarisation(Image Im, unsigned char Seuil)
{
  AFAIRE(Binarisation);
}

/*
 * Filtrage moyen d'une image de niveaux de gris
 * Entrées : image initiale en niveaux de gris
 *           taille du voisinage (Taille x Taille)
 * Sortie : image résultat
 */
Image Moyen(Image Im, int Taille)
{
  AFAIRE(Moyen);
}

/*
 * Filtrage médian d'une image de niveaux de gris
 * Entrées : image initiale en niveaux de gris
 *           taille du voisinage (Taille x Taille)
 * Sortie : image résultat
 */
Image Median(Image Im, int Taille)
{
  AFAIRE(Median);
}

/*
 * Vérification de la validité d'une matrice représentant un élément structurant
 * Entrée : matrice représentant un élément structurant
 * Sortie : 0 si la matrice est valide,
            ES_NOT_ODD si son nombre de lignes ou de colonnes n'est pas impair
            ES_NOT_INT si elle ne contient pas que des entiers
            ES_NOT_BIN si elle ne contient pas que des 0 et des 1
*/
int InvalideES(Matrix ElementStructurant)
{
  int **ES,NbLig,NbCol,i,j;

  if (MatType(ElementStructurant)!=Int)
    return ES_NOT_INT;
  NbLig=MatNbRow(ElementStructurant);
	if ((NbLig%2)!=1)
	  return ES_NOT_ODD;
  NbCol=MatNbCol(ElementStructurant);
	if ((NbCol%2)!=1)
	  return ES_NOT_ODD;
  ES=MatGetInt(ElementStructurant);
  for (i=0;i<NbLig;i++)
    for (j=0;j<NbCol;j++)
      if (ES[i][j]!=0 && ES[i][j]!=1)
        return ES_NOT_BIN;
  return 0;
}

/*
 * Érosion d'une image binaire
 * Entrées : image binaire initiale et élément structurant (matrice de int
 * contenant uniquement des 0 et des 1)
 * Sortie : image binaire erodée
 */
Image Erosion(Image Im, Matrix ElementStructurant)
{
  AFAIRE(Erosion);
}

/*
 * Dilatation d'une image binaire
 * Entreés : image binaire initiale et élément structurant (matrice de int
 * contenant uniquement des 0 et des 1)
 * Sortie : image binaire dilatée
 */
Image Dilatation(Image Im, Matrix ElementStructurant)
{
  AFAIRE(Dilatation);
}
