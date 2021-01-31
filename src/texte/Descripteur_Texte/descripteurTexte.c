#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "descripteurTexte.h"

#define CHEMIN "./data/Textes/"  // Avec le répertoire courant : FindMe

#define TO_LOWER_CASE 32    // distace entre une majuscule et une minuscule
#define NB_LIGNES_ENTETE 4  // nombre de lignes de l'entête

#define CLEAN "temp.clean"  // fichier de nettoyage
#define TOKEN "temp.tok"    // fichier de filtrage des tokens

#define NB_STOPWARDS 670    // nombre de stopwords

#define PERTINENT 1

char* stopwords[] = {
  "a", "abord", "absolument", "afin", "ah", "ai", "aie", "aient", "aies", "ailleurs", "ainsi", "ait", "allaient", "allo", "allons", "alors", "anterieur", "anterieure", "anterieures", "apres", "as", "assez", "attendu", "au", "aucun", "aucune", "aucuns", "aujourd'", "aupres", "auquel", "aura", "aurai", "auraient", "aurais", "aurait", "auras", "aurez", "auriez", "aurions", "aurons", "auront", "aussi", "autant", "autre", "autrefois", "autrement", "autres", "autrui", "aux", "auxquelles", "auxquels", "avaient", "avais", "avait", "avant", "avec", "avez", "aviez", "avions", "avoir", "avons", "ayant", "ayez", "ayons", "b", "b'", "bah", "bas", "basee", "bat", "beau", "beaucoup", "bien", "bigre", "bon", "boum", "bravo", "brrr", "c", "c'", "car", "ce", "ceci", "celle", "ci", "celles", "celui", "cela", "cent", "cependant", "certain", "certaine", "certaines", "certains", "certes", "ces", "cet", "cette", "ceux", "chacun", "chacune", "chaque", "cher", "chers", "chez", "chiche", "chut", "chere", "cheres", "cinq", "cinquantaine", "cinquante", "cinquantieme", "cinquieme", "clac", "clic", "combien", "comme", "comment", "comparable", "comparables", "compris", "concernant", "contre", "couic", "crac", "d", "d'", "da", "dans", "de", "debout", "dedans", "dehors", "deja", "dela", "depuis", "dernier", "derniere", "derriere", "des", "desquelles", "desquels", "dessous", "dessus", "deux", "deuxieme", "deuxiemement", "devant", "devers", "devra", "devrait", "different", "differente", "differentes", "differents", "dire", "directe", "directement", "dit", "dite", "dits", "divers", "diverse", "diverses", "dix", "dixieme", "doit", "doivent", "donc", "dont", "dos", "douze", "douzieme", "dring", "droite", "du", "duquel", "durant", "debut", "desormais", "e", "effet", "egale", "egalement", "egales", "eh", "elle", "elles", "en", "encore", "enfin", "entre", "envers", "environ", "es", "essai", "est", "et", "etc", "etre", "eu", "eue", "eues", "euh", "eurent", "eus", "eusse", "eussent", "eusses", "eussiez", "eussions", "eux", "exactement", "excepte", "extenso", "exterieur", "eumes", "eut", "eutes", "f", "f'", "fais", "faisaient", "faisant", "fait", "faites", "façon", "feront", "fi", "flac", "floc", "fois", "font", "force", "furent", "fus", "fusse", "fussent", "fusses", "fussiez", "fussions", "fut", "fumes", "futes", "g", "g'", "gens", "h", "ha", "haut", "hein", "hem", "hep", "hi", "ho", "hola", "hop", "hormis", "hors", "hou", "houp", "hue", "hui", "huit", "huitieme", "hum", "hurrah", "he", "helas", "i", "ici", "il", "ils", "importe", "j", "j'", "je", "jusqu'", "jusque", "juste", "k", "k'", "l", "l'", "laisser", "laquelle", "las", "le", "lequel", "les", "lesquelles", "lesquels", "leur", "leurs", "longtemps", "lors", "lorsqu'", "lorsque", "lui", "la", "m", "m'", "ma", "maint", "maintenant", "mais", "malgre", "maximale", "me", "meme", "memes", "merci", "mes", "mien", "mienne", "miennes", "miens", "mille", "mince", "mine", "minimale", "moi", "moindres", "moins", "mon", "mot", "moyennant", "multiple", "multiples", "n", "n'", "na", "naturel", "naturelle", "naturelles", "ne", "necessaire", "necessairement", "neuf", "neuvieme", "ni", "nombreuses", "nombreux", "nommes", "non", "nos", "notamment", "nous", "nouveau", "nouveaux", "nul", "neanmoins", "notre", "notres", "o", "oh", "ohe", "olle", "ole", "on", "ont", "onze", "onzieme", "ore", "ou", "ouf", "ouais", "oust", "ouste", "outre", "ouvert", "ouverte", "ouverts", "p", "p'", "paf", "pan", "par", "parce", "parfois", "parle", "parlent", "parler", "parmi", "parole", "parseme", "partant", "particulier", "particuliere", "particulierement", "pas", "passe", "pendant", "pense", "permet", "personne", "personnes", "peu", "peut", "peuvent", "peux", "pff", "pfft", "pfut", "pif", "pire", "piece", "plein", "plouf", "plupart", "plus", "plusieurs", "plutot", "possessif", "possessifs", "possible", "possibles", "pouah", "pour", "pourquoi", "pourrais", "pourrait", "pouvait", "prealable", "precisement", "premier", "premiere", "premierement", "probable", "probante", "procedant", "proche", "pres", "psitt", "pu", "puis", "puisque", "pur", "pure", "q", "qu'", "quand", "quant", "quanta", "quarante", "quatorze", "quatre", "quatrieme", "quatriemement", "que", "quel", "quelconque", "quelle", "quelles", "quelqu'", "quelque", "quelques", "quels", "qui", "quiconque", "quinze", "quoi", "quoique", "r", "r'", "rare", "rarement", "rares", "relative", "relativement", "remarquable", "rend", "rendre", "restant", "reste", "restent", "restrictif", "retour", "revoici", "revoila", "rien", "s", "s'", "sa", "sacrebleu", "sait", "sans", "sapristi", "sauf", "se", "sein", "seize", "selon", "semblable", "semblaient", "semble", "semblent", "sent", "sept", "septieme", "sera", "serai", "seraient", "serais", "serait", "seras", "serez", "seriez", "serions", "serons", "seront", "ses", "seul", "seule", "seulement", "si", "sien", "sienne", "siennes", "siens", "sinon", "six", "sixieme", "soi", "soient", "sois", "soit", "soixante", "sommes", "son", "sont", "sous", "souvent", "soyez", "soyons", "specifique", "specifiques", "speculatif", "stop", "strictement", "subtiles", "suffisant", "suffisante", "suffit", "suis", "suit", "suivant", "suivante", "suivantes", "suivants", "suivre", "sujet", "superpose", "sur", "surtout", "t", "t'", "ta", "tac", "tandis", "tant", "tardive", "te", "tel", "telle", "tellement", "telles", "tels", "tenant", "tend", "tenir", "tente", "tes", "tic", "tien", "tienne", "tiennes", "tiens", "toc", "toi", "ton", "touchant", "toujours", "tous", "tout", "toute", "toutefois", "toutes", "treize", "trente", "trois", "troisieme", "troisiemement", "trop", "tres", "tsoin", "tsouin", "tu", "u", "un", "une", "unes", "uniformement", "unique", "uniques", "uns", "v", "v'", "va", "vais", "valeur", "vas", "vers", "via", "vif", "vifs", "vingt", "vivat", "vive", "vives", "vlan", "voici", "voie", "voient", "voila", "voire", "vont", "vos", "vous", "vu", "ve", "votre", "votres", "w", "x", "y", "z", "zut", "ca", "etaient", "etais", "etait", "etant", "etat", "etiez", "etions", "ete", "etee", "etees", "etes", "%", "1er", "2e", "2eme", "2nd", "3e", "3eme", "4e", "4eme", "5e", "5eme", "6e", "6eme", "7e", "7eme", "8e", "8eme", "9e", "9eme"};

