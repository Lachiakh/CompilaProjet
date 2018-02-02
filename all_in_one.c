#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "lex.h"





//****************************************************************************************************
// IMPLEMENTATION ANALYSEUR LEXICAL
//*****************************************************************************************************


FILE* fichier = NULL;

//Lis un caractère à partir du flux d'entrée ( fichier )
void LireCaractere() {
    char c = fgetc(fichier);
   // if ( isalpha(c) ) c = tolower(c);
     caractereCourant = c;
}

void SymbolSuivant(){

	/** Passer les séparateurs */
	while ( caractereCourant==' ' || caractereCourant=='\n' || caractereCourant=='\t' || caractereCourant=='\r')	LireCaractere();
    /** Passer le commentaires */
    PasserCommentaire();
   if ( caractereCourant=='"' || ((int)caractereCourant)==39) { // debut de chaine de caractère " chaine "
        LireChaine();
    }
	else if ( isalpha(caractereCourant) ) { // alphabétique ( mot clé OU identifier )
		LireMot();
	}
	else if ( isdigit(caractereCourant) ) { // numérique
        LireNombre();
    }
    else if ( isSpecial(caractereCourant) ) { // /*-+.,;:<>=
       LireSpecial();
    }
    else symboleCourant.code=FIN_TOKEN ;
}

//consommer les commentaires entre /* et */
void PasserCommentaire(){
	int i=1;
if(caractereCourant=='/'){
		LireCaractere();
		if (caractereCourant=='*'){
			while ( i==1){
		
			     LireCaractere();

			     if (caractereCourant=='*'){

			         LireCaractere();
			         if (caractereCourant=='/') {
                            i=0;
                            LireCaractere();
                     }
		          }
	        }
	
        }
        else if(caractereCourant=='/'){
        	LireCaractere();
            while(caractereCourant !='\n'){
                LireCaractere();
            }
            LireCaractere();

        }
}
}
//lecture des symboles spéciaux
void LireSpecial() {
    	int i = 0;
    	int codeChar;
        symboleCourant.nom[i] = caractereCourant;
    	switch( caractereCourant ) {
            case ';' : codeChar = POINT_VIRG_TOKEN; break;
            case '.' : codeChar = POINT_TOKEN; break;
             
            case '/' : 
        		LireCaractere();
        		if( caractereCourant == '=') {
            		codeChar=DIV_EGALE_TOKEN;
            		symboleCourant.nom[i+1] = caractereCourant;
                                    i++;		
            		}
                else
		          codeChar=DIV_TOKEN;break;

            case '+' :  
        		LireCaractere();
        		if( caractereCourant == '=') {
            		codeChar=PLUS_EGALE_TOKEN;
            		symboleCourant.nom[i+1] = caractereCourant;
                                    i++;		
            		}
                else if(caractereCourant=='+'){
        		     codeChar = PLUS_PLUS_TOKEN ;
        		     symboleCourant.nom[i+1] = caractereCourant;
                      i++;
					}
				else{
					codeChar=PLUS_TOKEN ;
				}
				 break;
            case '-' : 
        		LireCaractere();
        		if( caractereCourant == '=') {
            		codeChar=MOINS_EGALE_TOKEN;
            		symboleCourant.nom[i+1] = caractereCourant;
                    i++;		
            		}
                else if(caractereCourant=='-'){
                		codeChar=MOINS_MOINS_TOKEN ;
                		symboleCourant.nom[i+1] = caractereCourant;
                    	i++;
                	}
        		 	else  codeChar = MOINS_TOKEN; break;
                
            case '*' :
                    LireCaractere();
        		if( caractereCourant == '=') {
            		 codeChar=MULT_EGALE_TOKEN;
            		 symboleCourant.nom[i+1] = caractereCourant;
                                    i++;		
            		}
                else  codeChar = MULT_TOKEN; break;
            case ',' : 
                codeChar = VIR_TOKEN; break;
            case '=' : 
        		LireCaractere();
        		if( caractereCourant == '=') {
            		codeChar=EGALE_EGALE_TOKEN ;
            		symboleCourant.nom[i+1] = caractereCourant;
                    i++;		
            		}
                else
                  	codeChar = EGALE_TOKEN; break;
	    case '%' : 
        		LireCaractere();
        		if( caractereCourant == '=') {
            		codeChar=MOD_EGALE_TOKEN;
            		symboleCourant.nom[i+1] = caractereCourant;
                                    i++;		
            		}
                else
        	        codeChar=MOD_TOKEN;break;
	    
         case '^' : 
        		LireCaractere();
        		if( caractereCourant == '=') {
            		codeChar=PUISS_EGALE_TOKEN;
            		symboleCourant.nom[i+1] = caractereCourant;
                                    i++;		
            		}
                else
        	        codeChar=PUISS_TOKEN;break;
	    

        case ':' : codeChar = deux_POINT_TOKEN;break;
        case '&' : 
        		LireCaractere();
                if ( caractereCourant == '&') {
                        codeChar = ET_TOKEN;
                        symboleCourant.nom[i+1] = caractereCourant;
                        i++;
                }
        		else {
                          codeChar=SYMBOLE_INCONNU_TOKEN ;
                                // Retour au caractètre précedent pour continuer lecture normalement
                              //  ou bien ungetc
                                fseek(fichier,-sizeof(char),SEEK_CUR);
                        }
        		break;
	   case '|' : 
                    LireCaractere();
                    if ( caractereCourant == '|') {
                            codeChar =OU_TOKEN;
                            symboleCourant.nom[i+1] = caractereCourant;
                            i++;
                    }
                    else {
                          codeChar=SYMBOLE_INCONNU_TOKEN ;
                            
                            //fseek(fichier,-sizeof(char),SEEK_CUR);
                    }
                	break;
		
            case '<' :
                    LireCaractere();
                    if ( caractereCourant == '=') {
                            codeChar = INF_EGALE_TOKEN;
                            symboleCourant.nom[i+1] = caractereCourant;
                            i++;
                    }

                    else {
                          codeChar = INF_TOKEN;
                           
                            fseek(fichier,-sizeof(char),SEEK_CUR);
                    }
                    break;
	    case '!':
             LireCaractere();
    	        if ( caractereCourant == '=') {
                            codeChar = DIFF_TOKEN;
                            symboleCourant.nom[i+1] = caractereCourant;
                            i++;
                    }
    	       else{
                            codeChar = NOT_TOKEN;
                        	fseek(fichier,-sizeof(char),SEEK_CUR);
                        }
                          
    		    break; 
            case '>' :
                LireCaractere();
                if ( caractereCourant == '=') {
                    codeChar = SUP_EGALE_TOKEN;
                    symboleCourant.nom[i+1] = caractereCourant;
                    i++;
                }
                else {
                        codeChar = SUP_TOKEN;
                        // Retour au caractètre précedent pour continuer lecture normalement
                        fseek(fichier,-sizeof(char),SEEK_CUR);
                }
                break;
            case '(' : codeChar = PAR_OUV_TOKEN; break;
            case ')' : codeChar = PAR_FER_TOKEN; break;
	   		case'{'  : codeChar=ACCOL_OUV_TOKEN;break;
	    	case'}'  : codeChar=ACCOL_FER_TOKEN;break;
            case'['  : codeChar=CROCH_OUV_TOKEN;break;
            case']'  : codeChar=CROCH_FER_TOKEN;break;
	   		case '_': codeChar=UNDERSCORE_TOKEN;break ;
	   		case EOF : 
	   			codeChar = FIN_TOKEN; break;
            
            default: codeChar=SYMBOLE_INCONNU_TOKEN; break;
        }
    	symboleCourant.nom[i+1] = '\0';
    	symboleCourant.code = codeChar;
    	LireCaractere(); 
}
// Lecture d'un mot, peut être un Mot Clé ou bien un Identificateur [A-Za-z][0-9A-Za-z] MetaRegle : longueur max = 20
void LireMot() {
	int i=0,j = 0;
	symboleCourant.nom[i] = caractereCourant;

	LireCaractere();

	while ( isalpha(caractereCourant) || isdigit(caractereCourant)) {
        symboleCourant.nom[i+1] = caractereCourant;
        i++;
        LireCaractere();
	}
	/* if(isSpecial(caractereCourant)){
		if(caractereCourant=='('){
		     fseek(fichier,-sizeof(char),SEEK_CUR);	
		     	j=1 ;
		}
	} */
    symboleCourant.nom[i+1] = '\0';

    /** Si mot clé ? sinon ID_TOKEN */
    symboleCourant.code = CodageLex(symboleCourant.nom); 
    if(symboleCourant.code==IDF_TOKEN){
    	if(caractereCourant=='('){
    		symboleCourant.code=METH_IDF_TOKEN ;
    	}
    }
}

