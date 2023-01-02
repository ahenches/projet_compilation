
#define MAX_CARACTERE_PAR_LIGNE 40
#define MAX_TRANSITIONS 40
#define CARACTERES_IMPRIMABLES 95
#define MAX_NOMBRE_ETATS_NON_DETERMINE 20

typedef char bool;

typedef struct Etats_N_det {
	int nombre_etats_N_det;
	int etats[MAX_NOMBRE_ETATS_NON_DETERMINE];
} etats_N_det;

typedef struct Alphabet {
	int nombre_lettres;
	char * lettres;
} alphabet;

typedef struct AFN {
	etats_N_det ** etats_transitions;
	int correspondance[CARACTERES_IMPRIMABLES];
	bool * sont_etats_finals;
	int nombre_etats;
	alphabet alphabet;
} afn;

typedef struct AFD{
    char caracteresRencontres[CARACTERES_IMPRIMABLES +1];
    int nbEtats;
    bool *etats;
    int **transitions;
}afd;

afn genererAFN(char *file_name);
afd nouveauAFD(int nbEtats);
void afficherAFD(afd *afd);
bool executer_AFN_rec(int etat_actuel, char chaine_restante[], afn *afn, int profondeur); // return 1 si mot restant valide PEUT ETRE RECURSIVE OU NON 
bool executer_AFD_rec(int etat_actuel, char chaine_restante[], afd *afd, int profondeur); // return 1 si mot restant valide PEUT ETRE RECURSIVE OU NON 

