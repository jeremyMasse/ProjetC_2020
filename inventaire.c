#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventaire.h"

//Fonction pour inventaire faite entièrement mais encyclopedie d'item non faite
//utilisation de liste chainee
Item_t *initialisation_I(void) //initialisation de l'inventaire avec une épée
{
    Item_t *inventaire = malloc(sizeof(Item_t));
    if (inventaire == NULL)return NULL;
    inventaire->nom_item = "epee";
    inventaire->consommable = 1;
    inventaire->nbr = 1;
    inventaire->next_item = NULL;
    inventaire->previous_item = NULL;
    inventaire->head = inventaire;
    inventaire->end = inventaire;
    return inventaire;
}
void print_inv(Item_t *inventaire)
{
    system("cls");
    Locate(50,2);
    Color(8,0);
    printf("Inventaire");
    if(count_item(inventaire)< 1){
        Color(4,0);
        Locate(40, 3);
        printf("Vous ne possedez rien dans l'inventaire");
    }
    inventaire = inventaire->head;
    int count = 4;
    Color(1,0);
    while (inventaire != NULL){
        Locate(40, count);
        printf("Dans l'inventaire il y a : %s x %d", inventaire->nom_item, inventaire->nbr);
        inventaire = inventaire->next_item;
        count = count + 1;
    }
    printf("\n\nAppuyez sur une touche pour retourner au jeu");
    _getch();
    system("cls");
}
int count_item(Item_t *inventaire)
{
    int counter = 0;
    inventaire = inventaire->head;
    while(inventaire != NULL){
        counter = counter + 1;
        inventaire = inventaire->next_item;
    }
    return counter;
}
Item_t *add_item(Item_t *inventaire, char *nom_item, int consommable) // ajoute un item à la fin
{
    for (Item_t *i = inventaire->head; i != NULL; i = i->next_item){
        if((strcmp(nom_item, i->nom_item)) == 0){
           i->nbr = i->nbr + 1;
           return inventaire;
        }}
    inventaire->end->next_item = malloc(sizeof(Item_t));
    if (inventaire->end->next_item == NULL) return NULL;
    inventaire->end->next_item->nom_item = nom_item;
    inventaire->end->next_item->nbr = 1;
    inventaire->end->next_item->consommable = 0;
    inventaire->end->next_item->next_item = NULL;
    inventaire->end->next_item->head = inventaire->head;
    inventaire->end->next_item->previous_item = inventaire->end;
    inventaire->end = inventaire->end->next_item;

    for (Item_t *i = inventaire->head; i != NULL; i = i->next_item){
        i->end = inventaire->end;
    }
    count_item(inventaire);
    return inventaire;
}
Item_t *del_item(Item_t *inventaire, char *nom)
{
    inventaire = inventaire->head;
    while(inventaire != NULL && strcmp(inventaire->nom_item, nom) != 0){
        inventaire = inventaire->next_item;
    }
    if (inventaire->nbr > 1){
        inventaire->nbr = inventaire->nbr - 1;
        return inventaire->head;
    }
    Item_t *tmp = inventaire;
    if ((count_item(inventaire)) == 1){
        inventaire->nom_item = "vide";
        inventaire->nbr = 0;
        return inventaire;
    }
    if (inventaire->previous_item != NULL && inventaire->next_item != NULL){
        inventaire->next_item->previous_item = inventaire->previous_item;
        inventaire->previous_item->next_item = inventaire->next_item;
        free(tmp);
        *inventaire = *inventaire->head;
    }
    else if (inventaire->previous_item == NULL ){
        inventaire->next_item->previous_item = NULL;
        for (Item_t *i = inventaire->end; i != NULL; i = i->previous_item){
            i->head = inventaire->next_item;
        }
        *inventaire = *inventaire->end;
        }
    else if (inventaire->next_item == NULL){

            inventaire->previous_item->next_item = NULL;
        for (Item_t *i = inventaire->head; i != NULL; i = i->next_item){
            i->end = inventaire->previous_item;
        }
        *inventaire = *inventaire->head;
        }
    return inventaire;
}
