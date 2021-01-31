// Bastian : Fichier contenant un programme utilisé pour traduire tout les fichier XML en utilisant des caractères non encodés pour un traitement et une lecture plus simple
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(){
	char* init = "iso-8859-1"; // encodage de départ
	char* terminal  = "ascii//TRANSLIT"; // encodage d'arrivée
	char debut[100] = "iconv -f ";
	strcat(debut,init);
	strcat(debut," -t ");
	strcat(debut,terminal);
	strcat(debut," ../../data/Textes/");
	

	// récupération du nombre de fichiers à modifier et de leur nom
	system("ls ../../data/Textes | grep '.xml' > temp");
	system("wc -l temp > temp2");
	int max = 0;

	// récupération du nombre de fichiers à modifier dans max
	FILE* fichier = NULL;
	fichier = fopen("temp2","r");
	fscanf(fichier,"%d",&max);
	fclose(fichier);
	
	// pour chaques nom de fichier lancer les commandes pour changer l'encodage du fichier
	char fichierCourant[100];
	fichier = fopen("temp","r");
	for(int i = 0;i<max;i++){
		char commande1[200] = "";
		char commande2[150] = "cat temp > ../../data/Textes/";
		
		//commande 1
		strcat(commande1,debut);
		fscanf(fichier,"%s",fichierCourant);
		strcat(commande1,fichierCourant);
		strcat(commande1," > temp");

		//commande 2
		strcat(commande2,fichierCourant);

		// Execution
		// iconv -f iso-8859-1 -t ascii//TRANSLIT chemin/fichier.xml > temp 
		// temp > chemin/fichier.xml
		system(commande1);
		system(commande2);
	}
	return EXIT_SUCCESS;
}