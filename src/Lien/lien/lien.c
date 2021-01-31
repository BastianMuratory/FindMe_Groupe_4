// Bastian : fonction permettant d'utiliser un Lien entre le nom d'un fichier et l'Id de son descripteur
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "lien.h"

/*
typedef struct s_Lien{
	int ID; // ID du descripteur
	char nomFichier[100]; // nom du fichier decrit
}Lien;
*/

// Creation du Lien
Lien creerLien(char* nomDuFichier,int ID){
	Lien l;
	strcpy(l.nomFichier,nomDuFichier);
	l.ID = ID;
	return l;
}

//getters
int getIdLien(Lien d){
	return d.ID;
}

char* getNomLien(Lien d){
	char* retour = malloc((TAILLE_MAX+1)*sizeof(char));
	strcat(retour,d.nomFichier);
	return retour;
}

//affectation
void affectLien(Lien* e,Lien* x){
	strcpy(x->nomFichier,e->nomFichier);
	x->ID = e->ID;
}

// affichage d'un lien
void afficheLien(Lien d){
	printf("Le texte %s est lié au descripteur %d\n",d.nomFichier,d.ID);
}

// sauvegarde d'un lien dans un fichier
int sauvegarderLien(FILE* fichier,Lien d){
	fprintf(fichier,"%d,%s\n",d.ID,d.nomFichier);
	return 0;
}

// chargement d'un lien dans un fichier
Lien chargerLien(FILE* fichier){
	Lien d;
	fscanf(fichier, "%d,%s\n",&d.ID,d.nomFichier);
	return d;
}