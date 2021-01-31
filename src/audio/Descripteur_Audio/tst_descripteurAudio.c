#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "descripteurAudio.h"

int main(int argc, char *argv[]) {
	bool test_Moumouni = true;
  
	if(test_Moumouni){
		// debut test
		int i, j;
		float *endroitDisntaceMin;
		puts("TEST 0");
		DescripteurAudio b = creerDescripteurAudioBin("corpus_fi.bin", 50, 2);
    
  	afficheDescripteurAudio(b);

		puts("TEST A");
		//* ******* TEST DISTANCE ***

		DescripteurAudio a= creerDescripteurAudioBin("jingle_fi.bin", 50, 1);
		float dist = 0;
    afficheDescripteurAudio(b);
    afficheDescripteurAudio(a);

		dist = distanceDescripteurAudio(&a, &b, endroitDisntaceMin);

		printf("\n##############################################################\ndistance entre %s et %s = %f pourcents \n endroit le plus pertinant : %f seconde(s)\n",a.nom,b.nom,dist,*endroitDisntaceMin);


		/* ***** Test Sauvgarde et Chargement ******/

		FILE *fichierTest = fopen("essaiBin", "wb"); // w = write
		

		/*int t = sauvegarderDescripteurAudio(fichierTest, a);
		fclose(fichierTest);
    if(t==0)
      printf("Sauvgarde : OK\n");
    else
      printf("Sauvgarde : NOK\n");
		*/
		fichierTest = fopen("essaiBin", "wb");
		DescripteurAudio nouveau;
		nouveau = chargerDescripteurAudio(fichierTest);
		fclose(fichierTest);

		if (a.ID == b.ID)
			printf("Id : OK\n");
		else
			printf("Id : NOK\n");
		if (strcmp(a.nom, b.nom) == 0)
			printf("nom : OK\n");
		else
			printf("nom : NOK\n");
		if (a.tailleDuDescripteur == b.tailleDuDescripteur)
			printf("tailleDuDescripteur : OK\n");
    else
      printf("tailleDuDescripteur : OK\n");
		if (a.vectNombre[10] == b.vectNombre[10] && a.vectNombre[101] == b.vectNombre[101])
			printf("vectNombre : OK\n");
    else
      printf("vectNombre : NOK\n");
		if (a.vectEndroit[a.tailleDuDescripteur - 10] ==
			b.vectEndroit[b.tailleDuDescripteur - 10])
			printf("vectEndroit : OK\n");
    else
      printf("vectEndroit : NOK\n");
		//===================================================================
		// Fin test Moumouni ################################################
		//===================================================================
	}else{ //##############################################################
		//===================================================================
		// Debut test Kosma #################################################
		//===================================================================
		int i, j;
		float *endroitDisntaceMin;

		DescripteurAudio ji = creerDescripteurAudio("jingle_fi.txt", 50, 1);
		/* test vectEndroit *
		printf("\n\n\n\nTest vectEndroit - le numero d'intervalle ou se place
		chaqu'une frequance\n*** tailleDuDescripteur = %d ********\n",
		e.tailleDuDescripteur); for(i=0; i< e.tailleDuDescripteur; i++){
			printf("%d\n", e.vectEndroit[i]);
		}
		/* test vectNombre*
		printf("\n\nTest vectNombre - le nombre de frequances dans chaqu'une
		intervalle\n*** nombreDesIntervalles = %d ********\n",
		e.nombreDesIntervalles); for(j=0; j< e.nombreDesIntervalles; j++){
			printf("%d\n", e.vectNombre[j]);
		}
		*/

		//* ******* DEBUT DU TESTES DE DISTANCE ****

		DescripteurAudio ji8 = creerDescripteurAudio("jingle_fi8.txt", 50, 8);

		DescripteurAudio ji10 = creerDescripteurAudio("jingle_fi10.txt", 50, 10);

		DescripteurAudio ji15 = creerDescripteurAudio("jingle_fi15.txt", 50, 15);

		DescripteurAudio c = creerDescripteurAudio("corpus_fi.txt", 50, 2);
		/* test vectEndroit *
		printf("\n\n\n\nTest vectEndroit - le numero d'intervalle ou se place
		chaqu'une frequance\n*** tailleDuDescripteur = %d ********\n",
		c.tailleDuDescripteur); for(i=0; i< c.tailleDuDescripteur; i++){
			printf("%d\n", c.vectEndroit[i]); // ca marche correctement :)
		}
		//
		/* test vectNombre*
		printf("\n\nTest vectNombre - le nombre de frequances dans chaqu'une
		intervalle\n*** nombreDesIntervalles = %d ********\n",
		c.nombreDesIntervalles); for(j=0; j< c.nombreDesIntervalles; j++){
			printf("%d\n", c.vectNombre[j]);
		}
		//*/

		DescripteurAudio c8 = creerDescripteurAudio("corpus_fi8.txt", 50, 9);

		DescripteurAudio c10 = creerDescripteurAudio("corpus_fi10.txt", 50, 11);

		DescripteurAudio c15 = creerDescripteurAudio("corpus_fi15.txt", 50, 16);

		DescripteurAudio cminus5 = creerDescripteurAudio("corpus_fi-5.txt", 50, -5);

		DescripteurAudio cminus10 = creerDescripteurAudio("corpus_fi-10.txt", 50, -10);

		float dist = 0;

		dist = distanceDescripteurAudio(&c, &ji, endroitDisntaceMin);
		printf(
			"\n##############################################################"
			"\ndistance entre %s et %s = %f pourcents\n endroit le plus pertinant : %f "
			"seconde(s)\n",
			ji.nom,
			c.nom,
			dist,
			*endroitDisntaceMin);

		dist = distanceDescripteurAudio(&ji, &ji, endroitDisntaceMin);
		printf(
			"\n##############################################################"
			"\ndistance entre %s et %s = %f pourcents\n endroit le plus pertinant : %f "
			"seconde(s)\n",
			ji.nom,
			ji.nom,
			dist,
			*endroitDisntaceMin);

		dist = distanceDescripteurAudio(&ji, &ji8, endroitDisntaceMin);
		printf(
			"\n##############################################################"
			"\ndistance entre %s et %s = %f pourcents\n endroit le plus pertinant : %f "
			"seconde(s)\n",
			ji.nom,
			ji8.nom,
			dist,
			*endroitDisntaceMin);

		dist = distanceDescripteurAudio(&ji, &ji10, endroitDisntaceMin);
		printf(
			"\n##############################################################"
			"\ndistance entre %s et %s = %f pourcents\n endroit le plus pertinant : %f "
			"seconde(s)\n",
			ji.nom,
			ji10.nom,
			dist,
			*endroitDisntaceMin);

		dist = distanceDescripteurAudio(&ji, &ji15, endroitDisntaceMin);
		printf(
			"\n##############################################################"
			"\ndistance entre %s et %s = %f pourcents\n endroit le plus pertinant : %f "
			"seconde(s)\n",
			ji.nom,
			ji15.nom,
			dist,
			*endroitDisntaceMin);

		dist = distanceDescripteurAudio(&c, &c8, endroitDisntaceMin);
		printf(
			"\n##############################################################"
			"\ndistance entre %s et %s = %f pourcents\n endroit le plus pertinant : %f "
			"seconde(s)\n",
			c.nom,
			c8.nom,
			dist,
			*endroitDisntaceMin);

		dist = distanceDescripteurAudio(&c8, &ji8, endroitDisntaceMin);
		printf(
			"\n##############################################################"
			"\ndistance entre %s et %s = %f pourcents\n endroit le plus pertinant : %f "
			"seconde(s)\n",
			c8.nom,
			ji8.nom,
			dist,
			*endroitDisntaceMin);

		dist = distanceDescripteurAudio(&c, &cminus5, endroitDisntaceMin);
		printf(
			"\n##############################################################"
			"\ndistance entre %s et %s = %f pourcents\n endroit le plus pertinant : %f "
			"seconde(s)\n",
			c.nom,
			cminus5.nom,
			dist,
			*endroitDisntaceMin);

		dist = distanceDescripteurAudio(&c, &cminus10, endroitDisntaceMin);
		printf(
			"\n##############################################################"
			"\ndistance entre %s et %s = %f pourcents\n endroit le plus pertinant : %f "
			"seconde(s)\n",
			c.nom,
			cminus10.nom,
			dist,
			*endroitDisntaceMin);

		dist = distanceDescripteurAudio(&ji, &cminus5, endroitDisntaceMin);
		printf(
			"\n##############################################################"
			"\ndistance entre %s et %s = %f pourcents\n endroit le plus pertinant : %f "
			"seconde(s)\n",
			ji.nom,
			cminus5.nom,
			dist,
			*endroitDisntaceMin);

		dist = distanceDescripteurAudio(&ji, &cminus10, endroitDisntaceMin);
		printf(
			"\n##############################################################"
			"\ndistance entre %s et %s = %f pourcents\n endroit le plus pertinant : %f "
			"seconde(s)\n",
			ji.nom,
			cminus10.nom,
			dist,
			*endroitDisntaceMin);

		//******* FIN DU TESTES DE DISTANCE **** *
		// afficheDescripteurAudio(e);
		// afftest(e);

		/* Testes des getters et de setters :
		DescripteurAudio ee = creerDescripteurAudio("corpus_fi.txt",50,2);

		puts("Test3");
		printf("ID descripteur e : %d = %d\nID descripteur ee : %d = %d\n",e.ID,
		getIdDescripteurAudio(e), ee.ID, getIdDescripteurAudio(ee) );

		puts("Test4");
		printf("nom descripteur e : %s = %s\nnom descripteur ee : %s = %s\n",e.nom,
		getNomDescripteurAudio(e), ee.nom, getNomDescripteurAudio(ee));

		puts("Test5");
		printf("taille descripteur e : %d\taille descripteur ee :
		%d\n",e.tailleDuDescripteur, ee.tailleDuDescripteur);

		puts("Test6");
		printf("ID descripteur e : %d != %d\nID descripteur ee : %d != %d\n",e.ID,
		setIdDescripteurAudio(&e, 666), ee.ID, setIdDescripteurAudio(&ee,333));
		*/

		printf("\n\n");

		/* ***** Test Sauvgarde et Chargement ******/

		FILE *fichierTest = fopen("Temp", "w"); // w = write

		//int t = sauvegarderDescripteurAudio(fichierTest, ji);
		fclose(fichierTest);

		fichierTest = fopen("Temp", "r");
		DescripteurAudio jiji;
		jiji = chargerDescripteurAudio(fichierTest);
		fclose(fichierTest);

		if (ji.ID == jiji.ID)
			printf("Id : OK\n");
		else
			printf("Id : NOK\n");
		if (strcmp(ji.nom, jiji.nom) == 0)
			printf("nom : OK\n");
		else
			printf("nom : NOK\n");
		if (ji.tailleDuDescripteur == jiji.tailleDuDescripteur)
			printf("tailleDuDescripteur : OK\n");
		if (ji.vectNombre[10] == jiji.vectNombre[10])
			printf("vectNombre : OK\n");
		if (ji.vectEndroit[ji.tailleDuDescripteur - 10] ==
			jiji.vectEndroit[jiji.tailleDuDescripteur - 10])
			printf("vectEndroit : OK\n");

		/* ***** FIN Test Sauvgarde et Chargement ****** */
	}
	return EXIT_SUCCESS;
}
