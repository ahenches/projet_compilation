#include "afn.h"

//Auteurs Arnaud Henches, Maud Lestienne

#define max(a,b) (a>=b?a:b)
#define min(a,b) (a<=b?a:b)

/**
 * @brief Structure de donnée représentant un automate fini deterministe
 * nombre_etats represente le nombre total d etas de l afd 
 * etat est un tableau indexé parr les etats de l automate,de taille nombre_etat,  contenant des booleen, 1 si l état est terminal sinon 0
 * transitions est un tableau 2D indexé par les etas de l automate et les caracteres de l'alphabet de l automate, il contient les etats d arrivée des transitions
 * ex: la transition (0,a,1) est stocké : transitions[0]['a'] = 1, pour l'indice 'a' on utilise le tableau de corespondance de la structure alphabet 
 * alphabet est une structure comportant les caracteres de l'alphabet de l automate
 */
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
