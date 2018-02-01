#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "lex.h"


extern node_token* node_token_courant ;
extern Symbole symboleCourant;

//_________________________________START__________________________
bool _start(){
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
						if(node_token_courant->Symbole_Courant.code==EOF_TOKEN){
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
		result=true
	}
	return result;
}

bool _class_implement(){
	bool result=false;
	bool loop=true;
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

bool _formal_parameter_list{
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
        bool loop=true;
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
    if(_block() || _selection_statement() || _iteration_statement() || _jump_statement() || _try_statement()){
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
    if(_local_variable_declaration() || _ local_constant_declaration()){
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
            if(_ boolean_expression()){
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
                        bool loop=true;
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
            if(_ boolean_expression()){
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
                    if(_ boolean_expression()){
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
	if(node_token_courant->Symbole_Courant.code==EGALE_EGALE_TOKEN || node_token_courant->Symbole_Courant.code=DIFF_TOKEN){
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
    if(node_token_courant->Symbole_Courant.code==INF_TOKEN || node_token_courant->Symbole_Courant.code=INF_EGALE_TOKEN || node_token_courant->Symbole_Courant.code=SUP_TOKEN || node_token_courant->Symbole_Courant.code=SUP_EGALE_TOKEN){
        result=true;
	}
	return result;
}

bool _additive_expression(){
	bool result= false;
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
	return result;
}

bool _additive_operator(){
	bool result= false;
	if(node_token_courant->Symbole_Courant.code==PLUS_TOKEN || node_token_courant->Symbole_Courant.code=MOINS_TOKEN){
        result=true;
	}
	return result;
}

bool _multiplicative_expression(){
	bool result= false;
	bool result= false;
	bool already=false;
    if(_unary_expression()){
        getNext();
        while(_multiplicative_operator() && !already){
            getNext();
            if(_unary_expression()){
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
	return result;
}

bool _multiplicative_operator(){
	bool result= false;
	if(node_token_courant->Symbole_Courant.code==MULT_TOKEN || node_token_courant->Symbole_Courant.code=DIV_TOKEN || node_token_courant->Symbole_Courant.code=MOD_TOKEN){
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
                SymbolSuivant()
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