/* Lit une ligne du fichier passé en paramètre */
void lireLigne(FILE* fic) {
  char c;
  do {
    fscanf(fic, "%c", &c);
  } while(c != '\n');
}

/* Lit les n premières ligne du fichier passé en paramètre */
void lireLignes(FILE* fic, int n) {
  int i;
  for(i=0; i<n; i++) lireLigne(fic);
}

/* Regarde si le resume est pertinant : 1 = oui ; 0 = non */
int resume(FILE* fic_in) {
  fpos_t debut_phrase;
  int nbCar = 0;
  char c;
  char buffer[TAILLE_MAX+1];
  char phraseNonPertinente[] = "Lisez l'integralite de l'article pour plus d'information.";
  fgetpos(fic_in, &debut_phrase);

  do fscanf(fic_in, "%c", &c); while(c != '>');
  fscanf(fic_in, "%c", &c); 
  while(c != '<' && nbCar < TAILLE_MAX) {
    buffer[nbCar++] = c;
    fscanf(fic_in, "%c", &c); 
  }
  do fscanf(fic_in, "%c", &c); while(c != '>');
  buffer[nbCar] = '\0';
  fflush(stdout);
  if(strcmp(buffer, phraseNonPertinente) != 0) {
    fsetpos(fic_in, &debut_phrase);
    return PERTINENT;
  } else {
    return !PERTINENT;
  }
}

