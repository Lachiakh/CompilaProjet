#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "lex.h"





//****************************************************************************************************


//*****************************************************************************************************


FILE* fichier = NULL;
Symbole symboleCourant;
char caractereCourant;

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
    else symboleCourant.code=FIN_TOKEN ; //why FIN_TOKEN ???
}

//consommer les commentaires entre /* et */
void PasserCommentaire(){
	int i; //int i=1;
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
                     //else{ungetc(caractereCourant,fichier)}; ou fseek(fichier,-sizeof(char),SEEK_CUR);
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
                            // Retour au caractètre précedent pour continuer lecture normalement (ou bien ungetc)
                            // POURQUOI?
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
	   		case EOF : //is not special not??
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
    		//LireCaractere
    	}
    }
}

//Lecture d'un nombre :  [0-9]+ ,MetaRegle : entiers slmnt
void LireNombre() {
    int i=0,testFloat=0 ;
    symboleCourant.nom[i] = caractereCourant;
	LireCaractere();
        //while ( isdigit(caractereCourant )|| (caractereCourant==',' && !testFloat) )
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
//Lecture d'une chaîne de caractères : tous les caractères entre guillemets " xxx "

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
                int j;
   		 		for(j=0;j<test;j++){
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
                    int j;
					for(j=0;j<test;j++){
						 fseek(fichier,-sizeof(char),SEEK_CUR);
						 symboleCourant.nom[i-1-j]='\0' ;
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

			    symboleCourant.nom[i+1] = '\0';
			    symboleCourant.code = CHAINE_TOKEN;
			}
	}
}
// Si c'est un mot clé : associe le code correspondant, Sinon retourne ID_TOKEN ( çàd le symbole est un identificateur )
int CodageLex( char * nomSymbole ) {

	    if ( !strcmp(nomSymbole,"using")) return USING_TOKEN;
	    if ( !strcmp(nomSymbole,"args")) return ARGS_TOKEN;
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

/****************************************************************************\
*                           MAIN FUNCTION :                                  *
\****************************************************************************/
/*
int main( int argc, char ** argv ) {
    OuvrirFichier("source.txt");
    LireCaractere();
    while (caractereCourant!=EOF) {
        SymboleSuivant();
        AfficherToken();
    }
    FermerFichier();
    return 0;
} */



