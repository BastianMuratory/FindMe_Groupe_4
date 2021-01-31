#ifndef __DescripteurAudio_h__
#define __DescripteurAudio_h__

#define TAILLE_MAX 100

typedef struct s_DescripteurAudio {
	int ID; // ID du descripteur
	char nom[TAILLE_MAX+1]; // nom du fichier decrit
	int nombreDesIntervalles;	// nombre des intervalles , changeable depuis le menu d'administrateur
	int tailleDuDescripteur; // variable contenant le nombre de ligne d'histogramme (=nombre de variables du fichier)
	int** histogramme; // matrice contenant l'histogramme
  int* vectNombre; // vecteur contenant le nombre d'apparation de frequences (dans telle et telle intervalle)
  int* vectEndroit; // vecteur contenant l'endroit (le placement) des frequances
} DescripteurAudio;
// vectNombre et vectEndroit sont des vecteurs crees a partir de l'histogramme. Ils sont une interpetation de l'histogramme qui nous permet de faire des calcules plus simples et plus rapides.

/* Creation des descripteurs */
// creation de descripteur a partir des fichiers bin
DescripteurAudio creerDescripteurAudioBin(char nomDuFichier[TAILLE_MAX+1],int nombreDesIntervalles, int id); 
// creation de descripteur a partir des fichiers txt
DescripteurAudio creerDescripteurAudio(char* nomDuFichier, int nombreDesIntervalles, int id); 

//Taille fichier binaiare
unsigned long tailleFichierBin(FILE *ficbin);



//getters et setters
int getIdDescripteurAudio(DescripteurAudio d);
char* getNomDescripteurAudio(DescripteurAudio d);
int setIdDescripteurAudio(DescripteurAudio* pointeur_d,int x);
//affectation et copie
void affectDescripteurAudio(DescripteurAudio* e,DescripteurAudio* x); // pas besoin ?
void afficheDescripteurAudio(DescripteurAudio d);
// calcul distance, retourne le pourcentage de différence entre deux fichiers (un reel compris entre 0 et 100);
float distanceDescripteurAudio(DescripteurAudio* d1,DescripteurAudio* d2, float*); 

/* fonction de sauvgardage (ecriture dans un fichier txt de : nom, Id, nombreDesIntervalles, tailleDuDescripteur, vectNombre, vectEndroit) d'un descripteur */
int sauvegarderDescripteurAudio(FILE* fichier,DescripteurAudio d); 

// fonction de chargement (lecture dans un fichier txt de : nom, Id, nombreDesIntervalles, tailleDuDescripteur, vectNombre, vectEndroit) d'un descripteur
DescripteurAudio chargerDescripteurAudio(FILE* fichier); 
// dans le sauvgardage et le chargement de descripteur audio on n'a pas besoin de l'histogramme, parce que tout ses informations sont contenu dans vectEndroit (et vectNombre)

#endif
