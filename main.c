//Bastian programme principale mettant en oeuvre toutes les fonctions et tout les modules dévellopés précédemment
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "src/FonctionMain/fonction.h" // fonctions générales
#include "src/chargement/chargement.h" // chargement des données (nottament les paramètre d'indexations)
#include "src/audio/audio.h" // tout ce qui est lié aux descripteurs audio
#include "src/texte/texte.h" // tout ce qui est lié aux descripteurs texte
#include "src/image/image.h" // tout ce qui est lié aux descripteurs image
#include "src/Indexation/indexation.h" // Indexation et recherche

int main(void) {
	// nettoyage du terminal des commandes de compilation
	system("clear"); 

	///////////////
	// Variables //
	///////////////

	bool admin = false; // mode administrateur sur true pour accés au menu admin
	int x; // sert pour le choix de la commande dans le menu

	// valeur des paramètres d'indexation courants dernièrement choisis
	int vT = -1; 
	int vI = -1;
	int vA = -1;

	// valeur des paramètres lors de la dernière indexation éfectuée
	int derniere_ind_text = -1;
	int derniere_ind_image = -1;
	int derniere_ind_audio = -1;

	// valeur des parametres lors de la dernière sauvegarde 
	int derniere_sauvegarde_texte = -1;
	int derniere_sauvegarde_image = -1;
	int derniere_sauvegarde_audio = -1;

	// Nombre de résultats à afficher suite à une recherche 
	int nombre_resultats_texte = 5;
	int nombre_resultats_image = 5;
	int nombre_resultats_audio = 3; 

	// booleans permettant de savoir si l'utilisateur peut faire les recherches ou doit attendre une nouvelle indexation
	bool peut_chercher_texte = true;
	bool peut_chercher_image = true;
	bool peut_chercher_audio = true;

	//Piles de liens et de descripteurs 
	PileDescripteurTexte pile_descripteur_texte;
	PileDescripteurImage pile_descripteur_image;
	PileDescripteurAudio pile_descripteur_audio;
	PileLien Liens_Texte,Liens_Audio,Liens_Image;

	// id des descripteurs
	int idImage,idTexte,idAudio;

	// booleen pour savoir si les sauvegardes doivent être écrasées suite à une nouvelle indexation.
	bool modifTexte = false;
	bool modifImage = false;
	bool modifAudio = false;

	/////////////////////////////////////////
	// Chargement des données sauvegardées //
	/////////////////////////////////////////

	// chargement des dernières valeures d'indexation choisies par l'utilisateur
	chargement_config(&vT,&vI,&vA,&peut_chercher_texte,&peut_chercher_image,&peut_chercher_audio);
	
	// chargement des dernières valeures de sauvegarde et d'indexation
	chargement_derniere_indexation(&derniere_ind_text,&derniere_ind_image,&derniere_ind_audio,&derniere_sauvegarde_texte,&derniere_sauvegarde_image,&derniere_sauvegarde_audio);
	
  // chargement de la pile de liens et de la pile de descripteurs des fichiers audios
  idAudio = 0;
	puts("Chargement des fichiers audio");
	pile_descripteur_audio = chargePileDescripteurAudio(&idAudio);
	Liens_Audio = chargePileLien("./sauvegarde/Descripteur_audio/Liste_base_audio");
  
	// chargement de la pile de liens et de la pile de descripteurs des fichiers images
	idImage = 0;
	puts("Chargement des fichiers image");
	pile_descripteur_image = chargePileDescripteurImage(&idImage);
	Liens_Image = chargePileLien("./sauvegarde/Descripteur_image/liste_base_image");

	// chargement de la pile de liens et de la pile de descripteurs des fichiers textes
	idTexte = 0;
	puts("Chargement des fichiers texte");
	pile_descripteur_texte = chargePileDescripteurTexte(&idTexte);
	Liens_Texte = chargePileLien("./sauvegarde/Descripteur_texte/liste_base_texte");

	// vérification des changements du fichier chargement_config
	if(vT != derniere_ind_text){
		peut_chercher_texte = false;
	}
	if(vI != derniere_ind_image){
		peut_chercher_image = false;
	}
	if(vA != derniere_ind_audio){
		peut_chercher_audio = false;
	}
	/*
	//Utilisé seulement lors du déboggage 
	affichePileDescripteurImage(pile_descripteur_image);
	affichePileLien(Liens_Image);

	affichePileDescripteurAudio(pile_descripteur_audio);
	affichePileLien(Liens_Audio);

	affichePileDescripteurTexte(pile_descripteur_texte);
	affichePileLien(Liens_Texte);
	*/

	//////////////////////////////////////////////
	// Lancement de la boucle du menu principal //
	//////////////////////////////////////////////
	
	logo(); // Affichage du logo du logiciel :-)

	do{
		// affichage du menu principal avec toutes les option et récupération du choix de l'utilisateur dans x
		affichage(admin,&x,vT,vI,vA,peut_chercher_texte,peut_chercher_image,peut_chercher_audio,derniere_ind_text,derniere_ind_image,derniere_ind_audio);
		
		// pour éviter de surcharger le terminal, efface le menu
		system("clear");
		
		switch (x){
			case 0:
				// quitter le logiciel
				system("clear");
				merci(); // affichage de MERCI :-)
				break;
			case 1:
				// Connexion au menu admin
				if(!admin){
					connection(&admin);
				}else{
					puts("Vous êtes déjà administrateur !");
				}
				break;
			case 2:
				// recherche de textes par mot clé
				if(peut_chercher_texte){
					color("jaune");
					printf("Recherche de mot en cours ...\n");
					color("reset");
					rechercher_mots_texte(&pile_descripteur_texte,nombre_resultats_texte);
				}else{
					// si le paramètre d'indexation à été changé 
					erreur_relancer_indexation();
				}
				break;
			case 3:
				// recherche de textes par un autre texte
				if(peut_chercher_texte){
					color("jaune");
					printf("Recherche de mot en cours ...\n");
					color("reset");
					rechercher_texte(&pile_descripteur_texte,&Liens_Texte,derniere_ind_text,nombre_resultats_texte);
				}else{
					// si le paramètre d'indexation à été changé 
					erreur_relancer_indexation();
				}
				break;
			case 4:
				// recherche d'image par une autre image
				if(peut_chercher_image){
					color("jaune");
					printf("Recherche d'image en cours ...\n");
					color("reset");
          rechercher_image(&pile_descripteur_image,&Liens_Image,derniere_ind_image,nombre_resultats_image);
				}else{
					// si le paramètre d'indexation à été changé 
					erreur_relancer_indexation();
				}
				break;
			case 5:
				// recherche d'un extrait audio dans des fichiers audios
				if(peut_chercher_audio){
					color("jaune");
          printf("Recherche audio en cours\n");
          color("reset");
          rechercher_audio(&pile_descripteur_audio,&Liens_Audio,derniere_ind_audio,nombre_resultats_audio);
				}else{
					// si le paramètre d'indexation à été changé 
					erreur_relancer_indexation();
				}
				break;
			
			// Début de la partie réservée à l'administrateur
			case 6:
				if(admin){
					// changer les paramètres d'indexation de texte
					changer_param_text(&vT,&peut_chercher_texte);
					if(vT == derniere_ind_text && !peut_chercher_texte){
						peut_chercher_texte = true;
					}
				}
				break;
			case 7:
				if(admin){
					// changer les paramètres d'indexation des images
					changer_param_image(&vI,&peut_chercher_image);
					if(vI == derniere_ind_image && !peut_chercher_image){
						peut_chercher_image = true;
					}
				}
				break;
			case 8:
				if(admin){
					// changer les paramètres d'indexation des fichiers audios
					changer_param_audio(&vA,&peut_chercher_audio);
					if(vA == derniere_ind_audio && !peut_chercher_audio){
						peut_chercher_audio = true;
					}
				}
				break;
			case 9:
				if(admin){
					// Indexation des fichiers Textes 
					if(vT == derniere_ind_text){
						printf("Vous avez déjà indexé les fichiers avec le paramètre %d !\n",vT);
					}else{
						printf("Indexation Texte en cours\n");
						indexation_fichiers_textes(&pile_descripteur_texte, &Liens_Texte,vT, &idTexte);
						//affichePileDescripteurTexte(pile_descripteur_texte);
						derniere_ind_text = vT;
						peut_chercher_texte = true;
						modifTexte = true;
				 		printf("Indexation terminée\n");
					}
				}
				break;
			case 10:
				if(admin){
					// Indexation des fichiers Image
					if(vI == derniere_ind_image){
						printf("Vous avez déjà indexé les fichiers avec le paramètre %d !\n",vI);
					}else{
				  	printf("Indexation Image en cours\n");
						indexation_fichiers_images(&pile_descripteur_image, &Liens_Image ,vI, &	idImage);
						//affichePileDescripteurImage(pile_descripteur_image);
						derniere_ind_image = vI;
						peut_chercher_image = true;
						modifImage = true;
				 		printf("Indexation terminée\n");
					}
				}
				break;
			case 11:
				if(admin){
					// Indexation des fichiers Audio
					if(vA == derniere_ind_audio){
						printf("Vous avez déjà indexé les fichiers avec le paramètre %d !\n",vA);
					}else{
				  	printf("Indexation Audio en cours\n");
						// traduction des fichiers binaire en texte
						system("./src/binTotxt/binTotxt.exe");
						indexation_fichiers_audio(&pile_descripteur_audio, &Liens_Audio ,vA, &idAudio);
						derniere_ind_audio = vA;
						peut_chercher_audio = true;
						modifAudio = true;
				 		printf("Indexation terminée\n");
					}
				}
				break;
			case 12:
				// déconnexion de la session admin
				admin = false;
				puts("Vous n'avez plus accés aux fonctionnalitées Admin");
				break;
  		default:
			// cette option n'est pas supposée arriver ... enfin je crois ...
			color("rouge");
      printf("============================================\n");
			printf("||            Action impossible           ||\n");
			printf("||        Problème : choix invalide       ||\n");
			printf("============================================\n");
		}
		color("reset");
	} while (x); 
	//  0 correspond à l'option quitter le logiciel



	// sauvegarde des derniers paramètres d'indexation selectionnés
	sauvegarde_config(vT,vI,vA,peut_chercher_texte,peut_chercher_image,peut_chercher_audio);

	// si la dernière sauvegarde et différente de l'indexation courante 
	if(modifTexte && (derniere_sauvegarde_texte != derniere_ind_text)){
		puts("\nSauvegarde des Descripteurs texte");
		SauvegardePileDescripteurTexte(pile_descripteur_texte, Liens_Texte);
		derniere_sauvegarde_texte = derniere_ind_text;
	}
	// si la dernière sauvegarde et différente de l'indexation courante 
	if(modifImage && (derniere_sauvegarde_image != derniere_ind_image)){
		puts("\nSauvegarde des Descripteurs image");
		SauvegardePileDescripteurImage(pile_descripteur_image, Liens_Image);
		derniere_sauvegarde_image = derniere_ind_image;
	}
	// si la dernière sauvegarde et différente de l'indexation courante 
	if(modifAudio && (derniere_sauvegarde_audio != derniere_ind_audio)){
		puts("\nSauvegarde des Descripteurs audio");
		SauvegardePileDescripteurAudio(pile_descripteur_audio, Liens_Audio);
		puts("");
		derniere_sauvegarde_audio = derniere_ind_audio;
	}
	
	// sauvegarde des paramètres utilisés lors de la dernière sauvegarde
	sauvegarde_derniere_indexation(derniere_ind_text,derniere_ind_image,derniere_ind_audio,derniere_sauvegarde_texte,derniere_sauvegarde_image,derniere_sauvegarde_audio);

  return EXIT_SUCCESS;
}
