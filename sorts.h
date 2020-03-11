#ifndef SORTS_H_INCLUDED
#define SORTS_H_INCLUDED
#include "structures.h"

Sort_t *add_sorts(Sort_t *sorts, char* nom, int attaque, int chargement, char *particularite);
Sort_t *initialisation_S();
void print_sorts(Sort_t *sorts);

#endif // SORTS_H_INCLUDED