//Lecture d'un nombre :  [0-9]+ ,MetaRegle : entiers slmnt
void LireNombre() {
    int i=0,testFloat=0 ;
    symboleCourant.nom[i] = caractereCourant;
	LireCaractere();
	
		while ( isdigit(caractereCourant )|| caractereCourant==',' )  {
	        symboleCourant.nom[i+1] = caractereCourant;
	       	i++;
	        if(caractereCourant==',') testFloat=1 ;
	        LireCaractere();
		}

    symboleCourant.nom[i+1] = '\0';
	if(testFloat=1) symboleCourant.code=FNUM_TOKEN ;
	else symboleCourant.code=INUM_TOKEN ;
}
//Lecture d'un chaîne de caractères : tous les caractères entre guillemets " xxx "

void LireChaine() {
    int i=0,test=0 ;
    symboleCourant.nom[i] = caractereCourant;
    i++ ;
	if(((int)caractereCourant)==39){
		LireCaractere() ;
   		while(((int)caractereCourant)!=39 && caractereCourant!=EOF ){
   		 	test++ ;
   		 	 if (test<2)  {
   		 	 	symboleCourant.nom[i] = caractereCourant;
   		 	// 	printf("................%c\n",caractereCourant) ;
   		 	 	
   		 	 	  LireCaractere() ;
   		 	 }
   		 	 else break ;
   		 }
   		 if(caractereCourant!=EOF){
   		 	if (test==2){
   		 		for(int j=0;j<test;j++){
   		 				fseek(fichier,-sizeof(char),SEEK_CUR);	
   		 		}
   		 		symboleCourant.nom[i] = '\0';
   		 		i++ ;
    			symboleCourant.code = SYMBOLE_INCONNU_TOKEN;
    			LireCaractere() ;

   		 	}
   		 	else if(test==1){
   		 		i++ ;
	   		 	symboleCourant.nom[i] = caractereCourant;
	   		 	i++ ;
	   		 	symboleCourant.nom[i] = '\0';
	    		symboleCourant.code = CHARACTER_TOKEN;
	    		LireCaractere() ;
			}
			else {
				symboleCourant.nom[i] = caractereCourant;
	   		 	LireCaractere() ;
	   		 	i++ ;
	   		 	symboleCourant.nom[i] = '\0';
	    		symboleCourant.code = SYMBOLE_INCONNU_TOKEN;
			}
		}
		else {
			symboleCourant.code=FIN_TOKEN ;
		}
	}
	else{
			LireCaractere();
		    while( (caractereCourant != '"') && caractereCourant!=EOF) {
		        symboleCourant.nom[i] = caractereCourant;
		        i++;
		        test++ ;
		        LireCaractere();
		       
		}
			if(caractereCourant != '"'){
					for(int j=0;j<test;j++){
						 fseek(fichier,-sizeof(char),SEEK_CUR);	
						// symboleCourant.nom[i-1-j]='\0' ;
						 i=i-1 ;

					}
					symboleCourant.nom[i] = '\0';
					symboleCourant.code = SYMBOLE_INCONNU_TOKEN;
				    i++;
				    //fseek(fichier,-sizeof(char),SEEK_CUR);	
				    LireCaractere() ;


			}
		    
		    else {
			    symboleCourant.nom[i] = '"';

			    LireCaractere();
			    i++;

			    symboleCourant.nom[i] = '\0';
			    symboleCourant.code = CHAINE_TOKEN;
			}
	}
}
// Si c'est un mot clé : associe le code correspondant, Sinon retourne ID_TOKEN ( çàd le symbole est un identificateur )
int CodageLex( char * nomSymbole ) {
	
	    if ( !strcmp(nomSymbole,"using")) return USING_TOKEN;
	    if ( !strcmp(nomSymbole,"string")) return STRING_TOKEN;
	    if ( !strcmp(nomSymbole,"System")) return SYSTEM_TOKEN;
	    if ( !strcmp(nomSymbole,"namespace")) return NAMESPACE_TOKEN;
	    if ( !strcmp(nomSymbole,"class")) return CLASS_TOKEN;
	    if ( !strcmp(nomSymbole,"private")) return PRIVATE_TOKEN;
	    if ( !strcmp(nomSymbole,"public")) return PUBLIC_TOKEN;
	    if ( !strcmp(nomSymbole,"static")) return STATIC_TOKEN;
	    if ( !strcmp(nomSymbole,"void")) return VOID_TOKEN;
	    if ( !strcmp(nomSymbole,"Main")) return MAIN_TOKEN;
	    if ( !strcmp(nomSymbole,"params")) return PARAMS_TOKEN;
	    if ( !strcmp(nomSymbole,"int")) return INT_TOKEN;
	    if ( !strcmp(nomSymbole,"long")) return LONG_TOKEN;
	    if ( !strcmp(nomSymbole,"char")) return CHAR_TOKEN;
	    if ( !strcmp(nomSymbole,"float")) return FLOAT_TOKEN;
	    if ( !strcmp(nomSymbole,"double")) return DOUBLE_TOKEN;
	    if ( !strcmp(nomSymbole,"bool")) return BOOL_TOKEN;
	    if ( !strcmp(nomSymbole,"string")) return STRING_TOKEN;
	    if ( !strcmp(nomSymbole,"new")) return NEW_TOKEN;
	    if ( !strcmp(nomSymbole,"Console")) return CONSOLE_TOKEN;
	    if ( !strcmp(nomSymbole,"WriteLine")) return WRITELINE_TOKEN;
	    if ( !strcmp(nomSymbole,"const")) return CONST_TOKEN;
	    if ( !strcmp(nomSymbole,"if")) return IF_TOKEN;
	    if ( !strcmp(nomSymbole,"else")) return ELSE_TOKEN;
	    if ( !strcmp(nomSymbole,"switch")) return SWITCH_TOKEN;
	    if ( !strcmp(nomSymbole,"case")) return CASE_TOKEN;
	    if ( !strcmp(nomSymbole,"default")) return DEFAULT_TOKEN;
	    if ( !strcmp(nomSymbole,"while")) return WHILE_TOKEN;
	    if ( !strcmp(nomSymbole,"do")) return DO_TOKEN;
	    if ( !strcmp(nomSymbole,"for")) return FOR_TOKEN;
	    if ( !strcmp(nomSymbole,"foreach")) return FOREACH_TOKEN;
	    if ( !strcmp(nomSymbole,"in")) return IN_TOKEN;
	    if ( !strcmp(nomSymbole,"break")) return BREAK_TOKEN;
	    if ( !strcmp(nomSymbole,"continue")) return CONTINUE_TOKEN;
	    if ( !strcmp(nomSymbole,"return")) return RETURN_TOKEN;
	    if ( !strcmp(nomSymbole,"true")) return TRUE_TOKEN;
	        if ( !strcmp(nomSymbole,"false")) return FALSE_TOKEN;
	    return IDF_TOKEN;
}
//Teste des caractères spéciaux
int isSpecial(char c) {
    switch(c) {

            case ';' : return 1;
            case '.' : return 1;
            case '+' : return 1;
            case '-' : return 1;
            case '*' : return 1;
            case ',' : return 1;
            case '=' : return 1;
            case ':' : return 1;
            case '<' : return 1;
            case '>' : return 1;
            case '(' : return 1;
            case ')' : return 1;
            case '}' : return 1;
            case '{' : return 1;
            case ']' : return 1;
            case '[' : return 1;
            case '!' : return 1;
            case '|' : return 1;
            case '&' : return 1;
            case '^' : return 1;

    default : return 0;
    }
}
// Affiche le type du token ( dans T* ) et sa valeur ( dans Sigma* )
void AfficherToken() {
    //char const* nomToken[] = { };
    printf("# %d\t---> %s\n",symboleCourant.code,symboleCourant.nom);
}

