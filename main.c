#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./automate.h"

int main( int argc, char *argv[ ] )
{
	afn afn_ = genererAFN(argv[1]);	
	etats_N_det etats_0, etats_1, e1= {0}, e2 = {0}, e3= {0}, e4= {0};
	e2.nombre_etats_N_det = 0;
	e1.etats[0] = 5;
	e1.nombre_etats_N_det++;
	etats_N_det * l[5];
	l[3] = &etats_1;
	l[0] = &e1;
	l[1] = &e2;
	l[2] = &e4;
	l[4] = &e3;
	etats_1.etats[0] = 0;
	etats_1.etats[1] = 5;
	etats_1.etats[2] = 4;
	etats_1.etats[3] = 1;
	etats_0.etats[0] = 0;
	etats_0.etats[1] = 5;
	etats_0.etats[2] = 4;
	etats_0.etats[3] = 1;
	etats_1.nombre_etats_N_det = 4;
	etats_0.nombre_etats_N_det = 4;
	//printf("%d", indice_set_etats_dans_tableau(&etats_0, l, 5));
	for(int i = 2; i < argc; i++)
	{
		// parcours de l'afn
		printf("%s\n", argv[i]);
		if (executer_AFN_rec(0, argv[i], &afn_, -3))
			printf("Mot Valide !\n");
		else
			printf("Mot NON Valide !\n");
	}
	afd afd_ = determinisationAFN(&afn_);
	afficherAFD(&afd_);
	// determinisation
	/*
	for(int i = 2; i < argc; i++)
	{
		// parcours de l'afd
		printf("%s\n", argv[i]);
		if (executer_AFD_rec(0, argv[i], &afd_, 0))
			printf("Mot Valide !\n");
		else
			printf("Mot NON Valide !\n");
	}
	*/
	// minimalisation
	for(int i = 2; i < argc; i++)
	{
		// parcours de l'afd réduit 
	}
	///////////////////////Test AFD///////////////////////////
/*	afd afd_ = nouveauAFD(5);
	afd_.alphabet = afn_.alphabet;
    afd_.etats[0] = 1;
    afd_.etats[1] = 1;
    afd_.etats[2] = 1;
    afd_.etats[4] = 1;
    afd_.transitions[0]['a'-' '] = 1;
    afd_.transitions[0]['b'-' '] = 2;
    afd_.transitions[1]['a'-' '] = 3;
    afd_.transitions[1]['b'-' '] = 2;
    afd_.transitions[2]['a'-' '] = 4;
    afd_.transitions[2]['b'-' '] = 2;
    afd_.transitions[3]['a'-' '] = 3;
    afd_.transitions[3]['b'-' '] = 3;
    afd_.transitions[4]['a'-' '] = 3;
    afd_.transitions[4]['b'-' '] = 2;

    afficherAFD(&afd_);
    afd afdM = minimisation(&afd_);
    afficherAFD(&afdM);
   */ 
/*
    afd afdwiki;
    afdwiki = nouveauAFD(8);
    afdwiki.alphabet = afn_.alphabet;
    afdwiki.alphabet.lettres[0] = '0';
    afdwiki.alphabet.lettres[1] = '1';
    afdwiki.etats[2] = 1;
    afdwiki.etats[6] = 1;
    afdwiki.transitions[0]['0'-' '] = 1;
    afdwiki.transitions[0]['1'-' '] = 5;
    afdwiki.transitions[1]['0'-' '] = 6;
    afdwiki.transitions[1]['1'-' '] = 2;
    afdwiki.transitions[2]['0'-' '] = 0;
    afdwiki.transitions[2]['1'-' '] = 2;
    afdwiki.transitions[3]['0'-' '] = 2;
    afdwiki.transitions[3]['1'-' '] = 6;
    afdwiki.transitions[4]['0'-' '] = 7;
    afdwiki.transitions[4]['1'-' '] = 5;
    afdwiki.transitions[5]['0'-' '] = 2;
    afdwiki.transitions[5]['1'-' '] = 6;
    afdwiki.transitions[6]['0'-' '] = 6;
    afdwiki.transitions[6]['1'-' '] = 4;
    afdwiki.transitions[7]['0'-' '] = 6;
    afdwiki.transitions[7]['1'-' '] = 2;
    
    afficherAFD(&afdwiki);
    if(executer_AFD_rec(0, "01011", &afdwiki, 0)){
        printf("ok\n");
    }
    else{
        printf("ko\n");
    }
    afd afdM = minimisation(&afdwiki);
    afficherAFD(&afdM);
*/
/*
    afd afdcours;
    afdcours = nouveauAFD(6);
    afdcours.alphabet = afn_.alphabet;
    afdcours.etats[0] = 1;
    afdcours.etats[1] = 1;
    afdcours.etats[2] = 1;
    afdcours.etats[5] = 1;
    afdcours.etats[3] = 1;
    afdcours.transitions[0]['a'-' '] = 1;
    afdcours.transitions[0]['b'-' '] = 2;
    afdcours.transitions[1]['a'-' '] = 4;
    afdcours.transitions[1]['b'-' '] = 3;
    afdcours.transitions[2]['a'-' '] = 1;
    afdcours.transitions[2]['b'-' '] = 2;
    afdcours.transitions[3]['a'-' '] = 1;
    afdcours.transitions[3]['b'-' '] = 2;
    afdcours.transitions[4]['a'-' '] = 4;
    afdcours.transitions[4]['b'-' '] = 4;
    afdcours.transitions[5]['a'-' '] = 1;
    afdcours.transitions[5]['b'-' '] = 2;
    afficherAFD(&afdcours);
    afd afdM = minimisation(&afdcours);
    afficherAFD(&afdM);
*/


	//////////////////////////////////////////////////////////////////////////

	// NE PAS OUBLIER DE FREE LA MEMOIRE

	return 0;
}

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
	free(afn1.alphabet.lettres);
	afn1.alphabet.lettres = (char*)malloc(afn1.alphabet.nombre_lettres*sizeof(char));
	fseek(ptr, save, SEEK_SET);
	
	for(int i = 0; i < afn1.alphabet.nombre_lettres; i++)
	{
		printf("%de lettre : %c\n", i, afn1.alphabet.lettres[i]);
	}
	
	// deuxième parcours pour remplir le tableau des transitions à deux entrées (etat, lettre)
	i = 0;
	afn1.etats_transitions = malloc(nombre_etats * sizeof(etats_N_det *)); 
	for (int i = 0; i < nombre_etats; i++)
	{
		afn1.etats_transitions[i] = calloc(afn1.alphabet.nombre_lettres, sizeof(etats_N_det)); 
	}
	int etat_d, etat_f, indice_lettre, indice_etat_f;
	while(fgets(line, MAX_CARACTERE_PAR_LIGNE, ptr) != NULL)
	{
		etat_d = atoi(strtok(line, delim));
		res = strtok(NULL, delim);
		etat_f = atoi(strtok(NULL, delim));
		indice_lettre = afn1.alphabet.correspondance[*res - ' '];
		indice_etat_f = afn1.etats_transitions[etat_d][indice_lettre].nombre_etats_N_det++;
		afn1.etats_transitions[etat_d][indice_lettre].etats[indice_etat_f] = etat_f;
	}
	fclose(ptr);
	return afn1;
}

