#include <stdio.h>

int main( int argc, char *argv[ ] )
{
	printf("%d\n", argc);
	
	
	for(int i = 0; i < argc; i++)
	{
		// parcours de l'afn
		printf("%s\n", argv[i]);
	}
	for(int i = 0; i < argc; i++)
	{
		// parcours de l'afd
	}
	for(int i = 0; i < argc; i++)
	{
		// parcours de l'afd réduit
	}


	return 0;
}
