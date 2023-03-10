#include "afn.h"

//Auteur : Arnaud Henches

/**
 * @brief Génére un afn à partir d'un fichier
 * 
 * @param filename le nom du fichier
 * @return afn1 l'afn nouvellement généré
 */
afn genererAFN(char *filename)
{
	
	FILE *ptr;
	long save;	
	char line[MAX_CARACTERE_PAR_LIGNE];
	
	// INITIALIZE AFN	
	afn afn1 = {0};
	afn1.alphabet.lettres = (char*)malloc(CARACTERES_IMPRIMABLES*sizeof(char));
	// initializing array elements
	for (int i = 0; i < CARACTERES_IMPRIMABLES; i++)
		afn1.alphabet.correspondance[i] = -1;
	// LECTURE FICHIER
	ptr = fopen(filename, "r");
	if (NULL == ptr) {
		printf("file can't be opened \n");
	}	
	
	// lecture du nombre d'états
	int nombre_etats;
	fgets(line, MAX_CARACTERE_PAR_LIGNE, ptr);
	nombre_etats = atoi(line);

	afn1.nombre_etats = nombre_etats;
	afn1.sont_etats_finals = calloc(nombre_etats, sizeof(char));


	// Lecture du nombre d'états finals	
	fgets(line, MAX_CARACTERE_PAR_LIGNE, ptr);
	char delim[] = " ";
	char *res = strtok(line, delim);
	int i = 0;
	while(res != NULL)
	{
		afn1.sont_etats_finals[atoi(res)] = 1; // res est un état final
		res = strtok(NULL, delim);
		i++;
	}
	
	// Lecture des transitions
	save = ftell(ptr);
	// premier parcours pour connaître le nombre de lettre dans l'alphabet
	afn1.alphabet.nombre_lettres = 0;
	while(fgets(line, MAX_CARACTERE_PAR_LIGNE, ptr) != NULL)
	{
		res = strtok(line, delim);
		res = strtok(NULL, delim);
		if (afn1.alphabet.correspondance[*res-' '] == -1)
		{
			afn1.alphabet.lettres[afn1.alphabet.nombre_lettres] = *res;
			afn1.alphabet.correspondance[*res-' '] = afn1.alphabet.nombre_lettres++;
		}
	}
	afn1.alphabet.lettres = (char *)realloc(afn1.alphabet.lettres, afn1.alphabet.nombre_lettres*sizeof(char));
	fseek(ptr, save, SEEK_SET);
	
	// deuxième parcours pour remplir le tableau des transitions à deux entrées (etat, lettre)
	i = 0;
	afn1.etats_transitions = malloc(nombre_etats * sizeof(etats_non_determinises *)); 
	for (int i = 0; i < nombre_etats; i++)
	{
		afn1.etats_transitions[i] = calloc(afn1.alphabet.nombre_lettres, sizeof(etats_non_determinises)); 
	}
	int etat_d, etat_f, indice_lettre, indice_etat_f;
	while(fgets(line, MAX_CARACTERE_PAR_LIGNE, ptr) != NULL)
	{
		etat_d = atoi(strtok(line, delim));
		res = strtok(NULL, delim);
		etat_f = atoi(strtok(NULL, delim));
		indice_lettre = afn1.alphabet.correspondance[*res - ' '];
		indice_etat_f = afn1.etats_transitions[etat_d][indice_lettre].nombre_etats_non_determinises++;
		afn1.etats_transitions[etat_d][indice_lettre].etats[indice_etat_f] = etat_f;
	}
	fclose(ptr);
	//mémoire à libérer
	return afn1;
}

// fonctions outils qui servent à l'affichage

/**
 * @brief Affiche une chaîne de caractère n_fois fois
 * 
 * @param str la chaine à afficher
 * @param n_fois le nombre de fois
 */
void afficher_n_fois(char * str, int n_fois)
{
	for (int j = 0; j < n_fois; j++)
		printf("%s", str);
}
/**
 * @brief Compte le nombre de chiffres
 * 
 * @param n le nombre
 * @return le nombre de chiffre nécessaire à écrire l'entier
 */
int compter_digit(int n)
{
	if (n/10 == 0)
		return 1;
	return 1 + compter_digit(n / 10);
}
// fin fonctions outils

/**
 * @brief Exécute l'AFN sur une chaine de caractère de manière récursive
 * 
 * @param etat_actuel l'état actuel dans la récursion
 * @param chaine_restante la chaine de caractère qu'il reste à lire
 * @param afn l'afn sur lequel on exécute la chaine
 * @param taille_retrait la distance à la marge permet le bel affichage
 * @return 1 si la chaine peut être lue par l'afn 0 sinon
 */
bool executer_AFN_rec(int etat_actuel, char chaine_restante[], afn *afn, int taille_retrait)
{
	printf("(%d, %s)", etat_actuel, chaine_restante);
	if (*chaine_restante == '\0')
	{
		printf(afn->sont_etats_finals[etat_actuel] ? " |- ok" : " |- ko");
		printf("\n");
		return afn->sont_etats_finals[etat_actuel]; // renvoie Vrai si état_actuel est final Faux sinon
	}
	else {
		bool mot_restant_valide = 0;
		taille_retrait += compter_digit(etat_actuel) + strlen(chaine_restante) + strlen("(, ) |- ");
		int i = 0;
		while(i < afn->etats_transitions[etat_actuel][afn->alphabet.correspondance[*chaine_restante-' ']].nombre_etats_non_determinises && !mot_restant_valide)
		{
			if (i > 0)
				afficher_n_fois(" ", taille_retrait);
			printf(" |- ");
			mot_restant_valide = mot_restant_valide |  executer_AFN_rec(afn->etats_transitions[etat_actuel][afn->alphabet.correspondance[*chaine_restante-' ']].etats[i], &chaine_restante[1], afn, taille_retrait);
			i++;
		}
		if (afn->etats_transitions[etat_actuel][afn->alphabet.correspondance[*chaine_restante-' ']].nombre_etats_non_determinises == 0)
			 printf(" |- ko \n");
		return mot_restant_valide;
	}
}
