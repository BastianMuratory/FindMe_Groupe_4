// Bastian : Fichier contenant les fonctions utilisées dans le main pour l'affichage et autre
#ifndef __F_main_H__
#define __F_main_H__

#include <stdbool.h>

#define TAILLE_MAX 100

// minimum et maximum des paramètres d'indexation 
#define MIN_INDEXATION_AUDIO 10
#define MAX_INDEXATION_AUDIO 250
#define MIN_INDEXATION_IMAGE 1
#define MAX_INDEXATION_IMAGE 7
#define MIN_INDEXATION_TEXTE 1
#define MAX_INDEXATION_TEXTE 1000

// vide le buffer
void clear (void);

// permet de vider le buffer après une saisie
void color(char* couleur);

// gère la connection au mode administrateur
void connection(bool* admin);

/* affichage du menu utilisateur et admin si possible
admin : correspond à un administrateur connecté ou un utilisateur
x : variable du choix de l'utilisateur
vT,vI,vA : variable contenant le paramètre d'indexation Texte Image et Audio courant
indT,indI,indA : booleen pour savoir si une indexation a été effectuée pour permettre une recherche après un changement de paramètre
der_audio,der_image,der_texte : contient la valeur de la dernière indexation du type de fichier correspondant */
void affichage(bool admin,int *x,int vT,int vI,int vA,bool indT,bool indI,bool indA,int der_texte,int der_image,int der_audio);

// affiche le logo du logiciel 
void logo();

// affiche un message de remerciement
void merci();

// affiche un message d'erreur d'indexation 
void erreur_relancer_indexation();

// fonction pour changer le paramètre d'indexation des textes
void changer_param_text(int* param,bool*); 

// fonction pour changer le paramètre d'indexation des images
void changer_param_image(int* param,bool*);

// fonction pour changer le paramètre d'indexation des fichiers audios
void changer_param_audio(int* param,bool*);



#endif

