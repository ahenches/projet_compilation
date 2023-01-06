#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./afd.h"
#include "./afn.h"

//Auteurs : Arnaud Henches, Maud Lestienne

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
    
    // determinisation
	afd afd_ = determinisationAFN(&afn_);
	afficherAFD(&afd_);
	for(int i = 2; i < argc; i++)
	{
		// parcours de l'afd
		if (executer_AFD_rec(0, argv[i], &afd_))
			printf("ok\n");
		else
			printf("ko\n");
	}

	// minimisation
    afd afdm = minimisation(&afd_);
    afficherAFD(&afdm);
	for(int i = 2; i < argc; i++)
	{
		// parcours de l'afd réduit 
        if (executer_AFD_rec(0, argv[i], &afdm))
			printf("ok\n");
		else
			printf("ko\n");
	}
	
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

    // libération afdm
	free(afdm.etats); 
	for(int i = 0; i < afdm.nombre_etats; i++)
	{
		free(afdm.transitions[i]);
	}
	free(afdm.transitions);


	return 0;
}


