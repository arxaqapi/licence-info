#ifndef LECTUREFICHIER_H
#define LECTUREFICHIER_H

#include "tspstat.h"

#define NB_BANIERES 8


bool prefix(char *motif, char *buf);
int lecture_fichier(char *filename, instance_t *instance);
int cherche_nombre(char *ligne, int *curseur);
void analyse_ligne(char *ligne, instance_t *instance);


#endif