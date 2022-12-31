#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./automate.h"

int main( int argc, char *argv[ ] )
{
	afn afn_ = genererAFN(argv[1]);	

	for(int i = 2; i < argc; i++)
	{
		// parcours de l'afn
		printf("%s\n", argv[i]);
		if (executer_AFN_rec(0, argv[i], &afn_, 0))
			printf("Mot Valide !\n");
		else
			printf("Mot NON Valide !\n");
	}
	// determinisation
	for(int i = 2; i < argc; i++)
	{
		// parcours de l'afd
	}
	// minimalisation
	for(int i = 2; i < argc; i++)
	{
		// parcours de l'afd réduit
	}


	return 0;
}

char executer_AFN_rec(int etat_actuel, char chaine_restante[], afn *afn, int profondeur) // return 1 si mot restant valide PEUT ETRE RECURSIVE OU NON 
{
	printf("%d, état : %d mot restante à lire : %s\n", profondeur, etat_actuel, chaine_restante);
	if (*chaine_restante == '\0')
	{
		return afn->sont_etats_finals[etat_actuel]; // renvoie Vrai si état_actuel est final Faux sinon
	}
	else {
		int mot_restant_valide = 0;
		for (int i = 0; i < afn->etats_transitions[etat_actuel][afn->correspondance[*chaine_restante-' ']].taille_etats_N_det; i++)
		{
			mot_restant_valide = mot_restant_valide | executer_AFN_rec(afn->etats_transitions[etat_actuel][afn->correspondance[*chaine_restante-' ']].etats[i], &chaine_restante[1], afn, profondeur+1);
		}
		return mot_restant_valide;
	}
}

afn genererAFN(char *filename)
{
	
	FILE *ptr;
	long save;	
	char line[MAX_CARACTERE_PAR_LIGNE];
	
	// INITIALIZE AFN	
	afn afn1 = {0};
	// initializing array elements
	for (int i = 0; i < CARACTERES_IMPRIMABLES; i++)
		afn1.correspondance[i] = -1;
	// LECTURE FICHIER
	ptr = fopen(filename, "r");
	// lecture du nombre d'états
	int nombre_etats;

	if (NULL == ptr) {
		printf("file can't be opened \n");
	}	
	fgets(line, MAX_CARACTERE_PAR_LIGNE, ptr);
	nombre_etats = atoi(line);
	printf("Nombre d'états : %d\n",nombre_etats); 

	char tableau_de_char_de_taille_nombre_etats[nombre_etats];

	afn1.nombre_etats = nombre_etats;
	afn1.sont_etats_finals = tableau_de_char_de_taille_nombre_etats;


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
	int indice_tableau_lettres = 0;
	while(fgets(line, MAX_CARACTERE_PAR_LIGNE, ptr) != NULL)
	{
		res = strtok(line, delim);
		res = strtok(NULL, delim);
		if (afn1.correspondance[*res-' '] == -1)
		{
			afn1.correspondance[*res-' '] = indice_tableau_lettres++;
		}
	}
	fseek(ptr, save, SEEK_SET);

	i = 0;
	etats_N_det * tableau_de_etats_N_det_de_taille_nombre_etats[nombre_etats];
	for (int i = 0; i < nombre_etats; i++)
	{
		tableau_de_etats_N_det_de_taille_nombre_etats[i] = calloc(indice_tableau_lettres, sizeof(etats_N_det)); 
	}
	afn1.etats_transitions = tableau_de_etats_N_det_de_taille_nombre_etats;
	int etat_d, etat_f, indice_lettre, indice_etat_f;
	while(fgets(line, MAX_CARACTERE_PAR_LIGNE, ptr) != NULL)
	{
		etat_d = atoi(strtok(line, delim));
		res = strtok(NULL, delim);
		etat_f = atoi(strtok(NULL, delim));
		indice_lettre = afn1.correspondance[*res - ' '];
		indice_etat_f = afn1.etats_transitions[etat_d][indice_lettre].taille_etats_N_det++;
		afn1.etats_transitions[etat_d][indice_lettre].etats[indice_etat_f] = etat_f;
	}
	fclose(ptr);
	return afn1;
}
