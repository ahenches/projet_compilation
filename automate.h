
#define MAX_CARACTERE_PAR_LIGNE 40
#define MAX_TRANSITIONS 40
#define CARACTERES_IMPRIMABLES 95
#define MAX_NOMBRE_ETATS_NON_DETERMINE 20

typedef struct Etats_N_det {
	int taille_etats_N_det;
	int etats[MAX_NOMBRE_ETATS_NON_DETERMINE];
} etats_N_det;


typedef struct AFN {
	etats_N_det ** etats_transitions;
	int correspondance[CARACTERES_IMPRIMABLES];
	char * sont_etats_finals;
	int nombre_etats;
} afn;

char executer_AFN_rec(int etat_actuel, char chaine_restante[], afn *afn, int profondeur); // return 1 si mot restant valide PEUT ETRE RECURSIVE OU NON 