void afficher_n_fois(char * str, int n_fois)
{
	for (int j = 0; j < n_fois; j++)
		printf("%s", str);
}
int compter_digit(long long n)
{
	if (n/10 == 0)
		return 1;
	return 1 + compter_digit(n / 10);
}
 

bool executer_AFN_rec(int etat_actuel, char chaine_restante[], afn *afn, int taille_retrait) // return 1 si mot restant valide PEUT ETRE RECURSIVE OU NON 
{
	printf("(%d, %s)", etat_actuel, chaine_restante);
	if (*chaine_restante == '\0')
	{
		printf(afn->sont_etats_finals[etat_actuel] ? "|- ok" : "|- ko");
		printf("\n");
		return afn->sont_etats_finals[etat_actuel]; // renvoie Vrai si état_actuel est final Faux sinon
	}
	else {
		bool mot_restant_valide = 0;
		taille_retrait += compter_digit(etat_actuel) + strlen(chaine_restante) + 7;
		int i = 0;
		while(i < afn->etats_transitions[etat_actuel][afn->alphabet.correspondance[*chaine_restante-' ']].nombre_etats_N_det && !mot_restant_valide)
		{
			if (i > 0)
				afficher_n_fois(" ", taille_retrait);
			printf("|- ");
			mot_restant_valide = mot_restant_valide |  executer_AFN_rec(afn->etats_transitions[etat_actuel][afn->alphabet.correspondance[*chaine_restante-' ']].etats[i], &chaine_restante[1], afn, taille_retrait);
			i++;
		}
		if (afn->etats_transitions[etat_actuel][afn->alphabet.correspondance[*chaine_restante-' ']].nombre_etats_N_det == 0)
			 printf("|- ko \n");
		return mot_restant_valide;
	}
}

afd nouveauAFD(int nombre_etats, alphabet * alphabet)
{
    afd afd;
	afd.alphabet = *alphabet;
    afd.nombre_etats = nombre_etats;
    afd.etats = (bool *)malloc(nombre_etats*sizeof(bool));
    afd.transitions =  (int**)malloc(nombre_etats*sizeof(int*));
    for(int i = 0; i < nombre_etats; i++)
    {
		afd.etats[i] = 0;
        afd.transitions[i] = (int*)malloc(alphabet->nombre_lettres*sizeof(int));
		for (int j = 0; j<alphabet->nombre_lettres; j++)
		{
			afd.transitions[i][j] = -1;
		}
    }
    return afd;
}


