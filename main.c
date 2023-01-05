#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./afd.h"
#include "./afn.h"


int main( int argc, char *argv[ ] )
{
	afn afn_ = genererAFN(argv[1]);	
	for(int i = 2; i < argc; i++)
	{
		// parcours de l'afn
		if (executer_AFN_rec(0, argv[i], &afn_, OFFSET_FOR_RECURSIVE_EXEC))
			printf("ok\n");
		else
			printf("ko\n");
	}
	afd afd_ = determinisationAFN(&afn_);
	afficherAFD(&afd_);
	// determinisation
	for(int i = 2; i < argc; i++)
	{
		// parcours de l'afd
		if (executer_AFD_rec(0, argv[i], &afd_, 0))
			printf("ok\n");
		else
			printf("ko\n");
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

	// NE PAS OUBLIER DE FREE LA MEMOIRE


	// LIBERATION DE MEMOIRE // 
	free(afn_.alphabet.lettres); // libération alphabet
	
	// libération afn_
	free(afn_.sont_etats_finals); 
	for(int i = 0; i < afd_.nombre_etats; i++)
	{
		free(afn_.etats_transitions[i]);
	}
	free(afn_.etats_transitions);
	
	// libération afd_
	free(afd_.etats); 
	for(int i = 0; i < afd_.nombre_etats; i++)
	{
		free(afd_.transitions[i]);
	}
	free(afd_.transitions);


	return 0;
}