/* Copie une ligne du fichier d'entrée 'fic_in' vers le fichier 'fic_out' en supprimant les balises, séparant les mots pas un espace, la ponctuation (‘.’, ‘,’, ‘ !’, ‘ ?’, ‘ :’…) sera enlevée et les majuscules remplacées par la lettre minuscule correspondante. 
Retroune le nombre de caractères écrient */
int copierPhrase(FILE* fic_in, FILE* fic_out) {
  int nbCar = 0;
  int parenthesage;
  int ponctuation;
  int chiffre_vu;
  int taille_nombre;
  char c;
  do {
    parenthesage = 0;
    ponctuation = 0;
    fscanf(fic_in, "%c", &c);
    /* Dans le cas où on rencontre une ou plusieurs balises, on la passe */
    do {
      if(c == '<') {
        do fscanf(fic_in, "%c", &c); while(c != '>');
        fscanf(fic_in, "%c", &c);
      }
    } while(c == '<');
    /* On regarde si le mot est un nombre */
    if('0' <= c && c <= '9' && !chiffre_vu) {
      taille_nombre = 0;
      fseek(fic_in, -2, SEEK_CUR);
      fscanf(fic_in, "%c", &c);
      if(c == ' ' || c == '(' || c == '-' || c == '.' || c == ':' || c == ';') {
        fscanf(fic_in, "%c", &c);
        while(('0' <= c && c <= '9') || c == ',') {
          fscanf(fic_in, "%c", &c);
          taille_nombre++;
        }
        if(c != ' ' && c != ')' && c != ',' && c != '.' && c != '-' && c != ':' && c != ';') {
          chiffre_vu = 1;
          fseek(fic_in, -taille_nombre-1, SEEK_CUR);
          fscanf(fic_in, "%c", &c);
        }
      } else {
        chiffre_vu = 1;
        fscanf(fic_in, "%c", &c);
      }
    }
    /* Quand le mot est terminé */
    if(chiffre_vu && c == ' ') {
      chiffre_vu = 0;
    }
    /* S'il y a une ponctuation */
    /* Ponctuations de fin de phrase */
    if(c == '.' || c == '!' || c == '?' || c == ':' || c == ';' || c == ',') {
      ponctuation = 1;
    }
    /* Autres ponctuations */
    if(c == '-' || c == '_') {
      c = ' ';
    }
    /* Si le caractère est une parenthèse ou autre */
    if(c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}' || c == '\"') parenthesage = 1;
    /* Si le caractère lu est une majuscule, on le remplace par le caractère en minuscule */
    if('A' <= c && c <= 'Z') c = c + TO_LOWER_CASE;
    /* Si le caractère lu est accentué : À Â È É Ê Ë Î Ï Ù Û Ç (les minuscules aussi) on lui retire son accent */
    if(c == '\xc3') {
      fscanf(fic_in, "%c", &c);
      if(c == '\x80' || c == '\x82' || c == '\xa0' || c == '\xa2') c = 'a'; 
      else if(c == '\x88' || c == '\x89' || c == '\x8a' || c == '\x8b' || c == '\xa8' || c == '\xa9' || c == '\xaa' || c == '\xab') c = 'e';
      else if(c == '\x8e' || c == '\xae' || c == '\x8f' || c == '\xaf') c = 'i';
      else if(c == '\x99' || c == '\x9b' || c == '\xb9' || c == '\xbb') c = 'u';
      else if(c == '\x87' || c == '\xa7') c = 'c';
      else { fprintf(stderr, "1.caractère inconnu : %02x\n", (unsigned char)c); return -1; }
    }
    /* Si le caractère est un e dans l'o : œ */
    if(c == '\xc5') {
      fscanf(fic_in, "%c", &c);
      if(c == '\x92' || c == '\x93') {
        fprintf(fic_out, "e");
        nbCar++;
        c = 'o';
      } else {
        fprintf(stderr, "2.caractère inconnu\n"); 
        return -2;
      }
    }
    /* Si le caractère est une apostrophe */
    if(c == '\'') {
      fprintf(fic_out, "%c", c);
      nbCar++;
      c = ' ';
    }
    /* Affichage du caractère dans le fichier si la ligne n'est pas vide */
    if((nbCar != 0 || c != '\n') && !feof(fic_in) && !parenthesage && !ponctuation) {
      fprintf(fic_out, "%c", c);
      nbCar++;
    }
  } while(c != '\n' && !feof(fic_in));
  return nbCar;
}

