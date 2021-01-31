// Bastian : fichier contenant les fonctions de gestion de la pile de descripteur audio
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./audio.h"

// Création de la cellule de la pile qui va garder le descripteur
CelluleAudio* initCelAudio(DescripteurAudio el){
	CelluleAudio* c = (CelluleAudio*)malloc(sizeof(CelluleAudio));
	c->suivant = NULL;
	affectDescripteurAudio(&el,&(c->descripteur));
	return c;
}

// initialise une pile vide
PileDescripteurAudio initPileDescripteurAudio(){
	PileDescripteurAudio p;
	p.taille = 0;
	p.tete = NULL;
	return p;
}

// empile un descripteur dans la pile
PileDescripteurAudio empileDescripteurAudio(PileDescripteurAudio p,DescripteurAudio d){
	CelluleAudio* c = initCelAudio(d);
	if(p.taille!=0){
		c->suivant = p.tete;
	}
	p.tete = c;
	p.taille++;
	return p;
}

//depile le premier descripteur de la pile
PileDescripteurAudio depileDescripteurAudio(PileDescripteurAudio p){
	if(p.taille==0){
		printf("Erreur : votre pile est déjà vide !\n");
	}else{
		CelluleAudio* cel = p.tete;
		p.tete = p.tete->suivant;
		free(cel);
		p.taille--;
	}
	return p;
}

// récupère le descripteur à la position indexe dans la pile 
DescripteurAudio* getDescripteurAudio(PileDescripteurAudio p,int indexe){
	CelluleAudio* courant = p.tete;
	if(indexe>p.taille-1){
		printf("Il n'y a pas assez de descripteur, le pointeur est null\n");
		return NULL;
	}else{
		for(int i=0;i<indexe;i++){
			courant = courant->suivant;
		}
	}
	return &(courant->descripteur);
}

// récupère le descripteur possédant l'id passé en parramètre 
DescripteurAudio* getDescripteurAudioViaId(PileDescripteurAudio p,int id){
	CelluleAudio* courant;
	int i = 0;
	int pasTrouve = 1;
	while(i<p.taille && pasTrouve){
		if(i==0){
			courant = p.tete;
		}else{
			courant = courant->suivant;
		}
		if(getIdDescripteurAudio(courant->descripteur)==id){
			pasTrouve = 0;
		}
		i++;
	}
	if(pasTrouve){
		puts("Le descripteur n'a pas été trouvé");
		return NULL;
	}
	return &(courant->descripteur);
}

// récupère le descripteur possédant le même nom que celui passé en parramètre
DescripteurAudio* getDescripteurAudioViaNom(PileDescripteurAudio p,char nom[50]){
	CelluleAudio* courant;
	int i = 0;
	int pasTrouve = 1;
	while(i<p.taille && pasTrouve){
		if(i==0){
			courant = p.tete;
		}else{
			courant = courant->suivant;
		}
		if(strcmp( nom, getNomDescripteurAudio(courant->descripteur))==0){
			pasTrouve = 0;
		}
		i++;
	}
	if(pasTrouve){
		puts("Le descripteur n'a pas été trouvé");
		return NULL;
	}
	//puts("Le descripteur a été trouvé");
	return &(courant->descripteur);
}

// affiche une pile de descripteur ( surtout utilisé pendant les tests)
void affichePileDescripteurAudio(PileDescripteurAudio p){
	printf("============================\nPile de [%d] descripteurs\n",p.taille);
	CelluleAudio* courant;
	for(int i=0;i<p.taille;i++){
		if(i==0){
			courant = p.tete;
		}else{
			courant = courant->suivant;
		}
		printf("[%d] ",i);
		afficheDescripteurAudio(courant->descripteur);
		puts("");
	}
	puts("============================");
}

// libère l'espace mémoire utilisé par la pile
void freePileDescripteurAudio(PileDescripteurAudio* p){
	int nombre = p->taille;
	if(nombre >0){
		for(int i =0;i<nombre;i++){
			*p = depileDescripteurAudio(*p);
		}
	}
}

// s'occupe de créer le descripteur du fichier passé en parramètre, de l'empiler sur la pile de descripteur et de créer son lien qui sera lui aussi empilé sur la pile de liens
int toutDescripteurAudio(char* nomDuFichier,PileDescripteurAudio* p,PileLien* l,int nombreIntervalle,int ID){
	// creation du descripteur 
	DescripteurAudio desc = creerDescripteurAudio(nomDuFichier,nombreIntervalle,ID);
	Lien lien = creerLien(desc.nom,desc.ID);

	*p = empileDescripteurAudio(*p, desc);
	*l = empileLien(*l, lien);

	return EXIT_SUCCESS;
}

/* Sauvegarde la pile de descripteur et la pile de liens dans les fichiers :
 - base_descripteur_audio
 - liste_base_audio */
int SauvegardePileDescripteurAudio(PileDescripteurAudio p,PileLien l){
	FILE* fichier = NULL;
	fichier = fopen("./sauvegarde/Descripteur_audio/Base_descripteur_audio","w");
	if(fichier == NULL){
		puts("Base_descripteur_audio n'existe pas ou n'est pas trouvé");
	}
	fprintf(fichier,"%d\n",p.taille);
	int pourcentage;
	printf("\x1b[33m");
	for(int i =0;i<p.taille;i++){
		sauvegarderDescripteurAudio(fichier,*getDescripteurAudio(p,i));
    pourcentage = ((i+1)*100)/p.taille;
    printProgressBar(pourcentage);
    fflush(stdout);
	}
	printf("\x1b[32m");
  printProgressBar(100);
  printf("\x1b[0m");
  printf("\n");
	//puts("sauvegarde pile desc fini");
	fclose(fichier);
	// Sauvegarde de la pile de liens
	sauvegardePileLien(l,"./sauvegarde/Descripteur_audio/Liste_base_audio");
	return 0;
}

/* Charge la pile de descripteur depuis le fichier de sauvegarde */
PileDescripteurAudio chargePileDescripteurAudio(int*id){
  int pourcentage;
	FILE* fichier = NULL;
	// Sauvegarde de la Pile de descripteurs
	int taille;
	PileDescripteurAudio p = initPileDescripteurAudio();
	fichier = fopen("./sauvegarde/Descripteur_audio/Base_descripteur_audio","r");
	if(fichier == NULL){
		puts("Base_descripteur_audio n'existe pas ou n'est pas trouvé");
		return p;
	}
	fscanf(fichier,"%d\n",&taille);
	*id = taille;
	printf("\x1b[33m");
	for(int i =0;i<taille;i++){
		p = empileDescripteurAudio(p,chargerDescripteurAudio(fichier));
    pourcentage = ((i+1)*100)/taille;
    printProgressBar(pourcentage);
    fflush(stdout);
	}
	printf("\x1b[32m");
  printProgressBar(100);
  printf("\x1b[0m");
  printf("\n");
	//puts("chargement pile desc fini");
	fclose(fichier);
	// Sauvegarde de la pile de liens
	return p;
}

