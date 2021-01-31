/* Kosma PRZYJEMSKI & Moumouni BELEM
Kosma :  creerDescripteurAudio - creation du descripteur audio a partir des tichiers .txt ;  distanceDescripteurAudio - fonction de calcule de distance entre deux descripteurs ; fonctions d'affichage : du descripteur, de l'histogramme, de vectEndroit, de vectNombre ;  affectDescripteurAudio - fonction d'affectation d'un descripteur a un autre ; fonctions getters et setter ; aide avec creerDescripteurAudioBin 
Moumouni : creerDescripteurAudioBin - creation du descripteur audio a partir des fichiers .bin ; tailleFichierBin - getter de taille du descripteur audio binaire ; 
Les fonctions de Moumouni sont mis en commentaire en bas du fichier, parce que au final nous utilisons la foncion ecrit dans le fichier binToTxt.c qui convertit et sauvegarde le fichier binaires recherché sous la forme d'un fichier txt afin de pouvoir utiliser les foncions deja créées pour le descipriteur audio (creerDescripteurAudio, chargerDescripteurAudio etc.)
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <conio.>

#include "descripteurAudio.h"



// Creation du descripteur
DescripteurAudio creerDescripteurAudio(char nomDuFichier[TAILLE_MAX+1],int nombreDesIntervalles, int id){
  // initialisation des variables locales
  int i,j;
	DescripteurAudio d;
	
	strcpy(d.nom,nomDuFichier); // mise a jour du nom
	d.ID = id; // mise a jour de l'id
  d.nombreDesIntervalles = nombreDesIntervalles;
	d.tailleDuDescripteur = 0; // initialisation de taille du descripteur a 0

  // creation de la commande pour ouvrir le fichier txt
  char maCommande[TAILLE_MAX+1] = "wc -l ./data/TEST_SON/";
	strcat(maCommande,d.nom);
	strcat(maCommande," > Temp");
	system(maCommande);
	
	// Création du fichier temporaire
	FILE* fichier = fopen("Temp","r");
  if (fichier == NULL){
    printf("Erreur <-- ouverture du fichier .txt\n");
    exit(EXIT_FAILURE);
  }

  // Recuperation de la taille du fichier .txt
	int taille = 0;
	fscanf(fichier,"%d",&taille);

  // affectation de la taille du fichier 
  d.tailleDuDescripteur=taille;
  
  // Reservation de la memoire pour l'histogramme
	d.histogramme = (int**)malloc(d.tailleDuDescripteur*sizeof(int*));
	for(i=0; i<d.tailleDuDescripteur; i++){
		d.histogramme[i] = (int*)malloc(d.nombreDesIntervalles*sizeof(int));
	}

  // Reservation de la memoire pour vectNombre
	d.vectNombre = (int*)malloc(d.nombreDesIntervalles*sizeof(int));
  // initialisation des toutes ses valeurs à 0
  for(i=0; i<d.nombreDesIntervalles; i++){
		d.vectNombre[i] = 0;
	}
  // Reservation de la memoire pour vectEndroit
	d.vectEndroit = (int*)malloc(d.tailleDuDescripteur*sizeof(int));
	// initialisation des toutes ses valeurs à 0
  for(i=0; i<d.tailleDuDescripteur; i++){
    d.vectEndroit[i] = 0;
	}

	//lecture du fichier audio
	char chemin[TAILLE_MAX+1] = "./data/TEST_SON/";

	strcat(chemin,nomDuFichier);
	fichier = NULL;
	fichier = fopen(chemin, "r");

	if(fichier == NULL){
		printf("Le fichier n'est pas touvé\n");	
	}
  
 
  double varTemp=0;
  float borneMax=0;
  float borneMin=0;
  float dist=1.2/(float)nombreDesIntervalles;
  // Creation de l'histogramme d.histogramme, de vectNombre - vecteur contenant le nombre d'apparation de frequences dans chaqune intervalle et de vectEndroit - vecteur contenant l'endroit (le placement) des frequances (par example 1 er valeur est contenu dans 26ieme intervalle --> vectEndroit[0]=26)
  for(i=0; i<d.tailleDuDescripteur; i++){
    // Recuperation de la valeur temporaire dans le ficier .txt 
    fscanf(fichier, " %lf\n", &varTemp); 
    for(j=0; j<d.nombreDesIntervalles; j++){
      // Calcule des bornes de l'intervalle j  
      borneMin = -0.6+j*dist;
      borneMax = -0.6+(j+1)*dist;
      // On remplis l'histogramme avec : 1 si valeur est contenue dans l'intervalle et 0 sinon. Si la vleur est dehors la borne minimal totale et la borne maximal toale, on affiche une message d'erreur pour pouvoir l'augmenter l'intervalle. 
      if (varTemp<(-0.6) || varTemp>0.6)
        printf("\x1b[31m Erreur --> valeurs hors les bornes !!! \x1b[0m\n");
      else if (varTemp>borneMin && varTemp<=borneMax){
        d.histogramme[i][j]=1; // on remplit l'histogramme avec 1 si la frequance est contenu dans l'intervalle courante
        d.vectNombre[j]+=1;  // on ajoute 1 a vectNombre[j] car la valeur est contenu dans l'intervalle j de l'histogramme
        d.vectEndroit[i]+=j; // on ajoute j a vectNombre[i] car la valeur est contenu dans j i-eme intervalle de l'histogramme
      }else {
        d.histogramme[i][j]=0; // on remplit l'histogramme avec 0 si la frequance n'est pas contenu dans l'intervalle courante
			}
		}
	}
  fclose(fichier);
  remove("Temp");
	return d;
}


// ### getters et setters ###
int getIdDescripteurAudio(DescripteurAudio d){
	return d.ID;
}
char* getNomDescripteurAudio(DescripteurAudio d){
  char* nom = malloc((TAILLE_MAX+1)*sizeof(char));
	strcpy(nom,d.nom);
	return nom;
}

int setIdDescripteurAudio(DescripteurAudio* pointeur_d,int x){
	pointeur_d->ID = x;
	return 0;
}


//affectation d'un descripteur audio a une autre
void affectDescripteurAudio(DescripteurAudio* e1,DescripteurAudio* e2){
  int i,j;
	// affectation de ID et du nom
  e2->ID = e1->ID;
  strcpy(e2->nom,e1->nom);
  // affectation du nombreDesIntervalles et de la tailleDuDescripteur
  e2->nombreDesIntervalles = e1->nombreDesIntervalles;
  e2->tailleDuDescripteur = e1->tailleDuDescripteur;

  /* reservation de memoire pour vectEndroit et vectNombre */
	e2->vectEndroit = (int*)malloc(e2->tailleDuDescripteur*sizeof(int));
	e2->vectNombre = (int*)malloc(e2->nombreDesIntervalles*sizeof(int));
	
  /* affectation de vectEndroit */
  for(i=0; i<e1->tailleDuDescripteur; i++){
    e2->vectEndroit[i] = e1->vectEndroit[i];
  }
  /* affectation de vectNombre */
  for(j=0; j<e1->nombreDesIntervalles; j++){  
    e2->vectNombre[j] = e1->vectNombre[j];
  }
}


