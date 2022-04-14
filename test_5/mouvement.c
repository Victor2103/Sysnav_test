#include "mouvement.h"



int remplirVoisins(int *nvGrille,int position,int colonnes,int tailleGrille,int cpt,int reussite){
    if (position%colonnes!=0){
        if (nvGrille[position-1]==0){
            nvGrille[position-1]=cpt;
        }
        if (nvGrille[position-1]==3){
            reussite=0;
        }
    }
    if (position%colonnes!=colonnes-1){
        if (nvGrille[position+1]==0){
            nvGrille[position+1]=cpt;
        }
        if (nvGrille[position+1]==3){
            reussite=0;
        }
    }
    if (position>=colonnes){
        if (nvGrille[position-colonnes]==0){
            nvGrille[position-colonnes]=cpt;
        }
        if (nvGrille[position-colonnes]==3){
            reussite=0;
        }
    }
    if (position+colonnes<tailleGrille){
        if (nvGrille[position+colonnes]==0){
            nvGrille[position+colonnes]=cpt;
        }
        if (nvGrille[position+colonnes]==3){
            reussite=0;
        }
    }
    return(reussite);
}

/* Renvoie le nombre de voisins ayant pour numéro le chemin. */
int parcourirCpt(int *nvGrille,int cpt,int tailleNvGrille){
    int i=0;
    int tmp=0;
    while (i<tailleNvGrille){
        if (nvGrille[i]==cpt){
            tmp+=1;
        }
        i+=1;
    }
    return(tmp);
}


/*Creer un tableau avec la position de chaque compteur de voisin*/
void tableauPos(int *nvGrille,int cpt,int *tableauPosition,int tailleGrille){
    int i=0;
    int j=0;
    while (i<tailleGrille){
        if (nvGrille[i]==cpt){
            tableauPosition[j]=i;
            j=j+1;
        }
        i+=1;
    }
}

void parcoursFeu(int *nvGrille,int position,int colonnes,int tailleGrille){
    if (position%colonnes!=0){
        if (nvGrille[position-1]<=4){
            nvGrille[position-1]=4;
        }
    }
    if (position%colonnes!=colonnes-1){
        if (nvGrille[position+1]<=4){
            nvGrille[position+1]=4;
        }
    }
    if (position>=colonnes){
        if (nvGrille[position-colonnes]<=4){
            nvGrille[position-colonnes]=4;
        }
        
    }
    if (position+colonnes<tailleGrille){
        if (nvGrille[position+colonnes]<=4){
            nvGrille[position+colonnes]=4;
        }
    }
}




/*Verifie si le chemin existe et n'est pas brulée avec le feu avant */
int faireChemin(int *nvGrille,int position,int colonnes,int tailleGrille,int cpt,int feuDepart){
    int sortieAtteinte=1;
    int nbDeCpt=0;
    int nbDeCasesEnFeu=0;
    parcoursFeu(nvGrille,feuDepart,colonnes,tailleGrille);
    sortieAtteinte=remplirVoisins(nvGrille,position,colonnes,tailleGrille,cpt,sortieAtteinte);
    while (sortieAtteinte==1){
        nbDeCpt=parcourirCpt(nvGrille,cpt,tailleGrille);
        nbDeCasesEnFeu=compteurFeu(nvGrille,tailleGrille);
        if (nbDeCpt==0){
            sortieAtteinte=2;
        }
        else {
            int *positionDesCpt=malloc(nbDeCpt*sizeof(int));
            int *positionFeu=malloc(nbDeCasesEnFeu*sizeof(int));
            tableauPos(nvGrille,cpt,positionDesCpt,tailleGrille);
            recupPositionFeu(positionFeu,nvGrille,tailleGrille);
            int i=0;
            while (i<nbDeCasesEnFeu){
                parcoursFeu(nvGrille,positionFeu[i],colonnes,tailleGrille);
                i+=1;
            }
            cpt+=1;
            i=0;
            while (i<nbDeCpt){
                sortieAtteinte=remplirVoisins(nvGrille,positionDesCpt[i],colonnes,tailleGrille,cpt,sortieAtteinte);
                if (sortieAtteinte==0){
                    break;
                }
                i+=1;
            }
            free(positionDesCpt);
            free(positionFeu);
        }
    }
    return(sortieAtteinte);
}



/* Cette fonction est appelé uniquement s'il existe un chemin. Elle renvoie la sortie que l'on peut emprunter.
Il faut rentrer la grille en paramètre avec le feu. */
int RecupNumBonneSortie(int *nvGrille,int tailleGrille){
    int i=0;
    int aRetourner=0;
    while (i<tailleGrille){
        if (nvGrille[i]==3){
            aRetourner=i;
        }
        i+=1;
    }
    return(aRetourner);
}


int renvoiePosminimumVoisin(int *nvGrille,int tailleGrille,int position,int colonnes,int *min){
    int pos=0;
    if (position%colonnes!=0){
        if (((nvGrille[position-1]<*min) && (nvGrille[position-1]>4)) || (nvGrille[position-1]==2)){
            *min=nvGrille[position-1];
            pos=position-1;
        }
    }
    if (position%colonnes!=colonnes-1){
        if (((nvGrille[position+1]<*min) && (nvGrille[position+1]>4)) || (nvGrille[position+1]==2)){
            *min=nvGrille[position+1];
            pos=position+1;
        }
    }
    if (position>=colonnes){
        if (((nvGrille[position-colonnes]<*min) && (nvGrille[position-colonnes]>4)) || (nvGrille[position-colonnes]==2)){
            *min=nvGrille[position-colonnes];
            pos=position-colonnes;
        }
    }
    if (position+colonnes<tailleGrille){
        if (((nvGrille[position+colonnes]<*min) && (nvGrille[position+colonnes]>4)) || (nvGrille[position+colonnes]==2)){
            *min=nvGrille[position+colonnes];
            pos=position+colonnes;
        }
    }
    return(pos);
}



int retrouverCheminTaille(int *nvGrille,int position,int tailleGrille,int colonnes,int *min){
    int i=0;
    while (*min!=2){
        position=renvoiePosminimumVoisin(nvGrille,tailleGrille,position,colonnes,min);
        i=i+1;
    }
    return(i);
}

void retrouverChemin(int *nvGrille,int position,int tailleGrille,int colonnes,int *min,int *suite){
     int i=0;
     while (*min!=2){
        suite[i]=position;
        position=renvoiePosminimumVoisin(nvGrille,tailleGrille,position,colonnes,min);
        i+=1;
    }
}

void transformerPositionURDL(int position,int tailleSuite,int* suite,int colonnes,char *suiteURDL){
    int i=tailleSuite-1;
    int j=0;
    while (i>=0){
        if (position-1==suite[i]){
            suiteURDL[j]='L';
            position=position-1;
        }
        if (position+1==suite[i]){
            suiteURDL[j]='R';
            position+=1;
        }
        if (position-colonnes==suite[i]){
            suiteURDL[j]='U';
            position=position-colonnes;
        }
        if (position+colonnes==suite[i]){
            suiteURDL[j]='D';
            position=position+colonnes;
        }
        j+=1;
        i-=1;
    }
}




