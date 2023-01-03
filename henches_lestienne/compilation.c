#include "compilation.h"

//////////////////////////////////////////////////////////////////////////////
int main( int argc, char *argv[ ] )
{
	afn afn_ = genererAFN(argv[1]);	

	for(int i = 2; i < argc; i++)
	{
		// parcours de l'afn
		printf("%s\n", argv[i]);
		if (executer_AFN_rec(0, argv[i], &afn_, -3))
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

	return 0;
}

afd minimisation(afd *afd_)
{
    afd afdMinimise;
    int taille = afd_->nbEtats;
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

    afdMinimise = nouveauAFD(couleur);
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