// fonction d'affichage d'histogramme
void afficheHistogramme (DescripteurAudio d){
  int i,j;
  /* affichage du histogramme */
  if (d.histogramme!=NULL) {//<-- verification si non-null
    for(i=0; i<d.tailleDuDescripteur; i++){
      // affichage de grille pour les raisons visuelles 
      for(j=0; j<d.nombreDesIntervalles; j++){
        printf("--");
      }
      printf("\n|");
      for(j=0; j<d.nombreDesIntervalles; j++) {
        if(d.histogramme[i][j]==1){
          // les 1s dans l'histogramme sont affichés en rouge
					printf("\x1b[31m%d",d.histogramme[i][j]);
					printf("\x1b[0m|");
				}else
					printf("%d|",d.histogramme[i][j]); // les 0s sont affichsé en blanc
      }
      printf("\n|");  
    }
    for(j=0; j<d.nombreDesIntervalles; j++)
        printf("___"); // l'affichage de la grille de l'histogramme
  } 
  else 
    printf("L'histogramme du descripteur %s est vide.\n",d.nom); 
}


// fonction d'affichage de vectNombre
void afficheVectNombre (DescripteurAudio d){
  for (int i=0; i<d.nombreDesIntervalles; i++){
    printf(" %d", d.vectNombre[i]);
  }
}


// affichage de vectEndroit
void afficheVectEndroit (DescripteurAudio d){
  for (int i=0; i<d.tailleDuDescripteur; i++){
    printf(" %d", d.vectEndroit[i]);
  }
}


