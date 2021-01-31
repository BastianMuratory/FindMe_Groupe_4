# Bastian : Permet de compiler le module DescripteurAudio affin de réaliser des tests unitaires. (Les tests ne fonctionneront probablement plus car les chemins utilisées dans les fonctions sont définis pour fonctionner avec le main ex "./sauvegarde/Base_descripteur_Audio" au lieu de  "../../../sauvegarde/Base_descripteur_Audio")

# compile et lance le fichier de test
run: clean descripteurAudio.o tst_descripteurAudio.o
	gcc -o test descripteurAudio.o tst_descripteurAudio.o
	./test

# compile le fichier de test
tst_descripteurAudio.o: tst_descripteurAudio.c
	gcc -c tst_descripteurAudio.c

# compile le fichier contenant les fonctions liées aux descripteurs audios
descripteurAudio.o: descripteurAudio.c descripteurAudio.h
	gcc -c descripteurAudio.c

clean:
	rm -rf *.o test


test2: