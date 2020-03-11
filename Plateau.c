#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "plateau.h"


void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage de couleurs
{
        HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}
char **open_the_file(char const *filepath) // Pour recuperer une carte dans un fichier
{
    FILE* file = fopen(filepath, "r");
    if (file == -1)
        return NULL;
    char **carte = malloc(sizeof(char*) * 10);
        for (int j = 0; j < 10; j = j + 1){
            carte[j] = malloc(sizeof(char) * 13);
        }
    if (carte == NULL)
        return NULL;
    int count = 0;
    for(int i = 0 ; i < 10; i++){
        for(int j = 0; j < 13; j++){
            char caractere = fgetc(file);
            carte[i][j]= caractere;
            count = count + 1;
        }
    }
    fclose(file);
    return (carte);
}
int liaison_monde(Carte_t *carte, Carte_t *haut, Carte_t *bas, Carte_t *gauche, Carte_t *droite)
{
    carte->haut = haut;
    carte->bas = bas;
    carte->gauche = gauche;
    carte->droite = droite;
    return 0;
}

Carte_t *creation_monde(Carte_t *monde) // Faire un monde composer de 9 cartes
{
    Carte_t *carte_un = monde->head;
    Carte_t *carte_deux = carte_un->next;
    Carte_t *carte_trois = carte_deux->next;
    Carte_t *carte_quatre = carte_trois->next;
    Carte_t *carte_cinq = carte_quatre->next;
    Carte_t *carte_six = carte_cinq->next;
    Carte_t *carte_sept = carte_six->next;
    Carte_t *carte_huit = carte_sept->next;
    Carte_t *carte_neuf = carte_huit->next;
    monde = monde->head;
    liaison_monde(monde, NULL, carte_quatre, NULL, carte_deux);
    monde = monde->next;
    liaison_monde(monde, NULL, carte_cinq, carte_un, carte_trois);
    monde = monde->next;
    liaison_monde(monde, NULL, carte_six, carte_deux, NULL);
    monde = monde->next;
    liaison_monde(monde, carte_un, carte_sept, NULL, carte_cinq);
    monde = monde->next;
    liaison_monde(monde, carte_deux, carte_huit, carte_quatre, carte_six);
    monde = monde->next;
    liaison_monde(monde, carte_trois, carte_neuf, carte_cinq, NULL);
    monde = monde->next;
    liaison_monde(monde, carte_quatre, NULL, NULL, carte_huit);
    monde = monde->next;
    liaison_monde(monde, carte_cinq, NULL, carte_sept, carte_neuf);
    monde = monde->next;
    liaison_monde(monde, carte_six, NULL, carte_huit, NULL);
    return monde->head;
}

Carte_t *add_carte(Carte_t *monde, char const *filepath, int num)
{
    monde->end->next = malloc(sizeof(Carte_t));
    monde->end->next->num = num;
    monde->end->next->carte = open_the_file(filepath);
    monde->end->next->head = monde->head;
    monde->end->next->next = NULL;
    monde->end->next->previous = monde->end;
   /*monde->end->next->minicarte = minicarte;  minicarte qui nous montre 9 cases et qui affiche dans laquelle nous sommes
    int count = 0;
  while(count != monde->end->num){
        for (int i = 0; i < 3; i = i + 1){
            for (int j = 0; j < 3; j = j + 1){
                if (count == num)
                minicarte[i][j] == 'J';
                minicarte[0][0] == '_';
            }
        }
    }*/
    for (Carte_t *i = monde->head; i != NULL; i = i->next){
        i->end = monde->end->next;
    }
    return monde;
}