// fonction d'affichage de DescripteurAudio - nom, Id et taille
void afficheDescripteurAudio(DescripteurAudio d){
	printf("*** Audio = %s | ID = %d | taille = %d ***",d.nom,d.ID, d.tailleDuDescripteur);
}

/* ??? */
float distanceDescripteurAudio(DescripteurAudio* d1, DescripteurAudio* d2, float* endroitLePlusPertinant){
  /* initialisation des variables locales */
  int i,j;
  int n=200; /* choix de decalage du fichier plus petit par rapport au fichier plus grand (n=1024, 2048, 4096 ou 8192 points) */
  int diffEndroit=0;
  int start;
  float endroitDistanceMin;
  /* on initialise distance et min a un nombre tres grand afin de pouvoir le diminuer avec des nombres minimaux trouvés lors de l'iteration de vectEndroit */
  float distance = 1000000000; 
  float min = 1000000000;
  /* comparaison de nombre des intervalles de chaque descripteur */
  if (d1->nombreDesIntervalles!= d2->nombreDesIntervalles){
    printf("\n\n\n&&&&&5 Il faut mettre a jour l'indexation ! &&&&&\n\n\n");
    EXIT_FAILURE; 
  }
  start = 0;
  /* cas 1 : d1 plus petit | d2 plus grand */
  if  (d2->tailleDuDescripteur > d1->tailleDuDescripteur){ 
    for(i=0; (start + d1->tailleDuDescripteur <= d2->tailleDuDescripteur); i++){
      /* on calcule le decalage du plus grand fichier */
      start=n*i;
      /* on verifie si le distance est minimal */
      if (distance<min){
        min=distance;
        endroitDistanceMin=i-1;
      }
      diffEndroit=0; // reinitialisation de la differance entre deux vecteurs vectEndroit 
      distance=0;        
      // on entre dans la boucle pour comparer directement les vecteurs "vectEndroit" de 2 descipriteurs 
      for (j=0; j < d1->tailleDuDescripteur  ; j++){
        // on arrete l'iteration quand on depasse la taille du plus grand fichier 
        if ( (start+j) > d2->tailleDuDescripteur){
          diffEndroit += d1->tailleDuDescripteur-j;
          distance+=diffEndroit;
          break;
        }
        // calcule de differance entre la frequance de d1 et la frequance de d2 
        diffEndroit = d2->vectEndroit[start+j] - d1->vectEndroit[j];
        // si la differance est negative, on change le sign 
        if (diffEndroit<0)
          diffEndroit = - diffEndroit;
        // on ajoute la differance au distance 
        distance+=diffEndroit;
      }
	  }
    // on verifie si le distance est minimal apres le dernier parcours 
    if (distance<min){
      min=distance;
      endroitDistanceMin=i;
    }
    // on recalcule le distance pour obtenir un pourcentage de differance entre les fichiers
    distance = (min / (d1->nombreDesIntervalles/2*d1->tailleDuDescripteur)) * n; 
  }
  // cas 2 : d1 plus grand | d2 plus petit --> memes calcules que dans le cas 1 sauf que on inverse les descipriteurs
  else {
    for(i=0; (start+d2->tailleDuDescripteur <= d1->tailleDuDescripteur); i++){
      start=n*i;
      if (distance<min){
        min=distance;
        endroitDistanceMin=i-1;
      }
      diffEndroit=0;
      distance=0;
      for (int j=0; j < d2->tailleDuDescripteur ; j++){
        if ( (start+j)>d1->tailleDuDescripteur){
          diffEndroit += d2->tailleDuDescripteur-j;
          distance+=diffEndroit;
          break;
        }
        diffEndroit = d1->vectEndroit[start+j] - d2->vectEndroit[j];
        if (diffEndroit<0)
          diffEndroit = - diffEndroit;
        distance+=diffEndroit;
      }
	  }
    if (distance<min){
      min=distance;
      endroitDistanceMin=i;
    }
    distance = min;
    distance = (distance / (d2->nombreDesIntervalles/2*d2->tailleDuDescripteur)) * n/2;
  }

  /* recuperation de l'endroit pour lequel le distance est min dans un poiteur qui est passé en parametre */
  *endroitLePlusPertinant = endroitDistanceMin * n/16384; /* 16284 = 2^14 --> 1s */
	return distance;
}

  
  
