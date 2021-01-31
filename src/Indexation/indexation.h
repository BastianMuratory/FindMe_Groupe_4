// Bastian : fichier contenant les fonctions de recherche et d'indexation des différents types de fichiers dans la base de donnée
#ifndef __Idexation_H__
#define __Idexation_H__

#include "../image/image.h"
#include "../audio/audio.h"
#include "../texte/texte.h"
#include "../Lien/liens.h"

// fonction d'indexation des fichiers image
// en entrée : une pile de descripteur image, une pile de liens entre image et descripteur, le nombre de bits de quantification et le pointeur vers l'id courant des images pour le mettre à jour
int indexation_fichiers_images(PileDescripteurImage* p,PileLien* l,int nmb_bits,int* ID);
// recherche d'un fichier image 
// en entrée : une pile de descripteur image, une pile de liens entre image et descripteur, le nombre de bits de quantification et le nombre de résultats attendus
int rechercher_image(PileDescripteurImage* p,PileLien* l,int nBits,int n_resultats);

// fonctions d'indexation' des fichiers audios avec les mêmes paramètres que la fonctions image 
int indexation_fichiers_audio(PileDescripteurAudio* p,PileLien* l,int nombreDesIntervales,int* ID);
// fonctions de recherche des fichiers audios avec les mêmes paramètres que les fonctions image
int rechercher_audio(PileDescripteurAudio* p,PileLien* l,int nombreDesIntervales,int n_resultats);

// fonctions d'indexation' des fichiers textes avec les mêmes paramètres que la fonctions image 
int indexation_fichiers_textes(PileDescripteurTexte* p,PileLien* l,int nmb_mots,int* ID);
// fonctions de recherche des fichiers textes avec les mêmes paramètres que les fonctions image
int rechercher_texte(PileDescripteurTexte* p,PileLien* l,int n_mots,int n_resultats);
// fonctions de recherche d'un mot avec les mêmes paramètres que les fonctions image
int rechercher_mots_texte(PileDescripteurTexte* p,int n_resultats);
#endif