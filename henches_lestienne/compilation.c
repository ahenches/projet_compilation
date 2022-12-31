#include "compilation.h"


int main (int argc, char** argv)
{
    /*if(argc > 1){
         lectureFichier(argv[1]);
    }*/
  
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




AFD nouveauAFD(int nbEtats)
{
    AFD afd;

    afd.nbEtats = nbEtats;
    afd.etats = (int*)malloc(nbEtats*sizeof(int));
    afd.transitions =  (int**)malloc(nbEtats*sizeof(int*));
    for(int i = 0; i < nbEtats; i++)
    {
        afd.transitions[i] = (int*)malloc(NB_CARACTERE_MAX*sizeof(int));
    }
    for(int i=0; i< nbEtats; i++)
    {
        afd.etats[i] = 0;
        for(int j =0; j<NB_CARACTERE_MAX; j++)
        {
            afd.transitions[i][j] = -1;
        }
    }
    afd.caracteresRencontres[NB_CARACTERE_MAX] = '\0';
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

int executer_AFN_rec(int etat_actuel, char chaine_restante[], AFD *afd, int profondeur) // return 1 si mot restant valide PEUT ETRE RECURSIVE OU NON 
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
            return executer_AFN_rec(afd->transitions[etat_actuel][*chaine_restante-' '], &chaine_restante[1], afd, profondeur+1);
        }

    }


}