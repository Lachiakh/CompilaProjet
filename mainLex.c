#include "lex.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>



//char caractereCourant ; //CHANGED INT TO CHAR & REMOVED EXTERN
//Symbole symboleCourant;// REMOVED EXTERN


Dlist *list = NULL; /* Déclaration d'une liste vide */
//node_token *node_token_courant ;


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
	bool result_analyse_syntaxique=_starting() ;
        printf("RESULTAT DE L'ANALYSE SYNTAXIQUE: %d", result_analyse_syntaxique);

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



Dlist *dlist_new(void)
{
    Dlist *p_new = malloc(sizeof *p_new);
    if (p_new != NULL)
    {
        p_new->length = 0;
        p_new->p_head = NULL;
        p_new->p_tail = NULL;
    }
    return p_new;
}

Dlist *dlist_append(Dlist *p_list,Symbole symbole)
{
    if (p_list != NULL) /* On vérifie si notre liste a été allouée */
    {
        struct node_token *p_new = malloc(sizeof *p_new); /* Création d'un nouveau node */
        if (p_new != NULL) /* On vérifie si le malloc n'a pas échoué */
        {
            p_new->Symbole_Courant.code= symbole.code; /* On 'enregistre' notre donnée */
            strcpy(p_new->Symbole_Courant.nom,symbole.nom) ;
            p_new->p_next = NULL; /* On fait pointer p_next vers NULL */
            if (p_list->p_tail == NULL) /* Cas où notre liste est vide (pointeur vers fin de liste à  NULL) */
            {
                p_new->p_prev = NULL; /* On fait pointer p_prev vers NULL */
                p_list->p_head = p_new; /* On fait pointer la tête de liste vers le nouvel élément */
                p_list->p_tail = p_new; /* On fait pointer la fin de liste vers le nouvel élément */
            }
            else /* Cas où des éléments sont déjà présents dans notre liste */
            {
                p_list->p_tail->p_next = p_new; /* On relie le dernier élément de la liste vers notre nouvel élément (début du chaînage) */
                p_new->p_prev = p_list->p_tail; /* On fait pointer p_prev vers le dernier élément de la liste */
                p_list->p_tail = p_new; /* On fait pointer la fin de liste vers notre nouvel élément (fin du chaînage: 3 étapes) */
            }
            p_list->length++; /* Incrémentation de la taille de la liste */
        }
    }
    return p_list; /* on retourne notre nouvelle liste */
}

void getNext(){
    struct node_token *p_temp=node_token_courant;
    if(node_token_courant!=NULL){
        node_token_courant=p_temp->p_next ;
    }
}
 void getBack(){
        struct node_token *p_temp=node_token_courant ;
        if(node_token_courant!=NULL){
            node_token_courant=p_temp->p_prev ;
    }
 }


void dlist_delete(Dlist **p_list)
{
    if (*p_list != NULL)
    {
        struct node_token *p_temp = (*p_list)->p_head;
        while (p_temp != NULL)
        {
            struct node_token *p_del = p_temp;
            p_temp = p_temp->p_next;
            free(p_del);
        }
        free(*p_list), *p_list = NULL;
    }
}
