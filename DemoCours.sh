#!/bin/sh

# file DemoCours.sh
#
# \brief Fractales de Julia
#
# \author Abdellatif BENNANI & Steve VANDYCKE
# \date December 05 2016

# Nettoyage de la console
clear

# Déclaration des variables
declare -i nbThread=13
declare -i nbTraitement=500
fichierResultat="Test/demoCours.txt"

# Vérificatie si le fichier de sauvegarde existe
if [ -e "$fichierResultat" ]
then
    # Supprime le fichier existant
    rm  $fichierResultat
fi

echo "********************************************"
echo "* Programmation temps réel                 *"
echo "* Démo : Fractales de Julia                *"
echo "* Binôme A. BENNANI & S. VANDYCKE          *"
echo "******************************************** \n"

echo "* Le résultat sera sauvegardé : $fichierResultat\n"

echo "* Nombre d'itérations : $nbTraitement"

# Compilation pour démo
g++ window.cpp -o FractalesJulia.out -std=c++11 -lopencv_highgui -lopencv_imgproc -lopencv_core -DWITH_THREAD -DNB_THREAD=$nbThread -D_H=400 -D_W=400 -I/usr/local/include -L/usr/local/lib

# Exécution du programme
./FractalesJulia.out $nbTraitement $fichierResultat

echo "\n********************************************"
echo "* Traitement terminé                       *"
echo "********************************************"