//sauvegarde du descripteur dans un fichier txt
int sauvegarderDescripteurAudio(FILE* fichier,DescripteurAudio d){
  int i;
  /* sauvegarde d'identifiant, du nom, de la taille et du nombre des intervalles */
	fprintf(fichier," %d %s %d %d\n",d.ID,d.nom, d.tailleDuDescripteur, d.nombreDesIntervalles);
  /* sauvegarde du vectNombre */
	for (i=0; i<d.nombreDesIntervalles; i++){
	  fprintf(fichier, " %d", d.vectNombre[i]);
	}
	fprintf(fichier,"\n");
  /* sauvegarde du vectEndroit */
	for (i=0; i<d.tailleDuDescripteur; i++){
	  fprintf(fichier, " %d", d.vectEndroit[i]);
	}
	fprintf(fichier,"\n");
	return 0;
}

// charge un descripteur depuis un fichier de sauvegarde
DescripteurAudio chargerDescripteurAudio(FILE* fichier){
	int i;
	DescripteurAudio d;
  // charchement d'identifiant, du nom, de la taille et du nombre des intervalles
	fscanf(fichier," %d %s %d %d\n",&d.ID,d.nom, &d.tailleDuDescripteur, &d.nombreDesIntervalles);

	// Reservation de la memoire pour vectNombre
	d.vectNombre = (int*)malloc(d.nombreDesIntervalles*sizeof(int));

  // Reservation de la memoire pour vectEndroit
	d.vectEndroit = (int*)malloc(d.tailleDuDescripteur*sizeof(int));
	
	// charchement du vectNombre
	for (i=0; i<d.nombreDesIntervalles; i++){
	  fscanf(fichier, " %d", &d.vectNombre[i]);
	}
	fscanf(fichier,"\n");
	// charchement du vectEndroit
	for (i=0; i<d.tailleDuDescripteur; i++){
	  fscanf(fichier, " %d", &d.vectEndroit[i]);
	}
	fscanf(fichier,"\n");
	return d;
}



 
/*
// Fonction Taille fichier binaire
unsigned long tailleFichierBin(FILE *ficbin){
  fseek(ficbin,0,SEEK_END);
  unsigned long  taille= ftell(ficbin);
  return taille;
}
*/


