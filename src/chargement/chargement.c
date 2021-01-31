// Bastian : Fonction de chargement et sauvegarde des paramètres d'indexation 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "./chargement.h"


// chargement des paramètres d'indexation (Valeures courantes choisies et booleens pour savoir si on peut effectuer une recherche) ces données sont sauvegardées dans le fichier config
int chargement_config(int* paramTexte,int* paramImage,int* paramAudio,
bool* chercheTexte,bool* chercheImage,bool* chercheAudio){
	FILE* fichier = NULL;
	fichier = fopen("./sauvegarde/configuration.config","r");
	int param = 0,indexation = 0;
	if(fichier!=NULL){
		//puts("chargement réussi\n");
		//fichiers textes
		fscanf(fichier,"Nombre de mots dans un descripteur texte :%d,%d\n",&param,&indexation);
		* paramTexte = param;
		if(indexation == 0){
			* chercheTexte = true;
		}else{
			* chercheTexte = false;
		}
		// fichiers Images
		fscanf(fichier,"Bit de poid fort dans une image :%d,%d\n",&param,&indexation);
		* paramImage = param;
		if(indexation == 0){
			* chercheImage = true;
		}else{
			* chercheImage = false;
		}
		// fichiers audio
		fscanf(fichier,"Nombre de fenêtres d'écoute dans un descripteur audio :%d,%d\n",&param,&indexation);
		* paramAudio = param;
		if(indexation == 0){
			* chercheAudio = true;
		}else{
			* chercheAudio = false;
		}
		fclose(fichier);
	}else{
		puts("\nattention problème, paramètres défauts chargés\n");
		* paramTexte = 10;
		* paramImage = 10;
		* paramAudio = 10;
		* chercheTexte = true;
		* chercheImage = true;
		* chercheAudio = true;
	}
	return 0;
}

// sauvegarde des paramètres de la fonction précédente
void sauvegarde_config(int paramTexte,int paramImage,int paramAudio,
bool chercheTexte,bool chercheImage,bool chercheAudio){
	FILE* fichier = NULL;
	//fichiers textes
	fichier = fopen("./sauvegarde/configuration.config","w");
	fprintf(fichier,"Nombre de mots dans un descripteur texte :%d,",paramTexte);
	if(chercheTexte){
		fprintf(fichier,"0\n");
	}else{
		fprintf(fichier,"1\n");
	}
	//fichiers images
	fprintf(fichier,"Bit de poid fort dans une image :%d,",paramImage);
	if(chercheImage){
		fprintf(fichier,"0\n");
	}else{
		fprintf(fichier,"1\n");
	}

	fprintf(fichier,"Nombre de fenêtres d'écoute dans un descripteur audio :%d,",paramAudio);
	if(chercheAudio){
		fprintf(fichier,"0\n");
	}else{
		fprintf(fichier,"1\n");
	}
	fclose(fichier);
	//puts("sauvegarde terminée");
}



// chargement des paramètres de dernière sauvegarde et dernière indexation
void chargement_derniere_indexation(int* texte,int* image,int* audio,int* s_texte,int* s_image,int* s_audio){
	FILE* fichier = NULL;
	//fichiers textes
	fichier = fopen("./sauvegarde/save.save","r");
	if(fichier == NULL){
		puts("ERREUR chargement dernières valeures");
	}else{
		fscanf(fichier,"texte:%d,%d\n",texte,s_texte);
		fscanf(fichier,"image:%d,%d\n",image,s_image);
		fscanf(fichier,"audio:%d,%d\n",audio,s_audio);
	}
	fclose(fichier);
}

// sauvegarde des paramètres de la fonction précédente
void sauvegarde_derniere_indexation(int texte,int image,int audio,int s_texte,int s_image,int s_audio){
	FILE* fichier = NULL;
	fichier = fopen("./sauvegarde/save.save","w");
	if(fichier != NULL){
		fprintf(fichier,"texte:%d,%d\n",texte,s_texte);
		fprintf(fichier,"image:%d,%d\n",image,s_image);
		fprintf(fichier,"audio:%d,%d\n",audio,s_audio);
		fclose(fichier);
	}
}