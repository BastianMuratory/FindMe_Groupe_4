// Bastian : Fichier contenant les fonctions utilisées dans le main pour l'affichage et autre
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "fonction.h"

// permet de vider le buffer après une saisie
void clear (void){    
  while ( getchar() != '\n' );
}

// permet de changer la couleur du terminal
void color(char* couleur){
	if(strcmp(couleur,"noir")==0){
		printf("\x1b[30m");
	}else if(strcmp(couleur,"rouge")==0){
		printf("\x1b[31m");
	}else if(strcmp(couleur,"vert")==0){
		printf("\x1b[32m");
	}else if(strcmp(couleur,"jaune")==0){
		printf("\x1b[33m");
	}else if(strcmp(couleur,"bleu")==0){
		printf("\x1b[34m");
	}else if(strcmp(couleur,"magenta")==0){
		printf("\x1b[35m");
	}else if(strcmp(couleur,"cyan")==0){
		printf("\x1b[36m");
	}else if(strcmp(couleur,"blanc")==0){
		printf("\x1b[37m");
	}else if(strcmp(couleur,"reset")==0){
		printf("\x1b[0m");
	}
}

// gère la connection au mode administrateur
void connection(bool* admin){ 
	char s[TAILLE_MAX+1];
	printf("Entrez le mdp 'Admin' pour vous connecter : ");
	scanf("%s",s);
	clear();
	if(strcmp( s, "Admin" ) == 0){
		printf("Vous avez maintenant accés aux fonctionnalitées Admin !\n");
		*admin = true;
	}else{
		color("rouge");
		printf("==============================\n");
		printf("||     Le MDP est erroné    ||\n");
		printf("|| Retour au menu principal ||\n");
		printf("==============================\n");
		color("reset");
	}
}

/* affichage du menu utilisateur et admin si possible
admin : correspond à un administrateur connecté ou un utilisateur
x : variable du choix de l'utilisateur
vT,vI,vA : variable contenant le paramètre d'indexation Texte Image et Audio courant
indT,indI,indA : booleen pour savoir si une indexation a été effectuée pour permettre une recherche après un changement de paramètre
der_audio,der_image,der_texte : contient la valeur de la dernière indexation du type de fichier correspondant
*/
void affichage(bool admin,int *x,int vT,int vI,int vA,bool indT,bool indI,bool indA,int der_texte,int der_image,int der_audio){ // affiche le menu 
	*x = -1;
	color("vert");
	printf("\n===== FindMe =======\n");
	puts("[0] Quitter");
	puts("[1] Se connecter en admin");

	if(indT){
		puts("[2] Rechercher un mot");
		puts("[3] Rechercher un texte");
	}else{
		color("jaune");
		puts("[2] Indisponible, relancez l'indextaion des textes");
		puts("[3] Indisponible, relancez l'indextaion des textes");
		color("vert");
	}

	if(indI){
		puts("[4] Rechercher une image");
	}else{
		color("jaune");
		puts("[4] Indisponible, relancez l'indextaion des images");
		color("vert");
	}

	if(indA){
		puts("[5] Rechercher un fichier audio");
	}else{
		color("jaune");
		puts("[5] Indisponible, relancez l'indextaion des fichiers audio");
		color("vert");
	}

	if(admin){
		color("cyan");
		puts("--------------------");
		puts("[6] Changer les paramètres d'indexation Texte ");
		color("blanc");
		printf("(Paramètre courant : %d, dernière indexation : %d)\n",vT,der_texte);
		color("cyan");
		puts("[7] Changer les paramètres d'indexation image ");
		color("blanc");
		printf("(Paramètre courant : %d, dernière indexation : %d)\n",vI,der_image);
		color("cyan");
		puts("[8] Changer les paramètres d'indexation Audio ");
		color("blanc");
		printf("(Paramètre courant : %d, dernière indexation : %d)\n",vA,der_audio);
		color("cyan");
		puts("[9] Lancer l'indexation des Textes");
		puts("[10] Lancer l'indexation des Images");
		puts("[11] Lancer l'indexation des Sons");
		puts("[12] Quitter le mode administrateur");
		puts("--------------------");
	}
	puts("====================\n");
	color("reset");
	printf("Action à effectuer : ");
  scanf("%d",x);
	// 12 est la derniere et 5 est la derniere avant les commandes admin
  while( (*x<0) || (*x>12) || ( *x>5 && !admin) ) {
		clear();
		color("rouge");
		puts("=======================================");
		puts("||      La saisie est incorrecte     ||");
		puts("|| Merci de choisir un numéro valide ||");
		puts("=======================================");
		color("reset");
		
		printf("Action à effectuer : ");
		scanf("%d",x);
  }
	
}

