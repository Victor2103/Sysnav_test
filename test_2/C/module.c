#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define TAILLE_TABLEAU 1000


/*Fichier qui transforme le fichier json en quatre tableaux, l'un qui est la longitude de tous les points, 
l'un la confiance de tous les points, l'un la latitude de tous les points et le dernier l'ID (ou le nom) de tous les points.
@param1: fichierAtraiter= fichier json à convertir
@param2: longitude= tableau de décimaux avec la longitude de chaque point
@param3: latitude= tableau de décimaux avec la latitude de chaque point
@param4: id= tableau d'entiers avec l'ID de chaque point
@param5: confiance= tableau de décimaux avec la confiance de chaque point */
void traitementData(FILE* fichierAtraiter,float* longitude,float* latitude,int* id,float* confiance){
    char traj[TAILLE_TABLEAU]="";
    int i=0;
    
    if (fichierAtraiter !=NULL){
        while (fgets(traj,1000,fichierAtraiter)!= NULL){
            char* conf=strstr(traj,"confiance");
            char* nom=strstr(traj,"id");
            char* longi=strstr(traj,"lng");
            char* lat=strstr(traj,"lat");
            if (conf!=NULL){
                char *test = malloc(TAILLE_TABLEAU*sizeof(char));
                test=strncpy(test,conf+11,9);
                confiance[i]=atof(test);
                free(test);
            }
            if (nom!=NULL){
                int j=4;
                int k=0;
                while (nom[j]!=','){
                    j=j+1;
                    k=k+1;
                }
                char *test = malloc(TAILLE_TABLEAU*sizeof(char));
                test=strncpy(test,nom+4,k);
                id[i]=atoi(test);
                free(test);
            }
            if (longi!=NULL){
                char *test=malloc(TAILLE_TABLEAU*sizeof(char));
                test=strncpy(test,longi+5,8);
                longitude[i]=atof(test);
                free(test);
            }
            if (lat!=NULL){
                char *test=malloc(TAILLE_TABLEAU*sizeof(char));
                test=strncpy(test,lat+5,8);
                latitude[i]=atof(test);
                free(test);
                i=i+1;
            }

        }
    }
}



/*Renvoie la taille du tableau placé en paramètre
@param1 : tableau= tableau dont on souhaite la taille */
int tailleFichier(float *tableau){
    int i=0;
    while(tableau[i]!=0.0){
        i=i+1;
    }
    return(i);
}


/*Calcul la moyenne de la confiance des points
@param1 : confiance= tableau de la confiance de tous les points
@param2: n=entier qui est la taille du tableau de la confiance de tous les points. */
float moyenneConfiance(float* confiance,int n){
    int i=0;
    float moy=0;
    while (i<n){
        moy=moy+confiance[i];
        i=i+1;
    }
    return(moy/n);
}



/* Renvoie le nombre de points que nous allons supprimer car leur confiance est trop faible 
@param1: confiance= tableau de la confiance de tous les points
@param2: moyenne= La moyenne de la confiance de tous les points
@param3: taille=entier qui est la taille du tableau de la confiance de tous les points. */
int tailleSupressionElements(float *confiance,float moyenne,int taille){
    int i=0;
    int j=0;
    while (i<taille){
        if (confiance[i]<moyenne){
            j=j+1;
        }
        i=i+1;
    }
    return(j);
}

/*Créer le tableau avec le position des points pour laquelle la confiance est trop faible
@param1: tab= tableau des positions pour laquelle la confiance est trop faible
@param2: confiance= tableau de la confiance de tous les points
@param3: taille=entier qui est la taille du tableau de la confiance de tous les points. */
void creationIndexSuppression(int *tab,float *confiance,float moyenne,int taille){
    int i=0;
    while (i<taille){
        if (confiance[i]<moyenne){
            tab[i]=i;
        }
        i=i+1;
    }
}


/*fonction qui ajoute un point dans le fichier KML 
@param1: fichierARemplir= pointeur sur le fichier kml dans lequel on va écrire
@param2: numID= l'ID du point ainsi que du placemark (qui sera numID+1)
@param3: nom=L'ID du point qui est aussi son nom
@param4: longitude=la longitude du point
@param5: latitude= la latitude du point */
void ajoutPoints(FILE* fichierARemplir,int numID,int nom,float longitude,float latitude){
    char charID[20]="";
    sprintf(charID,"%i",numID+1);
    char str[1000]="<Placemark id=\"";
    strcat(str,charID);
    strcat(str,"\">\n");
    char charNom[20]="";
    sprintf(charNom,"%i",nom);
    strcat(str,"<name>");
    strcat(str,charNom);
    strcat(str,"</name>\n");
    char iDPoint[20]="";
    sprintf(iDPoint,"%i",numID);
    strcat(str,"<Point id=\"");
    strcat(str,iDPoint);
    strcat(str,"\">\n");
    strcat(str,"<coordinates>");
    char charLongitude[20]="";
    sprintf(charLongitude,"%f,%f,",longitude,latitude);
    strcat(str,charLongitude);
    strcat(str,"0.0</coordinates>\n</Point>\n</Placemark>\n");
    fprintf(fichierARemplir,str);
}



/*Fonction qui ajoute tous les points selectionnés par rapport à leur confiance assez élevé dans le fichier KML
@param1: fichierARemplir= fichier dans lequel on ajoute tous les points
@param2: nom=tableau d'entiers avec l'ID de chaque point selectionnés
@param3: longitude= tableau de décimaux avec la longitude de chaque point selectionnés
@param4: latitude= tableau de décimaux avec la latitude de chaque point selectionés
@param5: confiance= tableau de décimaux avec la confiance de chaque point selectionnés
@param6: supression= tableau des indices ou les points ne sont pas selectionnés
@param7: taille=taille correspondant au nombre de points total présents dans le fichier
@param8: moy=la moyenne de la confiance des points */
void remplirFichierKml(FILE *fichierARemplir,int *nom,float *longitude,float *latitude,float *confiance,int *suppression,int taille,float moy){
    int i=0;
    int j=0;
    int iD=2;
    while (i<taille){
        if (i!=suppression[j]){
            if (confiance[i]>moy){
                ajoutPoints(fichierARemplir,iD,nom[i],longitude[i],latitude[i]);
                iD=iD+2;
            }
        }
        else {
            j=j+1;
        }
        i=i+1;
    }
}

/*Permet de donner un nom au fichier kml à partir du nom du fichier json
@param1: nomjson=le nom du fichier json
@param2: nomKml=le nom du fichier kml (au début vide lorque l'on lance la fonction)
@param3: taille= taille du nom du fichier json */
void nomFichierKml(char *nomjson,char *nomKml,int taille){
    int i=0;
    while (i<taille){
        if (nomjson[i]=='.'){
            strncpy(nomKml,nomjson,i);
        }
        i=i+1;
    }
    sprintf(nomKml,"%s%s",nomKml,".kml");
}


