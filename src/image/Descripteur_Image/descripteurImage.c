#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "descripteurImage.h"


/*
typedef struct s_Histo{
	bool couleur;// si l'histogramme représente une image en couleur ou pas
	int* histo; // tableau contenant le nombre d'apparition de la couleur représentée par son indice
	//[apparition_couleur_0,apparition_couleur_1,...]
}Histo;
*/

// cree un histogramme vide de la bonne taille en fonction du nombre de bits
Histo init_Histo(bool couleur,int nombre_bits){
	Histo h;
	int puissance_deux = 1;

	if(couleur){
		h.couleur = true;
		for(int i = 0;i<3*nombre_bits;i++){
			puissance_deux*=2;
		}
	}else{
		h.couleur = false;
		for(int i = 0;i<nombre_bits;i++){
			puissance_deux*=2;
		}
	}
	h.histo = (int*)malloc(puissance_deux*sizeof(int));
	h.taille = puissance_deux;
	for(int i =0;i<h.taille;i++){
		h.histo[i]  = 0;
	}
	//printf("[histogramme taille %d]\n",puissance_deux);
	return h;
}

// affiche l'histogramme h
void affiche_Histo(Histo h){
	puts("\n/==================\\");
	if(h.couleur){
		puts("Histo image colorée");
	}else{
		puts("Histo image noir/blanc");
	}
	printf("taille = %d\n",h.taille);
	for(int i=0;i<h.taille;i++){
		if(h.histo[i]!=0){
			printf("[%d|%d]\n",i,h.histo[i]);
		}
	}
	puts("\\==================/");
}

// ajout de la bonne valeur dans un histogramme dans le cas d'une image en noir et blanc
Histo add_Image_NB(Histo h,int intensite,int nombre_bit){
	int* bin = NULL;
	bin = (int*)malloc(nombre_bit*sizeof(int));

	if(bin == NULL){
		puts("Erreur !!!!");
		return h;
	}
	//INTENSITE
	int deux = 128;
	for(int i =0;i<nombre_bit;i++){
		if(intensite>=deux){
			bin[i] = 1;
			intensite-=deux;
		}else{
			bin[i] = 0;
		}
		deux/=2;
	}

	int resultat = 0;
	int puissance_deux = 1;
	for(int i = nombre_bit-1;i>=0;i--){
		resultat+=bin[i]*puissance_deux;
		puissance_deux*=2;
	}
	h.histo[resultat]++;

	free(bin);
	return h;
}


// ajout de la bonne valeur dans un histogramme dans le cas d'une image en couleur 
Histo add_Image_Coul(Histo h,int R,int G,int B,int nombre_bit){
	int* bin = NULL;
	bin = (int*)malloc(3*nombre_bit*sizeof(int));

	//traduction en binaire des nombres entrés;
	if(bin == NULL){
		puts("Erreur !!!!");
		return h;
	}
	//ROUGE
	int deux = 128;
	for(int i =0;i<nombre_bit;i++){
		if(R>=deux){
			
			bin[i] = 1;
			R-=deux;
		}else{
			bin[i] = 0;
		}
		deux/=2;
	}
	//VERT
	deux = 128;
	for(int i =0;i<nombre_bit;i++){
		if(G>=deux){
			bin[nombre_bit+i] = 1;
			G-=deux;
		}else{
			bin[nombre_bit+i] = 0;
		}
		deux/=2;
	}
	//BLEU
	deux = 128;
	for(int i =0;i<nombre_bit;i++){
		if(B>=deux){
			bin[nombre_bit*2+i] = 1;
			B-=deux;
		}else{
			bin[nombre_bit*2+i] = 0;
		}
		deux/=2;
	}

	//calcul du nombre binaire obtenu
	int resultat = 0;
	int puissance_deux = 1;
	for(int i = 3*nombre_bit-1;i>=0;i--){
		resultat+=bin[i]*puissance_deux;
		puissance_deux*=2;
	}
	//incrementation de la case contennat le résultat obtenu
	h.histo[resultat]++;
	free(bin);
	return h;
}


