// Fatima-Zohra, Kosma, Thomas, Bastian : Dans ce fichier nous avons codé les fonctions qui serviront dans le main affin de réaliser l'indexation des fichiers dans la base de donnée ainsi que les différentes recherches disponible :
// Fatima-Zohra / Bastian : Indexation et recherche d'image
// Kosma : Indexation et recherche d'audio
// Thomas : Indexation et recherche des textes / d'un mot
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "indexation.h"

// fonction permettant de changer la couleur du terminal
void couleur(char* couleur){
	if(strcmp(couleur,"noir")==0){
		printf("\x1b[30m");
	}else if(strcmp(couleur,"rouge")==0){
		printf("\x1b[31m");
	}else if(strcmp(couleur,"vert")==0){
		printf("\x1b[32m");
	}else if(strcmp(couleur,"jaune")==0){
		printf("\x1b[33m");
	}else if(strcmp(couleur,"bleu")==0){
		printf("\x1b[34m");
	}else if(strcmp(couleur,"magenta")==0){
		printf("\x1b[35m");
	}else if(strcmp(couleur,"cyan")==0){
		printf("\x1b[36m");
	}else if(strcmp(couleur,"blanc")==0){
		printf("\x1b[37m");
	}else if(strcmp(couleur,"reset")==0){
		printf("\x1b[0m");
	}
}

// Fonction d'affichage de l'ereur dans le cas le nom de fichier entré par l'utilisateur est incorrecte
void error(){
	couleur("rouge");
	puts("======================================================");
	puts("||         Le fichier recherché n'existe pas        ||");
	puts("|| Vérifiez son nom ou rajoutez le dans le dossier :||");
	puts("||                Fichier_Recherche                 ||");
	puts("======================================================");
	couleur("reset");
}

// fonction d'indexation des fichiers image
// en entrée : une pile de descripteur image, une pile de liens entre image et descripteur, le nombre de bits de quantification et le pointeur vers l'id courant des images pour le mettre à jour
int indexation_fichiers_images(PileDescripteurImage* p,PileLien* l,int nmb_bits,int* ID){
  int pourcentage = 0; // affichage de la barre de chargement 
	// vider la pile si elle est deja remplie
	if(p->taille > 0){
		freePileDescripteurImage(p);
		//puts("La pile de descripteur à été free");
	}
	// vider la pile de liens si deja remplie 
	if(l->taille > 0){
		freePileLien(l);
		//puts("La pile de liens à été free");
	}

	// récupération du nom des fichiers à indexer 
	system("ls ./data/TEST_NB | grep '.txt' > temp");
	system("ls ./data/TEST_RGB | grep '.txt' >> temp");
	system("wc -l temp > temp2");
	int max = 0;

	// récupération du nombre de fichiers à indexer
	FILE* fichier = NULL;
	fichier = fopen("temp2","r");
	fscanf(fichier,"%d",&max);
	fclose(fichier);
	/*
	printf("============================\n");
	printf("Il y a %d fichiers à indexer\n",max);
	printf("============================\n");
	*/

	// indexation de chacun de ces fichiers
	char fichierCourant[TAILLE_MOT+1];
	fichier = fopen("temp","r");
	couleur("jaune");
  printProgressBar(0);
  fflush(stdout);

	for(int i = 0;i<max;i++){
		fscanf(fichier,"%s",fichierCourant);
		toutDescripteurImage(fichierCourant,p,l,nmb_bits,i);
    pourcentage = ((i+1)*100)/max;
    printProgressBar(pourcentage);
    fflush(stdout);
	}
	couleur("vert");
  printProgressBar(100);
  fflush(stdout);
  couleur("reset");
  printf("\n");
	*ID = max;

	// fermeture des fichier et suppression des fichiers inutiles
	fclose(fichier);
	remove("temp");
	remove("temp2");
	return 0;
}


