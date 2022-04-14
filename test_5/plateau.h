#ifndef JEU
#define JEU
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*Renvoie le nombre de lignes de la grille 
@param1: fichierATraiter= le pointeur sur le fichier-grille .txt (ce pointeur est nulle il est initialisé dans la fonction)
@param2: nomduFichier= le nom du fichier rentré dans la ligne de commande par l'utilisateur */
int initialiserNbLignesGrille(FILE* fichierATraiter,char *nomduFichier);


/*Renvoie le nombre de colonnes de la grille
@param1: fichierATraiter= le pointeur sur le fichier-grille .txt (ce pointeur est nulle il est initialisé dans la fonction)
@param2: nomduFichier= le nom du fichier rentré dans la ligne de commande par l'utilisateur */
int initialiserNbColonnesGrille(FILE* fichierATraiter,char *nomduFichier);


/*Initialise un tableau à 1 dimension de caractère qui représente la grille placé en paramètre
@param1: fichierATraiter= le pointeur sur le fichier-grille .txt (ce pointeur est nulle il est initialisé dans la fonction)
@param2: grille=la grille qu'on initialise et qui sera ensuite notre grille
@param3: nomduFichier= le nom du fichier rentré dans la ligne de commande par l'utilisateur */
void initialiserGrille(FILE *fichierATraiter,char *grille,char *nomDuFichier);


/*Renvoie la position dans la grille de départ du personnage
@param1: grille=la grille de caractères qui représente le plateau
@param2: taille= la taille de la grille */
int renvoiePositionDepart(char *grille,int taille);


/*Renvoie la position dans la grille du feu au départ
@param1: grille= la grille de caractères qui représente le plateau
@param2: taille= la taille de la grille */
int renvoiePositionFeuDepart(char *grille,int taille);


/*Transforme la grille de caractères en grille d'entier pour des raisons de simplicité
@param1: grille=la grille de caractères obtenu sur le fichier
@param2: nvGrille= la grille d'entiers que l'on crée à partir de grille
@param3: tailleGrille= la taille de notre grille */
void transformationGrille(char *grille,int *nvGrille,int tailleGrille);


/* renvoie le nombre de cases enflammées qu'il existe sur la grille
@param1: nvGrille= la grille d'entiers qui représente le plateau à l'instant t
@param2: tailleGrille= la taille de la grille */
int compteurFeu(int *nvGrille,int tailleGrille);


/* creer un tableau avec la position des cases ou il y a du feu 
@param1: PosFeu=le tableau que l'on crée avec toutes les cases en feu
@param2: nvGrille= la grille d'entiers qui représente le plateau à l'instant t
@param3: tailleGrille= la taille de notre grille */
void recupPositionFeu(int *PosFeu,int *nvGrille,int tailleGrille);


/* Fonction que vous pouvez utiliser pour afficher la grille
@param1: grille=la grille d'entiers qui représente le plateau à l'instant t
@param2: tailleGrille= la taille de notre grille
@param3: colonnes= le nombre de colonnes de la grille */
void afficherGrille(int *grille,int tailleGrille,int colonnes);



#endif