//ouverture et fermeture du fichier
void OuvrirFichier( const char * nomFichier ) {
    fichier=NULL;
    fichier = fopen(nomFichier,"r");
}
void FermerFichier() {
    if (feof(fichier))
     printf("\n End of file reached.");
    else
     printf("\n Something went wrong.");
     fclose(fichier);
     
     getchar();
}

//****************************************************************************************************
// + IMPLEMENTATION OF LINKED LIST :)
//*****************************************************************************************************

Dlist *list = NULL; /* Déclaration d'une liste vide */

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
//****************************************************************************************************
// IMPLEMENTATION ANALYSEUR SYNTAXIQUE
//*****************************************************************************************************
extern node_token* node_token_courant;
//_________________________________START__________________________
bool _starting(){
	bool result=false;
	bool loop=true;
	while(node_token_courant->Symbole_Courant.code==USING_TOKEN && loop){
		getNext();
		if(_name_space()){
			getNext();
			if(node_token_courant->Symbole_Courant.code==POINT_VIRG_TOKEN){
				getNext();
			}
			else{
				loop=false;
			}
		}
		else{
			loop=false;
		}
	}
	if(loop) result=_program();
	return result;
}

bool _name_space(){
	bool result=false;
	if(node_token_courant->Symbole_Courant.code==SYSTEM_TOKEN) result=true;
	return result;
}