/* Si tab contient mot retourne 1 sinon 0 */
int contientMot(char* mot, char* tab[], int taille) {
  int i;
  for(i=0; i<taille; i++) 
    if(strcmp(tab[i], mot) == 0)
      return 1;
  return 0;
}

/* initialise une Cellule avec son token */
Cellule* initCellule(char token[TAILLE_MOT+1]) {
  Cellule* c;
  c = (Cellule*) malloc(sizeof(Cellule));
  strcpy(c->token, token);
  c->nbOcc = 1;
  c->suiv = NULL;
  return c;
}

/* Libère l'espace mémoire d'une cellule */
int freeCellule(Cellule* c) {
  free(c);
  return 0;
}

/* initialise une liste de termes */
ListeTermes initListeTermes() {
  ListeTermes lt;
  lt.tete = NULL;
  lt.taille = 0;
  return lt;
}

/* Libère l'espace mémoire d'une liste de termes */
int freeListeTermes(ListeTermes* lt) {
  Cellule* celCur;
  int erreur;
  while(lt->tete != NULL) {
    celCur = lt->tete;
    lt->tete = celCur->suiv;
    if((erreur = freeCellule(celCur)))
      return erreur;
  }
  return 0;
}

/* Libère l'espace mémoire d'un descripteur */
int freeDescripteurTexte(DescripteurTexte* d) {
  int erreur;
  if((erreur = freeListeTermes(&(d->termes))))
    return erreur;
  return 0;
}

/* retourne la liste de termes passées en paramètre en ajoutant le nouveau token newToken */
ListeTermes ajouterTermes(ListeTermes lt, char newToken[TAILLE_MOT+1]) {
  Cellule* celCur = lt.tete;
  if(lt.tete == NULL) {
    lt.tete = initCellule(newToken);
    lt.taille += 1;
    return lt;
  }
  while(celCur->suiv != NULL && (strcmp(celCur->token, newToken) != 0)) {
    celCur = celCur->suiv;
  }
  /* Si le token n'existe pas alors on crée un nouveau terme, sinon on incrémente le nombre d'occurences de ce token */
  if((strcmp(celCur->token, newToken) != 0)) {
    celCur->suiv = initCellule(newToken);
    lt.taille += 1;
  } else {
    celCur->nbOcc += 1;
  }
  return lt;
}

