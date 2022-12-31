#include <stdio.h>
#include <stdlib.h>

#define TAILLE_CHAINE 100
#define NB_CARACTERE_MAX 95

typedef struct
{
    char caracteresRencontres[NB_CARACTERE_MAX +1];
    int nbEtats;
    int *etats;
    int **transitions;
}AFD;

void lectureFichier(char* nomFichier);
AFD nouveauAFD(int nbEtats);
void afficherAFD(AFD *afd);
int executer_AFN_rec(int etat_actuel, char chaine_restante[], AFD *afd, int profondeur); // return 1 si mot restant valide PEUT ETRE RECURSIVE OU NON 

