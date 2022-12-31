
#define MAX_CHAR_BY_LINE 40
#define MAX_TRANSITIONS 40


typedef struct Transition {
	int etat_depart;
	char lettre;
	int etat_fin;
} transition;


typedef struct AFN {
	transition transitions[MAX_TRANSITIONS];
	int nombre_transitions;
	char * sont_etats_finals;
	int nombre_etats;
} afn;


char executer_AFN_rec(int etat_actuel, char chaine_restante[], afn *afn, int profondeur); // return 1 si mot restant valide PEUT ETRE RECURSIVE OU NON 