// recherche d'un fichier image 
// en entrée : une pile de descripteur image, une pile de liens entre image et descripteur, le nombre de bits de quantification et le nombre de résultats attendus
int rechercher_image(PileDescripteurImage* p,PileLien* l,int nBits,int n_resultats){
	int id_fichier_a_ouvrir = -1;
	char nom[TAILLE_MAX+1];

	// récupération du nom du fichier à rechercher
	printf("Entrez le nom de votre fichier : ");
	scanf("%s",nom);
	strcat(nom,".txt");
	if(strlen(nom)>TAILLE_MOT+1){
		printf("Ce nom de fichier est trop long, veuillez raccourcir le nom de votre fichier avant de réésayer !");
		return 1;
	}
	// récupération du descripteur correspondant
	DescripteurImage fichier_recherche;
	if(dejaVu(nom,*l)>=0){
		affectDescripteurImage(getDescripteurImageViaNom(*p,nom),&fichier_recherche);
	}else{
		char chemin[TAILLE_MAX+1] = "../../Fichier_Recherche/";
		char chemin_existe[TAILLE_MAX+1] = "./Fichier_Recherche/";
		strcat(chemin,nom);
		strcat(chemin_existe,nom);
		if( access( chemin_existe , F_OK ) == 0 ){
			fichier_recherche = creerDescripteurImage(chemin,nBits,-1);
		}else{
			error();
			return 2;
		}
	}
	//afficheDescripteurImage(fichier_recherche); // deboggage
	
	// calcul des distances avec les autres descripteurs
	int* id = NULL; // identificateur
	int* di = NULL; // distances
	di = (int*)malloc(p->taille*sizeof(int));
	id = (int*)malloc(p->taille*sizeof(int));
	if(di != NULL && id != NULL){
		for(int i = 0;i<n_resultats;i++){
			di[i] = -1;
			id[i] = -1;
		}
	}else{
		puts("ERREUR, Veuillez relancer la recherche");
		return 2;
	}
	// calcul des distances 
	int distance = 0;
	DescripteurImage* autre_desc;
	for(int i = 0;i<p->taille;i++){
		autre_desc = getDescripteurImage(*p,i);
		distance = distanceDescripteurImage(fichier_recherche,*autre_desc);
		di[i] = distance;
		id[i] = getIdDescripteurImage(*autre_desc);
	}
	puts("");

	// récupération des fichiers ressemblants
	printf("Les fichiers ressemblants sont :\n");
	int min;
	int indexe;
	for(int j = 0;j<n_resultats;j++){ // boucle sur le nombre de resultats définis
		min = -1;
		indexe = -1;
		for(int i = 0;i<p->taille;i++){ // boucle sur toutes les distances
			if(di[i]>-1 && (min == -1 || di[i]>min) ){ // si la distance est valide et que aucune distances n'a été trouvée
				min = di[i];
				indexe = i;
				if(j == 0) {
          id_fichier_a_ouvrir = i;
        }
			}
		}

		// affichage du résultat si trouvé
		if(min!=0){
			char nom_sans_extension[10] = "";
			strncat(nom_sans_extension,getNomDescripteurImage(*getDescripteurImageViaId(*p,id[indexe])),strlen(getNomDescripteurImage(*getDescripteurImageViaId(*p,id[indexe])))-4);
			printf("[%d] %s ressemblance = %ld%%\n",j+1,nom_sans_extension,100*di[indexe]/getTaille(&fichier_recherche));
			di[indexe] = -1;
		}
	}

	// ouverture du fichier le plus ressemblant 
	char commande[TAILLE_MAX+1] = "eog ./data/";
	if(getDescripteurImageViaId(*p,id[id_fichier_a_ouvrir])->histogramme.couleur){
		strcat(commande,"TEST_RGB/");
	}else{
		strcat(commande,"TEST_NB/");
	}
	strncat(commande,getNomDescripteurImage(*getDescripteurImageViaId(*p,id[id_fichier_a_ouvrir])),strlen(getNomDescripteurImage(*getDescripteurImageViaId(*p,id[id_fichier_a_ouvrir])))-3);
	if(getDescripteurImageViaId(*p,id[id_fichier_a_ouvrir])->histogramme.couleur){
		strcat(commande,"jpg");
	}else{
		strcat(commande,"bmp");
	}
	strcat(commande," &");
	system(commande);
	
	free(id);
	free(di);
	return 0;
}



