
#define MAX_CARACTERE_PAR_LIGNE 40
#define MAX_TRANSITIONS 40
#define CARACTERES_IMPRIMABLES 95
#define MAX_NOMBRE_ETATS_NON_DETERMINE 20

#define max(a,b) (a>=b?a:b)
#define min(a,b) (a<=b?a:b)

typedef char bool;

typedef struct Etats_N_det {
	int nombre_etats_N_det;
	int etats[MAX_NOMBRE_ETATS_NON_DETERMINE];
} etats_N_det;

bool est_set_etats_egaux(etats_N_det * etat1, etats_N_det * etat2);
int indice_set_etats_dans_tableau(etats_N_det * etats, etats_N_det ** liste_set_etats, int taille_liste);

typedef struct Alphabet {
	int nombre_lettres;
	char *lettres;
	int correspondance[CARACTERES_IMPRIMABLES];
} alphabet;

typedef struct AFN {
	etats_N_det ** etats_transitions;
	bool * sont_etats_finals;
	int nombre_etats;
	alphabet alphabet;
} afn;

typedef struct AFD {
    int nombre_etats;
    bool *etats;
    int **transitions;
	alphabet alphabet;
}afd;

afn genererAFN(char *file_name);
afd nouveauAFD(int nombre_etats, alphabet * alphabet);
afd determinisationAFN(afn * anf_a_determiniser);

afd minimisation(afd *afd_);
int sont_identique(char **tab1, char **tab2, int taille );
void afficherAFD(afd *afd);
bool executer_AFN_rec(int etat_actuel, char chaine_restante[], afn *afn, int profondeur); // return 1 si mot restant valide PEUT ETRE RECURSIVE OU NON 
bool executer_AFD_rec(int etat_actuel, char chaine_restante[], afd *afd, int profondeur); // return 1 si mot restant valide PEUT ETRE RECURSIVE OU NON 