bool est_set_etats_egaux(etats_N_det * etat1, etats_N_det * etat2)
{
	
		printf("\netats1\n");
	for(int i = 0; i < etat1->nombre_etats_N_det; i++)
	{
		printf("%d ", etat1->etats[i]);
	}
		printf("\netats2\n");
	for(int i = 0; i < etat2->nombre_etats_N_det; i++)
	{
		printf("%d ", etat2->etats[i]);
	}
	
	if (etat1->nombre_etats_N_det != etat2->nombre_etats_N_det) return 0;
	else 
	{
		for(int i = 0; i < etat1->nombre_etats_N_det; i++)
		{
			if (etat1->etats[i] != etat2->etats[i]) return 0;
		}
		return 1;
	}	
}

int indice_set_etats_dans_tableau(etats_N_det * etats, etats_N_det ** liste_set_etats, int taille_liste)
{
	for(int i = 0; i < taille_liste; i++)
	{
		printf("INDICE %d\n", i);
		if (est_set_etats_egaux(etats, liste_set_etats[i])) return i;
	}
	return -1;
}

afd determinisationAFN(afn * afn_a_determiniser)
{
	int nombre_max_etats = afn_a_determiniser->nombre_etats * afn_a_determiniser->alphabet.nombre_lettres+1;
	afd afd_a_renvoyer = nouveauAFD(nombre_max_etats, &afn_a_determiniser->alphabet);
	
	etats_N_det * file[nombre_max_etats];

	etats_N_det etats_0;
	etats_0.etats[0] = 0;
	etats_0.nombre_etats_N_det = 1;

	file[0] = &etats_0;

	int etat_actuel;
	afd_a_renvoyer.nombre_etats = 1;
	bool est_final;
	int taille_file = 1, indice_parcours = 0, indice_dans_file;
	
	printf("iadzkhzdhdosj%d\n", afn_a_determiniser->alphabet.nombre_lettres);
	while (indice_parcours < taille_file)
	{
		printf("indice_parcours%d\n", indice_parcours);
		est_final = 0;
		for (int j = 0; j < file[indice_parcours]->nombre_etats_N_det; j++)
		{
			etat_actuel = file[indice_parcours]->etats[j];
			printf("etat_actuel%d\n", etat_actuel);
			for(int indice_lettre = 0; indice_lettre < afn_a_determiniser->alphabet.nombre_lettres; indice_lettre++)
			{
				printf("indice_lettre%d\n", indice_lettre);
				etats_N_det etats_transition = afn_a_determiniser->etats_transitions[etat_actuel][indice_lettre];
				// Verification si etat_N_actuel est déjà dans file sinon on le rajoute
				indice_dans_file = indice_set_etats_dans_tableau(&etats_transition, file, taille_file);
				printf("indice_dans_file%d\n", indice_dans_file);
				if (indice_dans_file == -1)
				{
					file[taille_file] = &etats_transition;
					taille_file++;
					
					afd_a_renvoyer.transitions[indice_parcours][indice_lettre] = afd_a_renvoyer.nombre_etats;
					afd_a_renvoyer.nombre_etats++;
				}
				else 
				{
					afd_a_renvoyer.transitions[indice_parcours][indice_lettre] = indice_dans_file;
				}
			}
			if (afn_a_determiniser->sont_etats_finals[etat_actuel]) est_final = 1;
		}
		afd_a_renvoyer.etats[afd_a_renvoyer.nombre_etats] = est_final;
		indice_parcours++;	
	}
	printf("taille file = %d\n", taille_file);
	return afd_a_renvoyer;
}

void afficherAFD(afd *afd)
{
    char caractereRecontre;
    int i;
    printf("afd.nombre_etats %d\n", afd->nombre_etats);
    
    for(i = 0; i < afd->nombre_etats; i++)
    {
        if(afd->etats[i] != 0)
        {
            printf("%d ",i);
        }
    }
    printf("\n\t");
    i =0;
    do 
    {
        caractereRecontre = afd->alphabet.lettres[i];
        printf("%c\t", afd->alphabet.lettres[i]);
        i++;
    }while(caractereRecontre !='\0');
    printf("\n");
    
    for(i = 0; i < afd->nombre_etats; i++)
    {
        printf("%d\t",i);
        for(int j = 0; j < afd->alphabet.nombre_lettres; j++){
            caractereRecontre = afd->alphabet.lettres[j];
            printf("%d\t", afd->transitions[i][caractereRecontre-' ']);
        }
        printf("\n");
    }
}



bool executer_AFD_rec(int etat_actuel, char chaine_restante[], afd *afd, int profondeur)
{
    printf("(%d, %s) |- ", etat_actuel, chaine_restante);

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


