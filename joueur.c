#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "joueur.h"
#include "plateau.h"

int monter_niveau(Joueur_t *joueur)
{
     Color(1,0);
     if (joueur->xp >= (joueur->xp_besoin + 100 * joueur->niveau)){ // on demande 100 xp de plus à chaque niveau, ça commence à 200 xp pour passer niv 2
        joueur->niveau = joueur->niveau + 1;
        printf("\nVous montez niveau %d",joueur->niveau);
        joueur->xp = 0;
        joueur->vie = joueur->vie + joueur->croiss_vie; // augmente la vie par niveau
        joueur->vie_max = joueur->vie;
        joueur->attaque = joueur->attaque + joueur->croiss_attaque; //augmente l'attaque par niveau
        Color(10,0);
        printf("\nVous avez maintenant %d point de vie", joueur->vie);
        Color(4,0);
        printf("\nVous avez maintenant %d point d'attaque", joueur->attaque);
        Color(15,0);
     }
     else{
        Color(11,0);
        printf("\nVous etes niveau %d et avez %d/%d xp", joueur->niveau, joueur->xp, (joueur->xp_besoin + 100 * joueur->niveau));
     }
}
Joueur_t *initialisation_J(char *nom, Carte_t *monde)
{
    Joueur_t *joueur = malloc(sizeof(Joueur_t));
    if (joueur == NULL)
        return NULL;
    joueur->nom = nom;
    joueur->vie = 100;
    joueur->mort = 0;
    joueur->vie_max = joueur->vie;
    joueur->attaque = 35;
    joueur->xp = 0;
    joueur->niveau = 1;
    joueur->xp_besoin = 100;
    joueur->croiss_vie = 10;
    joueur->croiss_attaque = 3;
    Item_t *inventaire = initialisation_I();
    if (inventaire == NULL) return NULL;
    joueur->inventaire = inventaire;
    joueur->coord = malloc(sizeof(COORD_t));
    if (joueur->coord == NULL)
        return NULL;
    joueur->coord->x = 1;
    joueur->coord->y = 1;
    joueur->coord->carte_actuel = monde->head;
    return joueur;
}
void Afficher_stat(Joueur_t *joueur)
{
    system("cls");
    Locate(50,1);
    Color(13,0);
    printf("%s",joueur->nom);
    Locate(40,3);
    Color(1,0);
    printf("Niveau: %d", joueur->niveau);
    Locate(40,4);
    printf("XP: %d", joueur->xp);
    Locate(40,5);
    Color(10,0);
    printf("Vie: %d", joueur->vie);
    Locate(40,6);
    Color(4,0);
    printf("Attaque: %d", joueur->attaque);
    Locate(40,7);
    Color(15,0);
    printf("Vous vous trouvez sur la carte %d", joueur->coord->carte_actuel->num);
    printf("\nAppuyez sur une touche pour retourner au jeu");
    _getch();
    system("cls");
    return;
}
