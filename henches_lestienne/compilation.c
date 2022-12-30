#include "compilation.h"


int main (int argc, char** argv)
{
    if(argc > 1){
         lectureFichier(argv[1]);
    }

    return 0;
}

void lectureFichier(char* nomFichier){
    FILE* fichier = NULL;
    int nbEtat, etatAccepteur, etatDepart, etatArrivee;
    char charTransition; 
    int i =0;
    char chaine[TAILLE_CHAINE] ="";
    fichier = fopen(nomFichier, "r");

    if(fichier != NULL)
    {
        fgets(chaine, TAILLE_CHAINE, fichier);        
        sscanf(chaine, "%d",&nbEtat);
        // Creation des etats et de l'etat initial

        fgets(chaine, TAILLE_CHAINE, fichier);
        while(i< TAILLE_CHAINE && chaine[i]!='\r'&& chaine[i]!='\n')
        {
            etatAccepteur =0;
            if(chaine[i]!=' ')
            {
                etatAccepteur = chaine[i] - '0';
                if(chaine[i+1]!=' ' && chaine[i+1]!='\r')//si l'etat est un nombre et non un chiffre
                {
                    i++;
                    etatAccepteur = etatAccepteur*10 + (chaine[i]-'0');
                }
                //Ajout des etats accepteurs
            }
            i++;
        }

        while(fgets(chaine,TAILLE_CHAINE,fichier) != NULL)
        {
            sscanf(chaine, "%d %c %d",&etatDepart,&charTransition,&etatArrivee);
            //Ajout des transitions
        }
        
        fclose(fichier);
    }
    else 
    {
        printf("Impossible d'ouvrir le fichier\n");
    }
}