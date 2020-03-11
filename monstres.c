#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "monstres.h"

/* Creation de l'encyclopedie des monstres*/
Monstres_t *add_monstres(Monstres_t *monstres, Sort_t *sort, char* nom, int vie, int attaque, int croiss_vie, int croiss_attaque, int gain_xp)
{
    monstres->end->next = malloc(sizeof(Monstres_t));
    if (monstres->end->next == NULL) return NULL;
    monstres->end->next->niveau = 1;
    monstres->end->next->gain_xp = gain_xp;
    monstres->end->next->nom = nom;
    monstres->end->next->vie = vie;
    monstres->end->next->vie_max = vie;
    monstres->end->next->croiss_vie = croiss_vie;
    monstres->end->next->attaque = attaque;
    monstres->end->next->croiss_attaque = croiss_attaque;
    monstres->end->next->sort = sort;
    monstres->end->next->next = NULL;
    monstres->end->next->head = monstres->head;
    monstres->end->next->end = monstres->end->next;
    for (Monstres_t *i = monstres->head; i != NULL; i = i->next){
        i->end = monstres->end->next;
    }
    return monstres;
}
Monstres_t *initialisation_M(Sort_t *sorts)
{
    Monstres_t *monstres = malloc(sizeof(Monstres_t));
    if (monstres == NULL)return NULL;
    monstres->nom = "Trollolo";
    monstres->niveau = 1;
    monstres->gain_xp = 100;
    monstres->croiss_vie = 2;
    monstres->vie = 100;
    monstres->vie_max = monstres->vie;
    monstres->croiss_attaque = 2;
    monstres->attaque = 20;
    monstres->sort = sorts->head;
    monstres->next = NULL;
    monstres->head = monstres;
    monstres->end = monstres;
    sorts = sorts->head->next;
    add_monstres(monstres, sorts, "NynyPas", 150, 45, 3, 3, 150);
    sorts = sorts->next;
    add_monstres(monstres, sorts, "TankSnake", 200, 60, 6, 2,200);
    sorts = sorts->next;
    add_monstres(monstres, sorts, "Boss Mosse", 300, 80, 7, 5,300);
    return monstres;
}
/*Creation d'un monstre pour un combat*/
Monstres_t *Crea_monstre(Monstres_t *Monstres, int niveau, int num)
{
    Monstres_t *monstre = malloc(sizeof(Monstres_t)); //Va chercher le monstre en fonction de la map : map 1-2-3 = monstre 1
    if(num == 1 || num == 2 || num == 3){
        Monstres = Monstres->head;
        monstre->niveau = niveau;
    }
    else if (num == 4 || num == 5 || num == 6){ //map 4-5-6 = monstre 2
        Monstres = Monstres->head->next;
        monstre->niveau = niveau;
        if (niveau > 2)
            monstre->niveau = niveau - 2;
    }
    else if (num == 7 || num == 8){ //map 7-8-9 = monstre 3
        Monstres = Monstres->head->next->next;
        monstre->niveau = niveau;
        if (niveau > 3)
            monstre->niveau = niveau - 3;
    }
    else if(num == 9){
        Monstres = Monstres->end;
        monstre->niveau = niveau;
        if (niveau > 4 )
            monstre->niveau = niveau - 4;
    }
    monstre->nom = Monstres->nom;
    monstre->croiss_vie = Monstres->croiss_vie;
    monstre->gain_xp = Monstres->gain_xp;
    monstre->vie = Monstres->vie;
    monstre->croiss_attaque = Monstres->croiss_attaque;
    monstre->attaque = Monstres->attaque;
    monstre->next = NULL;
    monstre->head = NULL;
    monstre->end = NULL;
    if (niveau > 1){
        monstre->vie = monstre->vie + (monstre->croiss_vie) * niveau;
        monstre->attaque = Monstres->attaque + ((monstre->croiss_attaque)*niveau);
    }
    return monstre;
};

void print_monstres(Monstres_t *monstres)
{
    monstres = monstres->head;
    while (monstres != NULL){
        printf("\nDans l'encyclopedie des monstres il y a : %s", monstres->nom);
        printf("\nCe monstre a le sort %s", monstres->sort->nom);
        monstres = monstres->next;
    }
}


