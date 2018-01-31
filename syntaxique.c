#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "lex.h"

extern Symbole symboleCourant;

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

bool _type(){
	bool result= false;
	if(_value-type()){
		SymbolSuivant();
		//if(symboleCourant.code==CROCH_OUV_TOKENPOINT_VIRG_TOKEN)
	}
	return result;
}

bool {
	bool result= false;
	return result;
}

bool {
	bool result= false;
	return result;
}

bool {
	bool result= false;
	return result;
}

bool {
	bool result= false;
	return result;
}

bool {
	bool result= false;
	return result;
}

bool {
	bool result= false;
	return result;
}

bool {
	bool result= false;
	return result;
}

bool {
	bool result= false;
	return result;
}

bool {
	bool result= false;
	return result;
}

