/* Ajoute la cellule c dans la liste de termes lt à la ième position */
ListeTermes ajoutCellule_i(ListeTermes lt, Cellule* c, int i) {
  Cellule* celCur = lt.tete;
  Cellule* newCel = initCellule(c->token);  //copie en profondeur
  newCel->nbOcc = c->nbOcc;
  if(lt.tete == NULL) {
    lt.tete = newCel;
  } else if(celCur->nbOcc < newCel->nbOcc) {
    newCel->suiv = lt.tete;
    lt.tete = newCel;
  } else {
    while(celCur->suiv != NULL && celCur->suiv->nbOcc > newCel->nbOcc) {
      celCur = celCur->suiv;
    }
    newCel->suiv = celCur->suiv;
    celCur->suiv = newCel;
  }
  lt.taille += 1;
  return lt;
}

/* affichage de la liste de termes lt */
void afficherListeTermes(ListeTermes lt) {
  Cellule* celCur = lt.tete;
  while(celCur != NULL) {
    printf("[%25s ;%5d]\n", celCur->token, celCur->nbOcc);
    celCur = celCur->suiv;
  }
  fflush(stdout);
}

/* initialise un descripteur avec le nom du fichier nomFic et son identifiant ID */
DescripteurTexte initDescripteur(char nomFic[TAILLE_MAX+1], int ID) {
  DescripteurTexte d;
  d.termes = initListeTermes();
  d.nbTermes = 0;
  d.nbTokenFic = 0;
	strcpy(d.nom,nomFic);
	d.ID = ID;
  return d;
}

/* Fonction recurruente, ajouter le nopmbre nb dans le tableau tab i correspond à l'indice le plus à droite du tableau tab */
int ajouterOcc(int* tab[], int nb, int i) {
  int aux = (*tab)[i];
  if(i == -1 || (*tab)[i] >= nb) {
    return nb;
  }
  (*tab)[i] = ajouterOcc(tab, nb, i-1);
  return aux;
}

/* retourne la ième position de nb dans tab */
int contientOcc(int* tab, int nb, int taille) {
  fflush(stdout);
  int i;
  for(i=0; i<taille; i++)
    if(tab[i] == nb) {
      tab[i] = 0;
      return i+1;
    }
  return 0;
}

/* le netoyage d'un fichier texte au format .xml le transforme en fichier .clean. Enlever les balises, séparer les mots pas un espace, la ponctuation (‘.’, ‘,’, ‘ !’, ‘ ?’, ‘ :’…) sera enlevée et les majuscules remplacées par la lettre minuscule correspondante. 
Si le nettoyage ne rencontre pas de problème, il retourne 0.*/
int nettoyage(FILE* fic_in, FILE* fic_out) {
  /* On saute l'entête du fichier qui ne nous intéresse pas (les 4 premières lignes) */
  lireLignes(fic_in, NB_LIGNES_ENTETE);
  /* On écrit le titre */
  copierPhrase(fic_in, fic_out);
  /* On regarde si le résumé est pertinant à utiliser pour l'indexation */
  if(resume(fic_in) == PERTINENT)
    copierPhrase(fic_in, fic_out);
  /* On traite le reste du fichier */
  while(!feof(fic_in)) copierPhrase(fic_in, fic_out);
  return 0;
}

/* effectue le filtrage des token de fic_in à fic_out */
int filtrage(FILE* fic_in, FILE* fic_out) {
  char buffer[TAILLE_MAX+1];
  fscanf(fic_in, "%s", buffer);
  /* Pour chaque mots du fichier fic_in, si ce n'est pas un stopwords alors on l'écrit dans fic_out */
  do {
    if(!contientMot(buffer, stopwords, NB_STOPWARDS))
      fprintf(fic_out, "%s ", buffer);
    fscanf(fic_in, "%s", buffer);
  } while(!feof(fic_in));
  return 0;
}