// affiche le logo du logiciel 
void logo(){
	printf("\x1b[34m _____   _   __   _   _____   \x1b[31m    ___  ___   _____  \n");
	printf("\x1b[34m|  ___| | | |  \\ | | |  _  \\\x1b[31m     /   |/   | | ____| \n");
	printf("\x1b[34m| |__   | | |   \\| | | | | |\x1b[31m    / /|   /| | | |__   \n");
	printf("\x1b[34m|  __|  | | | |\\   | | | | | \x1b[31m  / / |__/ | | |  __|  \n");
	printf("\x1b[34m| |     | | | | \\  | | |_| | \x1b[31m / /       | | | |___  \n");
	printf("\x1b[34m|_|     |_| |_|  \\_| |_____/\x1b[31m /_/        |_| |_____| \n");
	color("reset");
}

// affiche un message de remerciement
void merci(){
	color("jaune");
	puts("\t\tÀ la prochaine !");
	printf("     ___  ___   _____   _____    _____   _       _ \n");
	printf("    /   |/   | | ____| |  _  \\  /  ___| | |     | |\n");
	printf("   / /|   /| | | |__   | |_| |  | |     | |     | |\n");
	printf("  / / |__/ | | |  __|  |  _  /  | |     | |     |_|\n");
	printf(" / /       | | | |___  | | \\ \\  | |___  | |      _ \n");
	printf("/_/        |_| |_____| |_|  \\_\\ \\_____| |_|     |_|\n");
	color("reset");
}

// affiche un message d'erreur d'indexation 
void erreur_relancer_indexation(){
	color("rouge");
	puts("===============================================================");
	puts("||           Le parammetre d'indexation à été changé         ||");
	puts("|| Veuillez relancer l'indexation du type de fichier choisit ||");
	puts("===============================================================");
	color("reset");
}

// affiche une erreur à propos du choix effectué par l'utilisateur
void message_erreur(){
	color("rouge");
	puts("=======================================");
	puts("||      La saisie est incorrecte     ||");
	puts("||     retour au menu principale     ||");
	puts("=======================================");
	color("reset");
}

// fonction pour changer le paramètre d'indexation des textes
void changer_param_text(int* param,bool* index){
	int x = 0;
	puts("Le parammètre d'indexation de texte correspond au nombre de mots retenus dans un descripteur de texte.");
	printf("Veuillez entrer un nombre entre %d et %d : ",MIN_INDEXATION_TEXTE,MAX_INDEXATION_TEXTE);
	scanf("%d",&x);
	if(x<MIN_INDEXATION_TEXTE || x>MAX_INDEXATION_TEXTE){
		message_erreur();
	}else{
		*param = x;
		*index = false;
	}
}

// fonction pour changer le paramètre d'indexation des images
void changer_param_image(int* param,bool* index){
	int x = 0;
	puts("Le parammètre d'indexation d'image correspond au nombre de bits pris en compte lors de la quantification."); 
	printf("Veuillez entrer un nombre entre %d et %d : ",MIN_INDEXATION_IMAGE,MAX_INDEXATION_IMAGE);
	scanf("%d",&x);
	if(x<MIN_INDEXATION_IMAGE || x>MAX_INDEXATION_IMAGE){
		message_erreur();
	}else{
		*param = x;
		*index = false;
	}
}

// fonction pour changer le paramètre d'indexation des fichiers audios
void changer_param_audio(int* param,bool* index){
	int x = 0;
	puts("Le parammètre d'indexation de fichier audio correspond au nombre d'intervales de l'echatillonnage.");
	printf("Veuillez entrer un nombre entre %d et %d : ",MIN_INDEXATION_AUDIO,MAX_INDEXATION_AUDIO);
	scanf("%d",&x);
	if(x<MIN_INDEXATION_AUDIO || x>MAX_INDEXATION_AUDIO){
		message_erreur();
	}else{
		*param = x;
		*index = false;
	}
}




