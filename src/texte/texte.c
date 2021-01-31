// Bastian : fichier contenant les fonctions de gestion de la pile de descripteur texte
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./texte.h"

// Création de la cellule de la pile qui va garder le descripteur
CelluleTexte* initCelTexte(DescripteurTexte el){
	CelluleTexte* c = (CelluleTexte*)malloc(sizeof(CelluleTexte));
	c->suivant = NULL;
	affectDescripteurTexte(&el,&(c->descripteur));
	return c;
}

// initialise une pile vide
PileDescripteurTexte initPileDescripteurTexte(){
	PileDescripteurTexte p;
	p.taille = 0;
	p.tete = NULL;
	return p;
}

// empile un descripteur dans la pile
PileDescripteurTexte empileDescripteurTexte(PileDescripteurTexte p,DescripteurTexte d){
	CelluleTexte* c = initCelTexte(d);
	if(p.taille!=0){
		c->suivant = p.tete;
	}
	p.tete = c;
	p.taille++;
	return p;
}

//depile le premier descripteur de la pile
PileDescripteurTexte depileDescripteurTexte(PileDescripteurTexte p){
	if(p.taille==0){
		printf("Erreur : votre pile est déjà vide !\n");
	}else{
		CelluleTexte* cel = p.tete;
		p.tete = p.tete->suivant;
		free(cel);
		p.taille--;
	}
	return p;
}


// récupère le descripteur à la position indexe dans la pile
DescripteurTexte* getDescripteurTexte(PileDescripteurTexte p,int indexe){
	CelluleTexte* courant = p.tete;
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
DescripteurTexte* getDescripteurTexteViaId(PileDescripteurTexte p,int id){
	CelluleTexte* courant;
	int i = 0;
	int pasTrouve = 1;
	while(i<p.taille && pasTrouve){
		if(i==0){
			courant = p.tete;
		}else{
			courant = courant->suivant;
		}
		if(getIdDescripteurTexte(courant->descripteur)==id){
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
DescripteurTexte* getDescripteurTexteViaNom(PileDescripteurTexte p,char nom[50]){
	CelluleTexte* courant;
	int i = 0;
	int pasTrouve = 1;
	while(i<p.taille && pasTrouve){
		if(i==0){
			courant = p.tete;
		}else{
			courant = courant->suivant;
		}
		if(strcmp( nom, getNomDescripteurTexte(courant->descripteur))==0){
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
void affichePileDescripteurTexte(PileDescripteurTexte p){
	printf("============================\nPile de [%d] descripteurs\n",p.taille);
	CelluleTexte* courant;
	for(int i=0;i<p.taille;i++){
		if(i==0){
			courant = p.tete;
		}else{
			courant = courant->suivant;
		}
		printf("[%d]",i);
		afficheDescripteurTexte(courant->descripteur);
		puts("");
	}
	puts("============================");
}

// libère l'espace mémoire utilisé par la pile ... enfin je crois 
void freePileDescripteurTexte(PileDescripteurTexte* p){
	int nombre = p->taille;
	if(nombre >0){
		for(int i =0;i<nombre;i++){
			*p = depileDescripteurTexte(*p);
		}
	}
}

// s'occupe de créer le descripteur du fichier passé en parramètre, de l'empiler sur la pile de descripteur et de créer son lien qui sera lui aussi empilé sur la pile de liens
int toutDescripteurTexte(char* nomDuFichier,PileDescripteurTexte* p,PileLien* l,int nmbMots,int ID){
	DescripteurTexte desc = creerDescripteurTexte(nomDuFichier,nmbMots,ID);
	Lien lien = creerLien(desc.nom,desc.ID);
	*p = empileDescripteurTexte(*p, desc);
	*l = empileLien(*l, lien);
	return EXIT_SUCCESS;
}

/* Sauvegarde la pile de descripteur et la pile de liens dans les fichiers :
 - base_descripteur_texte
 - liste_base_texte */
int SauvegardePileDescripteurTexte(PileDescripteurTexte p,PileLien l){
  int pourcentage;
	FILE* fichier = NULL;
	fichier = fopen("./sauvegarde/Descripteur_texte/base_descripteur_texte","w");
	if(fichier == NULL){
		puts("base_descripteur_texte n'existe pas ou n'est pas trouvé");
	}
	fprintf(fichier,"%d\n",p.taille);
	printf("\x1b[33m");
	for(int i =0;i<p.taille;i++){
		sauvegarderDescripteurTexte(fichier,*getDescripteurTexte(p,i));
    pourcentage = ((i+1)*100)/p.taille;
    printProgressBar(pourcentage);
    fflush(stdout);
	}
	printf("\x1b[32m");
  printProgressBar(100);
  printf("\x1b[0m");
  printf("\n");
	fclose(fichier);
	// Sauvegarde de la pile de liens
	sauvegardePileLien(l,"./sauvegarde/Descripteur_texte/liste_base_texte");
	return 0;
}

/* Charge la pile de descripteur depuis le fichier de sauvegarde */
PileDescripteurTexte chargePileDescripteurTexte(int*id){
	int pourcentage;
	FILE* fichier = NULL;
	// Sauvegarde de la Pile de descripteurs
	int taille;
	PileDescripteurTexte p = initPileDescripteurTexte();
	fichier = fopen("./sauvegarde/Descripteur_texte/base_descripteur_texte","r");
	if(fichier == NULL){
		puts("base_descripteur_texte n'existe pas ou n'est pas trouvé");
		return p;
	}
	printf("\x1b[33m");
	fscanf(fichier,"%d\n",&taille);
	*id = taille;
	for(int i =0;i<taille;i++){
		p = empileDescripteurTexte(p,chargerDescripteurTexte(fichier));
    pourcentage = ((i+1)*100)/taille;
    printProgressBar(pourcentage);
    fflush(stdout);
	}
	printf("\x1b[32m");
  printProgressBar(100);
  printf("\x1b[0m");
  printf("\n");
	puts("chargement pile desc fini");
	fclose(fichier);
	// Sauvegarde de la pile de liens
	return p;
}





