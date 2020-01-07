#ifndef TOOLS_H
#define TOOLS_H


long **create_long_mat(int nbRows, int nbCol);
void copy_array(int* array_source, int* array_destination, int dimension);
void init_array(int *array, int dimension);
double array_distance(int *node_array, instance_t reference_instance);
double instance_distance(instance_t *instance);
double euclidean_distance(long x1, long y1, long x2, long y2);

void erreur(char *message);
int random_node(int min, int max);
int *creer_tab_int(int dim);
char *creer_tab_char(int dim);
void affiche_tab_int(int *tab, int dim, FILE *logfp);
void affiche_tab_char_hex(char *tab, int dim, FILE *logfp);
void affiche_tab_char(char *tab, int dim, FILE *logfp);
int **creer_mat_int(int nbRows, int nbCol);
double **creer_mat_dist(int dimension);
void swap(int *tab, int ind1, int ind2);/// \brief inverse le contenu des cases ind1 et ind2 dans tab
void renverse_tab(int *tab, int prem, int der);

#endif