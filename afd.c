#include "afd.h"
//Auteurs : Arnaud Henches, Maud Lestienne


/**
 * @brief Pemet d'instancier les variables de la structure afd
 * 
 * @param nombre_etats le nombre d etats de l afd 
 * @param alphabet l'alphabet que l on passe à l'afd 
 * @return afd instancié
 */
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

/**
 * @brief Permet d'afficher l'afd passé en paramètre
 * 
 * @param afd l'afd a afficher
 */
void afficherAFD(afd *afd)
{
    char caractereRecontre;

    //Affichage du nombre d'etats
    printf("%d\n", afd->nombre_etats);
    
    //Affichage des etats finaux
    for(int i = 0; i < afd->nombre_etats; i++)
    {
        if(afd->etats[i] != 0)
        {
            printf("%d ",i);
        }
    }
    printf("\n\t");

    //Affichage des transitions
	for(int i = 0; i < afd->alphabet.nombre_lettres; i++)
	{
        printf("%c \t", afd->alphabet.lettres[i]);
	}
	printf("\n");
    for(int i = 0; i < afd->nombre_etats; i++)
    {
        printf("%d\t", i);
        for(int j = 0; j < afd->alphabet.nombre_lettres; j++){
            printf("%d\t", afd->transitions[i][j]);
        }
        printf("\n");
    }
}

/**
 * @brief Permet d executer l afd sur un mot, la fonction est recursive 
 * 
 * @param etat_actuel l'etat dans lequel on se trouve
 * @param chaine_restante le reste du mot a traiter
 * @param afd l afd sur lequel on execute le mot
 * @return true si le mot est valide pour l automate
 * @return false si le mot n est pas valide pour l'automate
 */
bool executer_AFD_rec(int etat_actuel, char chaine_restante[], afd *afd)
{
    //Affichage de l'etat actuel et du reste du mot a traiter
    printf("(%d, %s) |- ", etat_actuel, chaine_restante);

    //Fin du mot, on regarde si l etat actuel est terminal pour savoir si le mot est valide
    if(*chaine_restante == '\0')
    {
        return afd->etats[etat_actuel];
    }
    //Le mot n est pas fini, on lance la recursion si il existe une transiton pour l etat actuel avec le carcatere du mot
    //Sinon on retourne false car on ne va pas au bout du mot
    else
    {
        if(afd->transitions[etat_actuel][afd->alphabet.correspondance[*chaine_restante-' ']] == -1)
        {
            return 0;
        }
        else
        {
            return executer_AFD_rec(afd->transitions[etat_actuel][afd->alphabet.correspondance[*chaine_restante-' ']], &chaine_restante[1], afd);
        }
    }
}

// fonctions outils qui servent à determiniser

bool est_set_etats_egaux(etats_non_determinises * etats1, etats_non_determinises * etats2)
{
	
	if (etats1->nombre_etats_non_determinises != etats2->nombre_etats_non_determinises) return 0;
	else 
	{
		for(int i = 0; i < etats1->nombre_etats_non_determinises; i++)
		{
			if (etats1->etats[i] != etats2->etats[i]) return 0;
		}
		return 1;
	}	
}

int indice_set_etats_dans_tableau(etats_non_determinises * etats, etats_non_determinises ** liste_set_etats, int taille_liste)
{
	// printf("\t\t\t\t\tTEST_AFFICHAGE\n");
	for(int i = 0; i < taille_liste; i++)
	{
		// printf("\t\t\t\t\tINDICE %d\n", i);
		if (est_set_etats_egaux(etats, liste_set_etats[i])) return i;
	}
	return -1;
}

void set_etats_union(etats_non_determinises * etats1, etats_non_determinises * etats2) // fais l'union du set etats1, etats2 dans etats1
{
	bool etat_de_2_dans_1 = 0;
	for(int i = 0; i < etats2->nombre_etats_non_determinises; i++)
	{
		etat_de_2_dans_1 = 0;
		for (int j = 0; j < etats1->nombre_etats_non_determinises; j++)
		{
			if (etats2->etats[i] == etats1->etats[j]) etat_de_2_dans_1 = 1;
		}
		if (etat_de_2_dans_1 == 0) 
		{
			etats1->etats[etats1->nombre_etats_non_determinises++] = etats2->etats[i];
		}
	}

}

