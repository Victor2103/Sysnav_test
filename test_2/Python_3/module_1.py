#Ce module permet d'extraire toutes les données dans le fichier json. 

#Module permettant de créer facilement des fichiers kml en python. 
import simplekml



def moyenneConfiance(fichier_json):
    """Fonction qui renvoie la moyenne de la confiance de tous les points. 
    @fichier_json : le fichier json recuperer sous la forme d'une liste de dictionnaires (il est déjà traité)"""
    moy=0
    i=0
    while (i<len(fichier_json)):
        moy+=fichier_json[i]['confiance']
        i+=1
    return moy/len(fichier_json)
    
def selectionsPoints(fichier_json,moyenne):
    """Fonction qui enlève les points dont la confiance est inférieure à la moyenne.
    @fichier_json : le fichier json recuperer sous la forme d'une liste de dictionnaires (il est déjà traité)
    @moyenne : un décimal qui est la moyenne de la confiance de tous les points"""
    i=0
    while (i<len(fichier_json)):
        if (fichier_json[i]['confiance']<moyenne):
            del fichier_json[i]
        i+=1
    return(fichier_json)


"""Fonction qui permet de donner le nom du fichier kml retourner.
Elle prend en paramètre le nom du fichier et renvoie le nom de ce fichier mais sans le suffixe .json"""
def creationNom(nom):
    nom_retour=""
    for i in nom:
        if (i=='.'):
            break
        nom_retour+=i
    return(nom_retour)








def creation_point(fichier_json,fichier_kml):
    """Fonction qui ajoute tous les points de la trajectoire du fichier json dans le fichier kml
    @fichier_json: le fichier json recuperer sous la forme d'une liste de dictionnaire (il est déjà traité)
    @fichier_kml: le fichier kml que l'on va retourner après avoir ajouté les points. """
    i=0
    while (i<len(fichier_json)):
        fichier_kml.newpoint(name=fichier_json[i]['id'],coords=[(fichier_json[i]['lng'],fichier_json[i]['lat'])])
        i+=1
    return(fichier_kml)


