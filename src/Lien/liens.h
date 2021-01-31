// Bastian : fonctions permettant d'utiliser un lien dans une pile de liens
// Thomas : Fonction d'affichage de la barre de chargement  
#ifndef __F_liens_H__
#define __F_liens_H__

#include "./lien/lien.h"


#define TAILLE_PROGRESS_BAR 50 // taille de la barre de chargement 

/*============================================*/
typedef struct s_CelLien{ // la cellule qui va être empilée
	Lien descripteur; // le lien qui lie id et descripteur
	struct s_CelLien* suivant; // suivant dans la pile 
}CelluleLien;

typedef struct s_pileLien{
	int taille; // taille de la pile (permet des parcours plus simples)
	CelluleLien* tete; // première cellule de la pile
}PileLien;
/*============================================*/


//affiche la barre de progression selon le pourcentage
void printProgressBar(int pourcentage);

// crée une pile de lien vide
PileLien initPileLien();
// empile un lien sur la pile 
PileLien empileLien(PileLien,Lien);
// depile le premier lien de la pile 
PileLien depileLien(PileLien);

// récupère le lien à la position x dans la pile
Lien* getLien(PileLien,int x);
// récupère l'adresse du lien qui possède l'id id dans la pile
Lien* getLienViaId(PileLien,int);
// récupère l'adresse du lien qui possède le nom passé en parramètre
Lien* getLienViaNom(PileLien,char nom[50]);
// affiche une pile de liens 
void affichePileLien(PileLien);

//retourne l'indice si nomFichier est un fichier déjà présent dans la pile de liens sinon -1
int dejaVu(char* nomFichier,PileLien p);

// sauvegarde une pile de liens dans un fichier passé en parramètre
void sauvegardePileLien(PileLien p,char* nomFichier);
// charge une pile de liens depuis un fichier 
PileLien chargePileLien(char* nomFichier);

// libère l'espace mémoire de la pile de lien
void freePileLien(PileLien* p);

#endif
