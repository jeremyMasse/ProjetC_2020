#ifndef INVENTAIRE_H_INCLUDED
#define INVENTAIRE_H_INCLUDED
#include "structures.h"

Item_t *initialisation_I(void);
void print_inv(Item_t *inventaire);
Item_t *add_item(Item_t *inventaire, char *nom_item, int consommable);
Item_t *del_item(Item_t *inventaire, char *nom);
int count_item(Item_t *inventaire);

#endif // INVENTAIRE_H_INCLUDED