bool _program(){
	bool result=false;
	if(node_token_courant->Symbole_Courant.code==NAMESPACE_TOKEN){
		getNext();
		if(node_token_courant->Symbole_Courant.code==IDF_TOKEN){
			getNext();
			if(node_token_courant->Symbole_Courant.code==ACCOL_OUV_TOKEN){
				if(_name_space_implement()){
					getNext();
					if(node_token_courant->Symbole_Courant.code==ACCOL_FER_TOKEN){
						getNext();
						if(node_token_courant->Symbole_Courant.code==FIN_TOKEN){
							result= true;
						}
					}
				}
			}
		}
	}
	else result= _name_space_implement();
	return result;
}

bool _name_space_implement(){
	bool result=false;
	if(_p_p()){
		getNext();
		if(node_token_courant->Symbole_Courant.code==CLASS_TOKEN){
			getNext();
			if(node_token_courant->Symbole_Courant.code==IDF_TOKEN){
				getNext();
				if(node_token_courant->Symbole_Courant.code==ACCOL_OUV_TOKEN){
					if(_class_implement()){
						getNext();
						if(node_token_courant->Symbole_Courant.code==ACCOL_FER_TOKEN){
							result= true;
						}
					}
				}
			}
		}
	}
	return result;
}

bool _p_p(){
	bool result=false;
	if(node_token_courant->Symbole_Courant.code==PRIVATE_TOKEN || node_token_courant->Symbole_Courant.code==PUBLIC_TOKEN){
		result=true ;
	}
	return result;
}

bool _class_implement(){
	bool result=false;
	while(_methode_declaration()){
		getNext();
	}
	if(_main_implement() || node_token_courant->Symbole_Courant.code==ACCOL_FER_TOKEN) result=true; //Pas 100% ms ds plupart des cas usuels.
	return result;
}

bool _methode_declaration(){
	bool result= false;
	if(_p_p()){
		getNext();
		if(node_token_courant->Symbole_Courant.code==STATIC_TOKEN) getNext();
		if(_return_type()){
			getNext();
			if(_methode_name()){
				getNext();
				if(node_token_courant->Symbole_Courant.code==PAR_OUV_TOKEN){
					getNext();
					if(_formal_parameter_list()) getNext(); //96%
					if(node_token_courant->Symbole_Courant.code==PAR_FER_TOKEN){
						getNext();
						result = _methode_body();
					}
				}
			}
		}
	}
	return result;
}

bool _main_implement(){
	bool result= false;
	if(node_token_courant->Symbole_Courant.code==PUBLIC_TOKEN) getNext();
	if(node_token_courant->Symbole_Courant.code==STATIC_TOKEN){
		getNext();
		if(node_token_courant->Symbole_Courant.code==VOID_TOKEN){
			getNext();
			if(node_token_courant->Symbole_Courant.code==MAIN_TOKEN){
				getNext();
				if(node_token_courant->Symbole_Courant.code==PAR_OUV_TOKEN){
					getNext();
					if(node_token_courant->Symbole_Courant.code==STRING_TOKEN){
						getNext();
						if(node_token_courant->Symbole_Courant.code==IDF_TOKEN){
							getNext();
							if(node_token_courant->Symbole_Courant.code==PAR_FER_TOKEN){
								getNext();
								result = _methode_body();
							}
						}
					}
				}
			}
		}
	}
	return result;
}

bool _return_type(){
	bool result= false;
	if(node_token_courant->Symbole_Courant.code==VOID_TOKEN || _type()){
		result=true;
	}
	return result;
}

bool _methode_name(){
	bool result= false;
	if(node_token_courant->Symbole_Courant.code==IDF_TOKEN){
		node_token_courant->Symbole_Courant.code= METH_IDF_TOKEN; //A verifier
		result=true;
	}
	return result;
}

bool _formal_parameter_list(){
	bool result= false;
	bool loop=true;
	if(_fixed_parameters()){
		getNext();
		while(node_token_courant->Symbole_Courant.code==VIR_TOKEN && loop){
			getNext();
			if(_parameter_array()){
				getNext();
			}
			else loop=false;
		}
		if (loop) result=true;
	}
	else if(_parameter_array()) result=true;
	return result;
}

bool _fixed_parameters(){
	bool result= false;
	bool loop=true;
	if(_fixed_parameter()){
		getNext();
		while(node_token_courant->Symbole_Courant.code==VIR_TOKEN && loop){
			getNext();
			if(_fixed_parameter()){
				getNext();
			}
			else loop=false;
		}
		if (loop) result=true;
	}
	return result;
}

