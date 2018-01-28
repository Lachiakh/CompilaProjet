#include "lex.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


extern int caractereCourant ;
extern Symbole symboleCourant;

int main( int argc, char ** argv ) {
    OuvrirFichier("source.txt");
    LireCaractere();
    printf("..............................  %c \n",caractereCourant) ;
    	while(symboleCourant.code!=FIN_TOKEN){
    	

        SymbolSuivant();
         AfficherToken();
    }



    FermerFichier();
        printf("******************************fin ************************* \n") ;

    return 0;
}

