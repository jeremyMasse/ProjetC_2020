#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <windows.h>
#include "sorts.h"
#include "monstres.h"
#include "joueur.h"
#include "plateau.h"
#include "combat.h"
#include "menu.h"
#include "inventaire.h"

int choix_case()
{
    int curs = 0;
    int touche = 0;
    do{
        system("cls");
        Locate(30,2);
        Color(10,0);
        printf("Vous rencontrez un monstre, voulez-vous le combattre ?");
        Locate(50,3);
        printf("%c oui",(curs==0)?'>':' ');
        Locate(50,4);
        printf("%c non",(curs==1)?'>': ' ');
        Color(15,0);
        touche = _getch();
        if (touche==0xE0)
        {
            touche = _getch();
            if (touche==0x50 && curs < 2)
                curs = curs + 1;
            if (touche==0x48 && curs > 0)
                curs = curs - 1;
        }
    } while (touche!=0x0D);
    return curs;
}
int start(void){
    system ("cls");
    Locate(50,2);
    printf("Bienvenue dans notre jeu ");
    Sort_t *encyclopedie_s  = initialisation_S(); //initialisation des sorts
    if (encyclopedie_s == NULL)return NULL;
    print_sorts(encyclopedie_s);
    Monstres_t *encyclopedie_m = initialisation_M(encyclopedie_s); //initialisation des monstres
    if (encyclopedie_m  == NULL)return NULL;
    print_monstres(encyclopedie_m);
    Carte_t *monde = Initialisation_p(); //initialisation de la carte
    if (monde == NULL)return NULL;
    char nom_joueur[10];
    printf("\n\nEntrez le nom de votre personnage : ");
    scanf("%s", nom_joueur);
    Joueur_t *joueur = initialisation_J(nom_joueur, monde); //initialisation du joueur
    if (joueur == NULL)return NULL;

    char cases = '_';
    srand(time(NULL));
    while (1==1){
        system ("cls");
        print_plateau(joueur->coord->carte_actuel);
        joueur = deplacer(joueur, cases);
        print_plateau(joueur->coord->carte_actuel);
        cases = '_';
        int alea = rand_alea(0,100);
        if( alea % 2 == 0 || alea % 3 == 0){
            int choix = choix_case();
            if (choix == 0){
                Combat_t *un_combat = creer_combat(encyclopedie_m, joueur);
                combat(un_combat);
            }
            else
                cases = 'M';
        }
        else{
            printf("Vous avez trouve un coffre");
            Sleep(2000);
            cases = 'C';
        }
            //coffre();
    }
    return 0;
}

int main(void)
{
    menu();
    return 0;
}
