// Bastian : Fonction permettant la gestion d'une pile de descripteur audio
#ifndef __F_Audio_H__
#define __F_Audio_H__

#include "./Descripteur_Audio/descripteurAudio.h"
#include "../Lien/liens.h"

//structure contenant le descripteur et pouvant être empilée
typedef struct s_CelAudio{ 
	DescripteurAudio descripteur;
	struct s_CelAudio* suivant;
}CelluleAudio;

//Pile contenant les descripteurs audio
typedef struct s_pileDescripteurAudio{
	int taille;
	CelluleAudio* tete;
}PileDescripteurAudio;


// initialise une pile vide
PileDescripteurAudio initPileDescripteurAudio();
// empile un descripteur dans la pile
PileDescripteurAudio empileDescripteurAudio(PileDescripteurAudio,DescripteurAudio);
//depile le premier descripteur de la pile
PileDescripteurAudio depileDescripteurAudio(PileDescripteurAudio);

// récupère le descripteur à la position indexe dans la pile 
DescripteurAudio* getDescripteurAudio(PileDescripteurAudio,int indexe);
// récupère le descripteur possédant l'id passé en parramètre 
DescripteurAudio* getDescripteurAudioViaId(PileDescripteurAudio,int id);
// récupère le descripteur possédant le même nom que celui passé en parramètre
DescripteurAudio* getDescripteurAudioViaNom(PileDescripteurAudio,char nom[50]);
// affiche une pile de descripteur ( surtout utilisé pendant les tests)
void affichePileDescripteurAudio(PileDescripteurAudio);
// libère l'espace mémoire utilisé par la pile
void freePileDescripteurAudio(PileDescripteurAudio* p);

// s'occupe de créer le descripteur du fichier passé en parramètre, de l'empiler sur la pile de descripteur et de créer son lien qui sera lui aussi empilé sur la pile de liens
int toutDescripteurAudio(char* nomDuFichier,PileDescripteurAudio* p,PileLien* l,int nombreIntervalle,int ID);

/* Sauvegarde la pile de descripteur et la pile de liens dans les fichiers :
 - base_descripteur_audio
 - liste_base_audio */
int SauvegardePileDescripteurAudio(PileDescripteurAudio p,PileLien l);
/* Charge la pile de descripteur depuis le fichier de sauvegarde */
PileDescripteurAudio chargePileDescripteurAudio(int*);

#endif