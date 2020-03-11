#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED
#include "structures.h"

Joueur_t *initialisation_J(char *nom, Carte_t *monde);
void Afficher_stat(Joueur_t *joueur);
int monter_niveau(Joueur_t *joueur);
#endif // JOUEUR_H_INCLUDED
