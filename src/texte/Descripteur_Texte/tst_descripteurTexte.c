#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "descripteurTexte.h"

void printProgressBar(int pourcentage, int taille_progress_bar) {
  int fill_bar = pourcentage/(100/taille_progress_bar);
  printf("\r[");
  for(int i=0; i<taille_progress_bar; i++) {
    if(i+1 <= fill_bar) {
      printf("#");
    } else {
      printf("-");
    }
  }
  printf("]%3d%% ", pourcentage);
}

int main(int argc,char* argv[]){
/*
  DescripteurTexte e1;
  DescripteurTexte e2;
  DescripteurTexte x;
  FILE* f;
  int nb_mots = 20;

  printf("========== TESTS ==========\n");

  e1 = creerDescripteurTexte("17-Une_équipe_française_a_réussi.xml", nb_mots, 1);
  e2 = creerDescripteurTexte("06-US_Open___Mauresmo_et.xml", nb_mots, 2);

  afficheDescripteurTexte(e1);
  afficheDescripteurTexte(e2);

  f = fopen("descripteurs.csv", "w+");
  sauvegarderDescripteurTexte(f, e1);
  fclose(f);

  printf("Chargement des descripteurs :\n");

  f = fopen("descripteurs.csv", "r");
  x = chargerDescripteurTexte(f);
  fclose(f);

  afficheDescripteurTexte(x);

  printf("\n\n===========\n|  TESTS  |\n===========\n\n");
  printf("01."); if(e1.ID == 1) printf("OK\n"); else printf("\t\tNOK\n");
  printf("02."); if(distanceDescripteurMotTexte("mclaren", e1) == 12) printf("OK\n"); else printf("\t\tNOK\n");
  printf("03."); if(distanceDescripteurMotTexte("pablo", x) == 6) printf("OK\n"); else printf("\t\tNOK\n");
  printf("04."); if(distanceDescripteurMotTexte("mot", e1) == 0) printf("OK\n"); else printf("\t\tNOK\n");
  printf("05."); if(distanceDescripteurTexte(e1, x) == 77) printf("OK\n"); else printf("\t\tNOK\n");
  printf("06."); if(distanceDescripteurTexte(e2, e1) == 0) printf("OK\n"); else printf("\t\tNOK\n");

  printf("07.");  
  freeDescripteurTexte(&e1);
  freeDescripteurTexte(&e2);
  freeDescripteurTexte(&x);
  printf("OK\n");
*/
  
  int pourcentage = 0;
  int max = 10000;
  int taille_progress_bar = 50;

  for(int j=0; j<max; j++) {
    pourcentage = ((j+1)*100)/max;
    printProgressBar(pourcentage, taille_progress_bar);
  }
  printf("\n");

  return 0;

/*
 *	DescripteurTexte e;
 *	DescripteurTexte e2;
 *	FILE* fichier = NULL;
 *
 *	fichier = fopen("temp","r");
 *	e = chargerDescripteurTexte(fichier);
 *	e2 = chargerDescripteurTexte(fichier);
 *	fclose(fichier);
 *
 *	afficheDescripteurTexte(e);puts("");
 *	afficheDescripteurTexte(e2);
 *	puts("\naffichage reussi!");
 *
 *	fichier = fopen("temp","w");
 *	sauvegarderDescripteurTexte(fichier,e);
 *	sauvegarderDescripteurTexte(fichier,e2);
 *	fclose(fichier);
 */

/*
 * char* stopwords[] = {"a", "abord", "absolument", "afin", "ah", "ai", "aie", "aient", "aies", "ailleurs", "ainsi", "ait", "allaient", "allo", "allons", "alors", "anterieur", "anterieure", "anterieures", "apres", "as", "assez", "attendu", "au", "aucun", "aucune", "aucuns", "aujourd'", "aupres", "auquel", "aura", "aurai", "auraient", "aurais", "aurait", "auras", "aurez", "auriez", "aurions", "aurons", "auront", "aussi", "autant", "autre", "autrefois", "autrement", "autres", "autrui", "aux", "auxquelles", "auxquels", "avaient", "avais", "avait", "avant", "avec", "avez", "aviez", "avions", "avoir", "avons", "ayant", "ayez", "ayons", "b", "b'", "bah", "bas", "basee", "bat", "beau", "beaucoup", "bien", "bigre", "bon", "boum", "bravo", "brrr", "c", "c'", "car", "ce", "ceci", "celle", "ci", "celles", "celui", "cela", "cent", "cependant", "certain", "certaine", "certaines", "certains", "certes", "ces", "cet", "cette", "ceux", "chacun", "chacune", "chaque", "cher", "chers", "chez", "chiche", "chut", "chere", "cheres", "cinq", "cinquantaine", "cinquante", "cinquantieme", "cinquieme", "clac", "clic", "combien", "comme", "comment", "comparable", "comparables", "compris", "concernant", "contre", "couic", "crac", "d", "d'", "da", "dans", "de", "debout", "dedans", "dehors", "deja", "dela", "depuis", "dernier", "derniere", "derriere", "des", "desquelles", "desquels", "dessous", "dessus", "deux", "deuxieme", "deuxiemement", "devant", "devers", "devra", "devrait", "different", "differente", "differentes", "differents", "dire", "directe", "directement", "dit", "dite", "dits", "divers", "diverse", "diverses", "dix", "dixieme", "doit", "doivent", "donc", "dont", "dos", "douze", "douzieme", "dring", "droite", "du", "duquel", "durant", "debut", "desormais", "e", "effet", "egale", "egalement", "egales", "eh", "elle", "elles", "en", "encore", "enfin", "entre", "envers", "environ", "es", "essai", "est", "et", "etc", "etre", "eu", "eue", "eues", "euh", "eurent", "eus", "eusse", "eussent", "eusses", "eussiez", "eussions", "eux", "exactement", "excepte", "extenso", "exterieur", "eumes", "eut", "eutes", "f", "f'", "fais", "faisaient", "faisant", "fait", "faites", "façon", "feront", "fi", "flac", "floc", "fois", "font", "force", "furent", "fus", "fusse", "fussent", "fusses", "fussiez", "fussions", "fut", "fumes", "futes", "g", "g'", "gens", "h", "ha", "haut", "hein", "hem", "hep", "hi", "ho", "hola", "hop", "hormis", "hors", "hou", "houp", "hue", "hui", "huit", "huitieme", "hum", "hurrah", "he", "helas", "i", "ici", "il", "ils", "importe", "j", "j'", "je", "jusqu'", "jusque", "juste", "k", "k'", "l", "l'", "laisser", "laquelle", "las", "le", "lequel", "les", "lesquelles", "lesquels", "leur", "leurs", "longtemps", "lors", "lorsqu'", "lorsque", "lui", "la", "m", "m'", "ma", "maint", "maintenant", "mais", "malgre", "maximale", "me", "meme", "memes", "merci", "mes", "mien", "mienne", "miennes", "miens", "mille", "mince", "mine", "minimale", "moi", "moindres", "moins", "mon", "mot", "moyennant", "multiple", "multiples", "n", "n'", "na", "naturel", "naturelle", "naturelles", "ne", "necessaire", "necessairement", "neuf", "neuvieme", "ni", "nombreuses", "nombreux", "nommes", "non", "nos", "notamment", "nous", "nouveau", "nouveaux", "nul", "neanmoins", "notre", "notres", "o", "oh", "ohe", "olle", "ole", "on", "ont", "onze", "onzieme", "ore", "ou", "ouf", "ouais", "oust", "ouste", "outre", "ouvert", "ouverte", "ouverts", "p", "p'", "paf", "pan", "par", "parce", "parfois", "parle", "parlent", "parler", "parmi", "parole", "parseme", "partant", "particulier", "particuliere", "particulierement", "pas", "passe", "pendant", "pense", "permet", "personne", "personnes", "peu", "peut", "peuvent", "peux", "pff", "pfft", "pfut", "pif", "pire", "piece", "plein", "plouf", "plupart", "plus", "plusieurs", "plutot", "possessif", "possessifs", "possible", "possibles", "pouah", "pour", "pourquoi", "pourrais", "pourrait", "pouvait", "prealable", "precisement", "premier", "premiere", "premierement", "probable", "probante", "procedant", "proche", "pres", "psitt", "pu", "puis", "puisque", "pur", "pure", "q", "qu'", "quand", "quant", "quanta", "quarante", "quatorze", "quatre", "quatrieme", "quatriemement", "que", "quel", "quelconque", "quelle", "quelles", "quelqu'", "quelque", "quelques", "quels", "qui", "quiconque", "quinze", "quoi", "quoique", "r", "r'", "rare", "rarement", "rares", "relative", "relativement", "remarquable", "rend", "rendre", "restant", "reste", "restent", "restrictif", "retour", "revoici", "revoila", "rien", "s", "s'", "sa", "sacrebleu", "sait", "sans", "sapristi", "sauf", "se", "sein", "seize", "selon", "semblable", "semblaient", "semble", "semblent", "sent", "sept", "septieme", "sera", "serai", "seraient", "serais", "serait", "seras", "serez", "seriez", "serions", "serons", "seront", "ses", "seul", "seule", "seulement", "si", "sien", "sienne", "siennes", "siens", "sinon", "six", "sixieme", "soi", "soient", "sois", "soit", "soixante", "sommes", "son", "sont", "sous", "souvent", "soyez", "soyons", "specifique", "specifiques", "speculatif", "stop", "strictement", "subtiles", "suffisant", "suffisante", "suffit", "suis", "suit", "suivant", "suivante", "suivantes", "suivants", "suivre", "sujet", "superpose", "sur", "surtout", "t", "t'", "ta", "tac", "tandis", "tant", "tardive", "te", "tel", "telle", "tellement", "telles", "tels", "tenant", "tend", "tenir", "tente", "tes", "tic", "tien", "tienne", "tiennes", "tiens", "toc", "toi", "ton", "touchant", "toujours", "tous", "tout", "toute", "toutefois", "toutes", "treize", "trente", "trois", "troisieme", "troisiemement", "trop", "tres", "tsoin", "tsouin", "tu", "u", "un", "une", "unes", "uniformement", "unique", "uniques", "uns", "v", "v'", "va", "vais", "valeur", "vas", "vers", "via", "vif", "vifs", "vingt", "vivat", "vive", "vives", "vlan", "voici", "voie", "voient", "voila", "voire", "vont", "vos", "vous", "vu", "ve", "votre", "votres", "w", "x", "y", "z", "zut", "ca", "etaient", "etais", "etait", "etant", "etat", "etiez", "etions", "ete", "etee", "etees", "etes"};
 *
 *  int i=0;
 *  char string[50];
 *  do {
 *    strcpy(string, stopwords[i]);
 *    i++;
 *  } while(strcmp(string, "etes") != 0);
 *
 *  printf("Il y a %d stopwords.\n", i);
 *  printf("TESTS si mots pareils...\n");
 *
 *  for(int j=0; j<i; j++)
 *    for(int k=0; k<i; k++)
 *      if(j!=k)
 *        if(strcmp(stopwords[j], stopwords[k]) == 0)
 *          printf("il y deux fois %s : (%d, %d);\n", stopwords[j], j,  k);
 *
 *  printf("FIN TESTS\n");
 *
 *  return 0;
 */

/*
 *  char utf8[] = "terminé";
 *  char e_accent[] = u8"é";
 *  char e_accent1 = '\xc3';
 *  char e_accent2 = '\xa9';
 *
 *  printf("%s :\n", utf8);
 *  for(int i = 0; i<8 ; i++) {
 *    printf("caractère %d : %c --> %02x\n", i, utf8[i], (unsigned char) utf8[i]);
 *    if(utf8[i] == e_accent[0]) printf("\t1.c'est égale pour le %dème\n", i);
 *    if(utf8[i] == e_accent1) printf("\t2.c'est égale pour le %dème\n", i);
 *    if(utf8[i] == e_accent2) printf("\t3.c'est égale pour le %dème\n", i);
 *  }
 */

/*
 *  char accents[] = "À à Â È É Ê Ë Ï Ù Û Œ œ ";
 *  for(int i = 0; i<40 ; i++) {
 *    if(accents[i] == ' ') printf("\n");
 *    else printf("%02x", (unsigned char) accents[i]);
 *  }
 *  printf("\n");
 *
 *	return EXIT_SUCCESS;
 */
}