/* Retourne le descripteur du fichier fic_in passé en entré selon le nombre de mots pour l'indexation nb_termes, le nom du fichier nomFic et son identifiant ID */
DescripteurTexte chargerDescripteur(FILE* fic_in, int nb_termes, char* nomFic, int ID) {
  int i;
  char buffer[TAILLE_MAX];
  Cellule* celCur;
  ListeTermes lt = initListeTermes();
  int* nbOccTokens = (int*) malloc(nb_termes*sizeof(int));
  DescripteurTexte d = initDescripteur(nomFic, ID);
  // Construction de la liste de tous les termes (mot, nombre d'occurence) du fichier
  fscanf(fic_in, "%s", buffer);
  while(!feof(fic_in)) {
    lt = ajouterTermes(lt, buffer);
    d.nbTokenFic += 1; // ++
    fscanf(fic_in, "%s", buffer);
  }
  // Initialisation du tableau répertoriant les nombres d'occurences de manière decroissante
  for(i=0; i<nb_termes; i++) {
    nbOccTokens[i] = 0;
  }
  // Remplissage du tableau
  celCur = lt.tete;
  while(celCur != NULL) {
    ajouterOcc(&nbOccTokens, celCur->nbOcc, nb_termes-1);
    celCur = celCur->suiv;
  }
  // Pour chaque terme de la liste de termes on compare sont occurence avec celles contenues dans le tableau, si elle s'y trouve elle est ajoutée à la liste de termes du descripteur et le tableau se met à jours, sinon on regarde le terme suivant
  celCur = lt.tete;
  while(d.nbTermes < nb_termes && celCur != NULL) {
    if((i = contientOcc(nbOccTokens, celCur->nbOcc, nb_termes))) {
      d.termes = ajoutCellule_i(d.termes, celCur, i);
      d.nbTermes += 1;
    }
    celCur = celCur->suiv;
  }
  //printf("OK*\n");
  //fflush(stdout);
  return d;
}

/* Creation et retour du descripteur du fichier nomDuFichier avec comme paramètre d'indexation nmbDeMots et comme identifiant ID */
DescripteurTexte creerDescripteurTexte(char nomDuFichier[TAILLE_MAX+1],int nmbDeMots,int ID) {
	DescripteurTexte d;
  int erreur;
  FILE* fichierXML = NULL;
  FILE* clean = NULL;
  FILE* token = NULL;
	char chemin[TAILLE_MAX+1] = CHEMIN;
  
	strcat(chemin,nomDuFichier);
	//printf("ouverture du fichier %s avec %d mots\n",chemin,nmbDeMots);
  //fflush(stdout);
  /* Ouverture du fichier source */
  if((fichierXML = fopen(chemin, "r"))==NULL) {
    fprintf(stderr, "Erreur ouverture du fichier source.\n");
    return d;
  }
  /* Ouverture du fichier temporaire pour le nettoyage (vide) */
  if((clean = fopen(CLEAN, "w+"))==NULL) {
    fprintf(stderr, "Erreur création fichier de nettoyage.\n");
    return d;
  }
  /* Nettoyage du fichier */
  if((erreur = nettoyage(fichierXML, clean))) {
    fprintf(stderr, "Erreur %d nettoyage du fichier %s.\n", erreur, nomDuFichier);
    return d;
  }
  /* Fermeture des fichiers */
  fclose(fichierXML);
  fclose(clean);
  /* Ouverture du fichier source (clean) */
  if((clean = fopen(CLEAN, "r"))==NULL) {
    fprintf(stderr, "Erreur lecture fichier de nettoyage.\n");
    return d;
  }
  /* Ouverture du fichier temporaire pour le filtrage des tokens (vide) */
  if((token = fopen(TOKEN, "w+"))==NULL) {
    fprintf(stderr, "Erreur création fichier de filtrage des tokens.\n");
    return d;
  }
  /* Filtrage du fichier */
  if((erreur = filtrage(clean, token))) {
    fprintf(stderr, "Erreur %d nettoyage du fichier %s.\n", erreur, nomDuFichier);
    return d;
  }
  fclose(clean);
  fclose(token);
  /* Ouverture du fichier source (token) */
  if((token = fopen(TOKEN, "r"))==NULL) {
    fprintf(stderr, "Erreur lecture fichier de filtrage des tokens.\n");
    return d;
  }
  /* Création du descripteur */
  d = chargerDescripteur(token, nmbDeMots, nomDuFichier, ID);
  fclose(token);
  /* Suppression des fichiers temporaires */
  remove(CLEAN);
  remove(TOKEN);
	return d;
}

/* Retourne l'identifiant du descripteur d */
int getIdDescripteurTexte(DescripteurTexte d){
	return d.ID;
}

/* Retourne le nom du fichier du descripteur d */
char* getNomDescripteurTexte(DescripteurTexte d){
	char* nom = malloc((TAILLE_MAX+1) * sizeof(char));
	strcpy(nom,d.nom);
	return nom;
}