// Creation du descripteur à partir du fichier nomDuFichier en utilisant le nombre de bits forunis par l'administrateur
DescripteurImage creerDescripteurImage(char nomDuFichier[TAILLE_MAX+1],int nombre_bits,int ID){ 
	
	//les deux chemins possibles
	char image_couleur[TAILLE_MAX+1] = "./data/TEST_RGB/";
	char image_nb[TAILLE_MAX+1] = "./data/TEST_NB/";
	//char image_couleur[TAILLE_MAX+1] = "~/FindMe/data/TEST_RGB/";
	//char image_nb[TAILLE_MAX+1] = "~/FindMe/data/TEST_NB/";
	//system(image_couleur);


	//ajout du fichier aux chemins possibles
	strcat(image_couleur,nomDuFichier);
	strcat(image_nb,nomDuFichier);
	
	DescripteurImage d;
	bool couleur = false;
	//Ouverture du fichier + trouver si c'est une image en couleur ou en noir et blanc
	FILE* fichier = NULL;
	fichier = fopen(image_couleur,"r"); // r = read / w = write  
	if(fichier==NULL){
		fichier = fopen(image_nb,"r");
		if(fichier == NULL){
				puts("===============================");
				puts("||Aucun fichier ne correspond||");
				puts("===============================");
				d.ID = -1;
				return d;
		}
		//printf("Indexation de %s\n",image_nb);
	}else{
		couleur = true;
		//printf("Indexation de %s\n",image_couleur);
	}

	//création du descripteur
	
	d.ID = ID;
	strcpy(d.nom,nomDuFichier);
	d.nombre_bits = nombre_bits;

	//Debut lecture du fichier
	int nmColone=0,nmLigne=0,Composante=0;
	fscanf(fichier,"%d %d %d",&nmColone,&nmLigne,&Composante);
	// vérification supplémentaire
	if(Composante == 3){
		couleur = true;
	}else{
		couleur = false;
	}

	// initialisation de l'histogramme à la bonne taille
	d.histogramme = init_Histo(couleur,nombre_bits);
	int** matrice1 = NULL; // rouge
	int** matrice2 = NULL; // vert
	int** matrice3 = NULL; // bleu

	//Initiation des matrices pour stoker les valeurs
	matrice1 = (int**)malloc(nmLigne*sizeof(int*));
		for(int i=0;i<nmLigne;i++){
			matrice1[i] = (int*)malloc(nmColone*sizeof(int));
	}
	if (couleur){
		matrice2 = (int**)malloc(nmLigne*sizeof(int*));
		for(int i=0;i<nmLigne;i++){
			matrice2[i] = (int*)malloc(nmColone*sizeof(int));
		}
		matrice3 = (int**)malloc(nmLigne*sizeof(int*));
		for(int i=0;i<nmLigne;i++){
			matrice3[i] = (int*)malloc(nmColone*sizeof(int));
		}
	}
	//remplissage des matrices
	for(int i=0;i<nmLigne;i++){
		for(int j=0;j<nmColone;j++){
			fscanf(fichier,"%d",&matrice1[i][j]);
		}
		fscanf(fichier,"\n");
	}
	if(couleur){
		for(int i=0;i<nmLigne;i++){
			for(int j=0;j<nmColone;j++){
				fscanf(fichier," %d ",&matrice2[i][j]);
			}
			fscanf(fichier,"\n");
		}
		for(int i=0;i<nmLigne;i++){
			for(int j=0;j<nmColone;j++){
				fscanf(fichier," %d ",&matrice3[i][j]);
			}
			fscanf(fichier,"\n");
		}
	}

	// Remplissage des Histogrammes avec les matrices
	if (couleur){
		for(int i=0;i<nmLigne;i++){
			for(int j=0;j<nmColone;j++){
				d.histogramme = add_Image_Coul(d.histogramme,matrice1[i][j],matrice2[i][j],matrice3[i][j],nombre_bits);
			}
		}
	}else{
		for(int i=0;i<nmLigne;i++){
			for(int j=0;j<nmColone;j++){
				d.histogramme = add_Image_NB(d.histogramme,matrice1[i][j],nombre_bits);
			}
		}
	}
	free(matrice1);
	if(matrice2!=NULL)free(matrice2);
	if(matrice3!=NULL)free(matrice3);

	
	return d;
}


//getters et setters
int getIdDescripteurImage(DescripteurImage d){
	return d.ID;
}
char* getNomDescripteurImage(DescripteurImage d){
	char* nom = malloc((TAILLE_MAX+1)*sizeof(char));
	strcpy(nom,d.nom);
	return nom;
}

//affectation du descripteur e1 au e2
void affectDescripteurImage(DescripteurImage* e1,DescripteurImage* e2){
	e2->ID = e1->ID;
	e2->nombre_bits = e1->nombre_bits;
	strcpy(e2->nom,e1->nom);
	e2->histogramme = init_Histo(e1->histogramme.couleur,e1->nombre_bits);
	for(int i = 0;i< e1->histogramme.taille;i++){
		e2->histogramme.histo[i] = e1->histogramme.histo[i];
	}
}

// affiche le descripteur d
void afficheDescripteurImage(DescripteurImage d){
	printf("[Image=%s | ID=%d | n_bits=%d ]",d.nom,d.ID,d.nombre_bits);
	affiche_Histo(d.histogramme);
}

// fonction utilisée dans le calcul de distance 
int min(int a,int b){
	if(a<b){
		return a;
	}
	return b;
}