// fin fonctions outils

afd determinisationAFN(afn * afn_a_determiniser)
{
	int nombre_max_etats = afn_a_determiniser->nombre_etats * afn_a_determiniser->alphabet.nombre_lettres+1;
	afd afd_a_renvoyer = nouveauAFD(nombre_max_etats, &afn_a_determiniser->alphabet);
	
	etats_non_determinises * file[nombre_max_etats];

	etats_non_determinises etats_0;
	etats_0.etats[0] = 0;
	etats_0.nombre_etats_non_determinises = 1;

	file[0] = &etats_0;
	int indice_ensemble_vide = -1;
	int etat_actuel;
	afd_a_renvoyer.nombre_etats = 1;
	bool est_final;
	int taille_file = 1, indice_parcours = 0, indice_dans_file;
	
	while (indice_parcours < taille_file)
	{
		est_final = 0;
		for(int indice_lettre = 0; indice_lettre < afn_a_determiniser->alphabet.nombre_lettres; indice_lettre++)
		{
			if (file[indice_parcours]->nombre_etats_non_determinises == 0)
			{
				for(int indice_lettre = 0; indice_lettre < afn_a_determiniser->alphabet.nombre_lettres; indice_lettre++)
				{
					afd_a_renvoyer.transitions[indice_parcours][indice_lettre] = indice_ensemble_vide;
				}
			}
			else 
			{
				etats_non_determinises * etats_transition;
				etats_non_determinises * etats_totaux = malloc(sizeof(etats_non_determinises));
				etats_totaux->nombre_etats_non_determinises = 0;
				for (int j = 0; j < file[indice_parcours]->nombre_etats_non_determinises; j++)
				{
					etat_actuel = file[indice_parcours]->etats[j];
					etats_transition = &afn_a_determiniser->etats_transitions[etat_actuel][indice_lettre];
					set_etats_union(etats_totaux, etats_transition);
					if (afn_a_determiniser->sont_etats_finals[etat_actuel]) est_final = 1;
				}
				// Verification si etats_totaux est déjà dans file sinon on le rajoute
				if (indice_ensemble_vide == -1 && etats_totaux->nombre_etats_non_determinises == 0) indice_ensemble_vide = taille_file;
				indice_dans_file = indice_set_etats_dans_tableau(etats_totaux, file, taille_file);
				if (indice_dans_file == -1)
				{
					file[taille_file] = etats_totaux;
					taille_file++;

					afd_a_renvoyer.transitions[indice_parcours][indice_lettre] = afd_a_renvoyer.nombre_etats;
					afd_a_renvoyer.nombre_etats++;
				}
				else 
				{
					free(etats_totaux);
					afd_a_renvoyer.transitions[indice_parcours][indice_lettre] = indice_dans_file;
				}
			}
		}
		afd_a_renvoyer.etats[indice_parcours] = est_final;
		indice_parcours++;
	}
	for (int i = 1; i < taille_file; i++)
		free(file[i]);
	return afd_a_renvoyer;
}

//Fonctions pour la minimisation

/**
 * @brief Permet de savoir si le triangle inferieur gauche des tableaux sont identiques
 * 
 * @param tab1 un des tableaux a comparer
 * @param tab2  un des tableaux a comparer
 * @param taille la taille des tableaux
 * @return int 1 si les triangles inferieurs gauche sont identique sinon 0
 */
int sont_identique(char **tab1, char **tab2, int taille )
{
    int ide ;
    ide = 1;
    for(int l = 1; l < taille; l++)
    {
        for(int c =0; c < l; c++)
        {
            if(tab1[l][c] != tab2[l][c])
            {
                ide = 0;
            }
        }
    }
    return ide;
}

/**
 * @brief Minimise l' afd passe en parametre
 * On utilise l alogorithme de recherche d etats separables avec la methode de remplissage de table
 * source : https://fr.wikipedia.org/wiki/Minimisation_d%27un_automate_fini_déterministe 
 * 
 * @param afd_ l afd a minimisé
 * @return afd l afd minimisé 
 */
