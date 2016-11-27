#!/bin/sh

# Nettoyage de la console
clear

# Nettoyage du dossier
make clean

# Déclaration des variables
declare -i nbThread=0
declare -i nbThreadMax=5
declare -i nbTraitement=5

echo "********************************************"
echo "* Programmation temps réel                 *"
echo "* Banc d'essai : Fractales de Julia        *"
echo "* Binôme A. BENNANI & S. VANDYCKE          *"
echo "******************************************** \n"

echo "* Nombre de traitement par test : $nbTraitement"
echo "* Nombre de thread(s) maximum(s) testé(s) : $nbThreadMax \n"


while [ $nbThread -le $nbThreadMax ]
do
	if [ $nbThread -eq 0 ]
	then
  		# Compilation du programme 
		# Test sans thread
		echo "Calcul de la fractale sans thread"
		g++ window.cpp -o FractalesJulia.out -std=c++11 -lopencv_highgui -lopencv_imgproc -lopencv_core -I/usr/local/include -L/usr/local/lib
  	else
   		# Compilation du programme 
		# Test avec N thread(s)
		echo "Calcul de la fractale avec $nbThread thread(s)"
		g++ window.cpp -o FractalesJulia.out -std=c++11 -lopencv_highgui -lopencv_imgproc -lopencv_core -DWITH_THREAD -DNB_THREAD=$nbThread -I/usr/local/include -L/usr/local/lib
	fi	
	    
    # Exécution du programme
    ./FractalesJulia.out $nbTraitement Test/resultatsTest.txt
    
    # Incrémentation de 1 le nbThread
    nbThread=nbThread+1
done