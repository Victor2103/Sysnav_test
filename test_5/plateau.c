#include "plateau.h"



int initialiserNbLignesGrille(FILE* fichierATraiter,char *nomduFichier){
    
    fichierATraiter=fopen(nomduFichier,"r");
    int i=0;
    char chaine[1000]="";
    if (fichierATraiter!=NULL){
        while (fgets(chaine,1000,fichierATraiter)!=NULL){
            i=i+1;
        }
    }
    return(i);
}

int initialiserNbColonnesGrille(FILE* fichierATraiter,char *nomduFichier){
    fichierATraiter=fopen(nomduFichier,"r");
    char chaine[1000]="";
    if (fichierATraiter!=NULL){
        if (fgets(chaine,1000,fichierATraiter)!=NULL){
            return(strlen(chaine)-1);
        }
        else {
            return(0);
        }
    }
    return(0);
}

void initialiserGrille(FILE *fichierATraiter,char *grille,char *nomDuFichier){
    int i=0;
    int j=0;
    fichierATraiter=fopen(nomDuFichier,"r");
    char chaine[1000]="";
    if (fichierATraiter!=NULL){
        while(fgets(chaine,1000,fichierATraiter)!=NULL){
            while(j<strlen(chaine)-1){
                grille[i]=chaine[j];
                j+=1;
                i+=1;
            }
        j=0;
        }
    }
}

int renvoiePositionDepart(char *grille,int taille){
    int i=0;
    while (i<taille){
        if (grille[i]=='S'){
            return(i);
        }
        i=i+1;
    }
    return(i);
}

int renvoiePositionFeuDepart(char *grille,int taille){
    int i=0;
    while (i<taille){
        if (grille[i]=='F'){
            return(i);
        }
        i+=1;
    }
    return(i);
}

/*Compte le nombre de cellules en feu */
int compteurFeu(int *nvGrille,int tailleGrille){
    int i=0;
    int cpt=0;
    while (i<tailleGrille){
        if (nvGrille[i]==4){
            cpt+=1;
        }
        i+=1;
    }
    return(cpt);
}

void recupPositionFeu(int *PosFeu,int *nvGrille,int tailleGrille){
    int i=0;
    int j=0;
    while (i<tailleGrille){
        if (nvGrille[i]==4){
            PosFeu[j]=i;
            j+=1;
        }
        i+=1;
    }
}

void transformationGrille(char *grille,int *nvGrille,int tailleGrille){
    int i=0;
    while (i<tailleGrille){
        if (grille[i]=='.'){
            nvGrille[i]=0;
        }
        if (grille[i]=='#'){
            nvGrille[i]=1;
        }
        if (grille[i]=='F'){
            nvGrille[i]=4;
        }
        if (grille[i]=='S'){
            nvGrille[i]=2;
        }
        if (grille[i]=='E'){
            nvGrille[i]=3;
        }
        i+=1;
    }
}


void afficherGrille(int *grille,int tailleGrille,int colonnes){
    int i=0;
    while (i<tailleGrille){
        if (i%colonnes==0){
            printf("\n");
        }
        printf("%i ",grille[i]);
        i+=1;
        }
        
}