bool _fixed_parameter(){
	bool result= false;
	if(_type()){
		getNext();
		if(node_token_courant->Symbole_Courant.code==IDF_TOKEN){
			result=true;
		}
	}
	return result;
}

bool _parameter_array(){
	bool result= false;
	if(node_token_courant->Symbole_Courant.code==PARAMS_TOKEN){
		getNext();
		if(_array_type()){
			getNext();
			if(node_token_courant->Symbole_Courant.code==IDF_TOKEN){
				result=true;
			}
		}
	}
	return result;
}

bool _methode_body(){
	bool result= false;
	if(node_token_courant->Symbole_Courant.code==POINT_VIRG_TOKEN) result=true;
	else result=_block();
	return result;
}

//__________________________________TYPE__________________________
bool _type(){
	bool result= false;
	if(_value_type()){
		getNext();
		if(node_token_courant->Symbole_Courant.code==CROCH_OUV_TOKEN){
            getNext();
            if(node_token_courant->Symbole_Courant.code==CROCH_FER_TOKEN){
                result= true;
            }
		}
		else {
            getBack();
            result=true;
		}
	}
	return result;
}

bool _value_type(){
	bool result= false;
	if(node_token_courant->Symbole_Courant.code==INT_TOKEN || node_token_courant->Symbole_Courant.code==LONG_TOKEN || node_token_courant->Symbole_Courant.code==CHAR_TOKEN || node_token_courant->Symbole_Courant.code==FLOAT_TOKEN || node_token_courant->Symbole_Courant.code==DOUBLE_TOKEN || node_token_courant->Symbole_Courant.code==BOOL_TOKEN ){
        result=true;
	}
	return result;
}

bool _array_type(){
	bool result= false;
	if(_value_type()){
        getNext();
        if(node_token_courant->Symbole_Courant.code==CROCH_OUV_TOKEN){
            getNext();
            if(node_token_courant->Symbole_Courant.code==CROCH_FER_TOKEN){
                result=true;
            }
        }
	}
	return result;
}
////____________________________STATEMENT__________________________
bool _block(){
	bool result= false;
	if(node_token_courant->Symbole_Courant.code==ACCOL_OUV_TOKEN){
        getNext();
        while(_statement()){
            getNext();
        }
        if(node_token_courant->Symbole_Courant.code==ACCOL_FER_TOKEN) result=true; // Right in most cases
    }
	return result;
}

bool _statement(){
	bool result= false;
	if(_declaration_statement() || _embedded_statement()){//96%
        result=true;
	}
	return result;
}

bool _embedded_statement(){
	bool result= false;
    if(_block() || _selection_statement() || _iteration_statement() || _jump_statement()){
        result=true;
    }
    else if(_print() || _statement_expression()){
        getNext();
        if(node_token_courant->Symbole_Courant.code==POINT_VIRG_TOKEN){
            result=true;
        }
    }
	return result;
}

bool _print(){
	bool result= false;
	bool already=false;
	bool loop=true;
    if(node_token_courant->Symbole_Courant.code==SYSTEM_TOKEN){
        getNext();
        if(node_token_courant->Symbole_Courant.code==POINT_TOKEN){
            getNext();
        }
        else {
                already=true;;
        }
    }
    if(!already){
        if(node_token_courant->Symbole_Courant.code==CONSOLE_TOKEN){
            getNext();
            if(node_token_courant->Symbole_Courant.code==POINT_TOKEN){
                getNext();
                if(node_token_courant->Symbole_Courant.code==WRITELINE_TOKEN){
                    getNext();
                    if(node_token_courant->Symbole_Courant.code==PAR_OUV_TOKEN){
                        getNext();
                        while(_expression() && loop){
                            getNext();
                            if(node_token_courant->Symbole_Courant.code==PAR_FER_TOKEN){
                                result=true;
                                loop=false;
                            }
                            else if(node_token_courant->Symbole_Courant.code==PLUS_TOKEN){
                                getNext();
                            }
                        }
                    }
                }
            }
        }
    }
	return result;
}

bool _declaration_statement(){
	bool result= false;
    if(_local_variable_declaration() || _local_constant_declaration()){
        getNext();
        if(node_token_courant->Symbole_Courant.code==POINT_VIRG_TOKEN){
            result=true;
        }
    }
	return result;
}

bool _local_variable_declaration(){
	bool result= false;
	if(_type()){
        getNext();
        if(_variable_declarator()){
            getNext();
            bool loop=true;
            while(node_token_courant->Symbole_Courant.code==VIR_TOKEN && loop){
                getNext();
                if(_variable_declarator()){
                    getNext();
                }
                else{
                    loop=false;
                }
            }
            if(loop) {
                if(node_token_courant->Symbole_Courant.code==POINT_VIRG_TOKEN){
                    result=true;
                    getBack();
                }
            }
        }
	}
	return result;
}

bool _variable_declarator(){
	bool result= false;
	if(node_token_courant->Symbole_Courant.code==IDF_TOKEN){
        getNext();
        if(node_token_courant->Symbole_Courant.code==VIR_TOKEN || node_token_courant->Symbole_Courant.code==POINT_VIRG_TOKEN){
            result=true;
            getBack();
        }
        else if(node_token_courant->Symbole_Courant.code==EGALE_TOKEN){
            bool loop=true;
            while(node_token_courant->Symbole_Courant.code==EGALE_TOKEN && loop){
                getNext();
                if(_variable_initializer()){
                    getNext();
                }
                else{
                    loop=false;
                }
            }
            if(loop) {
                if(node_token_courant->Symbole_Courant.code==VIR_TOKEN || node_token_courant->Symbole_Courant.code==POINT_VIRG_TOKEN){
                    result=true;
                    getBack();
                }
            }
        }
	}
	return result;
}

