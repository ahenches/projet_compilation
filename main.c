#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./automate.h"


// int executer_automate(char chaine[], i); //return 1 si mot valide 

int main( int argc, char *argv[ ] )
{
    FILE* ptr;	
	char line[MAX_CHAR_BY_LINE];
	
	// LECTURE FICHIER
	afn afn1;
   	ptr = fopen(argv[1], "r");
 	// lecture du nombre d'états
	int nombre_etats;

    if (NULL == ptr) {
        printf("file can't be opened \n");
    }	
	fgets(line, MAX_CHAR_BY_LINE, ptr);
	nombre_etats = atoi(line);
	printf("Nombre d'états : %d\n",nombre_etats); 

	char tableau_de_char_de_taille_nombre_etats[nombre_etats];

	afn1.nombre_etats = nombre_etats;
	afn1.sont_etats_finals = tableau_de_char_de_taille_nombre_etats;


	// Lecture du nombre d'états finals	
	fgets(line, MAX_CHAR_BY_LINE, ptr);
	char delim[] = " ";
	char *res = strtok(line, delim);
	int i = 0;
	while(res != NULL)
	{
		afn1.sont_etats_finals[atoi(res)] = 1; // res est un état final
		res = strtok(NULL, delim);
		i++;
	}
	// nombre_etats_finals = i; POSSIBLEMENT UTILE?
	
	/*
	for(int i = 0; i < afn1.nombre_etats; i++)
	{
		if (afn1.sont_etats_finals[i])
			printf("%d est final\n", i);
		else
			printf("%d n'est pas final\n", i);
	} TESTED
	*/
	
	// Lecture des transitions
	i = 0;
	while(fgets(line, MAX_CHAR_BY_LINE, ptr) != NULL)
	{
		res = strtok(line, delim);
		afn1.transitions[i].etat_depart = atoi(res); 
		res = strtok(NULL, delim);
		afn1.transitions[i].lettre = *res; // normalement chaine de caractère composée d'un seul caractère 
		res = strtok(NULL, delim);
		afn1.transitions[i].etat_fin = atoi(res); 
		i++;
	}
	afn1.nombre_transitions = i;
	fclose(ptr);
	/*
	for(int i = 0; i < afn1.nombre_transitions; i++)
	{
		printf("%d :: etat depart : %d, lettre : %c, etat fin : %d est final\n", i, afn1.transitions[i].etat_depart, afn1.transitions[i].lettre, afn1.transitions[i].etat_fin);
	} TESTED
	*/
	
	for(int i = 2; i < argc; i++)
	{
		// parcours de l'afn
		printf("%s\n", argv[i]);
		if (executer_AFN_rec(0, argv[i], &afn1, 0))
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
		for (int i = 0; i < afn->nombre_transitions; i++)
		{
			if (afn->transitions[i].etat_depart == etat_actuel && afn->transitions[i].lettre == *chaine_restante)
				mot_restant_valide = mot_restant_valide | executer_AFN_rec(afn->transitions[i].etat_fin, &chaine_restante[1], afn, profondeur+1);
			//else 
				//printf("la transition : %d n'existe pas avec pour état %d et comme lettre %c\n", i, etat_actuel, *chaine_restante);
		}
		return mot_restant_valide;
	}
}

