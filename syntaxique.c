#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "lex.h"

extern Symbole symboleCourant;

//---------------------------------START--------------------------
bool _start(){
	bool result=false;
	bool loop=true;
	while(symboleCourant.code==USING_TOKEN && loop){
		SymbolSuivant();
		if(_name_space()){
			SymbolSuivant();
			if(symboleCourant.code==POINT_VIRG_TOKEN){
				SymbolSuivant();
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
	if(symboleCourant.code==SYSTEM_TOKEN) result=true;
	return result;
}

bool _program(){
	bool result=false;
	if(symboleCourant.code==NAMESPACE_TOKEN){
		SymbolSuivant();
		if(symboleCourant.code==IDF_TOKEN){
			SymbolSuivant();
			if(symboleCourant.code==ACCOL_OUV_TOKEN){
				if(_name_space_implement()){
					SymbolSuivant();
					if(symboleCourant.code==ACCOL_FER_TOKEN){
						SymbolSuivant();
						if(symboleCourant.code==EOF_TOKEN){
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
		SymbolSuivant();
		if(symboleCourant.code==CLASS_TOKEN){
			SymbolSuivant();
			if(symboleCourant.code==IDF_TOKEN){
				SymbolSuivant();
				if(symboleCourant.code==ACCOL_OUV_TOKEN){
					if(_class_implement()){
						SymbolSuivant();
						if(symboleCourant.code==ACCOL_FER_TOKEN){
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
	if(symboleCourant.code==PRIVATE_TOKEN || symboleCourant.code==PUBLIC_TOKEN){
		result=true
	}
	return result;
}

bool _class_implement(){
	bool result=false;
	bool loop=true;
	while(_methode_declaration()){
		SymbolSuivant();
	}
	if(_main_implement() || symboleCourant.code==ACCOL_FER_TOKEN) result=true; //Pas 100% ms ds plupart des cas usuels.
	return result;
}

bool _methode_declaration(){
	bool result= false;
	if(_p_p()){
		SymbolSuivant();
		if(symboleCourant.code==STATIC_TOKEN) SymbolSuivant();
		if(_return_type()){
			SymbolSuivant();
			if(_methode_name()){
				SymbolSuivant();
				if(symboleCourant.code==PAR_OUV_TOKEN){
					SymbolSuivant();
					if(_formal_parameter_list()) SymbolSuivant(); //96%
					if(symboleCourant.code==PAR_FER_TOKEN){
						SymbolSuivant();
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
	if(symboleCourant.code==PUBLIC_TOKEN) SymbolSuivant();
	if(symboleCourant.code==STATIC_TOKEN){
		SymbolSuivant();
		if(symboleCourant.code==VOID_TOKEN){
			SymbolSuivant();
			if(symboleCourant.code==MAIN_TOKEN){
				SymbolSuivant();
				if(symboleCourant.code==PAR_OUV_TOKEN){
					SymbolSuivant();
					if(symboleCourant.code==STRING_TOKEN){
						SymbolSuivant();
						if(symboleCourant.code==IDF_TOKEN){
							SymbolSuivant();
							if(symboleCourant.code==PAR_FER_TOKEN){
								SymbolSuivant();
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
	if(symboleCourant.code==VOID_TOKEN || _type()){
		result=true;
	}
	return result;
}

bool _methode_name(){
	bool result= false;
	if(symboleCourant.code==IDF_TOKEN){
		symboleCourant.code= METH_IDF_TOKEN; //A verifier
		result=true;
	}
	return result;
}

bool _formal_parameter_list{
	bool result= false;
	bool loop=true;
	if(_fixed-parameters()){
		SymbolSuivant();
		while(symboleCourant.code==VIR_TOKEN && loop){
			SymbolSuivant();
			if(_parameter-array()){
				SymbolSuivant();
			}
			else loop=false;
		}
		if (loop) result=true;
	}
	else if(_parameter-array()) result=true;
	return result;
}

bool _fixed-parameters(){
	bool result= false;
	bool loop=true;
	if(_fixed-parameter()){
		SymbolSuivant();
		while(symboleCourant.code==VIR_TOKEN && loop){
			SymbolSuivant();
			if(_fixed-parameter()){
				SymbolSuivant();
			}
			else loop=false;
		}
		if (loop) result=true;
	}
	return result;
}

bool _fixed-parameter(){
	bool result= false;
	if(_type()){
		SymbolSuivant();
		if(symboleCourant.code==IDF_TOKEN){
			result=true;
		}
	}
	return result;
}

bool _parameter-array(){
	bool result= false;
	if(symboleCourant.code==PARAMS_TOKEN){
		SymbolSuivant();
		if(_array-type()){
			SymbolSuivant();
			if(symboleCourant.code==IDF_TOKEN){
				result=true;
			}
		}
	}
	return result;
}

bool _methode_body(){
	bool result= false;
	if(symboleCourant.code==POINT_VIRG_TOKEN) result=true;
	else result=_block();
	return result;
}

//----------------------------------TYPE--------------------------
bool _type(){
	bool result= false;
	if(_value-type()){
		SymbolSuivant();
		if(symboleCourant.code==CROCH_OUV_TOKEN){
            SymbolSuivant();
            if(symboleCourant.code==CROCH_FER_TOKEN){
                result= true;
            }
		}
		else {
            GetBack();
            result=true;
		}
	}
	return result;
}

bool _value-type(){
	bool result= false;
	if(symboleCourant.code==INT_TOKEN || symboleCourant.code==LONG_TOKEN || symboleCourant.code==CHAR_TOKEN || symboleCourant.code==FLOAT_TOKEN || symboleCourant.code==DOUBLE_TOKEN || symboleCourant.code==BOOL_TOKEN ){
        result=true;
	}
	return result;
}

bool _array-type(){
	bool result= false;
	if(_value-type()){
        SymbolSuivant();
        if(symboleCourant.code==CROCH_OUV_TOKEN){
            SymbolSuivant();
            if(symboleCourant.code==CROCH_FER_TOKEN){
                result=true;
            }
        }
	}
	return result;
}
////----------------------------STATEMENT--------------------------
bool _block(){
	bool result= false;
	if(symboleCourant.code==ACCOL_OUV_TOKEN){
        SymbolSuivant();
        bool loop=true;
        while(_statement()){
            SymbolSuivant();
        }
        if(symboleCourant.code==ACCOL_FER_TOKEN) result=true; // Right in most cases
    }
	return result;
}

bool _statement(){
	bool result= false;
	if(_declaration-statement() || _embedded-statement()){//96%
        result=true;
	}
	return result;
}

bool _embedded-statement(){
	bool result= false;
    if(_block() || _selection-statement() || _iteration-statement() || _jump-statement() || _try-statement()){
        result=true;
    }
    else if(_print() || _statement-expression()){
        SymbolSuivant();
        if(symboleCourant.code==POINT_VIRG_TOKEN){
            result=true;
        }
    }
	return result;
}

bool _print(){
	bool result= false;
	bool already=false;
	bool loop=true;
    if(symboleCourant.code==SYSTEM_TOKEN){
        SymbolSuivant();
        if(symboleCourant.code==POINT_TOKEN){
            SymbolSuivant();
        }
        else {
                already=true;;
        }
    }
    if(!already){
        if(symboleCourant.code==CONSOLE_TOKEN){
            SymbolSuivant();
            if(symboleCourant.code==POINT_TOKEN){
                SymbolSuivant();
                if(symboleCourant.code==WRITELINE_TOKEN){
                    SymbolSuivant();
                    if(symboleCourant.code==PAR_OUV_TOKEN){
                        SymbolSuivant();
                        while(_expression() && loop){
                            SymbolSuivant();
                            if(symboleCourant.code==PAR_FER_TOKEN){
                                result=true;
                                loop=false;
                            }
                            else if(symboleCourant.code==PLUS_TOKEN){
                                SymbolSuivant();
                            }
                        }
                    }
                }
            }
        }
    }
	return result;
}

bool _declaration-statement(){
	bool result= false;
    if(_local-variable-declaration() || _ local-constant-declaration()){
        SymbolSuivant();
        if(symboleCourant.code==POINT_VIRG_TOKEN){
            result=true;
        }
    }
	return result;
}

bool _local-variable-declaration(){
	bool result= false;
	if(_type()){
        SymbolSuivant();
        if(_variable-declarator()){
            SymbolSuivant();
            bool loop=true;
            while(symboleCourant.code==VIR_TOKEN && loop){
                SymbolSuivant();
                if(_variable-declarator()){
                    SymbolSuivant();
                }
                else{
                    loop=false;
                }
            }
            if(loop) {
                if(symboleCourant.code==POINT_VIRG_TOKEN){
                    result=true;
                    GetBack();
                }
            }
        }
	}
	return result;
}

bool _variable-declarator(){
	bool result= false;
	if(symboleCourant.code==IDF_TOKEN){
        SymbolSuivant();
        if(symboleCourant.code==VIR_TOKEN || symboleCourant.code==POINT_VIRG_TOKEN){
            result=true;
            GetBack();
        }
        else if(symboleCourant.code==EGALE_TOKEN){
            bool loop=true;
            while(symboleCourant.code==EGALE_TOKEN && loop){
                SymbolSuivant();
                if(_variable-initializer()){
                    SymbolSuivant();
                }
                else{
                    loop=false;
                }
            }
            if(loop) {
                if(symboleCourant.code==VIR_TOKEN || symboleCourant.code==POINT_VIRG_TOKEN){
                    result=true;
                    GetBack();
                }
            }
        }
	}
	return result;
}

bool _variable-initializer(){
	bool result= _expression();
	return result;
}

bool _local-constant-declaration(){
	bool result= false;
    if(symboleCourant.code==CONST_TOKEN){
        SymbolSuivant();
        if(_type()){
            SymbolSuivant();
            if(_constant-declarator()){
                SymbolSuivant();
                bool loop=true;
                while(symboleCourant.code==VIR_TOKEN && loop){
                    SymbolSuivant();
                    if(_constant-declarator()){
                        SymbolSuivant();
                    }
                    else{
                        loop=false;
                    }
                }
                if(loop) {
                    if(symboleCourant.code==POINT_VIRG_TOKEN){
                        result=true;
                        GetBack();
                    }
                }
            }
        }
    }
	return result;
}

bool _constant-declarator(){
	bool result= false;
	if(symboleCourant.code==IDF_TOKEN){
        SymbolSuivant();
        if(symboleCourant.code==EGALE_TOKEN){
            SymbolSuivant();
            if(_expression()){
                result=true;
            }
        }
	}
	return result;
}

bool _statement-expression(){
	bool result= false;
    if(_invocation-expression() || _assignment()){
        result=true;
    }
	return result;
}

bool _selection-statement(){
	bool result= false;
    if(symboleCourant.code==IF_TOKEN){
        SymbolSuivant();
        if(symboleCourant.code==PAR_OUV_TOKEN){
            SymbolSuivant();
            if(_ boolean-expression()){
                SymbolSuivant();
                if(symboleCourant.code==PAR_FER_TOKEN){
                    SymbolSuivant();
                    if(_embedded-statement()){
                        result=true;
                        SymbolSuivant();
                        if(symboleCourant.code==ELSE_TOKEN){
                            SymbolSuivant();
                            if(!_embedded-statement()){
                                result=false;
                            }
                        }
                        else GetBack();
                    }
                }
            }
        }
    }
    else if(symboleCourant.code==SWITCH_TOKEN){
        SymbolSuivant();
        if(symboleCourant.code==PAR_OUV_TOKEN){
            SymbolSuivant();
            if(symboleCourant.code==IDF_TOKEN){
                SymbolSuivant();
                if(symboleCourant.code==PAR_FER_TOKEN){
                    SymbolSuivant();
                    if(symboleCourant.code==ACCOL_OUV_TOKEN){
                        SymbolSuivant();
                        bool loop=true;
                        while(_switch-section()){
                            SymbolSuivant();
                        }
                        if(symboleCourant.code==ACCOL_FER_TOKEN) result=true;
                    }
                }
            }
        }
    }
	return result;
}

bool _switch-section(){
	bool result= false;
    while(_switch-label()){
        SymbolSuivant();
    }
    while(_statement()){
        SymbolSuivant();
    }
    if(symboleCourant.code==BREAK_TOKEN){
        SymbolSuivant();
        if(symboleCourant.code==POINT_VIRG_TOKEN){
            result=true;
        }
    }
    else if(symboleCourant.code==ACCOL_FER_TOKEN){
        result=true;
        GetBack();
    }
	return result;
}

bool _switch-label(){
	bool result= false;
	if(symboleCourant.code==CASE_TOKEN){
        SymbolSuivant();
        if(_expression()){
            SymbolSuivant();
            if(symboleCourant.code==deux_POINT_TOKEN){
                result=true;
            }
        }
	}
	else if(symboleCourant.code==DEFAULT_TOKEN){
        SymbolSuivant();
        if(symboleCourant.code==deux_POINT_TOKEN){
            result=true;
        }
	}
	return result;
}

bool _iteration-statement(){
	bool result= false;
    if(symboleCourant.code==WHILE_TOKEN){
        if(symboleCourant.code==PAR_OUV_TOKEN){
            SymbolSuivant();
            if(_ boolean-expression()){
                SymbolSuivant();
                if(symboleCourant.code==PAR_FER_TOKEN){
                    SymbolSuivant();
                    if(_embedded-statement()){
                        result=true;
                    }
                }
            }
        }
    }
    else if(symboleCourant.code==DO_TOKEN){
        SymbolSuivant();
        if(_embedded-statement()){
            SymbolSuivant();
            if(symboleCourant.code==WHILE_TOKEN){
                SymbolSuivant();
                if(symboleCourant.code==PAR_OUV_TOKEN){
                    SymbolSuivant();
                    if(_ boolean-expression()){
                        SymbolSuivant();
                        if(symboleCourant.code==PAR_FER_TOKEN){
                            SymbolSuivant();
                            if(symboleCourant.code==POINT_VIRG_TOKEN){
                                result=true;
                            }
                        }
                    }
                }
            }
        }
    }
    else if(symboleCourant.code==FOR_TOKEN){
        SymbolSuivant();
        if(symboleCourant.code==PAR_OUV_TOKEN){
            SymbolSuivant();
            if(_for-initializer()){
                SymbolSuivant();
                if(symboleCourant.code==POINT_VIRG_TOKEN){
                    SymbolSuivant();
                    if(_boolean-expression()){
                        SymbolSuivant();
                        if(symboleCourant.code==POINT_VIRG_TOKEN){
                            SymbolSuivant();
                            if(_for-iterator()){
                                SymbolSuivant();
                                if(symboleCourant.code==PAR_FER_TOKEN){
                                    SymbolSuivant();
                                    if(_embedded-statement()){
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
    else if(symboleCourant.code==FOREACH_TOKEN){
        SymbolSuivant();
        if(symboleCourant.code==PAR_OUV_TOKEN){
            SymbolSuivant();
            if(_type()){
                SymbolSuivant();
                if(symboleCourant.code==IDF_TOKEN){
                    SymbolSuivant();
                    if(symboleCourant.code==IN_TOKEN){
                        SymbolSuivant();
                        if(symboleCourant.code==IDF_TOKEN){
                            SymbolSuivant();
                            if(symboleCourant.code==PAR_FER_TOKEN){
                                SymbolSuivant();
                                if(_embedded-statement()){
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

bool _for-initializer(){
	bool result= false;
    if(_local-variable-declaration() || _assignment()){
        result=true;
    }
	return result;
}

bool _for-iterator(){
	bool result= _statement-expression();
	return result;
}

bool _jump-statement(){
	bool result= false;
    if(symboleCourant.code==BREAK_TOKEN || symboleCourant.code==CONTINUE_TOKEN){
        SymbolSuivant();
        if(symboleCourant.code==POINT_VIRG_TOKEN){
            result=true;
        }
    }
    else if(symboleCourant.code==RETURN_TOKEN){
        SymbolSuivant();
        if(_expression()) SymbolSuivant();
        if(symboleCourant.code==POINT_VIRG_TOKEN){
            result=true;
        }
    }
	return result;
}

bool _boolean-expression(){
	bool result= _expression();
	return result;
}

////----------------------------EXPRESSION--------------------------
bool _assignment(){
	bool result= false;
	if(symboleCourant.code==IDF_TOKEN){
        SymbolSuivant();
        if(_assignment-body()){
            result=true;
        }
	}
	return result;
}

bool _assignment-body(){
	bool result= false;
	if(symboleCourant.code==PLUS_PLUS_TOKEN || symboleCourant.code==MOINS_MOINS_TOKEN){
        result=true;
	}
	else if(_assignment_operator()){
        SymbolSuivant();
        if(symboleCourant.code==PAR_OUV_TOKEN){
            SymbolSuivant();
            if(_type()){
                SymbolSuivant();
                if(symboleCourant.code==PAR_FER_TOKEN){
                    SymbolSuivant();
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
    if(symboleCourant.code==EGALE_TOKEN || symboleCourant.code==PLUS_EGALE_TOKEN || symboleCourant.code==MOINS_EGALE_TOKEN || symboleCourant.code==MULT_EGALE_TOKEN || symboleCourant.code==DIV_EGALE_TOKEN || symboleCourant.code==MOD_EGALE_TOKEN || symboleCourant.code==PUISS_EGALE_TOKEN){
        result=true;
    }
	return result;
}

bool _expression(){
	bool result= _conditional-or-expression();
	return result;
}

bool _conditional-or-expression(){
	bool result= false;
	bool already=false;
    if(_conditional-and-expression()){
        SymbolSuivant();
        while(symboleCourant.code==OU_TOKEN && !already){
            SymbolSuivant();
            if(_conditional-and-expression()){
                SymbolSuivant();
            }
            else{
                already=true;
            }
        }
        if(!already){
            result=true;
            GetBack();
        }
    }
	return result;
}

bool _conditional-and-expression(){
	bool result= false;
	bool already=false;
    if(_inclusive-or-expression()){
        SymbolSuivant();
        while(symboleCourant.code==ET_TOKEN && !already){
            SymbolSuivant();
            if(_inclusive-or-expression()){
                SymbolSuivant();
            }
            else{
                already=true;
            }
        }
        if(!already){
            result=true;
            GetBack();
        }
    }
	return result;
}

bool _inclusive-or-expression(){
	bool result= false;
	bool already=false;
    if(_relational-expression()){
        SymbolSuivant();
        while(_equality_operator() && !already){
            SymbolSuivant();
            if(_relational-expression()){
                SymbolSuivant();
            }
            else{
                already=true;
            }
        }
        if(!already){
            result=true;
            GetBack();
        }
    }
	return result;
}

bool _equality_operator(){
	bool result= false;
	if(symboleCourant.code==EGALE_EGALE_TOKEN || symboleCourant.code=DIFF_TOKEN){
        result=true;
	}
	return result;
}

bool _relational-expression(){
	bool result= false;
	bool already=false;
    if(_additive-expression()){
        SymbolSuivant();
        while(_relational_operator() && !already){
            SymbolSuivant();
            if(_additive-expression()){
                SymbolSuivant();
            }
            else{
                already=true;
            }
        }
        if(!already){
            result=true;
            GetBack();
        }
    }
	return result;
}

bool _relational_operator(){
	bool result= false;
    if(symboleCourant.code==INF_TOKEN || symboleCourant.code=INF_EGALE_TOKEN || symboleCourant.code=SUP_TOKEN || symboleCourant.code=SUP_EGALE_TOKEN){
        result=true;
	}
	return result;
}

bool _additive-expression(){
	bool result= false;
	bool result= false;
	bool already=false;
    if(_multiplicative-expression()){
        SymbolSuivant();
        while(_additive_operator() && !already){
            SymbolSuivant();
            if(_multiplicative-expression()){
                SymbolSuivant();
            }
            else{
                already=true;
            }
        }
        if(!already){
            result=true;
            GetBack();
        }
    }
	return result;
	return result;
}

bool _additive_operator(){
	bool result= false;
	if(symboleCourant.code==PLUS_TOKEN || symboleCourant.code=MOINS_TOKEN){
        result=true;
	}
	return result;
}

bool _multiplicative-expression(){
	bool result= false;
	bool result= false;
	bool already=false;
    if(_unary-expression()){
        SymbolSuivant();
        while(_multiplicative_operator() && !already){
            SymbolSuivant();
            if(_unary-expression()){
                SymbolSuivant();
            }
            else{
                already=true;
            }
        }
        if(!already){
            result=true;
            GetBack();
        }
    }
	return result;
	return result;
}

bool _multiplicative_operator(){
	bool result= false;
	if(symboleCourant.code==MULT_TOKEN || symboleCourant.code=DIV_TOKEN || symboleCourant.code=MOD_TOKEN){
        result=true;
	}
	return result;
}

bool _primary-expression(){
	bool result= false;
    if(symboleCourant.code==IDF_TOKEN){
        SymbolSuivant();
        if(symboleCourant.code==CROCH_OUV_TOKEN){
            SymbolSuivant();
            if(symboleCourant.code==INUM_TOKEN){
                SymbolSuivant()
                if(symboleCourant.code==CROCH_FER_TOKEN){
                    result=true;
                }
            }
        }
        else{
            result=true;
            GetBack();
        }
    }
    else if(symboleCourant.code==PAR_OUV_TOKEN){
        SymbolSuivant();
        if(_conditional-or-expression()){
            SymbolSuivant();
            if(symboleCourant.code==PAR_FER_TOKEN){
                result=true;
            }
        }
    }
    else if(_invocation-expression()){
        result=true;
    }
    else if(symboleCourant.code==INUM_TOKEN || symboleCourant.code==FNUM_TOKEN || symboleCourant.code==TRUE_TOKEN || symboleCourant.code==FALSE_TOKEN || symboleCourant.code==CHAINE_TOKEN || symboleCourant.code==CHARACTER_TOKEN){
        result=true;
    }
    else if(_array-creation-expression()){
        result=true;
    }
	return result;
}

bool _invocation-expression(){
	bool result= false;
	if(symboleCourant.code==METH_IDF_TOKEN){
        SymbolSuivant();
        if(symboleCourant.code==PAR_OUV_TOKEN){
            SymbolSuivant();
            if(symboleCourant.code==PAR_FER_TOKEN){
                result=true;
            }
            else if(_argument-list()){
                SymbolSuivant();
                if(symboleCourant.code==PAR_FER_TOKEN){
                    result=true;
                }
            }
        }
	}
	return result;
}

bool _argument-list(){
	bool result= false;
    if(_argument()){
        bool loop=true;
        while(symboleCourant.code==VIR_TOKEN && loop){
            SymbolSuivant();
            if(_argument()){
                SymbolSuivant();
            }
            else{
                loop=false;
            }
        }
        if(loop) {
            result=true;
            GetBack();
        }
    }
	return result;
}

bool _argument(){
	bool result= _expression();
	return result;
}

bool _array-creation-expression(){
	bool result= false;
	if(symboleCourant.code==NEW_TOKEN){
        SymbolSuivant();
        if(_value-type()){
            SymbolSuivant();
            if(symboleCourant.code==CROCH_OUV_TOKEN){
                SymbolSuivant();
                if(_array-length()){
                    SymbolSuivant();
                    if(_array-initializer()){
                        result=true;
                    }
                    else{
                        result=true;
                        GetBack();
                    }
                }
            }
        }
	}
	return result;
}

bool _array-length(){
	bool result= false;
	if(symboleCourant.code==INUM_TOKEN){
        SymbolSuivant();
        if(symboleCourant.code==CROCH_FER_TOKEN){
            result=true;
        }
	}
	else if(symboleCourant.code==CROCH_FER_TOKEN){
        result=true;
    }
	return result;
}

bool _array-initializer(){
	bool result= false;
    if(symboleCourant.code==ACCOL_OUV_TOKEN){
        SymbolSuivant();
        if(symboleCourant.code==ACCOL_FER_TOKEN){
            result=true;
        }
        else if(_expression()){
            SymbolSuivant();
            if(symboleCourant.code==VIR_TOKEN){
                SymbolSuivant();
                while(_expression()){
                    SymbolSuivant();
                    if(symboleCourant.code==VIR_TOKEN){
                        SymbolSuivant();
                    }
                    else if(symboleCourant.code==ACCOL_FER_TOKEN){
                        result=true;
                        break;
                    }
                }
            }
            else if(symboleCourant.code==ACCOL_FER_TOKEN){
                result=true;
            }
        }
    }
	return result;
}














