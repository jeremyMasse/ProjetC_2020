#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "menu.h"
void a_propos()
{
    printf("bien le bonjour aventurier et bienvenue dans le merveilleux monde du cauchemar.");
    printf("\nVous etes tomber dans un cauchemar en vous couchant vous ne voulez pas restez dedans !");
    printf("\nPour rejoindre le monde des licorne rose unijambique qui chie des arc-en-ciel,");
    printf("\nIl vous faudra vaincre les differents monstres sur votre chemin");
    printf("\nsi vous mourez votre cauchemar recommence...");
    Color(5,0);
    printf("\nBoss Mosse :");
    Color(15,0);
    printf("\"Si vous vous pensez pret, venez me voir sur la derniere carte, je me trouve dans mon donjon\"");
}

void Locate(int x,int y)
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    COORD C;
    C.X=(SHORT)x;
    C.Y=(SHORT)y;
    SetConsoleCursorPosition(H,C);
}

void menu_principal(int curs)
{
    Locate(0,0);
    printf("%c nouvelle partie\n",(curs==0)?'>':' ');
    printf("%c charger sauvegarde(pas active)\n",(curs==1)?'>':' ');
    printf("%c a propos\n",(curs==2)?'>':' ');
    printf("%c quitter\n",(curs==3)?'>':' ');
}

int Choisir(char *menu_diff)
{
    int curs = 0;
    int touche;
    do
    {
        if((strcmp(menu_diff,"principal")) == 0)
            menu_principal(curs);
        else if ((strcmp(menu_diff, "en_jeu")) == 0)
            afficher_menu_en_jeu(curs);
        touche = _getch();
        if (touche==0xE0) // fleche : le code fleche renvoie 2 caracteres.
        {
            touche = _getch();
            if (touche==0x50 && curs <= 2)  // fleche bas
                curs = curs + 1;
            if (touche==0x48 && curs >= 1)  // fleche haut
                curs = curs - 1;
        }
    } while (touche!=0x0D);  // enter
    return curs;
}

int menu()
{
    int choix;
    choix = Choisir("principal");
    Locate(0,4);

    if (choix == 0){
        start();
    }
    else if (choix == 1){
        //load_save(); pas active
    }
     else if (choix == 2){
        a_propos();
    }
     else if (choix == 3){
        exit(0);
    }
    //printf("Vous avez choisi : %s\n",);
    return 0;
}

void afficher_menu_en_jeu(int curs)
{
    Locate(0,0);
    printf("%c Afficher les stats du joueur\n",(curs==0)?'>':' ');
    printf("%c Ouvrir l'inventaire\n",(curs==1)?'>':' ');
    printf("%c sauvegarder\n",(curs==2)?'>':' ');
    printf("%c quitter le jeu\n",(curs==3)?'>':' ');
}
int menu_en_jeu(Joueur_t *joueur)
{
    system("cls");
    int choix;
    choix = Choisir("en_jeu");
    if (choix == 0)
        Afficher_stat(joueur);
    else if (choix == 1)
        print_inv(joueur->inventaire);
    else if (choix == 2){
        printf("pas active");
    }
    else if (choix == 3)
        exit(0);
}