bool _variable_initializer(){
	bool result= _expression();
	return result;
}

bool _local_constant_declaration(){
	bool result= false;
    if(node_token_courant->Symbole_Courant.code==CONST_TOKEN){
        getNext();
        if(_type()){
            getNext();
            if(_constant_declarator()){
                getNext();
                bool loop=true;
                while(node_token_courant->Symbole_Courant.code==VIR_TOKEN && loop){
                    getNext();
                    if(_constant_declarator()){
                        getNext();
                    }
                    else{
                        loop=false;
                    }
                }
                if(loop) {
                    if(node_token_courant->Symbole_Courant.code==POINT_VIRG_TOKEN){
                        result=true;
                        getBack();
                    }
                }
            }
        }
    }
	return result;
}

bool _constant_declarator(){
	bool result= false;
	if(node_token_courant->Symbole_Courant.code==IDF_TOKEN){
        getNext();
        if(node_token_courant->Symbole_Courant.code==EGALE_TOKEN){
            getNext();
            if(_expression()){
                result=true;
            }
        }
	}
	return result;
}

bool _statement_expression(){
	bool result= false;
    if(_invocation_expression() || _assignment()){
        result=true;
    }
	return result;
}

bool _selection_statement(){
	bool result= false;
    if(node_token_courant->Symbole_Courant.code==IF_TOKEN){
        getNext();
        if(node_token_courant->Symbole_Courant.code==PAR_OUV_TOKEN){
            getNext();
            if(_boolean_expression()){
                getNext();
                if(node_token_courant->Symbole_Courant.code==PAR_FER_TOKEN){
                    getNext();
                    if(_embedded_statement()){
                        result=true;
                        getNext();
                        if(node_token_courant->Symbole_Courant.code==ELSE_TOKEN){
                            getNext();
                            if(!_embedded_statement()){
                                result=false;
                            }
                        }
                        else getBack();
                    }
                }
            }
        }
    }
    else if(node_token_courant->Symbole_Courant.code==SWITCH_TOKEN){
        getNext();
        if(node_token_courant->Symbole_Courant.code==PAR_OUV_TOKEN){
            getNext();
            if(node_token_courant->Symbole_Courant.code==IDF_TOKEN){
                getNext();
                if(node_token_courant->Symbole_Courant.code==PAR_FER_TOKEN){
                    getNext();
                    if(node_token_courant->Symbole_Courant.code==ACCOL_OUV_TOKEN){
                        getNext();
                        while(_switch_section()){
                            getNext();
                        }
                        if(node_token_courant->Symbole_Courant.code==ACCOL_FER_TOKEN) result=true;
                    }
                }
            }
        }
    }
	return result;
}

bool _switch_section(){
	bool result= false;
    while(_switch_label()){
        getNext();
    }
    while(_statement()){
        getNext();
    }
    if(node_token_courant->Symbole_Courant.code==BREAK_TOKEN){
        getNext();
        if(node_token_courant->Symbole_Courant.code==POINT_VIRG_TOKEN){
            result=true;
        }
    }
    else if(node_token_courant->Symbole_Courant.code==ACCOL_FER_TOKEN){
        result=true;
        getBack();
    }
	return result;
}

bool _switch_label(){
	bool result= false;
	if(node_token_courant->Symbole_Courant.code==CASE_TOKEN){
        getNext();
        if(_expression()){
            getNext();
            if(node_token_courant->Symbole_Courant.code==deux_POINT_TOKEN){
                result=true;
            }
        }
	}
	else if(node_token_courant->Symbole_Courant.code==DEFAULT_TOKEN){
        getNext();
        if(node_token_courant->Symbole_Courant.code==deux_POINT_TOKEN){
            result=true;
        }
	}
	return result;
}

