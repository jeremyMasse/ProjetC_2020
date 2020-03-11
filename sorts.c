#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sorts.h"
//Fonctions encylopedie de sorts faites mais les sorts ne sont pas codés
Sort_t *add_sorts(Sort_t *sorts, char* nom, int attaque, int chargement, char *particularite)
{
    sorts->end->next = malloc(sizeof(Sort_t));
    if (sorts->end->next == NULL) return NULL;
    sorts->end->next->nom = nom;
    sorts->end->next->attaque = attaque;
    sorts->end->next->chargement = chargement;
    sorts->end->next->particularite = particularite;
    sorts->end->next->next = NULL;
    sorts->end->next->head = sorts->head;
    sorts->end->next->end = sorts->end->next;

    for (Sort_t *i = sorts->head; i != NULL; i = i->next){
        i->end = sorts->end->next;
    }
    return sorts->head;
}
Sort_t *initialisation_S()
{
    Sort_t *sorts = malloc(sizeof(Sort_t));
    if (sorts == NULL)return NULL;
    sorts->nom = "Coup de massue";
    sorts->attaque = 30;
    sorts->chargement = 2;
    sorts->particularite = "aucune";
    sorts->next = NULL;
    sorts->head = sorts;
    sorts->end = sorts;

    sorts = add_sorts(sorts, "Panini", 50, 3, "pain/fromage");
    sorts = add_sorts(sorts, "sournoiserie", 40, 1, "Aucune");
    sorts = add_sorts(sorts, "Incarnation demoniaque", 30, 3, "regen");
    sorts = add_sorts(sorts, "Crie de Coro", 30, 2, "assourdissant");
    return sorts;
}

void print_sorts(Sort_t *sorts)
{
    sorts = sorts->head;
    while (sorts != NULL){
        printf("\nDans l'encyclopedie des sorts il y a : %s", sorts->nom);
        sorts = sorts->next;
    }
}