/* @@@@@@@@@@@@ Inexation et Recherche Audio @@@@@@@@@@@@@@ */
/* Indexation des fichiers audio */
int indexation_fichiers_audio(PileDescripteurAudio* p,PileLien* l,int nombreDesIntervales,int* ID){
	int pourcentage;

	// vider la pile si elle est deja remplie
	if(p->taille > 0){
		freePileDescripteurAudio(p);
		//puts("La pile de descripteur a été free");
	}

	// vider la pile de liens si deja remplie 
	if(l->taille > 0){
		freePileLien(l);
		//puts("La pile de liens a été free");
	}

	// récupération du nom des fichiers à indexer 
	//system("ls ./data/TEST_SON | grep '.bin' > tempSON");
	system("ls ./data/TEST_SON | grep '.txt' > tempSON");
	system("wc -l tempSON > tempSON2");
	int max = 0;

	// récupération du nombre de fichiers à indexer
	FILE* fichier = NULL;
	fichier = fopen("tempSON2","r");
	fscanf(fichier,"%d",&max);
	fclose(fichier);
	//printf("============================\n");
	//printf("Il y a %d fichiers à indexer\n",max);
	//printf("============================\n");

	// indexation de chacun de ces fichiers
	char fichierCourant[TAILLE_MOT+1];
	fichier = fopen("tempSON","r");
	couleur("jaune");
  printProgressBar(0);
  fflush(stdout);
	for(int i = 0;i<max;i++){
		fscanf(fichier,"%s",fichierCourant);
		toutDescripteurAudio(fichierCourant,p,l,nombreDesIntervales,i);
    pourcentage = ((i+1)*100)/max;
    printProgressBar(pourcentage);
    fflush(stdout);
	}
	couleur("vert");
  printProgressBar(100);
  fflush(stdout);
  couleur("reset");
  printf("\n");
	*ID = max;

	// fermeture des fichier et suppression des fichiers inutiles
	fclose(fichier);
	remove("tempSON");
	remove("tempSON2");
	return 0;
}


