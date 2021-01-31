# Bastian : Permet de compiler tout les modules et éxécuter le main, Le clean permet de supprimer les fichiers objets et l'executable
O = ./Objet/

Objet = $(O)lien.o $(O)liens.o $(O)descripteurAudio.o $(O)audio.o $(O)descripteurTexte.o $(O)texte.o $(O)descripteurImage.o $(O)image.o $(O)main.o $(O)fonction.o $(O)chargement.o $(O)indexation.o

# Fonction principale permettant de compiler le programme et l'exécuter
run: fonction.o chargement.o liens.o audio.o texte.o image.o indexation.o
	gcc -o $(O)main.o -c main.c 
	gcc -o main.out $(Objet)
	./main.out

#Fonctions utilisées par le Main seulement
fonction.o: src/FonctionMain/fonction.c src/FonctionMain/fonction.h
	gcc -o $(O)fonction.o -c -Wall src/FonctionMain/fonction.c

#Fonction pour charger les fichiers config
chargement.o: src/chargement/chargement.c src/chargement/chargement.h
	gcc -o $(O)chargement.o -c -Wall src/chargement/chargement.c

# ====== Fichiers texte ======
texte.o: descripteurTexte.o src/texte/texte.c  src/texte/texte.h
	gcc -o $(O)texte.o -c -Wall src/texte/texte.c

descripteurTexte.o: src/texte/Descripteur_Texte/descripteurTexte.c src/texte/Descripteur_Texte/descripteurTexte.h
	gcc -o $(O)descripteurTexte.o -c -Wall src/texte/Descripteur_Texte/descripteurTexte.c
# ============================

# ------ Fichiers image ------
image.o: descripteurImage.o src/image/image.c  src/image/image.h
	gcc -o $(O)image.o -c -Wall src/image/image.c

descripteurImage.o: src/image/Descripteur_Image/descripteurImage.c src/image/Descripteur_Image/descripteurImage.h
	gcc -o $(O)descripteurImage.o -c -Wall src/image/Descripteur_Image/descripteurImage.c
# ----------------------------

# ~~~~~~ Fichiers Audio ~~~~~~
audio.o: descripteurAudio.o src/audio/audio.c  src/audio/audio.h
	gcc -o $(O)audio.o -c -Wall src/audio/audio.c

descripteurAudio.o: src/audio/Descripteur_Audio/descripteurAudio.c src/audio/Descripteur_Audio/descripteurAudio.h
	gcc -o $(O)descripteurAudio.o -c -Wall src/audio/Descripteur_Audio/descripteurAudio.c
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# Liens entre descripteur et nom de fichier 
liens.o: lien.o src/Lien/liens.c src/Lien/liens.h
	gcc -o $(O)liens.o -c -Wall src/Lien/liens.c

lien.o: src/Lien/lien/lien.c src/Lien/lien/lien.h
	gcc -o $(O)lien.o -c -Wall src/Lien/lien/lien.c 

# Indexation.c qui sert pour l'indexation et la recherche de fichiers
indexation.o: src/Indexation/indexation.c src/Indexation/indexation.h
	gcc -o $(O)indexation.o -c -Wall src/Indexation/indexation.c

clean:
	rm $(O)*.o main.exe