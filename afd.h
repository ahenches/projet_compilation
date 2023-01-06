#include "afn.h"

//Auteurs Arnaud Henches, Maud Lestienne

#define max(a,b) (a>=b?a:b)
#define min(a,b) (a<=b?a:b)

typedef struct AFD {
    int nombre_etats;
    bool *etats;
    int **transitions;
	alphabet alphabet;
}afd;

afd nouveauAFD(int nombre_etats, alphabet * alphabet);
void afficherAFD(afd *afd);
bool executer_AFD_rec(int etat_actuel, char chaine_restante[], afd *afd); 
afd determinisationAFN(afn * anf_a_determiniser);
afd minimisation(afd *afd_);
int sont_identique(char **tab1, char **tab2, int taille);