/* Foncion qui cree un descripteur audio a partir d'un fichier bin */
/*
DescripteurAudio creerDescripteurAudioBin(char nomDuFichier[TAILLE_MAX+1],int nombreDesIntervalles, int id){
  // initialisation des variables locales
    int i,j;
    DescripteurAudio d;
	
	  strcpy(d.nom,nomDuFichier); // mise a jour du nom
	  d.ID = id; // mise a jour de l'id
    d.nombreDesIntervalles = nombreDesIntervalles;
  	d.tailleDuDescripteur = 0;
  
    // char maCommande[TAILLE_MAX+1] = "wc -l ./data/TEST_SON/"; // chemin depuis le main 
    
    char maCommande[TAILLE_MAX+1] = "wc -l ../../../data/TEST_SON/";
	  strcat(maCommande,d.nom); 
    //   ./data/TEST_SON/ --> pour compiler depuis le main

    //Creation d'un nouveau fichier binaire
    strcat(maCommande," > fbin");

    system(maCommande);
		//puts("B");
    FILE * ficbin = NULL ;

    //ficbin = fopen("nouveauFichierBinaire", "wb+"); //w+ lecture ecriture et création si fichier n'existe pas;

    ficbin = fopen("fbin","rb");
    if (ficbin == NULL){
    	printf("Erreur <-- ouverture du fichier .bin\n");
    	exit(EXIT_FAILURE);
    }
  //  int tabbin[10000] ;

	//d.tailleDuDescripteur = fread(tabbin, sizeof(int), 10000, ficbin);
    //puts("C");
    
	//Taille du fichier.bin
 
 // d.tailleDuDescripteur= tailleFichierBin(ficbin);
  
   //printf("taille = %d\n",d.tailleDuDescripteur );

  fclose(ficbin); 

	//lecture du fichier audio
	char chemin[TAILLE_MAX+1] = "../../../data/TEST_SON/";
	//system("")
	strcat(chemin,nomDuFichier);

	FILE* ficbin2 = fopen(chemin,"rb"); // 

  // Creation du d.histogramme
   double varTemp=0;
  float borneMax=0;
  float borneMin=0;
  float dist=1.2/(float)nombreDesIntervalles;
  //char c;

  //puts("L'erreur arrive apres ce puts");
  
  double tabbin[1010000]; // bloc inconn
  //puts("avant tabbin !!!");
  int 	nb = fread(tabbin, sizeof(double),1010000, ficbin2);
  //puts("apres tabbin !!!");

		// la ligne precedente permet de lire le contenu accessible
		// depuis ficbin par bloc de 10000 int au max
		// et range cela dans le tableau tabbin
		// s'il y a moins de 10000 int ds le fichier, alors nb 
		// contiendra le nb d'int lus
     // Reservation de la memoire pour l'histogramme
     d.tailleDuDescripteur=nb;

  d.histogramme = (int**)malloc(d.tailleDuDescripteur*sizeof(int*));

	for(i=0; i<d.tailleDuDescripteur; i++){
		d.histogramme[i] = (int*)malloc(d.nombreDesIntervalles*sizeof(int));
	}

  // Reservation de la memoire pour vectNombre
	d.vectNombre = (int*)malloc(d.nombreDesIntervalles*sizeof(int));
  // initialisation des toutes ses valeurs à 0
  for(i=0; i<d.nombreDesIntervalles; i++){
		d.vectNombre[i] = 0;
	}
  // Reservation de la memoire pour vectEndroit
	d.vectEndroit = (int*)malloc(d.tailleDuDescripteur*sizeof(int));
	// initialisation des toutes ses valeurs à 0
  for(i=0; i<d.tailleDuDescripteur; i++){
    d.vectEndroit[i] = 0;
	}

	//	printf("nb = %d", nb);
  
		if (feof(ficbin))
			printf("\n arret : fin fichier\n") ;
		if (ferror(ficbin))
			printf("\n arret : erreur lecture\n") ;
		
		// affichage contenu du fichier binaire sous la forme d'int
  printf("\n");
	//	for (int i = 0 ; i < d.tailleDuDescripteur ; i++) 
	//		printf("%d - ", tabbin[i]) ;
		
	
//	printf("taille du desc %d, nombre des intervalles = %d\n",d.tailleDuDescripteur,d.nombreDesIntervalles);

  for(i=0; i<d.tailleDuDescripteur; i++){
    //Recuperation de la valeur temporaire dans le ficier .bin
    fscanf(ficbin2, " %lf\n", &varTemp);

    //Il faut afficher impérativement le fichier

    varTemp = tabbin[i]; // ok
   //printf("ok ok ok %lf\n",varTemp);

    //printf("i=%d",i);puts("");
    // fread() pour des fichiers .bin
    for(j=0; j<d.nombreDesIntervalles; j++){
      // Calcule des bornes de l'intervalle j  
      borneMin = -0.6+j*dist;
      borneMax = -0.6+(j+1)*dist;
      //printf("j=%d", j);puts("");
      // On remplis l'histogramme avec : 1 si valeur est contenue dans l'intervalle et 0 sinon. Si la vleur est dehors la borne minimal totale et la borne maximal toale, on affiche une message d'erreur pour pouvoir l'augmenter l'intervalle. 
    
      if (varTemp<(-0.6) || varTemp>0.6){
				//printf("\x1b[31m Erreur --> valeurs hors les bornes !!! \x1b[0m\n");
			}else 
			if (varTemp>borneMin && varTemp<=borneMax){
        d.histogramme[i][j]=1;
			//	puts("1");
        d.vectNombre[j]+=1;
        d.vectEndroit[i]+=j;
        
				//printf("%f est compris entre %f et %f\n",varTemp,borneMin,borneMax);
      }else {
				//printf("i=%d j=%d",i,j); // PROBLEME à i=42 j=0 
        d.histogramme[i][j]=0;
				//printf("%f n'est pas compris entre %f et %f\n",varTemp,borneMin,borneMax);
			}
		}
	}
  //puts("L'erreur arrive apres ce puts\n");
	//puts("I");

  // Affichage de la taille d'histogramme
 // printf("\nTaille du descripteur %s = %d par %d\n", d.nom, d.tailleDuDescripteur,d.nombreDesIntervalles);
  fclose(ficbin2);
	return d;
}
*/
