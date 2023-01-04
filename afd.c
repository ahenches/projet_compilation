#include "afd.h"
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



void afficherAFD(afd *afd)
{
    char caractereRecontre;
    printf("afd.nombre_etats %d\n", afd->nombre_etats);
    
    for(int i = 0; i < afd->nombre_etats; i++)
    {
        if(afd->etats[i] != 0)
        {
            printf("%d ",i);
        }
		else
			printf("NF%d ",i);
    }
    printf("\n\t");

	for(int i = 0; i < afd->alphabet.nombre_lettres; i++)
	{
        printf("%c\t", afd->alphabet.lettres[i]);
	}
	printf("\n");
    for(int i = 0; i < afd->nombre_etats; i++)
    {
        printf("%d\t", i);
        for(int j = 0; j < afd->alphabet.nombre_lettres; j++){
            //caractereRecontre = afd->alphabet.lettres[j];
            //printf("%d\t", afd->transitions[i][afd->alphabet.correspondance[caractereRecontre-' ']]);
            printf("%d\t", afd->transitions[i][j]);
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

// fonctions outils qui servent à determiniser

bool est_set_etats_egaux(etats_non_determine * etat1, etats_non_determine * etat2)
{
	
		printf("\netats1\n");
	for(int i = 0; i < etat1->nombre_etats_non_determine; i++)
	{
		printf("%d ", etat1->etats[i]);
	}
		printf("\netats2\n");
	for(int i = 0; i < etat2->nombre_etats_non_determine; i++)
	{
		printf("%d ", etat2->etats[i]);
	}
	
	if (etat1->nombre_etats_non_determine != etat2->nombre_etats_non_determine) return 0;
	else 
	{
		for(int i = 0; i < etat1->nombre_etats_non_determine; i++)
		{
			if (etat1->etats[i] != etat2->etats[i]) return 0;
		}
		return 1;
	}	
}

int indice_set_etats_dans_tableau(etats_non_determine * etats, etats_non_determine ** liste_set_etats, int taille_liste)
{
	for(int i = 0; i < taille_liste; i++)
	{
		printf("INDICE %d\n", i);
		if (est_set_etats_egaux(etats, liste_set_etats[i])) return i;
	}
	return -1;
}

// fin fonctions outils

afd determinisationAFN(afn * afn_a_determiniser)
{
	int nombre_max_etats = afn_a_determiniser->nombre_etats * afn_a_determiniser->alphabet.nombre_lettres+1;
	afd afd_a_renvoyer = nouveauAFD(nombre_max_etats, &afn_a_determiniser->alphabet);
	
	etats_non_determine * file[nombre_max_etats];

	etats_non_determine etats_0;
	etats_0.etats[0] = 0;
	etats_0.nombre_etats_non_determine = 1;

	file[0] = &etats_0;

	int etat_actuel;
	afd_a_renvoyer.nombre_etats = 1;
	bool est_final;
	int taille_file = 1, indice_parcours = 0, indice_dans_file;
	
	while (indice_parcours < taille_file)
	{
		printf("indice_parcours%d\n", indice_parcours);
		est_final = 0;
		for (int j = 0; j < file[indice_parcours]->nombre_etats_non_determine; j++)
		{
			etat_actuel = file[indice_parcours]->etats[j];
			printf("etat_actuel%d\n", etat_actuel);
			for(int indice_lettre = 0; indice_lettre < afn_a_determiniser->alphabet.nombre_lettres; indice_lettre++)
			{
				printf("indice_lettre%d\n", indice_lettre);
				etats_non_determine * etats_transition = &afn_a_determiniser->etats_transitions[etat_actuel][indice_lettre];
				// Verification si etat_N_actuel est déjà dans file sinon on le rajoute
				if (etats_transition->nombre_etats_non_determine > 0)
				{
					indice_dans_file = indice_set_etats_dans_tableau(etats_transition, file, taille_file);
					printf("indice_dans_file%d\n", indice_dans_file);
					if (indice_dans_file == -1)
					{
						file[taille_file] = etats_transition;
						taille_file++;
						
						afd_a_renvoyer.transitions[indice_parcours][indice_lettre] = afd_a_renvoyer.nombre_etats;
						afd_a_renvoyer.nombre_etats++;
					}
					else 
					{
						afd_a_renvoyer.transitions[indice_parcours][indice_lettre] = indice_dans_file;
					}
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

afd minimisation(afd *afd_)
{
    afd afdMinimise;
    int taille = afd_->nombre_etats;
    int etatArrivee1, etatArrivee2, indice =0;
    char carCourant;
	char **table1 = (char**)malloc(sizeof(char*) * taille);
    char **copie_table1 =  (char**)malloc(sizeof(char*) * taille);
    int tabCouleur[taille];
    int couleur;

	for (int i =0; i< taille; i++)
	{
		table1[i] = (char*) malloc(sizeof(char) * taille);
		copie_table1[i] = (char*) malloc(sizeof(char) * taille);
	}

    for (int i=0 ; i < taille ; i++)
    {
        for(int j = 0; j < taille; j++)
        {
            table1[i][j] = '0';
            copie_table1[i][j] = '0';
        }
    }

    for(int l = 1; l < taille; l++)
    {
        for(int c =0; c < l; c++)
        {
            if((afd_->etats[l]== 0 && afd_->etats[c] ==1)||(afd_->etats[l]== 1 && afd_->etats[c] ==0))
            {
                table1[l][c] = 'X';
            }
        }
    }

    printf("%d\n", taille);
       	for(int i=0; i < taille; i++)
        {
            printf("\t%d", i);
        }
        printf("\n");

        for(int l = 1; l < taille; l++)
        {
            printf("%d\t",l);
            for(int c =0; c < l; c++)
            {
                printf("%c\t", table1[l][c]);
            }
            printf("\n");
        }
    	printf("\n----------------------------------------------------\n");
    do
    {
        //Copie de la table
        for(int l = 1; l < taille; l++)
        {
            for(int c =0; c < l; c++)
            {
                copie_table1[l][c] = table1[l][c];
            }
        }

        for(int l = 1; l < taille; l++)
        {
            for(int c =0; c < l; c++)
            {
                
                for(int car =0; car < afd_->alphabet.nombre_lettres; car++ )
                {
                    carCourant = afd_->alphabet.lettres[car];
                    if(afd_->transitions[l][carCourant-' ']!= afd_->transitions[c][carCourant-' '])
                    {
                        if(afd_->transitions[l][carCourant-' '] == -1 || afd_->transitions[c][carCourant-' '] == -1 )
                        {
                            table1[l][c] = 'X';
                        }
                        else
                        {
                            etatArrivee1 = afd_->transitions[l][carCourant-' '];
                            etatArrivee2 = afd_->transitions[c][carCourant-' '];
                            if(table1[max(etatArrivee1,etatArrivee2)][min(etatArrivee1,etatArrivee2)] == 'X')
                            {
                                table1[l][c] = 'X';
                            }
                        }
                    }
                } 
            }
        }
        printf("%d\n", taille);
       	for(int i=0; i < taille; i++)
        {
            printf("\t%d", i);
        }
        printf("\n");

        for(int l = 1; l < taille; l++)
        {
            printf("%d\t",l);
            for(int c =0; c < l; c++)
            {
                printf("%c\t", table1[l][c]);
            }
            printf("\n");
        }
    	printf("\n----------------------------------------------------\n");
        indice++;
    } while (sont_identique(table1,copie_table1, taille) != 1);
    

    //Nouveaux sommets Colorisation pour trouver le nouveau nombre de sommets
    couleur = 0;
    for(int i = 0; i < taille; i++)
    {
        tabCouleur[i] = -1;
    }
    for(int l = 1; l < taille; l++)
    {
        for(int c =0; c < l; c++)
        {
            if(table1[l][c] == '0')
            {
                if(tabCouleur[l]== -1 && tabCouleur[c] == -1)
                {
                    couleur++;
                    tabCouleur[l] = couleur;
                    tabCouleur[c] = couleur;
                }
                else if(tabCouleur[l]== -1)
                {
                    tabCouleur[l] = tabCouleur[c];
                }
                else if(tabCouleur[c]== -1)
                {
                    tabCouleur[c] = tabCouleur[l];
                }
            }
        }
    }
    for(int i = 0; i < taille; i++)
    {
        if(tabCouleur[i] == -1)
        {
            couleur++;
            tabCouleur[i] = couleur;
        }
        printf("%d : %d\n", i, tabCouleur[i]);
    }
    printf("couleur : %d\n", couleur);

    int etatMarque[couleur];
    int etatCourant;
    for(int i = 0; i < couleur; i++)
    {
        etatMarque[i] = 0;
    }

    afdMinimise = nouveauAFD(couleur, &afd_->alphabet);
    afdMinimise.alphabet = afd_->alphabet;

    for(int i = 0 ; i < taille; i++)
    {
        etatCourant = tabCouleur[i] -1;
        if(etatMarque[etatCourant] == 0)
        {
            for (int car = 0; car < afd_->alphabet.nombre_lettres; car++)
            {
                carCourant = afd_->alphabet.lettres[car];
                afdMinimise.transitions[etatCourant][carCourant - ' '] = tabCouleur[afd_->transitions[i][carCourant - ' ']] -1;
            }
        }
        if(afd_->etats[i] == 1)
        {
            afdMinimise.etats[etatCourant] = 1;
        }
    }

    return afdMinimise;
}