// renvoie la distance entre deux descripteurs (calcule l'intersection entre les deux histogrammes)
int distanceDescripteurImage(DescripteurImage d1,DescripteurImage d2){
	int distance = 0;
	int val = 0;
	if(strcmp(d1.nom,d2.nom)==0 && d1.ID == d2.ID){
		return -1;
	}
	if(d1.histogramme.couleur == d2.histogramme.couleur){
		for(int i =0;i<d1.histogramme.taille;i++){
				val = min(d1.histogramme.histo[i],d2.histogramme.histo[i]);
				distance+= val;
			}
	}else{
		return -1;
	}
	return distance;
};



//sauvegarde un descripteur dans un fichier pour la sauvegarde
int sauvegarderDescripteurImage(FILE* fichier,DescripteurImage d){
	fprintf(fichier,"%d,%d,%s\n",d.ID,d.nombre_bits,d.nom);
	if(d.histogramme.couleur){
		fprintf(fichier,"1 %d\n",d.histogramme.taille);
	}else{
		fprintf(fichier,"0 %d\n",d.histogramme.taille);
	}
	for(int i = 0;i<d.histogramme.taille;i++){
		fprintf(fichier,"%d ",d.histogramme.histo[i]);
	}
	fprintf(fichier,"\n");
	return 0;
}

// charge un descripteur depuis un fichier de sauvegarde
DescripteurImage chargerDescripteurImage(FILE* fichier){
	DescripteurImage d;
	int boole;
	fscanf(fichier, "%d,%d,%s\n",&d.ID,&d.nombre_bits,d.nom);
	fscanf(fichier, "%d %d\n",&boole,&d.histogramme.taille);
	if(boole){
		d.histogramme.couleur = true;
	}else{
		d.histogramme.couleur = false;
	}
	d.histogramme.histo = (int*)malloc(d.histogramme.taille*sizeof(int));
	for(int i=0;i<d.histogramme.taille;i++){
		fscanf(fichier,"%d ",&d.histogramme.histo[i]);
	}
	fscanf(fichier,"\n");
	return d;
}

// libère l'espace mémoire utilisé par un descripteur
void freeDescripteurImage(DescripteurImage* pointeur){
	free(pointeur->histogramme.histo);
}

// retourne la taille de l'image (les dimensions n'etants pas sauvegardées on peut la calculer comme cela )
long int getTaille(DescripteurImage* pointeur){
	int somme = 0;
	for(int i = 0;i<pointeur->histogramme.taille;i++){
		somme+=pointeur->histogramme.histo[i];
	}
	return somme;
}



/*
	Soit le pixel suivant ayant les valeurs (255, 128, 64), c’est-à-dire une
intensité de 255 sur la composante rouge (R), de 128 sur la composante verte (G) et
de 64 sur la composante bleue (B).

La quantification sur les 2 premiers bits donne :
Pour 255 =
1 x 2^7 + 1 x 2^6 + 1 x 2^5 + 1 x 2^4 + 1 x 2^3 + 1 x 2^2 + 1 x 2^1 + 1 x 2^0 =
128 + 64 + 32 + 16 + 8 + 4 + 2 + 1
1er bit R1: 1, 2ème bit R2: 1

Pour 128 =
1 x 128 + 0 + 0 + 0 + 0 + 0 + 0 + 0
1er bit G1: 1, 2ème bit G2: 0

Pour 64 =
0 + 1 x 64 + 0 + 0 + 0 + 0 + 0 + 0
1er bit B1: 0, 2ème bit B2: 1

On se retrouve avec 6 bits (que l’on organise par exemple ainsi) : R1 R2 G1 G2 B1 B2
R1 1er bit de la composante rouge  1
R2 2ème bit de la composante rouge 1
G1 1er bit de la composante verte  1
G2 2ème bit de la composante verte 0
B1 1er bit de la composante bleue  0
B2 2ème bit de la composante bleue 1

Sur notre exemple, nous avons : 1 1 1 0 0 1, soit le nombre : 57
57 = 1 x 2^5 + 1 x 2^4 + 1 x 2^3 + 0 x 2^2 + 0 x 2^1 + 1 x 2^0
Donc avec une quantification sur 2 bits, nous obtenons des pixels ayant une valeur
entre 0 (les 6 bits à 0) et 63 (les 6 bits à 1).
*/

/*
Pour 255 =
(1 x 2^7 + 1 x 2^6) + 1 x 2^5 + 1 x 2^4 + 1 x 2^3 + 1 x 2^2 + 1 x 2^1 + 1 x 2^0 =
(128 + 64) + 32 + 16 + 8 + 4 + 2 + 1
code (1 1) 1 1 1 1 1 1
1er bit R1: 1, 2ème bit R2: 1

*/