/* Recherche d'un fichier audio */
int rechercher_audio(PileDescripteurAudio* p,PileLien* l,int nombreDesIntervales,int n_resultats){
	bool ajout_par_utilisateur = false;
	if(nombreDesIntervales==-1){
		puts("ERREUR, nombre d'intervalles negatif");
		return 1;
	}
	int* id = NULL; // identificateur
	float* di = NULL; // distances
	di = (float*)malloc(p->taille*sizeof(float));
	id = (int*)malloc(p->taille*sizeof(int));
	if(di != NULL && id != NULL){
		for(int i = 0;i<n_resultats;i++){
			di[i] = -1;
			id[i] = -1;
		}
	}

	// fichier déjà dans la base de donnée ou ajouté par l'utilisateur
	char nom[TAILLE_MAX+1];
	printf("Entrez le nom de votre fichier : ");
	scanf("%s",nom);
	strcat(nom,".txt");
	
	if(strlen(nom)>TAILLE_MOT+1){
		printf("Ce nom de fichier est trop long, veuillez raccourcir le nom de votre fichier avant de réésayer !");
		return 1;
	}
	
	DescripteurAudio fichier_recherche;
  /* si le descripteur etait deja vu (existe dans la base des donnes) on l'affect, sinon (il n'existe pas dans la base de donnes alors soit ilest ajoute par utilisateur, soit il n'existe pas du tout) on le cherche dans le repertoir Fichier_Recherche */
	if(dejaVu(nom,*l)>=0){ 
		affectDescripteurAudio(getDescripteurAudioViaNom(*p,nom),&fichier_recherche);
	}else{
		char chemin[TAILLE_MAX+1] = "../../Fichier_Recherche/";
		char chemin_existe[TAILLE_MAX+1] = "./Fichier_Recherche/";
		strcat(chemin,nom);
		strcat(chemin_existe,nom);
		if( access( chemin_existe , F_OK ) == 0 ){
			fichier_recherche = creerDescripteurAudio(chemin,nombreDesIntervales,-1);
			ajout_par_utilisateur = true;
		}else{
			error();
			return 2;
		}
	}
	
	
	/* calcul des distances */
	float distance = 0;
	float meilleurEndroit = -1.0;
  float* tableauMeilleurEndroit = NULL;
  tableauMeilleurEndroit = (float*)malloc(p->taille*sizeof(float));
	DescripteurAudio* autre_desc;
	for(int i = 0;i<p->taille;i++){
		autre_desc = getDescripteurAudio(*p,i);
		distance = distanceDescripteurAudio(autre_desc, &fichier_recherche, &meilleurEndroit); // on appelle la fonction de calcule de distance
		di[i] = distance; // on sauvegarde le distance dans le tableau di[]
		id[i] = getIdDescripteurAudio(*autre_desc); // on sauvgarde l'identifiant dans le tableau id[]
    tableauMeilleurEndroit[i]=meilleurEndroit;
	}
	puts("");
	printf("Les fichiers ressemblants sont :\n");
	float min;
	int indexe;
  int nb_resultatsAffiches=0;
  int nb_resultatsNegliges=0;
  // boucle sur le nombre de resultats définis + on prend en compte le fichier recherche (on ne l'affiche pas) 
	static int id_fichier_a_ouvrir;
  while ( (nb_resultatsAffiches+nb_resultatsNegliges)<=n_resultats && (nb_resultatsAffiches+nb_resultatsNegliges)<p->taille){
		min = -1;
		indexe = -1;
		// boucle sur toutes les distances
		for(int i = 0;i<p->taille;i++){ 
      // si la distance est valide et que soit aucune distances n'a été trouvée
			if(di[i]>=0 && (min == -1 || di[i]<min) ){ 
				min = di[i];
				indexe = i;
			}
		}
		
    // recuperation du nom de descripteur et affichage de ressemblance
    char* nomDescripteurCourant;
    nomDescripteurCourant = getNomDescripteurAudio(*getDescripteurAudioViaId(*p,id[indexe]));
    if (strcmp(nomDescripteurCourant, nom)!=0){
			char nom_sans_extension[TAILLE_MOT+1] = "";
      strncat(nom_sans_extension, getNomDescripteurAudio(*getDescripteurAudioViaId(*p,id[indexe])),strlen(getNomDescripteurAudio(*getDescripteurAudioViaId(*p,id[indexe])))-4);
      float ressemblance = 100 - di[indexe]; // changement de différence min vers ressemblance max
      printf("[%d] %s : ressemblance = %.2f %%  \n",nb_resultatsAffiches+1,nom_sans_extension,ressemblance); // affichage des fichiers correspondant avec le pourcentage de ressemblance
			if(nb_resultatsAffiches==0){ 
				id_fichier_a_ouvrir = indexe;
			}
      // affichage de l'endroit le plus pertinant en secondes (dans if) ou dans minutes et secondes (dans else)
      if (tableauMeilleurEndroit[indexe]<60){
        printf("    L'endroit le plus pertinant est : %.2f seconde(s)\n", tableauMeilleurEndroit[indexe]);
      nb_resultatsAffiches++;
      }
      else {
        int minutes = tableauMeilleurEndroit[indexe]/60;
        printf("    L'endroit le plus pertinant est : %d minute(s) et %.2f seconde(s)\n", minutes, tableauMeilleurEndroit[indexe]-minutes*60);
      nb_resultatsAffiches++;
      }
    }
    else{
      if(nb_resultatsNegliges==0){
				id_fichier_a_ouvrir = indexe;
			}
      nb_resultatsNegliges++;
    }
		di[indexe] = -1;
	}

  /* $$$$$ l'affichage (l'ecoute) de fichier audio  $$$$$ */

  /* creation de commande pour ecouter le fichier le plus ressemblant */
  char commandeAfficherAudio[80] = "play ./data/TEST_SON/";
  int lenghtNom = strlen(getNomDescripteurAudio(*getDescripteurAudioViaId(*p,id_fichier_a_ouvrir)));
   
  char cheminAudio[80] = "./data/TEST_SON/";
  strncat(cheminAudio, nom,lenghtNom-3);
  strcat(cheminAudio,"wav");
  
    strncat(commandeAfficherAudio, getNomDescripteurAudio(*getDescripteurAudioViaId(*p,id_fichier_a_ouvrir)),lenghtNom-3);
    strcat(commandeAfficherAudio,"wav trim ");
    char result[50]; 
    float num = tableauMeilleurEndroit[id_fichier_a_ouvrir];
    int num2 = (int) num;
    
    int tempsAudioRecherche = 0;
    if (ajout_par_utilisateur == false){
      tempsAudioRecherche = (int) getDescripteurAudioViaNom(*p, nom)->tailleDuDescripteur/16384;
    }
    else {
      tempsAudioRecherche = (int) fichier_recherche.tailleDuDescripteur/16384;
    }
    
    // recuperation de l'endroit au format : minutes:secondes ou heures:minutes:secondes selon le cas
    while (num2>=60){
      num2-=60;
    }
    if (num>=3600){
      sprintf(result, "%d:", (int)num/3600);
    }
    sprintf(result, "%d:%d", (int)num/60, num2); 
    strcat(commandeAfficherAudio, result);
    
    int ouvert=-1;
    int c;
    
    // recuperation du nom final de fichier (sans le terminaison bin)
    char nomFinal[TAILLE_MOT+1];
    nomFinal[0]= '\0';
    strncat(nomFinal, getNomDescripteurAudio(*getDescripteurAudioViaId(*p,id_fichier_a_ouvrir)), strlen(getNomDescripteurAudio(*getDescripteurAudioViaId(*p,id_fichier_a_ouvrir)))-3);
    // ajoute de "wav" au "nomDuFichier."
    strcat(nomFinal, "wav");
    // boucle pour demander a l'utilisateur s'il souhaite ecouter le fichier audio
    do {
    	while ((c = getchar()) != '\n' && c != EOF) { }
      printf("\nVoulez-vous écouter le fichier %s ?\nSi oui, tapez 1, sinon tapez 2 : ", nomFinal);
      scanf("%d", &ouvert);
    } while (ouvert!=1 && ouvert!=2);
  
    
    // ####### Preparation de la commande qui permetra d'ecouter fichier audio ########
    char trim2[TAILLE_MOT+1];
      if (ouvert==1){

        if (num>tempsAudioRecherche && (num+tempsAudioRecherche+4)<=(getDescripteurAudioViaId(*p,id_fichier_a_ouvrir)->tailleDuDescripteur)/16384){

          int temps2 = tempsAudioRecherche+4;
            int temps22 = temps2;
            while (temps22>=60){
              temps22-=60;
            }
            // si le fichier a afficher est suffisament grand, on l'affiche le fichier avec un marge a la fin
        sprintf(trim2, "%d:%d", (int)(temps2)/60, temps22); 
        strcat(commandeAfficherAudio, " ");
        strcat(commandeAfficherAudio, trim2);
        }

		// si le fichier est petit on l'affiche en totalite (jingle_fi fait 2 secondes, il n'y a pas besoin de faire un trim)
		if(tempsAudioRecherche>(getDescripteurAudioViaId(*p,id_fichier_a_ouvrir)->tailleDuDescripteur)/16384){
			char commandeTropLong[100] = "play ./data/TEST_SON/";
			strncat(commandeTropLong,getNomDescripteurAudio(*getDescripteurAudioViaId(*p,id_fichier_a_ouvrir)),strlen(getNomDescripteurAudio(*getDescripteurAudioViaId(*p,id_fichier_a_ouvrir)))-4);
			strcat(commandeTropLong,".wav");
			printf("\nExecution de : system(%s);\n",commandeTropLong);
			system(commandeTropLong);
		}else{ // si le fichier est assez grand, on passe a execution de commande
      printf("\nExecution de : system(%s);\n",commandeAfficherAudio);
      system(commandeAfficherAudio); // execution de la commande d'ecoute du fichier audio au terminal
    }
  }
  // ###### fin de la commande qui permetra d'ecouter le fichier audio ######
	free(id); // liberation de memoire pour le vecteur id
	free(di); // liberation de memoire pour le vecteur di
	return 0;
}



