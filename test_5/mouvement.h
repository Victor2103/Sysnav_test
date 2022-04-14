#ifndef JEU2
#define JEU2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*La fonction va noter si le personnage peut se déplacer sur les cases à coté de lui.
S'il peut se déplacer, la case à proximité va être remplacé par un entier noté cpt (cette case était marqué avant par 0, l'abscence d'obsctacle).
S'il ne peut pas se déplacer, alors aucune case ne sera marqué.
La fonction renvoie un entier reussite qui est égale à 0 si l'un des voisins est l'arrivée pour le personnage (entier correspondant à 3)
@param1: nvGrille= la grille d'entiers qui représente le plateau à l'instant t
@param2: position= la position pour laqulle on va regarder les cases voisines
@param3: colonnes= le nombre de colonnes
@param4: tailleGrille= la taille total du plateau ou de la grille
@param5: cpt= le compteur que l'on va écrire sur les cases voisines de positions qui sont libres
@param6: reussite= Un entier qui est égal à 0 si l'un des voisins de position est la sortie pour le personnage*/
int remplirVoisins(int *nvGrille,int position,int colonnes,int tailleGrille,int cpt,int reussite);


/*La fonction va renvoyer le nombre de cases pour lesquelles la valeur de la case est égale à l'entier cpt.   
@param1: nvGrille= la grille d'entiers qui représente le plateau à l'instant t
@param2: cpt= l'entier que l'on recherche dans la grille
@param3: tailleNvGrille= la taille de la grille d'entiers */
int parcourirCpt(int *nvGrille,int cpt,int tailleNvGrille);


/*La fonction creer un tableau que l'on rentre en paramètre qui recense les positions pour lesquelles les cases de la grill sont égales à l'entier cpt.  
@param1: nvGrille= la grille d'entiers qui représente le plateau à l'instant t 
@param2: cpt= l'entier que l'on recherche dans la grille 
@param3: tableauPosition= le tableau initialement vide que l'on remplit avec les positions de l'endroit ou se situe les cpt. 
@param4: tailleGrille= la taille du plateau*/
void tableauPos(int *nvGrille,int cpt,int *tableauPosition,int tailleGrille);


/*Cette fonction simule le passage du feu une fois et modifie la grille
@param1: nvGrille= la grille d'entiers qui représente le plateau à l'instant t  
@param2: position= une position ou le feu est présent sur la case 
@param3: colonnes= le nomnbre de colonnes de la grille
@param4: tailleGrille= la taille du plateau*/
void parcoursFeu(int *nvGrille,int position,int colonnes,int tailleGrille);


/*Cette fonction simule le chemin parcouru par le personnage ainsi que le feu. Elle renvoie un entier. 
Si cet entier est égale à 0, alors il existe un chemin sans que le personnage soit brulé.
Si il est égale à 1 ou 2, alors aucune sortie n'est atteinte et il n'existe pas de chemin.
La fonction remplit la grille avec des entiers, ou chaque entier à partir de 5 est un chemin. 
@param1:  nvGrille= la grille d'entiers qui représente le plateau à l'instant t  
@param2: position=la position de départ du personnage à l'instant t=0
@param3: colonnes= nombres de colonnes du plateau
@param4: tailleGrille= la taille du plateau
@param5: cpt=l'entier qui va débuter le chemin (ici 5 au début)
@param6: feuDepart=la position du feu au départ à l'instant t=0   */
int faireChemin(int *nvGrille,int position,int colonnes,int tailleGrille,int cpt,int feuDepart);


/*Renvoie la position dans le tableau ou le personnage peut sortir (c'est aussi la sortie que l'on peut atteindre après le passage du feu)
@param1: nvGrille=la grille d'entiers qui représente le plateau à l'instant t 
@param2: tailleGrille= la taille du plateau  */
int RecupNumBonneSortie(int *nvGrille,int tailleGrille);


/*Cette fonction permet de renvoyer la position du voisin pour lequel on trouve le minimum.
@param1: nvGrille=la grille d'entiers qui représente le plateau à l'instant t 
@param2: tailleGrille= la taille du plateau 
@param3: position=la position pour laquelle on va regarder les voisins
@param4: colonnes=le nombre de colonnes du plateau
@param5: min=un pointeur sur le minimum, le pointeur permet de garder la valeur du minimum*/
int renvoiePosminimumVoisin(int *nvGrille,int tailleGrille,int position,int colonnes,int *min);


/*Cette fonction utilise la fonction renvoiePosminimumVoisin. 
Elle part de la position d'arrivée du personnage et remonte le chemin juqu'à arriver à la position ou la grille est égàle à 2 qui est la position de départ.
La fonction renvoie la taille du chemin. 
Par exemple je pars de la sortie nvGrille[position]=3 puis je trouve un voisin =7 puis je me place sur la position du voisin=7.
Et je trouve ensuite voisin=6 etc je remonte jusqu'à tomber sur le voisin =2 qui est la position de départ. 
@param1: nvGrille=la grille d'entiers qui représente le plateau à l'instant t 
@param2: position=la position d'arrivée que le personnage doit atteindre$
@param3: tailleGrille= la taille du plateau
@param4: colonnes= le nombre de colonnes du plateau
@param5: min=un pointeur sur le minimum pour le garder à chaque déplacement */
int retrouverCheminTaille(int *nvGrille,int position,int tailleGrille,int colonnes,int *min);


/* Cette fonction est la même que retrouverChemin taille sauf qu'elle remplit le tableau suite au lieu de renvoyer la taille du chemin. 
@param1: nvGrille=la grille d'entiers qui représente le plateau à l'instant t 
@param2: position=la position d'arrivée que le personnage doit atteindre$
@param3: tailleGrille= la taille du plateau
@param4: colonnes= le nombre de colonnes du plateau
@param5: min=un pointeur sur le minimum pour le garder à chaque déplacement
@param6: suite= le tableau des positions du chemin (indice=0-> position d'arrivée et indice=taille-1->position de départ) */
void retrouverChemin(int *nvGrille,int position,int tailleGrille,int colonnes,int *min,int *suite);


/* Cette fonction transforme les positions du chemin en une suite de URDL qui correspond au chemin final. 
On part de la fin du chemin car cela correspond à la position de départ.
@param1: position=la position ou se trouve le personnage à t=0
@param2: tailleSuite= la taille du chemin (obtenu avec retrouverCheminTaille)
@param3: suite=la suite de position du chemin obtenu avec retrouverChemin
@param4: colonnes=le nombre de colonnes du plateau
@param5: suiteURDL= le tableau que l'on remplit avec les char 'U','R','D' ou 'L'. */
void transformerPositionURDL(int position,int tailleSuite,int* suite,int colonnes,char *suiteURDL);


#endif