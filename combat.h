#ifndef COMBAT_H_INCLUDED
#define COMBAT_H_INCLUDED
#include "structures.h"
Combat_t *creer_combat(Monstres_t *monstres, Joueur_t *joueur);
int attaquer(Monstres_t *monstre, int attaque);
int print_consommable(Joueur_t *joueur);
int boire_potion(Joueur_t *joueur);
int choix_invent(Joueur_t *joueur);
int choix_combat(Joueur_t *joueur, Monstres_t *monstre);
int rand_alea(int a, int b);
int combat(Combat_t *un_combat);
void afficher_vie(Monstres_t *m, Joueur_t *j);

#endif // COMBAT_H_INCLUDED