/* Affect la valeur x à l'indexation du descripteur pointeur_d et retourne 0 si tout s'est bien passé */
int setValueDescripteurTexte(DescripteurTexte* pointeur_d,int x){
	pointeur_d->ID = x;
	return 0;
}


/* Copie en profondeur du descripteur e1 dans le descripteur e2 */
void affectDescripteurTexte(DescripteurTexte* e1,DescripteurTexte* e2){
	Cellule* celCur = (e1->termes).tete;
  strcpy(e2->nom,e1->nom);
	e2->ID = e1->ID;
  e2->termes = initListeTermes();
  while(celCur != NULL) {
    e2->termes = ajoutCellule_i(e2->termes, celCur, e1->nbTermes);
    celCur = celCur->suiv;
  }
  e2->nbTermes = e1->nbTermes;
  e2->nbTokenFic = e1->nbTokenFic;
}

/* Affichage du descripteur d */
void afficheDescripteurTexte(DescripteurTexte d){
  printf("%s :\n", d.nom);
  printf("[%17d%15c]\n", d.ID, ' ');
  afficherListeTermes(d.termes);
  printf("[%17d%15c]\n", d.nbTermes, ' ');
  printf("[%17d%15c]\n", d.nbTokenFic, ' ');
}

/* Retourne la distance entre deux descripteurs d1 et d2 */
int distanceDescripteurTexte(DescripteurTexte d1,DescripteurTexte d2){
	if(d1.ID==d2.ID){
		return -1;
	}
  int distance = 0;
  Cellule* celCur2;
  Cellule* celCur1 = (d1.termes).tete;
  /* Parcours des listes de termes de d1 et d2, si le token est présent dans les deux, la distance est égale au plus petit nombre d'occurences */
  while(celCur1 != NULL) {
    celCur2 = (d2.termes).tete;
    while(celCur2 != NULL) {
      if(strcmp(celCur1->token, celCur2->token) == 0) {
        if(celCur1->nbOcc < celCur2->nbOcc) {
          distance += celCur1->nbOcc;
        } else {
          distance += celCur2->nbOcc;
        }
      }
    celCur2 = celCur2->suiv;
    }
    celCur1 = celCur1->suiv;
  }
	return distance;
}


/* Retourne la distance entre un mot mot et un descripteur d */
int distanceDescripteurMotTexte(char* mot,DescripteurTexte d){
  Cellule* celCur = (d.termes).tete;
  /* Parcours des listes de termes de d, si le mot est présent dans la liste, la distance est égale au nombre d'occurences du token */
  while(celCur != NULL) {
    if(strcmp(mot, celCur->token) == 0) {
      return celCur->nbOcc;
    }
    celCur = celCur->suiv;
  }
	return 0;
};

/* Ecrit la pile des descripteurs d dans le fichier fic */
int sauvegarderDescripteurTexte(FILE* fic,DescripteurTexte d){
	fprintf(fic, "%s ;%d;%d;%d;", d.nom, d.ID, d.nbTermes, d.nbTokenFic);
  Cellule* celCur = d.termes.tete;
  while(celCur != NULL) {
    fprintf(fic, "%s %d ", celCur->token, celCur->nbOcc);
    celCur = celCur->suiv;
  }
  fprintf(fic, "\n");
	return 0;
}

/* Retourne la pile des descripteurs à partir du fichier de sauvegarde des descripteurs fichier */
DescripteurTexte chargerDescripteurTexte(FILE* fichier){
	DescripteurTexte d;
  Cellule* c;
  int i;
	fscanf(fichier, "%s ;%d;%d;%d;", d.nom, &(d.ID), &(d.nbTermes), &(d.nbTokenFic));
  fflush(stdout);
  d.termes = initListeTermes();
  c = (Cellule*) malloc(sizeof(Cellule));
  c->suiv = NULL;
  for(i=1; i<d.nbTermes+1; i++) {
    fscanf(fichier, "%s %d ", c->token, &(c->nbOcc));
    d.termes = ajoutCellule_i(d.termes, c, i-1);
    fflush(stdout);
  }
	return d;
}