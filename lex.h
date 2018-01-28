
#ifndef LEX_H
#define LEX_H 



void PasserCommentaire();
void SymbolSuivant();
int CodageLex( char * nomSymbole );
void LireCaractere();
void LireChaine();
void LireMot();
void LireNombre();
void LireSpecial();
int isSpecial(char c);
void AfficherToken();
void OuvrirFichier( const char * nomFichier ) ;
void FermerFichier() ;


 // ******CARACTERES SPECIAUX******
enum CodeLex{

PLUS_PLUS_TOKEN  ,// ++    ----------   
MOINS_MOINS_TOKEN ,// --    ----------    
PLUS_EGALE_TOKEN ,// +=    ----------    
MOINS_EGALE_TOKEN ,// -=    ----------    
DIV_EGALE_TOKEN ,// /=    ----------
MULT_EGALE_TOKEN ,// *=    ----------    
MOD_EGALE_TOKEN ,// %=    ----------    
PUISS_EGALE_TOKEN, // ^=    ----------   
OU_TOKEN,// ||    ----------    
ET_TOKEN ,// &&    ----------    
EGALE_EGALE_TOKEN ,// ==    ----------    
DIFF_TOKEN ,// !=    ---------- 
NOT_TOKEN ,// ! 
PUISS_TOKEN, // ^ 
UNDERSCORE_TOKEN ,//_  
INF_EGALE_TOKEN ,// <=    ----------    
SUP_EGALE_TOKEN ,// >=    ----------    
EGALE_TOKEN ,// =     ----------    
INF_TOKEN ,// <     ----------    
SUP_TOKEN ,// >     ----------    
PLUS_TOKEN ,// +    ----------    
MOINS_TOKEN ,//  -     ----------    
MULT_TOKEN ,// *     ----------    
DIV_TOKEN ,// /     ----------    
MOD_TOKEN ,// %     ----------    
ACCOL_OUV_TOKEN ,// {     ----------    
ACCOL_FER_TOKEN ,// }     ----------    
CROCH_OUV_TOKEN ,// [     ----------    
CROCH_FER_TOKEN ,// ]     ----------    
PAR_OUV_TOKEN ,// (     ----------    
PAR_FER_TOKEN ,// )     ----------    
VIR_TOKEN ,// ,     ----------    
POINT_TOKEN ,// .     ----------    
deux_POINT_TOKEN,// :     ----------    
POINT_VIRG_TOKEN ,// ;     ----------    


//******MOTS CLEFS******

   USING_TOKEN,
   SYSTEM_TOKEN,
   NAMESPACE_TOKEN,
   CLASS_TOKEN,
   PRIVATE_TOKEN,
   PUBLIC_TOKEN,
   STATIC_TOKEN,
   VOID_TOKEN,
   MAIN_TOKEN,
   ARGS_TOKEN, //
   STRING_TOKEN, //
   PARAMS_TOKEN,
   INT_TOKEN,
   LONG_TOKEN,
   CHAR_TOKEN,
   FLOAT_TOKEN,
   DOUBLE_TOKEN,
   BOOL_TOKEN,
   NEW_TOKEN,
   CONSOLE_TOKEN,
   WRITELINE_TOKEN,
   CONST_TOKEN,
   IF_TOKEN,
   ELSE_TOKEN,
   SWITCH_TOKEN,
   CASE_TOKEN,
   DEFAULT_TOKEN,
   WHILE_TOKEN,
   DO_TOKEN,
   FOR_TOKEN,
   FOREACH_TOKEN,
   IN_TOKEN,
   BREAK_TOKEN,
   CONTINUE_TOKEN,
   RETURN_TOKEN,
   TRUE_TOKEN,
   FALSE_TOKEN,


//******AUTRES******
//!!!! Dans ce cas la valeur du token est aussi à stocker !!!!

INUM_TOKEN , //     (un nombre entier)
FNUM_TOKEN  ,  //   (un nombre avec virgule)
CHAINE_TOKEN ,   // (une chaine de charactères)
CHARACTER_TOKEN,   // (un charactère)
IDF_TOKEN       ,// (un identificateur ( =lettre {character} )
METH_IDF_TOKEN ,// (c'est un identificateur mais qui représente le nom d'une méthode)

//********** Symboles erronee/inconnus***************
SYMBOLE_INCONNU_TOKEN,

/** end of file */
FIN_TOKEN

    
};
typedef enum CodeLex CodeLex ;

struct Symbole{
	CodeLex code;
	char nom[30];
};
typedef struct Symbole Symbole ;



#endif
