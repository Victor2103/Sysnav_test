#include "plateau.c"
#include "mouvement.c"

int main(int argc, char *argv[]){
    if (argc<2){
        printf("Merci de rentrer une grille après le ./\"nom de l'executable\"\n");
    }
    else {
        FILE *grid1=NULL;
        char *plateau=NULL;
        char nomfichier[1000]="";
        // Création du répertoire ou se situe les grilles. Le chemin est à changer car c'est celui de mon ordinateur. 
        sprintf(nomfichier,"/home/eisti/Documents/test_Sysnav/test_5/grids/%s",argv[1]);
        int nbLignes=initialiserNbLignesGrille(grid1,nomfichier);
        int nbColonnes=initialiserNbColonnesGrille(grid1,nomfichier);
        int tailleplateau=nbLignes*nbColonnes;
        //Allocation de la mémoire pour créer le plateau de chaine de caractère récupéré par la grille passé en paramètre. 
        plateau=malloc(tailleplateau*sizeof(char));
        initialiserGrille(grid1,plateau,nomfichier);

        int *cheminGrille=NULL;
        cheminGrille=malloc(tailleplateau*sizeof(int));
        //Creation de la grille qui est le plateau mais avec des entiers. 
        transformationGrille(plateau,cheminGrille,tailleplateau);
        int PosDepart=renvoiePositionDepart(plateau,tailleplateau);
        int PosFeu=renvoiePositionFeuDepart(plateau,tailleplateau);
        int boolCheminPossible=faireChemin(cheminGrille,PosDepart,nbColonnes,tailleplateau,5,PosFeu);
        int positionSortie=RecupNumBonneSortie(cheminGrille,tailleplateau);
        int *suitePositions=NULL;
        char *suiteFinalURDL=NULL;
        //Verification pour voir s'il existe un chemin 
        if (boolCheminPossible==0){
            printf("Le chemin existe !\n");
            int minimum=10000;
            int taille=retrouverCheminTaille(cheminGrille,positionSortie,tailleplateau,nbColonnes,&minimum);
            suitePositions=malloc(taille*sizeof(int));
            minimum=10000;
            retrouverChemin(cheminGrille,positionSortie,tailleplateau,nbColonnes,&minimum,suitePositions);
            suiteFinalURDL=malloc(taille*sizeof(char));
            transformerPositionURDL(PosDepart,taille,suitePositions,nbColonnes,suiteFinalURDL);
            printf("Voici le chemin : \n%s\n",suiteFinalURDL);
            exit(0);

            
        }
        else {
            exit(1);
        }
        //Liberer la mémoire de chaque pointeur utilisé pour les tableaux. 
        free(suiteFinalURDL);
        free(plateau);
        free(cheminGrille);
        free(suitePositions);
    }
    return(0);
}