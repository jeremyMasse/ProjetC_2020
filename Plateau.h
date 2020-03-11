#ifndef PLATEAU_H_INCLUDED
#define PLATEAU_H_INCLUDED
#include "structures.h"
void Color(int couleurDuTexte,int couleurDeFond);
char **open_the_file(char const *filepath); //lire un fichier
int liaison_monde(Carte_t *carte, Carte_t *haut, Carte_t *bas, Carte_t *gauche, Carte_t *droite);
Carte_t *creation_monde(Carte_t *monde);
Carte_t *add_carte(Carte_t *monde, char const *filepath, int num); //ajouter une carte
Carte_t *Initialisation_p(); //initialisation de la structure carte
void print_plateau(Carte_t *monde);
Joueur_t *deplacer(Joueur_t *joueur, char cases);
//char **Map_crea(COORD_map_t *map);
//int PrintMap(char **MiniMap);

#endif // PLATEAU_H_INCLUDED

