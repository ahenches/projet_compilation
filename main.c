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
	///////////////////////Test AFD///////////////////////////
	AFD afd = nouveauAFD(3);
    
    afd.etats[0] = 1;
    afd.etats[1] = 1;
    afd.caracteresRencontres[0] = 'a';
    afd.caracteresRencontres[1] = 'b';
    afd.caracteresRencontres[2] = '\0';
    afd.transitions[0]['a'-' '] = 1;
    afd.transitions[0]['b'-' '] = 0;
    afd.transitions[1]['a'-' '] = 1;
    afd.transitions[1]['b'-' '] = 2;
    afd.transitions[2]['a'-' '] = 2;
    afd.transitions[2]['b'-' '] = 2;

    afficherAFD(&afd);
    if(executer_AFN_rec(0, "aaa", &afd, 0)){
        printf("ok\n");
    }
    else{
        printf("ko\n");
    }
	//////////////////////////////////////////////////////////////////////////

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
	afn1.etats_transitions = malloc(nombre_etats * sizeof(etats_N_det *)); 
	for (int i = 0; i < nombre_etats; i++)
	{
		afn1.etats_transitions[i] = calloc(indice_tableau_lettres, sizeof(etats_N_det)); 
	}
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


AFD nouveauAFD(int nbEtats)
{
    AFD afd;

    afd.nbEtats = nbEtats;
    afd.etats = (int*)malloc(nbEtats*sizeof(int));
    afd.transitions =  (int**)malloc(nbEtats*sizeof(int*));
    for(int i = 0; i < nbEtats; i++)
    {
        afd.transitions[i] = (int*)malloc(CARACTERES_IMPRIMABLES*sizeof(int));
    }
    for(int i=0; i< nbEtats; i++)
    {
        afd.etats[i] = 0;
        for(int j =0; j<CARACTERES_IMPRIMABLES; j++)
        {
            afd.transitions[i][j] = -1;
        }
    }
    afd.caracteresRencontres[CARACTERES_IMPRIMABLES] = '\0';
    return afd;
}


void afficherAFD(AFD *afd)
{
    char caractereRecontre;
    int i, nbCaracteresRencontres;
    printf("%d\n", afd->nbEtats);
    
    for(i = 0; i < afd->nbEtats; i++)
    {
        if(afd->etats[i] != 0)
        {
            printf("%d ",i);
        }
    }
    printf("\n\t");
    i =0;
    nbCaracteresRencontres = 0;
    do 
    {
        caractereRecontre = afd->caracteresRencontres[i];
        printf("%c\t", caractereRecontre);
        nbCaracteresRencontres++;
        i++;
    }while(caractereRecontre !='\0');
    printf("\n");
    
    for(i = 0; i < afd->nbEtats; i++)
    {
        printf("%d\t",i);
        for(int j = 0; j < nbCaracteresRencontres -1; j++){
            caractereRecontre = afd->caracteresRencontres[j];
            printf("%d\t", afd->transitions[i][caractereRecontre-' ']);
        }
        printf("\n");
    }
}



int executer_AFD_rec(int etat_actuel, char chaine_restante[], AFD *afd, int profondeur)
{
    printf("(%d, %s) |-\t", etat_actuel, chaine_restante);

    if(*chaine_restante == '\0')
    {
        return afd->etats[etat_actuel];
    }
    else
    {
        if(afd->transitions[etat_actuel][*chaine_restante-' '] == -1)
        {
            return 0;
        }
        else
        {
            return executer_AFD_rec(afd->transitions[etat_actuel][*chaine_restante-' '], &chaine_restante[1], afd, profondeur+1);
        }
    }
}