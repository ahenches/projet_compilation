//Auteur : Arnaud Henches

#if !defined(AFN)
#define AFN
#define OFFSET_FOR_RECURSIVE_EXEC -4
#define MAX_CARACTERE_PAR_LIGNE 40
#define MAX_TRANSITIONS 40
#define CARACTERES_IMPRIMABLES 95
#define MAX_NOMBRE_ETATS_NON_DETERMINE 20

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef char bool;


/**
 * @brief Structure de donnée représentant un alphabet fini
 * nombre_lettres donne le nombre de lettres de l'alphabet
 * lettre est un tableau de taille nombre_lettres qui contient les lettres
 * correspondance est un tableau de taille 95 le nombre de caractère imprimable du code ascii il permet de donner directement à une lettre l'indice dans le tableau lettre
 */
typedef struct AFN {
typedef struct Alphabet {
	int nombre_lettres;
	char *lettres;
	int correspondance[CARACTERES_IMPRIMABLES];
} alphabet;


/**
 * @brief Structure de donnée représentant une liste d'etats non determinisé ( appelé extensivement set par la suite ) 
 * nombre_etats_non_determinises la taille de cette liste
 * etats les états 
 */
typedef struct Etats_non_determinises {
	int nombre_etats_non_determinises;
	int etats[MAX_NOMBRE_ETATS_NON_DETERMINE];
} etats_non_determinises;

bool est_set_etats_egaux(etats_non_determinises * etat1, etats_non_determinises * etat2); // 1 si set égaux 0 sinon
int indice_set_etats_dans_tableau(etats_non_determinises * etats, etats_non_determinises ** liste_set_etats, int taille_liste); // Retourne l'indice du set etats dans liste_set_etats -1 si pas dedans
void set_etats_union(etats_non_determinises * etats1, etats_non_determinises * etats2); // fais l'union du set etats1, etats2 dans etats1


/**
 * @brief Structure de donnée représentant un automate fini non-deterministe
 * nombre_etats represente le nombre total d etas de l afd 
 * sont_etats_finaux est un tableau indexé par les etats de l automate, de taille nombre_etat, contenant des boolean, 1 si l état est terminal 0 sinon
 * etat_transitions est un tableau 2D indexé par les etats de l automate et les caracteres de l'alphabet de l automate, il contient la structure recevant les multiples possible états d'arrivé possiblement vide
 * alphabet est une structure comportant les caracteres de l'alphabet de l automate
 */
typedef struct AFN {
	bool * sont_etats_finals;
	int nombre_etats;
	etats_non_determinises ** etats_transitions;
	alphabet alphabet;
} afn;


afn genererAFN(char *file_name);

// fonctions outils qui servent à l'affichage

void afficher_n_fois(char * str, int n_fois);
int compter_digit(int n);

// fin fonctions outils

bool executer_AFN_rec(int etat_actuel, char chaine_restante[], afn *afn, int taille_retrait);
#endif

