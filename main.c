#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_CHAR_BY_LINE 40
#define MAX_TRANSITIONS 40

// int executer_automate(char chaine[], i); //return 1 si mot valide 
int executer_automate_rec(int etat_actuel, char chaine_restante[], int etats_finals[], int nombre_etats_finals, char *transitions[3], int nombre_transitions); // return 1 si mot restant valide PEUT ETRE RECURSIVE OU NON 

int main( int argc, char *argv[ ] )
{
    FILE* ptr;	
	char line[MAX_CHAR_BY_LINE];
	
	printf("nombre d'arguments %d\n", argc);

	// LECTURE FICHIER
   	ptr = fopen(argv[1], "r");
 	// lecture du nombre d'états
	int nombre_etats;

    if (NULL == ptr) {
        printf("file can't be opened \n");
    }	
	fgets(line, MAX_CHAR_BY_LINE, ptr);
	nombre_etats = atoi(line);


	// Lecture du nombre d'états finals	
	int etats_finals[nombre_etats];
	int nombre_etats_finals;
	printf("%d\n",nombre_etats); 
	fgets(line, MAX_CHAR_BY_LINE, ptr);
	char delim[] = " ";
	char *res = strtok(line, delim);
	int i = 0;
	while(res != NULL)
	{
		etats_finals[i] = atoi(res); 
		res = strtok(NULL, delim);
		i++;
	}
	nombre_etats_finals = i;

	
	// Lecture des transitions
	char transitions[MAX_TRANSITIONS][3];
	int nombre_transitions;
	
	i = 0;
	while(fgets(line, MAX_CHAR_BY_LINE, ptr) != NULL)
	{
		res = strtok(line, delim);
		transitions[i][0] = atoi(res); 
		res = strtok(NULL, delim);
		transitions[i][1] = *res; // normalement chaine de caractère composée d'un seul caractère 
		res = strtok(NULL, delim);
		transitions[i][2] = atoi(res); 
		i++;
	}
	nombre_transitions = i;

	fclose(ptr);

	
	for(int i = 2; i < argc; i++)
	{
		// parcours de l'afn
		printf("%s\n", argv[i]);
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


//int executer_automate(char chaine[])
//{
//	return executer_automate_rec(0, chaine);
//}


int executer_automate_rec(int etat_actuel, char chaine_restante[], int etats_finals[], int nombre_etats_finals, char *transitions[3], int nombre_transitions)
{
	if (*chaine_restante == '\0')
	{
		// check si état actuel est final
	}
	return 1;
}