afd minimisation(afd *afd_)
{
    afd afdMinimise;
    int taille = afd_->nombre_etats;
    int etatArrivee1, etatArrivee2;
    char carCourant;
	char **table1 = (char**)malloc(sizeof(char*) * taille); //la table que l on rempli indexe par les etats de l afd 
    char **copie_table1 =  (char**)malloc(sizeof(char*) * taille); //copie de la table pour savoir quand s arreter
    int tabCouleur[taille]; //Tableau pour la colorisation des etats
    int couleur;

    //Allocation memoire et initialisation des tableaux
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

    //On met une croix dans une case quand l un des etat est terminal et l autre non (les etats etant les indices de la case)
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

                    //On met une croix dans une case quand les 2 etats n ont pas le meme etats d arrivé pour une transition sur un caractere (les etats sont les indices de la case)
                    if(afd_->transitions[l][afd_->alphabet.correspondance[carCourant-' ']]!= afd_->transitions[c][afd_->alphabet.correspondance[carCourant-' ']])
                    {
                        if(afd_->transitions[l][afd_->alphabet.correspondance[carCourant-' ']] == -1 || afd_->transitions[c][afd_->alphabet.correspondance[carCourant-' ']] == -1 )
                        {
                            table1[l][c] = 'X';
                        }
                        else
                        {
                            etatArrivee1 = afd_->transitions[l][afd_->alphabet.correspondance[carCourant-' ']];
                            etatArrivee2 = afd_->transitions[c][afd_->alphabet.correspondance[carCourant-' ']];
                            if(table1[max(etatArrivee1,etatArrivee2)][min(etatArrivee1,etatArrivee2)] == 'X')
                            {
                                table1[l][c] = 'X';
                            }
                        }
                    }
                } 
            }
        }
    } while (sont_identique(table1,copie_table1, taille) != 1);
    

    //Nouveaux sommets Colorisation pour trouver le nouveau nombre de sommets
    couleur = -1;
    for(int i = 0; i < taille; i++)
    {
        tabCouleur[i] = -1;
    }
    for(int l = 1; l < taille; l++)
    {
        for(int c =0; c < l; c++)
        {
            //Si une case est sans croix les etats doivent regroupés ont leur attribut la meme couleur
            if(table1[l][c] == '0')
            {
                //Si aucun des etats n a encore de couleur attribué ont leur associe une nouvelle couleur
                if(tabCouleur[l]== -1 && tabCouleur[c] == -1)
                {
                    couleur++;
                    tabCouleur[l] = couleur;
                    tabCouleur[c] = couleur;
                }
                //Sinon on associe la couleur de l'un à l'autre car ils sont du meme groupe
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
    //On associe une nouvelle couleur aux etats seuls
    for(int i = 0; i < taille; i++)
    {
        if(tabCouleur[i] == -1)
        {
            couleur++;
            tabCouleur[i] = couleur;
        }
    }

    int etatMarque[couleur + 1];
    int etatCourant;
    for(int i = 0; i < couleur +1; i++)
    {
        etatMarque[i] = 0;
    }

    //On creer le nouvel afd
    afdMinimise = nouveauAFD(couleur+1, &afd_->alphabet);
    afdMinimise.alphabet = afd_->alphabet;

    for(int i = 0 ; i < taille; i++)
    {
        etatCourant = tabCouleur[i];
        if(etatMarque[etatCourant] == 0)
        {
            for (int car = 0; car < afd_->alphabet.nombre_lettres; car++)
            {
                //On prends les transitions du premier etat que l on croise pour le groupe
                carCourant = afd_->alphabet.lettres[car];
                afdMinimise.transitions[etatCourant][afd_->alphabet.correspondance[carCourant-' ']] = tabCouleur[afd_->transitions[i][afd_->alphabet.correspondance[carCourant-' ']]] ;
            }
        }
        //Si un groupe possede un etat accepteur alors le groupe devient accepteur
        if(afd_->etats[i] == 1)
        {
            afdMinimise.etats[etatCourant] = 1;
        }
    }

    //Liberation de la memoire
    for (int i =0; i< taille; i++)
	{
		free(table1[i]); 
		free(copie_table1[i]);
	}
    free(table1);
    free(copie_table1);

    return afdMinimise;
}