bool _iteration_statement(){
	bool result= false;
    if(node_token_courant->Symbole_Courant.code==WHILE_TOKEN){
        if(node_token_courant->Symbole_Courant.code==PAR_OUV_TOKEN){
            getNext();
            if(_boolean_expression()){
                getNext();
                if(node_token_courant->Symbole_Courant.code==PAR_FER_TOKEN){
                    getNext();
                    if(_embedded_statement()){
                        result=true;
                    }
                }
            }
        }
    }
    else if(node_token_courant->Symbole_Courant.code==DO_TOKEN){
        getNext();
        if(_embedded_statement()){
            getNext();
            if(node_token_courant->Symbole_Courant.code==WHILE_TOKEN){
                getNext();
                if(node_token_courant->Symbole_Courant.code==PAR_OUV_TOKEN){
                    getNext();
                    if(_boolean_expression()){
                        getNext();
                        if(node_token_courant->Symbole_Courant.code==PAR_FER_TOKEN){
                            getNext();
                            if(node_token_courant->Symbole_Courant.code==POINT_VIRG_TOKEN){
                                result=true;
                            }
                        }
                    }
                }
            }
        }
    }
    else if(node_token_courant->Symbole_Courant.code==FOR_TOKEN){
        getNext();
        if(node_token_courant->Symbole_Courant.code==PAR_OUV_TOKEN){
            getNext();
            if(_for_initializer()){
                getNext();
                if(node_token_courant->Symbole_Courant.code==POINT_VIRG_TOKEN){
                    getNext();
                    if(_boolean_expression()){
                        getNext();
                        if(node_token_courant->Symbole_Courant.code==POINT_VIRG_TOKEN){
                            getNext();
                            if(_for_iterator()){
                                getNext();
                                if(node_token_courant->Symbole_Courant.code==PAR_FER_TOKEN){
                                    getNext();
                                    if(_embedded_statement()){
                                        result=true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    else if(node_token_courant->Symbole_Courant.code==FOREACH_TOKEN){
        getNext();
        if(node_token_courant->Symbole_Courant.code==PAR_OUV_TOKEN){
            getNext();
            if(_type()){
                getNext();
                if(node_token_courant->Symbole_Courant.code==IDF_TOKEN){
                    getNext();
                    if(node_token_courant->Symbole_Courant.code==IN_TOKEN){
                        getNext();
                        if(node_token_courant->Symbole_Courant.code==IDF_TOKEN){
                            getNext();
                            if(node_token_courant->Symbole_Courant.code==PAR_FER_TOKEN){
                                getNext();
                                if(_embedded_statement()){
                                    result=true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
	return result;
}

bool _for_initializer(){
	bool result= false;
    if(_local_variable_declaration() || _assignment()){
        result=true;
    }
	return result;
}

bool _for_iterator(){
	bool result= _statement_expression();
	return result;
}

bool _jump_statement(){
	bool result= false;
    if(node_token_courant->Symbole_Courant.code==BREAK_TOKEN || node_token_courant->Symbole_Courant.code==CONTINUE_TOKEN){
        getNext();
        if(node_token_courant->Symbole_Courant.code==POINT_VIRG_TOKEN){
            result=true;
        }
    }
    else if(node_token_courant->Symbole_Courant.code==RETURN_TOKEN){
        getNext();
        if(_expression()) getNext();
        if(node_token_courant->Symbole_Courant.code==POINT_VIRG_TOKEN){
            result=true;
        }
    }
	return result;
}

bool _boolean_expression(){
	bool result= _expression();
	return result;
}

////____________________________EXPRESSION__________________________
bool _assignment(){
	bool result= false;
	if(node_token_courant->Symbole_Courant.code==IDF_TOKEN){
        getNext();
        if(_assignment_body()){
            result=true;
        }
	}
	return result;
}

bool _assignment_body(){
	bool result= false;
	if(node_token_courant->Symbole_Courant.code==PLUS_PLUS_TOKEN || node_token_courant->Symbole_Courant.code==MOINS_MOINS_TOKEN){
        result=true;
	}
	else if(_assignment_operator()){
        getNext();
        if(node_token_courant->Symbole_Courant.code==PAR_OUV_TOKEN){
            getNext();
            if(_type()){
                getNext();
                if(node_token_courant->Symbole_Courant.code==PAR_FER_TOKEN){
                    getNext();
                    if(_expression()){
                        result=true;
                    }
                }
            }
        }
	}
	return result;
}

bool _assignment_operator(){
	bool result= false;
    if(node_token_courant->Symbole_Courant.code==EGALE_TOKEN || node_token_courant->Symbole_Courant.code==PLUS_EGALE_TOKEN || node_token_courant->Symbole_Courant.code==MOINS_EGALE_TOKEN || node_token_courant->Symbole_Courant.code==MULT_EGALE_TOKEN || node_token_courant->Symbole_Courant.code==DIV_EGALE_TOKEN || node_token_courant->Symbole_Courant.code==MOD_EGALE_TOKEN || node_token_courant->Symbole_Courant.code==PUISS_EGALE_TOKEN){
        result=true;
    }
	return result;
}

bool _expression(){
	bool result= _conditional_or_expression();
	return result;
}

bool _conditional_or_expression(){
	bool result= false;
	bool already=false;
    if(_conditional_and_expression()){
        getNext();
        while(node_token_courant->Symbole_Courant.code==OU_TOKEN && !already){
            getNext();
            if(_conditional_and_expression()){
                getNext();
            }
            else{
                already=true;
            }
        }
        if(!already){
            result=true;
            getBack();
        }
    }
	return result;
}

bool _conditional_and_expression(){
	bool result= false;
	bool already=false;
    if(_inclusive_or_expression()){
        getNext();
        while(node_token_courant->Symbole_Courant.code==ET_TOKEN && !already){
            getNext();
            if(_inclusive_or_expression()){
                getNext();
            }
            else{
                already=true;
            }
        }
        if(!already){
            result=true;
            getBack();
        }
    }
	return result;
}

bool _inclusive_or_expression(){
	bool result= false;
	bool already=false;
    if(_relational_expression()){
        getNext();
        while(_equality_operator() && !already){
            getNext();
            if(_relational_expression()){
                getNext();
            }
            else{
                already=true;
            }
        }
        if(!already){
            result=true;
            getBack();
        }
    }
	return result;
}

bool _equality_operator(){
	bool result= false;
	if(node_token_courant->Symbole_Courant.code==EGALE_EGALE_TOKEN || node_token_courant->Symbole_Courant.code==DIFF_TOKEN){
        result=true;
	}
	return result;
}

bool _relational_expression(){
	bool result= false;
	bool already=false;
    if(_additive_expression()){
        getNext();
        while(_relational_operator() && !already){
            getNext();
            if(_additive_expression()){
                getNext();
            }
            else{
                already=true;
            }
        }
        if(!already){
            result=true;
            getBack();
        }
    }
	return result;
}

bool _relational_operator(){
	bool result= false;
    if(node_token_courant->Symbole_Courant.code==INF_TOKEN || node_token_courant->Symbole_Courant.code==INF_EGALE_TOKEN || node_token_courant->Symbole_Courant.code==SUP_TOKEN || node_token_courant->Symbole_Courant.code==SUP_EGALE_TOKEN){
        result=true;
	}
	return result;
}

bool _additive_expression(){
	bool result= false;
	bool already=false;
    if(_multiplicative_expression()){
        getNext();
        while(_additive_operator() && !already){
            getNext();
            if(_multiplicative_expression()){
                getNext();
            }
            else{
                already=true;
            }
        }
        if(!already){
            result=true;
            getBack();
        }
    }
	return result;
}

bool _additive_operator(){
	bool result= false;
	if(node_token_courant->Symbole_Courant.code==PLUS_TOKEN || node_token_courant->Symbole_Courant.code==MOINS_TOKEN){
        result=true;
	}
	return result;
}

bool _multiplicative_expression(){
	bool result= false;
	bool already=false;
    if(_primary_expression()){
        getNext();
        while(_multiplicative_operator() && !already){
            getNext();
            if(_primary_expression()){
                getNext();
            }
            else{
                already=true;
            }
        }
        if(!already){
            result=true;
            getBack();
        }
    }
	return result;
}

bool _multiplicative_operator(){
	bool result= false;
	if(node_token_courant->Symbole_Courant.code==MULT_TOKEN || node_token_courant->Symbole_Courant.code==DIV_TOKEN || node_token_courant->Symbole_Courant.code==MOD_TOKEN){
        result=true;
	}
	return result;
}

bool _primary_expression(){
	bool result= false;
    if(node_token_courant->Symbole_Courant.code==IDF_TOKEN){
        getNext();
        if(node_token_courant->Symbole_Courant.code==CROCH_OUV_TOKEN){
            getNext();
            if(node_token_courant->Symbole_Courant.code==INUM_TOKEN){
                SymbolSuivant() ;
                if(node_token_courant->Symbole_Courant.code==CROCH_FER_TOKEN){
                    result=true;
                }
            }
        }
        else{
            result=true;
            getBack();
        }
    }
    else if(node_token_courant->Symbole_Courant.code==PAR_OUV_TOKEN){
        getNext();
        if(_conditional_or_expression()){
            getNext();
            if(node_token_courant->Symbole_Courant.code==PAR_FER_TOKEN){
                result=true;
            }
        }
    }
    else if(_invocation_expression()){
        result=true;
    }
    else if(node_token_courant->Symbole_Courant.code==INUM_TOKEN || node_token_courant->Symbole_Courant.code==FNUM_TOKEN || node_token_courant->Symbole_Courant.code==TRUE_TOKEN || node_token_courant->Symbole_Courant.code==FALSE_TOKEN || node_token_courant->Symbole_Courant.code==CHAINE_TOKEN || node_token_courant->Symbole_Courant.code==CHARACTER_TOKEN){
        result=true;
    }
    else if(_array_creation_expression()){
        result=true;
    }
	return result;
}

bool _invocation_expression(){
	bool result= false;
	if(node_token_courant->Symbole_Courant.code==METH_IDF_TOKEN){
        getNext();
        if(node_token_courant->Symbole_Courant.code==PAR_OUV_TOKEN){
            getNext();
            if(node_token_courant->Symbole_Courant.code==PAR_FER_TOKEN){
                result=true;
            }
            else if(_argument_list()){
                getNext();
                if(node_token_courant->Symbole_Courant.code==PAR_FER_TOKEN){
                    result=true;
                }
            }
        }
	}
	return result;
}

bool _argument_list(){
	bool result= false;
    if(_argument()){
        bool loop=true;
        while(node_token_courant->Symbole_Courant.code==VIR_TOKEN && loop){
            getNext();
            if(_argument()){
                getNext();
            }
            else{
                loop=false;
            }
        }
        if(loop) {
            result=true;
            getBack();
        }
    }
	return result;
}

bool _argument(){
	bool result= _expression();
	return result;
}

bool _array_creation_expression(){
	bool result= false;
	if(node_token_courant->Symbole_Courant.code==NEW_TOKEN){
        getNext();
        if(_value_type()){
            getNext();
            if(node_token_courant->Symbole_Courant.code==CROCH_OUV_TOKEN){
                getNext();
                if(_array_length()){
                    getNext();
                    if(_array_initializer()){
                        result=true;
                    }
                    else{
                        result=true;
                        getBack();
                    }
                }
            }
        }
	}
	return result;
}

bool _array_length(){
	bool result= false;
	if(node_token_courant->Symbole_Courant.code==INUM_TOKEN){
        getNext();
        if(node_token_courant->Symbole_Courant.code==CROCH_FER_TOKEN){
            result=true;
        }
	}
	else if(node_token_courant->Symbole_Courant.code==CROCH_FER_TOKEN){
        result=true;
    }
	return result;
}

bool _array_initializer(){
	bool result= false;
    if(node_token_courant->Symbole_Courant.code==ACCOL_OUV_TOKEN){
        getNext();
        if(node_token_courant->Symbole_Courant.code==ACCOL_FER_TOKEN){
            result=true;
        }
        else if(_expression()){
            getNext();
            if(node_token_courant->Symbole_Courant.code==VIR_TOKEN){
                getNext();
                while(_expression()){
                    getNext();
                    if(node_token_courant->Symbole_Courant.code==VIR_TOKEN){
                        getNext();
                    }
                    else if(node_token_courant->Symbole_Courant.code==ACCOL_FER_TOKEN){
                        result=true;
                        break;
                    }
                }
            }
            else if(node_token_courant->Symbole_Courant.code==ACCOL_FER_TOKEN){
                result=true;
            }
        }
    }
	return result;
}














