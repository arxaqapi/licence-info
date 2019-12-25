// header global pour le TSP
// vd-software 2019
#ifndef TSPSTAT_H
#define TSPSTAT_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <assert.h>

#define TAILLENOM 32  // les noms sont limités à 32 caractères
#define MAXBUF 256    // taille du buffer de lecture des fichiers
#define NIL -1        // indique l'échec dans une fonction


// SD pour lire le fichier d'instance TSPLIB
typedef struct instance_s
{
  char name[TAILLENOM]; // nom de l'instance
  char type[TAILLENOM]; // type de l'instance
  int dimension;        // nombre de sommets dans l'instance
  char EDGE_TYPE[TAILLENOM];
  double length;    // longueur de la tournée (calcul)
  int **tabCoord;   // tableau des coordonnées (x,y,marque=0 pas vu, n° ordre)
  double **matDist; // demie matrice des distances euclidiennes (calcul)
  int *tabTour;     // tableau des villes formant la tournée (dans l'ordre) (calcul)
} instance_t;

// SD pour lire le fichier "tour" de TSPLIB
typedef struct tour_s
{
  char name[TAILLENOM]; // nom de l'instance
  int dimension;        // nombre de sommets dans l'instance
  double length;        // longueur du tour (calculée ou lue)
  int *tour;            // liste des noeuds de la tournée lus dans le fichier tour
} tour_t;

// variables externes
// permet d'éviter de se trainer les mêmes paramètres dans les sous-programmes
extern FILE *logfp;       // fichier log
extern FILE *resfile;     // fichier de résultats (CSV)
extern bool verbose_mode; // mode bavard
extern bool sans_zero;    // avec ou sans zéro

// prototypes des sp en vrac à classer
void dump_tour(tour_t tour);
bool next_permutation(int *tab, int dim);
double swap_2opt(instance_t instance, tour_t *tournee, int ind1, int ind2);
double improve_2opt_syst(instance_t instance, tour_t *tournee, int ind1);
double all_2opt(instance_t instance, tour_t *tournee);
void verify_dist(instance_t instance);
bool villes_adjacentes(tour_t tournee, int ind1, int ind2);
void dump_instance(instance_t instance);
void dump_matrice_dist(instance_t instance);
void print_solution(char *methode, instance_t instance, tour_t t, double longueur, double tps);


// Balises OK
//  void print_help();
//  void analyse_balises(int argc, char **argv, int tab_arg[NB_BALISES]);

// Lecture fichier tsplib
bool prefix(char *motif, char *buf);
int lecture_fichier(char *filename, instance_t *instance);

// Brute Force
double brute_force_tsp(instance_t instance, tour_t *tournee, tour_t *pire, bool use_mat);
bool nextPermutation(int *array, int dim);

// Random Walk
double init_tour_random(instance_t instance, int ville_depart, tour_t *tournee);

// Plus Proche Voisin
double init_tour_ppv(instance_t instance, int depart, tour_t *tournee);

// GA
/// NOT HERE

// TSP Toold, fct° annexe
void init_instance(instance_t *instance);
void init_tour(tour_t *tour);
double dist_euclidienne(instance_t instance, int v1, int v2);
double dist_mat(instance_t instance, int node1, int node2);
void compute_dist(instance_t *instance);
void hard_copy_tour(tour_t *t1, tour_t t2);
double tour_length(instance_t instance, int *tabTour, bool sans_zero);
double tour_length_mat(instance_t instance, int *tabTour);
bool node_in_tour(int node, tour_t tour);
void add_tail(int som, tour_t *tournee);

// tools, Fonction diverses
void erreur(char *message);        // affiche me message et fait un exit
int random_node(int min, int max); // donne un nb aléatoire entre min et max
int *creer_tab_int(int dim);
//
void affiche_tab_int(int *tab, int dim, FILE *logfp);
void affiche_tab_char_hex(char *tab, int dim, FILE *logfp);
void affiche_tab_char(char *tab, int dim, FILE *logfp);
int **creer_mat_int(int nbRows, int nbCol);
double **creer_mat_dist(int dimension);
void swap(int *tab, int ind1, int ind2);
void renverse_tab(int *tab, int prem, int der);


#endif