/////////////////////
// fichiers Textes //
/////////////////////

/* Indexe les fichier textes de la base de données dans la pile de descripteurs texte p et la pile de lien l selon le paramètre d'indexation nmb_mots et l'identifiant ID */
int indexation_fichiers_textes(PileDescripteurTexte* p,PileLien* l,int nmb_mots,int* ID){
	int pourcentage;

	// vider la pile si elle est deja remplie
	if(p->taille > 0){
		freePileDescripteurTexte(p);
		//puts("La pile de descripteur à été free");
	}
	// vider la pile de liens si deja remplie 
	if(l->taille > 0){
		freePileLien(l);
		//puts("La pile de liens à été free");
	}

	// récupération du nom des fichiers à indexer 
	system("ls ./data/Textes | grep '.xml' > temp");
	system("wc -l temp > temp2");
	int max = 0;

	// récupération du nombre de fichiers à indexer
	FILE* fichier = NULL;
	fichier = fopen("temp2","r");
	fscanf(fichier,"%d",&max);
	fclose(fichier);
	/*
	printf("============================\n");
	printf("Il y a %d fichiers à indexer\n",max);
	printf("============================\n");
	*/

	// indexation de chacun de ces fichiers
	char fichierCourant[TAILLE_MAX+1];
	fichier = fopen("temp","r");
	couleur("jaune");
  printProgressBar(0);
  fflush(stdout);
	for(int i = 0;i<max;i++){
		fscanf(fichier,"%s",fichierCourant);
		toutDescripteurTexte(fichierCourant,p,l,nmb_mots,i);
    pourcentage = ((i+1)*100)/max;
    printProgressBar(pourcentage);
    fflush(stdout);
	}
	couleur("vert");
  printProgressBar(100);
  fflush(stdout);
  couleur("reset");
  printf("\n");
	*ID = max;

	// fermeture des fichier et suppression des fichiers inutiles
	fclose(fichier);
	remove("temp");
	remove("temp2");
	return 0;
}

