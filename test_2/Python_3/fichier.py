import simplekml
import module_1
import json


#Ceci permet de récupérer le fichier que l'on souhaite transformer en .kml
#Il faut rentrer le nom du fichier .json
#Le fichier sera récupérer sous la forme d'une liste de dictionnaires qui est dans la variable "data"
while True :
    try:
        fichierAtraiter=input("Veuillez entrer le nom du fichier : ")
        #Le répertoire ci dessous est à modifier en fonction de là ou se trouve votre document. 
        with open('/home/eisti/Documents/test_Sysnav/test_2/Python_3/trajectories/'+fichierAtraiter) as mon_fichier:
            data = json.load(mon_fichier)
        break
    except IOError:
        print("Merci d'entrer un fichier valide")



#Création du fichier KML
monkml = simplekml.Kml()
 
#reajustement de la variable data, on prend uniquement les dictionnaires avec une confiance supérieure à la moyenne des confiances.
data=module_1.selectionsPoints(data,module_1.moyenneConfiance(data))

#AJout des points dans le fichier kml. Chaque point est une ligne du dictionnaire. 
monkml=module_1.creation_point(data,monkml)

#creation du nom du fichier kml
nom_kml=module_1.creationNom(fichierAtraiter)

# création du fichier kml
monkml.save(nom_kml+".kml")
