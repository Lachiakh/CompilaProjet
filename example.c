typedef struct{char code[20]; char nom[20];}Tsym_cour;
typedef struct Code Code;
struct Code{char code[20]; char nom[20]; Code *next;};

char curr_token[20];
char curr_name[20];
Code* first;

void anal_lex(char* nom_fichier){

  first= malloc(sizeof(*first));
  Code* current= first;
  int comp=0;  
  FILE *f;
  f= fopen(nom_fichier,"r");
  int loop=1;
  char car_cour;

  while(loop && car_cour!=EOF){
	car_cour=fgetc(f);
	Tsym_cour sym_cour;
	int c;
	char car_cour2;
	//Si mot (Mot-clé,ID ou EOF)
	if ( (car_cour>64 && car_cour<91) || (car_cour>96 && car_cour<123) ) { //Cas d'une lettre 
		sym_cour= getMot(f,car_cour);
		//printf("%s\n",sym_cour.code);
		strcpy(current->code, sym_cour.code);
		strcpy(current->nom, sym_cour.nom);
		current->next= malloc(sizeof(Code));
		current=current->next;
		if(strcmp(sym_cour.nom,"EOF")==0) loop=0;
	}

	//Si numero
	else if(car_cour<58 && car_cour>47){//Cas d'un nombre
		strcpy(sym_cour.nom,getNum(f,car_cour));
		//printf("NUM_TOKEN\n");
		strcpy(current->code, "NUM_TOKEN");
		strcpy(current->nom, sym_cour.nom);
		current->next= malloc(sizeof(Code));
		current=current->next;
	}
	
	//Si commentaire
	else if(car_cour=='/') {
		car_cour=fgetc(f);
		if (car_cour=='/') while(fgetc(f)!='\n');
		else if(car_cour=='*'){
			car_cour=fgetc(f);
			car_cour2=fgetc(f);
			while(car_cour!='*' || car_cour2!='/'){
				car_cour=fgetc(f);
				car_cour2=fgetc(f);
			}
		}
		else ungetc(car_cour,f);			
	}

	//Si car.spécial (END déjà traité)
	else if(c= isCarSpe(car_cour,f)){
		strcpy(sym_cour.code,tokens[c-1]);
		strcpy(sym_cour.nom,noms[c-1]);
		//printf("%s\n",sym_cour.code);
		strcpy(current->code, sym_cour.code);
		strcpy(current->nom, sym_cour.nom);
		current->next= malloc(sizeof(Code));
		current=current->next;
	}

  	//Si espace, retour à la ligne ou tabulation
	else if(car_cour==32 || car_cour=='\n' || car_cour=='\t');

	//Si EOF
	else if(car_cour==EOF){
		//printf("FIN_TOKEN\n");
		strcpy(current->code, "FIN_TOKEN");
		strcpy(current->nom, "EOF");
		current->next= malloc(sizeof(Code));
		current=current->next;
	}

	//Sinon (erreur)
	else{
		//printf("ERREUR_TOKEN\n");
		strcpy(current->code, "ERREUR_TOKEN");
		strcpy(current->nom, &car_cour);
		current->next= malloc(sizeof(Code));
		current=current->next;
	}
  } 
  fclose(f);
  return;
 
}

void show(){
	while(first!=NULL){
		printf("%s----------%s\n",first->code,first->nom);
		first= first->next;
	}
}

void move_token(){
	printf("move_token() called:\n");
	strcpy(curr_token, first->code);
	strcpy(curr_name, first->nom);
	first=first->next;
}


int main(){
	anal_lex("text.txt");
	//show();
	int i=0;
	while(strcmp(curr_token,"FIN_TOKEN")!=0){
		move_token();
		printf("Current token/name: ------------%d-------%s------------%s---------\n",i,curr_token,curr_name);
		i++;
	}

}