/* Recherche les n_resultats fichiers ressemblant au fichier lu dans la fonction selon la pile de descripteurs texte p, la pile de lien l et le paramètre d'indexation nmb_mots */
int rechercher_texte(PileDescripteurTexte* p,PileLien* l,int n_mots,int n_resultats){
	//bool ajoute_par_utilisateur = false;
	char nom[TAILLE_MAX+1];
	printf("Entrez le nom de votre fichier (sans l'extension) : ");
	scanf("%s",nom);
	strcat(nom,".xml");
	
	if(strlen(nom)>75){
		printf("Ce nom de fichier est trop long, veuillez raccourcir le nom de votre fichier avant de réésayer !");
		return 1;
	}

	// fichier déjà dans la base de donnée ou ajouté par l'utilisateur
	DescripteurTexte fichier_recherche;
	if(dejaVu(nom,*l)>=0){
		affectDescripteurTexte(getDescripteurTexteViaNom(*p,nom),&fichier_recherche);
		puts("Le fichier est présent dans la base de donnée.");
	}else{
		char chemin[TAILLE_MAX+1] = "../../Fichier_Recherche/";
		char chemin_existe[TAILLE_MAX+1] = "./Fichier_Recherche/";
		strcat(chemin,nom);
		strcat(chemin_existe,nom);
		if( access( chemin_existe , F_OK ) == 0 ){
			fichier_recherche = creerDescripteurTexte(chemin,n_mots,-2);
		}else{
			error();
			return 2;
		}
	}
	//afficheDescripteurImage(fichier_recherche);
	
	int* id = NULL; // identificateur
	int* di = NULL; // distances
	di = (int*)malloc(p->taille*sizeof(int));
	id = (int*)malloc(p->taille*sizeof(int));;
	
	if(di != NULL && id != NULL){
		for(int i = 0;i<n_resultats;i++){
			di[i] = -1;
			id[i] = -1;
		}
	}else{
		puts("ERREUR, recherche impossible");
		return 2;
	}
	
	// calcul des distances 
	int distance = 0;
	int id_fichier_a_ouvrir = -1;
	DescripteurTexte* autre_desc;
	for(int i = 0;i<p->taille;i++){
		autre_desc = getDescripteurTexte(*p,i);
		distance = distanceDescripteurTexte(fichier_recherche,*autre_desc);
		//printf("distance entre %s et %s = %d\n",getNomDescripteurTexte(fichier_recherche),getNomDescripteurTexte(*autre_desc),distance);
		di[i] = distance;
		id[i] = getIdDescripteurTexte(*autre_desc);
	}
	puts("");

	printf("Rquête fichier : \"%s\"\n\n", nom);
  printf("Résultats (fichier -> nombre de mots-clés communs) :\n");
	int min;
	//int idmin;
	int indexe;
	int nombre_fichiers_trouves = 0;
	for(int j = 0;j<n_resultats;j++){ // boucle sur le nombre de resultats définis
		min = -1;
		//idmin = -1;
		indexe = -1;
		for(int i = 0;i<p->taille;i++){ // boucle sur toutes les distances
			if(di[i]>-1 && (min == -1 || di[i]>min) ){ // si la distance est valide et que soit aucune distances n'a été trouvée
				min = di[i];
				//idmin = id[i];
				indexe = i;

				if(j == 0) {
          id_fichier_a_ouvrir = i;
        }
			}
		}

		if(min!=0){
			nombre_fichiers_trouves++;
			printf("%s -> %d\n",getNomDescripteurTexte(*getDescripteurTexteViaId(*p,id[indexe])),di[indexe]);
		}
		
		//printf("[%d] différence = %d\n",j,di[indexe]);
		di[indexe] = -1;
	}
	if(nombre_fichiers_trouves==0){
		puts("\nAucun dossier dans la base de donnée ne traite du même sujet.");
	} else {
    char commande[TAILLE_MAX+1] = "gedit ";
    char* nom_fichier_a_ouvrir = getNomDescripteurTexte(*getDescripteurTexteViaId(*p,id[id_fichier_a_ouvrir]));
		char chemin[TAILLE_MAX+1] = "./data/Textes/";
    strcat(commande, chemin);
		strcat(commande,nom_fichier_a_ouvrir);
		strcat(commande," &");
		//printf("\nexecution : %s\n",commande);
		system(commande);
  }

	free(id);
	free(di);
	return 0;
}

