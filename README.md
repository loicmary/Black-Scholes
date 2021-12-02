Le fichier qui utilise l'ensemble des classes que nous avons crée pour construire le vecteur C(0,.) est main.cpp
Nous avons donc crée un Makefile pour simplifier la compilation.
Voici donc la procédure :
    1) il faut taper make à la racine du dossier
    2) aller dans le sous dossier bin et taper ./main

L'arboresence du projet est la suivante:
bin : -> les executables
build : -> les .o
include : -> les .h
src : -> les .cpp
