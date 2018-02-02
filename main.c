#include "lex.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main( int argc, char ** argv ) {
	OuvrirFichier("source.txt");
	LireCaractere();
	list=dlist_new() ;
	while(symboleCourant.code!=FIN_TOKEN){
		SymbolSuivant(); 
		AfficherToken();       
		dlist_append(list,symboleCourant) ;
		if(symboleCourant.code==FIN_TOKEN) break ; //BRING IT HERE TO THE BOTTOM   		    
	}
	// AfficherToken();
	node_token_courant=list->p_head ;
	bool result=_starting() ;
	printf("RESULTAT DU SYNTAXIQUE: %d",result);
	//printf(result);

       /*
       for(int i=0;i<30;i++){
            if(node_token_courant!=NULL){
                printf(" #%d....yes we can...%s\n",node_token_courant->Symbole_Courant.code,node_token_courant->Symbole_Courant.nom) ;
                fflush(stdout);
                getNext() ;
            }
       }
       */
       
       printf("****************************************************************************\n") ;
       getBack() ;
       while(node_token_courant!=NULL){
            printf(" #%d....yes we can...%s\n",node_token_courant->Symbole_Courant.code,node_token_courant->Symbole_Courant.nom) ;
                        fflush(stdout);
            getBack() ;
       }
	
       FermerFichier();
       dlist_delete(&list) ;// ADDED &

       printf("******************************Fin******************************* \n") ;

       return 0;
}
