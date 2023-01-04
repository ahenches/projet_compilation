#if !defined(AFN)
#define AFN
#define MAX_CARACTERE_PAR_LIGNE 40
#define MAX_TRANSITIONS 40
#define CARACTERES_IMPRIMABLES 95
#define MAX_NOMBRE_ETATS_NON_DETERMINE 20

#define max(a,b) (a>=b?a:b)
#define min(a,b) (a<=b?a:b)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef char bool;


typedef struct Alphabet {
	int nombre_lettres;
	char *lettres;
	int correspondance[CARACTERES_IMPRIMABLES];
} alphabet;


typedef struct Etats_non_determine {
	int nombre_etats_non_determine;
	int etats[MAX_NOMBRE_ETATS_NON_DETERMINE];
} etats_non_determine;

bool est_set_etats_egaux(etats_non_determine * etat1, etats_non_determine * etat2);
int indice_set_etats_dans_tableau(etats_non_determine * etats, etats_non_determine ** liste_set_etats, int taille_liste);


typedef struct AFN {
	etats_non_determine ** etats_transitions;
	bool * sont_etats_finals;
	int nombre_etats;
	alphabet alphabet;
} afn;


afn genererAFN(char *file_name);

// fonctions outils qui servent à l'affichage

void afficher_n_fois(char * str, int n_fois);
int compter_digit(long long n);

// fin fonctions outils

bool executer_AFN_rec(int etat_actuel, char chaine_restante[], afn *afn, int taille_retrait);
#endif

