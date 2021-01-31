// Bastian : Fonction de chargement et sauvegarde des paramètres d'indexation 
#ifndef __F_CHARGEMENT_H__
#define __F_CHARGEMENT_H__


// Chargement et sauvegarde des paramètres d'indexation : ces données sont sauvegardées dans le fichier config
int chargement_config(int* parramTexte,int* parramImage,int* parramAudio,bool* chercheTexte,bool* chercheImage,bool* chercheAudio);

void sauvegarde_config(int parramTexte,int parramImage,int parramAudio,bool chercheTexte,bool chercheImage,bool chercheAudio);


// Chargement et sauvegarde des paramètres de dernière indexation et dernière sauvegarde
void chargement_derniere_indexation(int* texte,int* image,int* audio,int* s_texte,int* s_image,int* s_audio);

void sauvegarde_derniere_indexation(int texte,int image,int audio,int s_texte,int s_image,int s_audio);


#endif