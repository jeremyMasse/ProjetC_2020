#ifndef MONSTRES_H_INCLUDED
#define MONSTRES_H_INCLUDED
#include "structures.h"

Monstres_t *add_monstres(Monstres_t *monstres, Sort_t *sort, char* nom, int vie, int attaque, int croiss_vie, int croiss_attaque, int gain_xp);
Monstres_t *initialisation_M(Sort_t *sorts);
void print_monstres(Monstres_t *monstres);
Monstres_t *Crea_monstre(Monstres_t *Monstres, int niveau, int num);
#endif // MONSTRES_H_INCLUDED
