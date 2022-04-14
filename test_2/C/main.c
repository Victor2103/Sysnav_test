#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "module.c"

#define TAILLE_MAX 1000 


int main(int argc, char *argv[])
{
    if (argc<=1){
        printf("Merci de rentrer un fichier json après l'execution \n");
    }
    else {
        char nomFile[60]="";
        /*Repertoire ci dessous à changer en fonction de là ou se trouve les fichier json*/
        sprintf(nomFile,"/home/eisti/Documents/test_Sysnav/test_2/C/trajectories/%s",argv[1]);
        FILE* fichierjson=fopen(nomFile,"r");
        char nomKML[strlen(argv[1])];
        nomFichierKml(argv[1],nomKML,strlen(argv[1]));
        FILE* fichierkml=fopen(nomKML,"w");

        /*On test ci la conversion s'est bien déroulé */
        if ((fichierkml!=NULL)&&(fichierjson!=NULL)){
            float* laLongitude=malloc(TAILLE_TABLEAU*sizeof(float));
            float* laLatitude=malloc(TAILLE_TABLEAU*sizeof(float));
            int* leNom=malloc(TAILLE_TABLEAU*sizeof(float));
            float* laConfiance=malloc(TAILLE_TABLEAU*sizeof(float));
            /*On récupère tout les éléments nécessaires à la conversion avec la fonction traitementData*/
            traitementData(fichierjson,laLongitude,laLatitude,leNom,laConfiance);
            int tailleDonnees=tailleFichier(laConfiance);
            float moyenne=moyenneConfiance(laConfiance,tailleDonnees);
            int tailleConfianceTropPetite=tailleSupressionElements(laConfiance,moyenne,tailleDonnees);
            int *aSupprimer=malloc(tailleConfianceTropPetite*sizeof(int));
            creationIndexSuppression(aSupprimer,laConfiance,moyenne,tailleConfianceTropPetite);
            /*On commence à écrire dans le fichier kml puis on ajoute les points selectionnées */
            fprintf(fichierkml,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
            fprintf(fichierkml,"<kml xmlns=\"http://www.opengis.net/kml/2.2\" xmlns:gx=\"http://www.google.com/kml/ext/2.2\">\n");
            fprintf(fichierkml,"<Document id=\"1\">\n");
            remplirFichierKml(fichierkml,leNom,laLongitude,laLatitude,laConfiance,aSupprimer,tailleDonnees,moyenne);
            fprintf(fichierkml,"</Document>\n</kml>");

            /*On libère la mémoire alloué aux différents tableaux)*/
            free(laLongitude);
            free(laLatitude);
            free(leNom);
            free(laConfiance);
        }
    }

    return 0;
}