/* Recherche les n_resultats fichiers ressemblant au mot lu dans la fonction selon la pile de descripteurs texte */
int rechercher_mots_texte(PileDescripteurTexte* p,int n_resultats){
	char motLu[TAILLE_MAX+1];
  char mot[TAILLE_MAX+1];
  char c;
  int i;
  int j;
  
	printf("Entrez le mot : ");
	scanf("%s",motLu);
	
	/* Traitement du mot */
  i = 0;
  j = 0;
  c = motLu[i];
  while(c != '\0') {
    /* Si le caractère est une majuscule on le passe en minuscule */
    if('A' <= c && c <= 'Z') { 
      mot[j] = motLu[i] + 32; 
    }
    /* Si le caractère lu est accentué : À Â È É Ê Ë Î Ï Ù Û Ç (les minuscules aussi) on lui retire son accent */
    else if(c == '\xc3') {
      i++;
      c = motLu[i];
      if(c == '\x80' || c == '\x82' || c == '\xa0' || c == '\xa2') mot[j] = 'a'; 
      else if(c == '\x88' || c == '\x89' || c == '\x8a' || c == '\x8b' || c == '\xa8' || c == '\xa9' || c == '\xaa' || c == '\xab') mot[j] = 'e';
      else if(c == '\x8e' || c == '\xae' || c == '\x8f' || c == '\xaf') mot[j] = 'i';
      else if(c == '\x99' || c == '\x9b' || c == '\xb9' || c == '\xbb') mot[j] = 'u';
      else if(c == '\x87' || c == '\xa7') mot[j] = 'c';
      else { fprintf(stderr, "1.caractère inconnu\n"); return -1; }
    }
    /* Si le caractère est un e dans l'o : œ */
    else if(c == '\xc5') {
      i++;
      c = motLu[i];
      if(c == '\x92' || c == '\x93') {
        mot[j] = 'e';
        ++j;
        mot[j] = 'o';
      } else {
        fprintf(stderr, "2.caractère inconnu\n"); 
        return -2;
      }
    }
    else {
      mot[j] = motLu[i];
    }
    ++i;
    c = motLu[i];
    ++j;
  }

  mot[j] = c;

  int* id = NULL; // identificateur
	int* di = NULL; // distances
	di = (int*)malloc(p->taille*sizeof(int));
	id = (int*)malloc(p->taille*sizeof(int));;
	
	if(di != NULL && id != NULL){
		for(int i = 0;i<n_resultats;i++){
			di[i] = -1;
			id[i] = -1;
		}
	}else{
		puts("ERREUR, recherche impossible");
		return 2;
	}
	
	// calcul des distances 
	int distance = 0;
	DescripteurTexte* autre_desc;
	for(int i = 0;i<p->taille;i++){
		autre_desc = getDescripteurTexte(*p,i);
		distance = distanceDescripteurMotTexte(mot,*autre_desc);
		//printf("distance entre %s et %s = %d\n",mot,getNomDescripteurTexte(*autre_desc),distance);
		di[i] = distance;
		id[i] = getIdDescripteurTexte(*autre_desc);
	}
	


	puts("");

	printf("Requête mot-clé : \"%s\"\n\n",motLu);
  printf("Résultats (fichier -> occurrences) :\n");
	int min;
	//int idmin;
	int indexe;
	int nombre_fichiers_trouves =0;
  int id_fichier_a_ouvrir = -1;
	for(int j = 0;j<n_resultats;j++){ // boucle sur le nombre de resultats définis
		min = -1;
		//idmin = -1;
		indexe = -1;
		for(int i = 0;i<p->taille;i++){ // boucle sur toutes les distances
			if(di[i]>-1 && (min == -1 || di[i]>min) ){ // si la distance est valide et que soit aucune distances n'a été trouvée
				min = di[i];
				//idmin = id[i];
				indexe = i;
        if(j == 0) {
          id_fichier_a_ouvrir = i;
        }
			}
		}
		
		if(min!=0){
			nombre_fichiers_trouves++;
			printf("%s -> %d\n",getNomDescripteurTexte(*getDescripteurTexteViaId(*p,id[indexe])),di[indexe]);
		}
		//printf("[%d] différence = %d\n",j,di[indexe]);
		di[indexe] = -1;
	}
	if(nombre_fichiers_trouves==0){
		printf("\nAucun fichier dans la base de donnée contient le mot : %s\n",motLu);
		puts("Vous pouvez essayer de demander à l'administrateur de relancer une indexation avec plus de mots");
	} else {
    char commande[TAILLE_MAX+1] = "gedit ";
    char* nom_fichier_a_ouvrir = getNomDescripteurTexte(*getDescripteurTexteViaId(*p,id[id_fichier_a_ouvrir]));
		char chemin[TAILLE_MAX+1] = "./data/Textes/";
    strcat(commande, chemin);
		strcat(commande,nom_fichier_a_ouvrir);
		strcat(commande," &");
		//printf("\nexecution de : %s\n",commande);
		system(commande);
  }
	free(id);
	free(di);
	return 0;
}
