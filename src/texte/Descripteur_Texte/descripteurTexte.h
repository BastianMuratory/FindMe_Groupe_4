#ifndef __DescripteurTexte_h__
#define __DescripteurTexte_h__

#define TAILLE_MAX 100
#define TAILLE_MOT 50

typedef struct s_Cellule {
  char token[TAILLE_MOT+1];
  int nbOcc;
  struct s_Cellule* suiv;
} Cellule;

typedef struct s_ListeTermes {
  Cellule* tete;
  int taille;
} ListeTermes;

typedef struct s_DescripteurTexte{
	ListeTermes termes; // Liste des termes les plus significatifs
  int nbTermes; // Nombre total des termes retenus
  int nbTokenFic; // Taille du fichier en nombre de token
	int ID; // ID du descripteur
	char nom[TAILLE_MAX+1]; // nom du fichier decrit
}DescripteurTexte;

/* Libère l'espace mémoire d'un descripteur */
int freeDescripteurTexte(DescripteurTexte* d);

/* Creation et retour du descripteur du fichier nomDuFichier avec comme paramètre d'indexation nmbDeMots et comme identifiant ID */
DescripteurTexte creerDescripteurTexte(char nomDuFichier[TAILLE_MAX+1],int nmbDeMots,int ID);

/** getters et setters **/
/* Retourne l'identifiant du descripteur d */
int getIdDescripteurTexte(DescripteurTexte d);
/* Retourne le nom du fichier du descripteur d */
char* getNomDescripteurTexte(DescripteurTexte d);
/* Affect la valeur x à l'indexation du descripteur pointeur_d et retourne 0 si tout s'est bien passé */
int setIdDescripteurTexte(DescripteurTexte* pointeur_d,int x);

/** copie et affichage **/
/* Copie en profondeur du descripteur e1 dans le descripteur e2 */
void affectDescripteurTexte(DescripteurTexte* e,DescripteurTexte* x);
/* Affichage du descripteur d */
void afficheDescripteurTexte(DescripteurTexte d);

/** Calcul des distances **/
/* Retourne la distance entre deux descripteurs d1 et d2 */
int distanceDescripteurTexte(DescripteurTexte d1,DescripteurTexte d2);
/* Retourne la distance entre un mot mot et un descripteur d */
int distanceDescripteurMotTexte(char* mot,DescripteurTexte d2);

/** Chargement et sauvegarde du fichier descripteur **/
/* Retourne la pile des descripteurs à partir du fichier de sauvegarde des descripteurs fichier */
int sauvegarderDescripteurTexte(FILE* fichier,DescripteurTexte d);
/* Ecrit la pile des descripteurs d dans le fichier fic */
DescripteurTexte chargerDescripteurTexte(FILE* fic);

#endif
