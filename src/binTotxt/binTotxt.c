// Bastian et Kosma : Programme permettant de traduire des fichiers binaires en fichiers textes utilisables par le logiciel
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define TAILLE 100


int main(){
	//system("clear");
	// récupération du nombre de fichiers à modifier et de leur nom
	system("ls ./data/TEST_SON | grep '.bin' > temp");
	system("wc -l temp > temp2");
	int max = 0;

	// récupération du nombre de fichiers à modifier dans max
	FILE* fichier = NULL;
	fichier = fopen("temp2","r");
	fscanf(fichier,"%d",&max);
	fclose(fichier);
	
	// pour chaques nom de fichier lancer les commandes pour changer l'encodage du fichier
	char fichierCourant[TAILLE+1];
	fichier = fopen("temp","r");
	char cheminVersBin[TAILLE+1];
	char cheminVersTxt[TAILLE+1];
	FILE* fichierBin = NULL;
	FILE* fichierResultat = NULL;

	for(int i = 0;i<max;i++){
		 
  	int nb_val_lues = TAILLE ;
  	int j;

		fscanf(fichier,"%s",fichierCourant);
		strcpy(cheminVersBin,"./data/TEST_SON/"); //jinglefi.bin
		strcpy(cheminVersTxt,"./data/TEST_SON/"); //jinglefi.txt
	

    strcat(cheminVersBin, fichierCourant);
  
    strncat(cheminVersTxt,fichierCourant,strlen(fichierCourant)-4);
    strcat(cheminVersTxt, ".txt");
    
		
		if( access( cheminVersTxt , F_OK ) == -1 ){
			fichierBin = fopen(cheminVersBin,"rb");
			fichierResultat = fopen(cheminVersTxt,"w");
			double buffer[TAILLE+1];

			printf("%s -> %s\n",cheminVersBin,cheminVersTxt); // verification des chemins
			puts("&");
			while ( nb_val_lues == TAILLE ) {
				nb_val_lues = fread( buffer, sizeof(double), TAILLE, fichierBin);
				for (j=0; j<nb_val_lues; j++) {
          fprintf(fichierResultat, "%le\n", buffer[j]);
				}
    	}
			fclose(fichierBin);
			fclose(fichierResultat);
		}
		
	}
	remove("temp");
  remove("temp2");
	return EXIT_SUCCESS;
}
