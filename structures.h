#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED
//Fichier qui repertorie toutes les structures
typedef struct Carte_s Carte_t;
struct Carte_s{
    int num;
    char **carte;
    char **minicarte;
    Carte_t *next;
    Carte_t *previous;
    Carte_t *head;
    Carte_t *end;
    Carte_t *haut;
    Carte_t *bas;
    Carte_t *gauche;
    Carte_t *droite;
};
typedef  struct COORD_s COORD_t;
struct COORD_s{
    int x;
    int y;
    Carte_t *carte_actuel;
};
/*typedef struct COORD_map{
    int a;
    int b;
}COORD_map_t;*/

typedef struct Item_s Item_t;
struct Item_s {
    char *nom_item;
    int nbr;
    int consommable;
    Item_t *next_item;
    Item_t *previous_item;
    Item_t *head;
    Item_t *end;
};
typedef struct Sort_s Sort_t;
 struct Sort_s {
    int rang;
    char *nom;
    int attaque;
    int chargement;
    char *particularite;
    Sort_t *next;
    Sort_t *head;
    Sort_t *end;
};
typedef struct Monstres_s Monstres_t;
struct Monstres_s {
    char *nom;
    int vie;
    int vie_max;
    int croiss_vie;
    int attaque;
    int gain_xp;
    int croiss_attaque;
    int niveau;
    Sort_t *sort;
    Monstres_t *next;
    Monstres_t *head;
    Monstres_t *end;
    char **Butin;
};
typedef struct Joueur_s Joueur_t;
struct Joueur_s {
    char *nom;
    int mort;
    int argent;
    int vie;
    int vie_max;
    int attaque;
    int xp;
    int xp_besoin;
    int niveau;
    int croiss_vie;
    int croiss_attaque;
    Sort_t *sort;
    Item_t *inventaire;
    COORD_t *coord;
};
typedef struct Combat_s Combat_t;
struct Combat_s{
    int tour;
    Monstres_t *monstre;
    Joueur_t *joueur;
    int gain_xp;
};

#endif // STRUCTURES_H_INCLUDED
