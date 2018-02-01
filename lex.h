
#ifndef LEX_H
#define LEX_H 




//*************************** fonction syntaxique **********************
bool _start();
bool _name_space();
bool _program();
bool _name_space_implement();
bool _p_p();
bool _class_implement();
bool _main_implement();
bool _methode_declaration();
bool _return_type();
bool _methode_name();
bool _formal_parameter_list();
bool _fixed_parameters();
bool _fixed_parameter();
bool _parameter_array();
bool _methode_body();
bool _type();
bool _value_type();
bool _array_type();
bool _block();
bool _statement();
bool _embedded_statement();
bool _print();
bool _declaration_statement();
bool _local_variable_declaration();
bool _variable_declarator();
bool _variable_initializer();
bool _local_constant_declaration();
bool _constant_declarator();
bool _statement_expression();
bool _selection_statement();
bool _switch_section();
bool _switch_label();
bool _iteration_statement();
bool _for_initializer();
bool _for_iterator();
bool _jump_statement();
bool _boolean_expression();
bool _expression();
bool _assignment();
bool _assignment_body();
bool _assignment_operator();
bool _conditional_or_expression();
bool _conditional_and_expression();
bool _inclusive_or_expression();
bool _equality_operator();
bool _relational_expression();
bool _relational_operator();
bool _additive_expression();
bool _additive_operator();
bool _multiplicative_expression();
bool _multiplicative_operator();
bool _primary_expression();
bool _invocation_expression();
bool _argument_list();
bool _argument();
bool _array_creation_expression();
bool _array_length();
bool _array_initializer();
















//************************** fonction lexical ***********************
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

PLUS_PLUS_TOKEN  ,// ++    __________   
MOINS_MOINS_TOKEN ,// __    __________    
PLUS_EGALE_TOKEN ,// +=    __________    
MOINS_EGALE_TOKEN ,// _=    __________    
DIV_EGALE_TOKEN ,// /=    __________
MULT_EGALE_TOKEN ,// *=    __________    
MOD_EGALE_TOKEN ,// %=    __________    
PUISS_EGALE_TOKEN, // ^=    __________   
OU_TOKEN,// ||    __________    
ET_TOKEN ,// &&    __________    
EGALE_EGALE_TOKEN ,// ==    __________    
DIFF_TOKEN ,// !=    __________ 
NOT_TOKEN ,// ! 
PUISS_TOKEN, // ^ 
UNDERSCORE_TOKEN ,//_  
INF_EGALE_TOKEN ,// <=    __________    
SUP_EGALE_TOKEN ,// >=    __________    
EGALE_TOKEN ,// =     __________    
INF_TOKEN ,// <     __________    
SUP_TOKEN ,// >     __________    
PLUS_TOKEN ,// +    __________    
MOINS_TOKEN ,//  _     __________    
MULT_TOKEN ,// *     __________    
DIV_TOKEN ,// /     __________    
MOD_TOKEN ,// %     __________    
ACCOL_OUV_TOKEN ,// {     __________    
ACCOL_FER_TOKEN ,// }     __________    
CROCH_OUV_TOKEN ,// [     __________    
CROCH_FER_TOKEN ,// ]     __________    
PAR_OUV_TOKEN ,// (     __________    
PAR_FER_TOKEN ,// )     __________    
VIR_TOKEN ,// ,     __________    
POINT_TOKEN ,// .     __________    
deux_POINT_TOKEN,// :     __________    
POINT_VIRG_TOKEN ,// ;     __________    


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
