// Bastian : Fonction permettant la gestion d'une pile de descripteur texte
#ifndef __F_Texte_H__
#define __F_Texte_H__

#include "./Descripteur_Texte/descripteurTexte.h"
#include "../Lien/liens.h"

//structure contenant le descripteur et pouvant être empilée
typedef struct s_CelTexte{ 
	DescripteurTexte descripteur;
	struct s_CelTexte* suivant;
}CelluleTexte;

//Pile contenant les descripteurs texte
typedef struct s_pileDescripteurTexte{
	int taille;
	CelluleTexte* tete;
}PileDescripteurTexte;


// initialise une pile vide
PileDescripteurTexte initPileDescripteurTexte();
// empile un descripteur dans la pile
PileDescripteurTexte empileDescripteurTexte(PileDescripteurTexte,DescripteurTexte);
//depile le premier descripteur de la pile
PileDescripteurTexte depileDescripteurTexte(PileDescripteurTexte);

// récupère le descripteur à la position indexe dans la pile 
DescripteurTexte* getDescripteurTexte(PileDescripteurTexte,int indexe);
// récupère le descripteur possédant l'id passé en parramètre 
DescripteurTexte* getDescripteurTexteViaId(PileDescripteurTexte,int id);
// récupère le descripteur possédant le même nom que celui passé en parramètre
DescripteurTexte* getDescripteurTexteViaNom(PileDescripteurTexte,char nom[50]);
// affiche une pile de descripteur ( surtout utilisé pendant les tests)
void affichePileDescripteurTexte(PileDescripteurTexte);
// libère l'espace mémoire utilisé par la pile ... enfin je crois 
void freePileDescripteurTexte(PileDescripteurTexte* p);

// s'occupe de créer le descripteur du fichier passé en parramètre, de l'empiler sur la pile de descripteur et de créer son lien qui sera lui aussi empilé sur la pile de liens
int toutDescripteurTexte(char* nomDuFichier,PileDescripteurTexte* p,PileLien* l,int nmbMots,int ID);

/* Sauvegarde la pile de descripteur et la pile de liens dans les fichiers :
 - base_descripteur_texte
 - liste_base_texte */
int SauvegardePileDescripteurTexte(PileDescripteurTexte p,PileLien l);
/* Charge la pile de descripteur depuis le fichier de sauvegarde */
PileDescripteurTexte chargePileDescripteurTexte(int*id);



#endif