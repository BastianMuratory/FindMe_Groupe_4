// Bastian : fichier contenant les fonctions de gestion de la pile de descripteur image
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./image.h"

// Création de la cellule de la pile qui va garder le descripteur
CelluleImage* initCelImage(DescripteurImage el){ // nbits sert a rien
	CelluleImage* c = (CelluleImage*)malloc(sizeof(CelluleImage));
	c->suivant = NULL;
	affectDescripteurImage(&el,&(c->descripteur));
	return c;
}

// initialise une pile vide
PileDescripteurImage initPileDescripteurImage(){
	PileDescripteurImage p;
	p.taille = 0;
	p.tete = NULL;
	return p;
}

// empile un descripteur dans la pile
PileDescripteurImage empileDescripteurImage(PileDescripteurImage p,DescripteurImage d){
	CelluleImage* c = initCelImage(d);
	if(p.taille!=0){
		c->suivant = p.tete;
	}
	p.tete = c;
	p.taille++;
	return p;
}

//depile le premier descripteur de la pile
PileDescripteurImage depileDescripteurImage(PileDescripteurImage p){
	if(p.taille!=0){
		CelluleImage* cel = p.tete;
		p.tete = p.tete->suivant;
		freeDescripteurImage(&(cel->descripteur));
		free(cel);
		p.taille--;
	}
	return p;
}

// récupère le descripteur à la position indexe dans la pile 
DescripteurImage* getDescripteurImage(PileDescripteurImage p,int indexe){
	CelluleImage* courant = p.tete;
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
DescripteurImage* getDescripteurImageViaId(PileDescripteurImage p,int id){
	CelluleImage* courant;
	int i = 0;
	int pasTrouve = 1;
	while(i<p.taille && pasTrouve){
		if(i==0){
			courant = p.tete;
		}else{
			courant = courant->suivant;
		}
		if(getIdDescripteurImage(courant->descripteur)==id){
			pasTrouve = 0;
		}
		i++;
	}
	if(pasTrouve){
		//puts("Le descripteur n'a pas été trouvé");
		return NULL;
	}
	//puts("Le descripteur a été trouvé");
	return &(courant->descripteur);
}

// récupère le descripteur possédant le même nom que celui passé en parramètre
DescripteurImage* getDescripteurImageViaNom(PileDescripteurImage p,char nom[50]){
	CelluleImage* courant;
	int i = 0;
	int pasTrouve = 1;
	while(i<p.taille && pasTrouve){
		if(i==0){
			courant = p.tete;
		}else{
			courant = courant->suivant;
		}
		if(strcmp( nom, getNomDescripteurImage(courant->descripteur))==0){
			pasTrouve = 0;
		}
		i++;
	}
	if(pasTrouve){
		//puts("Le descripteur n'a pas été trouvé");
		return NULL;
	}
	//puts("Le descripteur a été trouvé");
	return &(courant->descripteur);

}

// affiche une pile de descripteur ( surtout utilisé pendant les tests)
void affichePileDescripteurImage(PileDescripteurImage p){
	printf("============================\nPile de [%d] descripteurs\n",p.taille);
	CelluleImage* courant;
	for(int i=0;i<p.taille;i++){
		if(i==0){
			courant = p.tete;
		}else{
			courant = courant->suivant;
		}
		printf("[%d]",i);
		afficheDescripteurImage(courant->descripteur);
		puts("");
	}
	puts("============================\n");
}

// modifiée

// libère l'espace mémoire utilisé par la pile ... enfin je crois 
void freePileDescripteurImage(PileDescripteurImage* p){
	int nombre = p->taille;
	if(nombre >0){
		for(int i =0;i<nombre;i++){
			*p = depileDescripteurImage(*p);
		}
	}
}

// s'occupe de créer le descripteur du fichier passé en parramètre, de l'empiler sur la pile de descripteur et de créer son lien qui sera lui aussi empilé sur la pile de liens
int toutDescripteurImage(char* nomDuFichier,PileDescripteurImage* p,PileLien* l,int n_bits, int ID){
	DescripteurImage desc = creerDescripteurImage(nomDuFichier,n_bits,ID);
	Lien lien = creerLien(desc.nom,desc.ID);
	*p = empileDescripteurImage(*p, desc);
	*l = empileLien(*l, lien);
	return EXIT_SUCCESS;
}

/* Sauvegarde la pile de descripteur et la pile de liens dans les fichiers :
 - base_descripteur_image
 - liste_base_image */
int SauvegardePileDescripteurImage(PileDescripteurImage p,PileLien l){
  int pourcentage;
	FILE* fichier = NULL;
	fichier = fopen("./sauvegarde/Descripteur_image/base_descripteur_image","w");
	if(fichier == NULL){
		return 1;
	}
	printf("\x1b[33m");
	fprintf(fichier,"%d\n",p.taille);
	for(int i =0;i<p.taille;i++){
		sauvegarderDescripteurImage(fichier,*getDescripteurImage(p,i));
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
	sauvegardePileLien(l,"./sauvegarde/Descripteur_image/liste_base_image");
	return 0;
}

/* Charge la pile de descripteur depuis le fichier de sauvegarde */
PileDescripteurImage chargePileDescripteurImage(int*id){
  int pourcentage;
	FILE* fichier = NULL;
	// Sauvegarde de la Pile de descripteurs
	int taille;
	PileDescripteurImage p = initPileDescripteurImage();
	fichier = fopen("./sauvegarde/Descripteur_image/base_descripteur_image","r");
	if(fichier == NULL){
		puts("base_descripteur_image n'existe pas ou n'est pas trouvé");
		return p;
	}
	fscanf(fichier,"%d\n",&taille);
	*id = taille;
	printf("\x1b[33m");
	for(int i =0;i<taille;i++){
		DescripteurImage d = chargerDescripteurImage(fichier);
		p = empileDescripteurImage(p,d);
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

