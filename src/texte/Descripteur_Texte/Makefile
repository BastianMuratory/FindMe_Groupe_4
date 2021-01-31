# Bastian : Permet de compiler le module DescripteurTexte affin de réaliser des tests unitaires. (Les tests ne fonctionneront probablement plus car les chemins utilisées dans les fonctions sont définis pour fonctionner avec le main ex "./sauvegarde/Base_descripteur_Texte" au lieu de  "../../../sauvegarde/Base_descripteur_Texte")

# lancement du fichier de test apres recompilation
run: descripteurTexte.o tst_descripteurTexte.o
	gcc -o test descripteurTexte.o tst_descripteurTexte.o
	./test

# compilation du fichier de test
tst_descripteurTexte.o: tst_descripteurTexte.c
	gcc -c -Wall tst_descripteurTexte.c

# compilation des fonction relatives au descripteur
descripteurTexte.o: descripteurTexte.c descripteurTexte.h
	gcc -c -fstack-protector -Wall descripteurTexte.c

clean:
	rm -rf *.o test temp*
