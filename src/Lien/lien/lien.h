// Bastian : fonction permettant d'utiliser un Lien entre le nom d'un fichier et l'Id de son descripteur
#ifndef __fichier_h__
#define __fichier_h__

#define TAILLE_MAX 100

typedef struct s_Lien{
	int ID; // ID du descripteur
	char nomFichier[TAILLE_MAX+1]; // nom du fichier decrit
}Lien;

// Creation du descripteur
Lien creerLien(char* nomDuFichier,int ID);
//getters
int getIdLien(Lien d);
char* getNomLien(Lien d);
//affectation et affichage
void affectLien(Lien* e,Lien* x);
void afficheLien(Lien d);

#endif