Carte_t *Initialisation_p() // initialise le monde
{
    Carte_t *Monde = malloc(sizeof(Carte_t));
    Monde->num = 1;
    Monde->carte = open_the_file("fichierTXT/carte1.txt");
    Monde->head = Monde;
    Monde->end = Monde;
    Monde->next = NULL;
    Monde->previous = NULL;
    char **minicarte = malloc(sizeof(char*) * 3);
    for (int i = 0; i < 3; i = i + 1){
        minicarte[i] = malloc(sizeof(char) * 4);
    }
    int count = 0;
    /*for (int i = 0; i < 4; i = i + 1){
            for(int j = 0; j < 4; j = j + 1){
                if (count == 1)
                    minicarte[i][j] = 'J';
                else
                    minicarte[i][j] = (char)count;
                count = count + 1;
            }
    }
    Monde->minicarte = minicarte;*/
    Monde = add_carte(Monde, "fichierTXT/carte2.txt", 2);
    Monde = add_carte(Monde, "fichierTXT/carte3.txt", 3);
    Monde = add_carte(Monde, "fichierTXT/carte4.txt", 4);
    Monde = add_carte(Monde, "fichierTXT/carte5.txt", 5);
    Monde = add_carte(Monde, "fichierTXT/carte6.txt", 6);
    Monde = add_carte(Monde, "fichierTXT/carte7.txt", 7);
    Monde = add_carte(Monde, "fichierTXT/carte8.txt", 8);
    Monde = add_carte(Monde, "fichierTXT/carte9.txt", 9);
    Monde = creation_monde(Monde);
    return Monde;
}
/*char **Plateau_Crea(Joueur_t *joueur)
{
    char **carte = malloc(sizeof(char*) * 11);
    for(int i = 0 ; i < 10; i++){
        carte[i] = malloc(sizeof(char) *11);
    }
    for(int i = 0 ; i < 10;i++){
        for(int j = 0;j < 10;j++){
            carte[i][j]='_';
        }
    }
    carte[5][5] = '*';
    joueur->coord->x = 5;
    joueur->coord->y = 5;
    return carte;
}*/
Joueur_t *deplacer(Joueur_t *joueur, char cases)
{
    char deplacement = ' ';
    int i = joueur->coord->x;
    int j = joueur->coord->y;
    Carte_t *ancienne_carte = joueur->coord->carte_actuel;
    printf("Deplacer votre personnage(z/q/s/d): ");
    printf("\nm pour lancer le menu\n");
    do{
        scanf("%c",&deplacement);
        if (deplacement == 'z'){
            if(i > 1)
                i = i - 1;
            else if (joueur->coord->carte_actuel->haut != NULL){
                joueur->coord->carte_actuel = joueur->coord->carte_actuel->haut;
                i = i + 7 ;
            }
            else
                deplacement = ' ';
        }
        if (deplacement == 'q'){
            if(j > 1)
                j = j - 1;
            else if (joueur->coord->carte_actuel->gauche != NULL){
                joueur->coord->carte_actuel = joueur->coord->carte_actuel->gauche;
                j = j + 9;
            }
            else
                deplacement = ' ';
        }
        if (deplacement == 's'){
            if (i < 8)
                i = i + 1;
            else if (joueur->coord->carte_actuel->bas != NULL){
                joueur->coord->carte_actuel = joueur->coord->carte_actuel->bas;
                i = i - 7;
            }
            else
                deplacement = ' ';
        }
        if (deplacement == 'd'){
            if (j < 10)
                j = j + 1;
            else if (joueur->coord->carte_actuel->droite != NULL){
                joueur->coord->carte_actuel = joueur->coord->carte_actuel->droite;
                j = j - 9;
            }
            else
                deplacement = ' ';
        }
        if (deplacement == 'm'){
            menu_en_jeu(joueur);
            print_plateau(joueur->coord->carte_actuel);
            printf("Deplacer votre personnage(z/q/s/d): ");
            printf("\nm pour lancer le menu\n");
            deplacement = ' ';
        }
    }while (deplacement != 'z' && deplacement != 'q' && deplacement != 's' && deplacement != 'd');
    deplacement = getchar();
    if (joueur->coord->carte_actuel->num != ancienne_carte->num){
        Color(4,0);
        printf("Vous passer dans la map %d", joueur->coord->carte_actuel->num);
        print_plateau(joueur->coord->carte_actuel);
        Sleep(3000);
    }
    joueur->coord->carte_actuel->carte[i][j] = 'J';
    ancienne_carte->carte[joueur->coord->x][joueur->coord->y] = cases;
    joueur->coord->x = i;
    joueur->coord->y = j;
    return joueur;
}

void print_plateau(Carte_t *monde)
{
    char **carte = monde->carte;
    printf("\n");
    for(int i = 0 ; i < 10;i++){
        for(int j = 0;j < 12;j++){
            if ((monde->haut != NULL && i == 0) || (monde->bas != NULL && i == 9) || (monde->gauche != NULL && j == 0) || (monde->droite != NULL && j==11))
                    Color(10, 0);
            else if ((monde->haut == NULL && i == 0) || (monde->bas == NULL && i == 9) || (monde->gauche == NULL && j == 0) || (monde->droite == NULL && j==11))
                    Color(4,0);
            else
                if (monde->carte[i][j] == 'M')
                    Color(1,1);
                else if (monde->carte[i][j] == 'C')
                    Color(11,11);
                else if (monde->carte[i][j] == 'J')
                    Color(15,15);
                else
                    Color(15,0);

            printf ("%c", carte[i][j]);
            if (i != 0 && j != 0 && j < 10){
                Color(15,0);
                printf("|");
            }
            else if(i == 0 && j > 0){
                printf(" ");
            }
        }
        Color(15,0);
        printf("\n");
    }
    Color(1,0);
    printf("monstre    ");
    Color(11,0);
    printf("coffre     ");
    Color(15,0);
    printf("joueur\n");
}

/*int PrintMap(char **MiniMap)
{
    printf("plateau");
    printf("\n");
    for(int i = 0 ; i < 4;i++){
        for(int j = 0;j < 4;j++){
            printf ("%c",MiniMap[i][j]);
            printf("|");
        }
        printf("\n");
    }
}
*/
