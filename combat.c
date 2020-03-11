#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <windows.h>
#include "combat.h"
#include "structures.h"
#include "plateau.h"

Combat_t *creer_combat(Monstres_t *monstres, Joueur_t *joueur) // une structure combat qui sera supprimer a la fin du combat
{
    int num_carte = joueur->coord->carte_actuel->num;
    Monstres_t *monstre = Crea_monstre(monstres, joueur->niveau , num_carte);
    Combat_t *un_combat = malloc(sizeof(Combat_t));
    un_combat->tour = 1;
    un_combat->joueur = joueur;
    un_combat->monstre = monstre;
    un_combat->gain_xp = monstre->gain_xp;
    return un_combat;
}
int attaquer(Monstres_t *monstre, int attaque)
{
    if (monstre->vie - attaque > 0){
        monstre->vie = monstre->vie - attaque;
    }
    else
        monstre->vie = 0;
    return 0;
}
int print_consommable(Joueur_t *joueur) //afficher les item consommables de l'inventaire
{
    Item_t *i = joueur->inventaire->head;
    int count = 0;
    while (count < count_item(i)){
        if ((strcmp(i->nom_item, "potion")) == 0){
            printf("Vous avez %d potions", i->nbr);
            printf("En utiliser une ? (O/N)");
            char choix = 0;
            do {
                scanf("%c", &choix);
                if (choix == 'O' || choix == 'o')
                    return 1;
                else if (choix =='N' || choix == 'n')
                    return 0;
                else{
                    printf("Repondre par 'O' ou 'N'");
                    choix = 0;
                }
            }while(choix == 0);
        }
        count = count + 1;
        printf("\nVous n'avez pas de consommables");
        printf("\nAppuyez sur une touche pour revenir au combat");
        _getch();
    }
    return -1;
}
int boire_potion(Joueur_t *joueur)
{
    if (joueur->vie + 30 <= joueur->vie_max)
        joueur->vie = joueur->vie + 30;
}
int choix_invent(Joueur_t *joueur) // si il y a une potion on a le choix de prendre la potion ou pas
{
    int touche;
    int choix = print_consommable(joueur);
    if(choix == 0 || choix == -1)
        return -1;
    else
        boire_potion(joueur);
    return 0;
}
int choix_combat(Joueur_t *joueur, Monstres_t *monstre)
{
    int curs = 0;
    int touche;
    do
    {
        Locate(0,10);
        printf("%c Attaquer \n",(curs==0)?'>':' ');
        printf("%c Ouvrir l'inventaire\n",(curs==1)?'>':' ');
       // printf("%c Lancer un sort(pas active)\n",(curs==2)?'>':' ');
        touche = _getch();
        if (touche==0xE0)
        {
            touche = _getch();
            if (touche==0x50 && curs < 1)  // fleche bas
                curs = curs + 1;
            if (touche==0x48 && curs > 0)  // fleche haut
                curs = curs - 1;
        }
    } while (touche!=0x0D);  // enter
    Locate(0,12);
    if (curs == 0)
        attaquer(monstre, joueur->attaque);
    else if (curs == 1){
        if ((choix_invent(joueur)) == -1)
            system("cls");
            printf("\nVous etes en combat contre %s niveau %d", monstre->nom, monstre->niveau);
            afficher_vie(monstre, joueur);
            choix_combat(joueur, monstre);
    }
    /*else if (curs == 2){
        printf("Fonctionnalite pas encore implemente");
    }*/
    return 0;
}
int rand_alea(int a, int b)
{
    return rand()%(b-a) + a;
}
int combat(Combat_t *un_combat)
{
    char premier;
    srand(time(NULL));
    if ((rand_alea(1,3)) == 1){
        premier = 'm';
    }
    while (un_combat->joueur->vie > 0 && un_combat->monstre->vie > 0){
        system("cls");
        printf("\nVous etes en combat contre %s niveau %d", un_combat->monstre->nom, un_combat->monstre->niveau);
        afficher_vie(un_combat->monstre, un_combat->joueur);
        if (premier == 'm'){
            if (un_combat->monstre->vie >0)
                un_combat->joueur->vie = un_combat->joueur->vie - un_combat->monstre->attaque;
            if (un_combat->joueur->vie > 0)
                choix_combat(un_combat->joueur, un_combat->monstre);
        }
        else{
            if (un_combat->joueur->vie > 0)
                choix_combat(un_combat->joueur, un_combat->monstre);
            if (un_combat->monstre->vie > 0)
                un_combat->joueur->vie = un_combat->joueur->vie - un_combat->monstre->attaque;
        }
        afficher_vie(un_combat->monstre, un_combat->joueur);
    }
    if (un_combat->monstre->vie == 0){
        system("cls");
        printf("Vous avez gagne contre le monstre %s", un_combat->monstre->nom);
        un_combat->joueur->xp = un_combat->joueur->xp + un_combat->gain_xp;
        // ici on recupere le butin qui ets gain d_xp dans l'ideal on aurait pu aussi recuperer des items
        un_combat->joueur->vie = un_combat->joueur->vie_max; //comme il n y a pas d'item, il n y a pas de potion donc on redonne la vie_max
        monter_niveau(un_combat->joueur);
        free(un_combat);
    }
    else
        printf("\nVous etes mort et aller revenir à la vie avec une mort");
        un_combat->joueur->vie = un_combat->joueur->vie_max;
        un_combat->joueur->mort = un_combat->joueur->mort + 1;
        free(un_combat);
        Sleep(3000);
    return 0;
}

void afficher_vie(Monstres_t *m, Joueur_t *j)
{
    int vie = j->vie;
    char *nom = j->nom;
    int pos_y = 3;
    for(int i = 0; i < 2; i = i + 1){
        printf("\n");
        for (int i  = 0; i < 50; i = i + 1){
            Locate(50,pos_y); // positionne le cursor dans la fenetre à 50 espaces de gauche et pos_y espaces du haut
        }
        printf("%s:\n", nom);
        pos_y = pos_y + 1;
        for (int i  = 0; i < 50; i = i + 1){
            Locate(50,pos_y);
        }
        printf(" vie");
        Color(5,10);
        for(int i = 0; i < vie/10; i = i + 1){
            if (i == vie/10/2)
                printf("%d", vie);
            else
                printf(" ");
        }
        Color(15,0);
        printf("\n");
        nom = m->nom;
        vie = m->vie;
        pos_y = pos_y + 1;
    }
}
