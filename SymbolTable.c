#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "SymbolTable.h"

//Current Scope and Symbol Tables are globally defined

//===========================================================================================
//===========================Hash Function===================================================
//===========================================================================================

int hashFunc(char *name)
{
	
	int hashval =0, length = strlen(name), i ,multiplier = 1, a = 26;
	for(i=0;i<length;i++)
	{
		hashval += (name[i])*multiplier;
		multiplier=(multiplier*a)%M_SIZE;
		hashval=hashval%M_SIZE;
		
	}
	//printf("name=%s hash=%d\n",name,hashval%M_SIZE);
	return hashval%M_SIZE;
}

//===========================================================================================
//===========================Initialize Symbol tables========================================
//===========================================================================================

void SymbolTable_Initialize()
{
	int i,j;
	symtab table;
	table.s=empty;
	table.argumentListip_size=0;
	table.argumentListop_size=0;
	table.argument_output=0;
	for(i=0;i<MAX_ARGUMENTS;i++)
	{
		table.argumentListip[i]=-1;
		table.argumentListop[i]=-1;
	}
	//table.argument_end=-1;
	strcpy(table.value,"");
	for(i=0;i<M_SIZE;i++)
	{
		ST[i]=table;
		for(j=0;j<M_SIZE;j++)
		{
			ST[i].SymbolTable[j]=init_val;
		}
	}
	
}

void global_SymbolTable_Initialize()
{
	int i;
	for(i=0;i<M_SIZE;i++)
	{
		gST[i]=init_val;
	}
}

void rec_SymbolTable_Initialize()
{
	int i,j;
	rec table1;
	table1.s=empty;
	strcpy(table1.value,"");
	for(i=0;i<M_SIZE;i++)
	{
		rST[i]=table1;
		for(j=0;j<M_SIZE;j++)
		{
			rST[i].SymbolTable[j]=init_val;
		}		
	}
	
}


//===========================================================================================
//=====================Complete Print Function --- Modify to use=============================
//===========================================================================================

void SymbolTable_print(FILE *fp)
{
	int i, j, k;
    fprintf(fp,"\n============================\n\tSymbol Table 1\t\n============================\n");
	for(i=0;i<M_SIZE;i++)
	{
		if(ST[i].s==empty)
			continue;
		else	
		{	
            fprintf(fp,"Hash-Index of Symbol Table %d\n",i);
            fprintf(fp,"Function name %s \nNumber of Input Arguments %d\nNumber of Output Arguments %d\n",ST[i].value,ST[i].argumentListip_size,ST[i].argumentListop_size);
			if(ST[i].argumentListip_size>0)
			{
				fprintf(fp,"Arguments passed to Function %s are:",ST[i].value);
				for(j=0;j<ST[i].argumentListip_size;j++)
				{
					fprintf(fp,"%s ",ST[i].SymbolTable[ST[i].argumentListip[j]].value);
					
				}
				fprintf(fp,"\n");
			}
			if(ST[i].argumentListop_size>0)
			{
				fprintf(fp,"Output Arguments to Function %s are:",ST[i].value);
				for(j=0;j<ST[i].argumentListop_size;j++)
				{
					fprintf(fp,"%s ",ST[i].SymbolTable[ST[i].argumentListop[j]].value);
					
				}
				fprintf(fp,"\n");
			}
            //fprintf(fp,"Name\tHash\tType\tLine_num\n");
            //This Prints all the variables including the Function input and output arguments and the local variables of the function
            for(j=0;j<M_SIZE;j++)
			{
				if(ST[i].SymbolTable[j].s)
				{
                    /*for(j=0;j<ST[i].argumentListip_size;j++)
					{
						if(k==argumentListip[j])
						continue;
						else
						k++;
                    }*/
                    fprintf(fp,"%s\t\t%d\ttoken=%d\toffset=%d\tline=%d\n",ST[i].SymbolTable[j].value,j,ST[i].SymbolTable[j].t,ST[i].SymbolTable[j].offset,ST[i].SymbolTable[j].line_num);
				}
				
				//fprintf(fp,"\n");
			}
		}
	}
    fprintf(fp,"\n============================\n\tSymbol Table 2: Records\t\n============================\n");
    for(i=0;i<M_SIZE;i++)
    {
        if(rST[i].s==empty)
            continue;
        else
        {
            fprintf(fp,"Hash-Index of Record Symbol Table %d\n",i);
            fprintf(fp,"Record name %s\n",rST[i].value);
            for(j=0;j<M_SIZE;j++)
            {
                if(rST[i].SymbolTable[j].s)
                {
                    fprintf(fp,"%s\t\t%d\ttoken=%d\toffset=%d\tline=%d\n",rST[i].SymbolTable[j].value,j,rST[i].SymbolTable[j].t,rST[i].SymbolTable[j].offset,rST[i].SymbolTable[j].line_num);
                }
            }
        }

    }
    fprintf(fp,"\n============================\n\tSymbol Table 3: Global Variable\t\n============================\n");
    for(i=0;i<M_SIZE;i++)
    {
        if(gST[i].s==empty)
            continue;
        else
        {
            fprintf(fp,"%s\t\t%d\ttoken=%d\toffset=%d\tline=%d\n",gST[i].value,i,gST[i].t,gST[i].offset,gST[i].line_num);
        }
    }
	fprintf(fp,"\n============================\n\t\tEnd\t\t\n============================\n");
}


//===========================================================================================
//===========================Inserting into symbol tables====================================
//===========================================================================================

//Symbol Table for Functions and Local Variables

void HashTableInsert_Func(char *name, int line_num)
{
	int pos = hashFunc(name);
	//printf("hashFunc called %d\n",pos);
	int i =1;
	//printf("hi\n");
	while(ST[pos].s != empty)
	{
		//printf("inside while\n");
		if(!strcmp(ST[pos].value,name))
		{
			printf("ERROR line %d:Multiple Functions of same name %s\n",line_num,name);
			//exit(1);
		}
		//Quadratic Probing
		pos = (pos + i*i)%M_SIZE;
		i++;
	}
	//Insert Function into HashTable and create scope
	//printf("while called\n");
	strcpy(ST[pos].value,name);
	curr_scope=pos;
	ST[pos].s = full;	
	ST[pos].line_num=line_num;
}

int HashTableInsert_var(char *name,token Type,int offset,int line_num)
{
	int pos = hashFunc(name);
	int i =1;
	while(ST[curr_scope].SymbolTable[pos].s != empty)
	{
		if(!strcmp(ST[curr_scope].SymbolTable[pos].value,name))
		{
			printf("ERROR line %d:Multiple Variable of same name in same scope %s\n",line_num,name);
			//exit(1);
		}
		pos = (pos + i*i)%M_SIZE;
		i++;
	}
	//Insert Variable into Symbol Table
	strcpy(ST[curr_scope].SymbolTable[pos].value,name);
	ST[curr_scope].SymbolTable[pos].line_num = line_num;
	ST[curr_scope].SymbolTable[pos].offset=offset;
	ST[curr_scope].SymbolTable[pos].t=Type;
	ST[curr_scope].SymbolTable[pos].s = full;	
	return pos;	
}

//Symbol Table Record

void HashTableInsert_Rec(char *name, int line_num)
{
	int pos = hashFunc(name);
	int i=1;
	while(rST[pos].s!=empty)
	{
		if(!strcmp(rST[pos].value,name))
		{
			printf("ERROR line %d:Multiple RECORD of same name %s\n",line_num,name);
			//exit(1);
		}
		pos = (pos + i*i)%M_SIZE;
		i++;		
	}
	strcpy(rST[pos].value,name);
	rST[pos].s = full;
}

int HashTableInsert_Rec_var(char *name,token Type,int offset,int line_num)
{
	int pos = hashFunc(name);
	int i=1;
	while(rST[rec_curr_scope].SymbolTable[pos].s != empty)
	{
		if(!strcmp(rST[rec_curr_scope].SymbolTable[pos].value,name))
		{
			printf("ERROR line %d:Multiple Global Variable in RECORD of same name %s\n",line_num,name);
			//exit(1);
		}
		pos = (pos + i*i)%M_SIZE;
		i++;
	}
	//Insert Variable into Symbol Table
	strcpy(rST[curr_scope].SymbolTable[pos].value,name);
	rST[rec_curr_scope].SymbolTable[pos].line_num = line_num;
	rST[rec_curr_scope].SymbolTable[pos].offset=offset;
	rST[rec_curr_scope].SymbolTable[pos].t=Type;
	rST[rec_curr_scope].SymbolTable[pos].s = full;	
	return pos;
}

//Symbol Table Global Variable

int HashTableInsert_global_var(char *name,token Type,int offset,int line_num)
{
	int pos = hashFunc(name);
	int i=1;
	while(gST[pos].s!=empty)
	{
		if(!strcmp(gST[pos].value,name))
		{
			printf("ERROR line %d:Multiple Global Variables of same name %s\n",line_num,name);
			//exit(1);
		}
		pos = (pos + i*i)%M_SIZE;
		i++;
	}
	strcpy(gST[pos].value,name);
	gST[pos].s=full;
	gST[pos].t=Type;
	gST[pos].offset=offset;
	gST[pos].line_num=line_num;
	return pos;
}

//===========================================================================================
//===========================Scope Look up for symbol table==================================
//===========================================================================================

int Var_Scope(char *name)
{
	int pos = hashFunc(name);
	int i =1;
	while(ST[curr_scope].SymbolTable[pos].s != empty)
	{
		if(strcmp(ST[curr_scope].SymbolTable[pos].value,name)==0)
			return pos;
		pos = (pos + i*i)%M_SIZE;
		i++;
	}
	return -1;
}

int Func_Scope(char *name)
{
	int i,j;
	int pos = hashFunc(name);
	while(ST[pos].s != empty)
	{
		if(strcmp(ST[pos].value,name)==0)
			return pos;
		pos = (pos + i*i)%M_SIZE;
		i++;
	}
	return -1;	
}

int Rec_Scope(char *name)
{
	int i,j;
	int pos = hashFunc(name);
	while(rST[pos].s != empty)
	{
		if(strcmp(rST[pos].value,name)==0)
			return pos;
		pos = (pos + i*i)%M_SIZE;
		i++;
	}
	return -1;	
}

int Rec_Var_Scope(char *name)
{
	int pos = hashFunc(name);
	int i =1;
	while(rST[rec_curr_scope].SymbolTable[pos].s != empty)
	{
		if(strcmp(rST[rec_curr_scope].SymbolTable[pos].value,name)==0)
			return pos;
		pos = (pos + i*i)%M_SIZE;
		i++;
	}
	return -1;
}

int Global_Scope(char *name)
{
	int pos = hashFunc(name);
	int i =1;
	while(gST[pos].s != empty)
	{
		if(strcmp(gST[pos].value,name)==0)
			return pos;
		pos = (pos + i*i)%M_SIZE;
		i++;
	}
	return -1;
}

int getIndex(int a[]){
	int i=0;
	while(i<MAX_ARGUMENTS){
		if(a[i]==-1){
			return i;
		}
		i++;
	}
}

void findIpParameters(abstractSyntaxTree temp){
	if(temp->s.terminal==TK_FUNID && flag_func==1){
		printf("ERROR line %d: Function %s declared inside another function\n",temp->t.line_num,temp->t.lexeme);
	}
	if(temp->s.terminal==TK_OUTPUT){
		//end of input list
		return;
	}
	if(temp->s.terminal==TK_INT || temp->s.terminal==TK_REAL || temp->s.terminal==TK_RECORD){
		// update Offset
		if(temp->s.terminal==TK_INT){globalOff+=4;}
		else if(temp->s.terminal==TK_REAL){globalOff+=8;}
		else if(temp->s.terminal==TK_RECORD){globalOff+=16;}//find correct value in 2nd pass
		
		// id is in its sibling insert it into the funstions input par table
		int hashIndex=HashTableInsert_var(temp->sibling->t.lexeme,temp->sibling->s.terminal,globalOff,temp->sibling->t.line_num);
		// make fun for getting index
		int idIndex=getIndex(ST[curr_scope].argumentListip);
		ST[curr_scope].argumentListip[idIndex]=hashIndex;
		(ST[curr_scope].argumentListip_size)++;
	} 
	
	//DFS PART
	if(temp->child!=NULL){
		//printf("if 2\n");
		findIpParameters(temp->child);
	}
	if(temp->sibling!=NULL){
		//printf("if 3\n");
		findIpParameters(temp->sibling);
	}
	if(temp->sibling==NULL){
		//printf("if 4\n");
		return;
	}
}

void findOpParameters(abstractSyntaxTree temp){
	if(temp->s.terminal==TK_FUNID && flag_func==1){
		printf("ERROR line %d: Function %s declared inside another function\n",temp->t.line_num,temp->t.lexeme);
	}
	if(temp->s.nonterminal==stmts){
		//end of output list
		return;
	}
	if(temp->s.terminal==TK_INT || temp->s.terminal==TK_REAL || temp->s.terminal==TK_RECORD){
		// update Offset
		if(temp->s.terminal==TK_INT){globalOff+=4;}
		else if(temp->s.terminal==TK_REAL){globalOff+=8;}
		else if(temp->s.terminal==TK_RECORD){globalOff+=16;}//find correct value in 2nd pass
		// id is in its sibling insert it into the funstions output par table
		int hashIndex=HashTableInsert_var(temp->sibling->t.lexeme,temp->sibling->s.terminal,globalOff,temp->sibling->t.line_num);
		// make fun for getting index
		int idIndex=getIndex(ST[curr_scope].argumentListop);
		ST[curr_scope].argumentListop[idIndex]=hashIndex;
		(ST[curr_scope].argumentListop_size)++;
		//printf("op par = %d\n",(ST[curr_scope].argumentListop_size));
	} 
	
	//DFS PART
	if(temp->child!=NULL){
		//printf("if 2\n");
		findOpParameters(temp->child);
	}
	if(temp->sibling!=NULL){
		//printf("if 3\n");
		findOpParameters(temp->sibling);
	}
	if(temp->sibling==NULL){
		//printf("if 4\n");
		return;
	}
}

void findIpAndOpParameters(abstractSyntaxTree temp){
	//abstractSyntaxTree temp=ast;
	//populating input and output parameters
	flag_func=1;
	if(temp->s.terminal==TK_INPUT){
		//insert into input list
		findIpParameters(temp);
	}
	if(temp->s.terminal==TK_OUTPUT){
		//insert into output list
		findOpParameters(temp);
		return;
	}
	
	//DFS PART
	if(temp->child!=NULL){
		//printf("if 2\n");
		findIpAndOpParameters(temp->child);
	}
	if(temp->sibling!=NULL){
		//printf("if 3\n");
		findIpAndOpParameters(temp->sibling);
	}
	if(temp->sibling==NULL){
		//printf("if 4\n");
		return;
	}
}

int checkGlobal(abstractSyntaxTree temp){
	abstractSyntaxTree new_temp=temp;
	if(new_temp->sibling->s.terminal==TK_GLOBAL){
		return 1;
	}
	else{
		return 0;
	}
}

void insertTheVar(abstractSyntaxTree temp){
	if(temp->s.terminal==TK_ID){
		//insert the var into func table and if global insert into global table
		int g=checkGlobal(temp);//check if its global
		int x=hashFunc(temp->t.lexeme);
		if(gST[x].s==full){
			printf("ERROR line %d: Identifier %s already declared globally, can't be decared again\n",temp->t.line_num,temp->t.lexeme); 
		}
		
		if(g==1){
			//ie its global
			//insert in global table
			int hashIndex=HashTableInsert_global_var(temp->t.lexeme,temp->s.terminal,globalOff,temp->t.line_num);
			
			gST[hashIndex].s=full;
		}
		else{
			//insert in func table
			// id is in its sibling insert it into the funstions output par table
			int hashIndex=HashTableInsert_var(temp->t.lexeme,temp->s.terminal,globalOff,temp->t.line_num);
			// make fun for getting index
		}
		return;
	}
	
	//DFS PART
	if(temp->child!=NULL){
		//printf("if 2\n");
		insertTheVar(temp->child);
	}
	if(temp->sibling!=NULL){
		//printf("if 3\n");
		insertTheVar(temp->sibling);
	}
	if(temp->sibling==NULL){
		//printf("if 4\n");
		return;
	}
}

void insertDec(abstractSyntaxTree temp){
	if(temp->s.terminal==TK_INT || temp->s.terminal==TK_REAL || temp->s.terminal==TK_RECORD){
		// update Offset
		if(temp->s.terminal==TK_INT){globalOff+=4;}
		else if(temp->s.terminal==TK_REAL){globalOff+=8;}
		else if(temp->s.terminal==TK_RECORD){globalOff+=16;}//find correct value in 2nd pass
		//find the variable to insert
		insertTheVar(temp);
		//variable inserted
		return;
	}
	
	//DFS PART
	if(temp->child!=NULL){
		//printf("if 2\n");
		insertDec(temp->child);
	}
	if(temp->sibling!=NULL){
		//printf("if 3\n");
		insertDec(temp->sibling);
	}
	if(temp->sibling==NULL){
		//printf("if 4\n");
		return;
	}
}

void insertForMain(abstractSyntaxTree temp){
	//check the declaration variables
	if(temp->s.terminal==TK_TYPE){
		//declaration found
		//put the variable in symbol table of the function if global put in the global symb table
		insertDec(temp->child);
	}
	if(temp->s.nonterminal==stmts){
		return;
	}
	//DFS PART
	if(temp->child!=NULL){
		//printf("if 2\n");
		insertForMain(temp->child);
	}
	if(temp->sibling!=NULL){
		//printf("if 3\n");
		insertForMain(temp->sibling);
	}
	if(temp->sibling==NULL){
		//printf("if 4\n");
		return;
	}
}

void insertRecFields(abstractSyntaxTree temp){
	if(temp->s.terminal==TK_INT || temp->s.terminal==TK_REAL){
		// update Offset
		if(temp->s.terminal==TK_INT){globalOff+=4;}
		else if(temp->s.terminal==TK_REAL){globalOff+=8;}
		// id is in its sibling insert it into the funstions output par table
		int hashIndex=HashTableInsert_Rec_var(temp->sibling->t.lexeme,temp->sibling->s.terminal,globalOff,temp->sibling->t.line_num);
		return;
	}
	
	//DFS PART
	if(temp->child!=NULL){
		//printf("if 2\n");
		insertRecFields(temp->child);
	}
	if(temp->sibling!=NULL){
		//printf("if 3\n");
		insertRecFields(temp->sibling);
	}
	if(temp->sibling==NULL){
		//printf("if 4\n");
		return;
	}
}

void insertForRec(abstractSyntaxTree temp){
	//check the declaration variables
	if(temp->s.terminal==TK_TYPE){
		//declaration found
		//put the variable in symbol table of the function if global put in the global symb table
		insertRecFields(temp->child);
	}
	
	if(temp->s.nonterminal==declarations || temp->s.terminal==E){
		return;
	}
	
	//DFS PART
	if(temp->child!=NULL){
		//printf("if 2\n");
		insertForRec(temp->child);
	}
	if(temp->sibling!=NULL){
		//printf("if 3\n");
		insertForRec(temp->sibling);
	}
	if(temp->sibling==NULL){
		//printf("if 4\n");
		return;
	}
}

void fillSymbolTable(abstractSyntaxTree ast){
	//printf("fill called\n");
	abstractSyntaxTree parent=ast;
	//printf("%s \n",parent->t.lexeme);
	if(parent->s.terminal==TK_FUNID && main_flag!=1){
		//printf("hashTbaleinsert called\n");
		//printf("main flag=%d\n",main_flag);
		//printf("%s \n",parent->t.lexeme);
		HashTableInsert_Func(parent->t.lexeme,parent->t.line_num);
		ST[curr_scope].s=full;
		ST[curr_scope].line_num=parent->t.line_num;
		//printf("strcpy called\n");
		strcpy(ST[curr_scope].value,parent->t.lexeme);
		//printf("strcpy cool\n");
		//populate ip and op parameters
		//printf("calling fillIpOp\n");
		//parent=parent->child;//go to children of TK_FUNID
		findIpAndOpParameters(parent);
		flag_func=0;
	}
	//check the declaration variables
	if(parent->s.terminal==TK_TYPE){
		//declaration found
		//put the variable in symbol table of the function if global put in the global symb table
		insertDec(parent->child);
	}
	
	if(parent->s.terminal==TK_MAIN){
		main_flag=1;
		//printf("main flag set\n");
		HashTableInsert_Func(parent->t.lexeme,parent->t.line_num);
		ST[curr_scope].s=full;
		ST[curr_scope].line_num=parent->t.line_num;
		strcpy(ST[curr_scope].value,parent->t.lexeme);
		insertForMain(parent->child);	
	}
	
	if(parent->s.terminal==TK_RECORD){
		HashTableInsert_Rec(parent->child->t.lexeme,parent->child->t.line_num);
		rST[rec_curr_scope].s=full;
		rST[rec_curr_scope].line_num=parent->child->t.line_num;
		strcpy(rST[rec_curr_scope].value,parent->child->t.lexeme);
		insertForRec(parent->child);	
	}
	
	//DFS PART
	if(parent->child!=NULL){
		//printf("if 2\n");
		fillSymbolTable(parent->child);
	}
	if(parent->sibling!=NULL){
		//printf("if 3\n");
		fillSymbolTable(parent->sibling);
	}
	if(parent->sibling==NULL){
		//printf("if 4\n");
		return;
	}
}

void typeChecker(abstractSyntaxTree ast){
	abstractSyntaxTree parent=ast;
	if(parent->s.terminal==TK_INT){
		//printf("%s %d int\n",parent->t.lexeme,parent->t.line_num);
		abstractSyntaxTree temp=parent->sibling;
		temp->exp=integer;
	}
	else if(parent->s.terminal==TK_REAL){
		//printf("%s %d int\n",parent->t.lexeme,parent->t.line_num);
		abstractSyntaxTree temp=parent->sibling;
		temp->exp=real;
		
	}
	else if(parent->s.terminal==TK_RECORD){
		//printf("%s %d int\n",parent->t.lexeme,parent->t.line_num);
		abstractSyntaxTree temp=parent->sibling;
		temp->exp=record;
		
	}
	else if(parent->s.terminal==TK_NUM){
		//printf("%s %d intxx\n",parent->t.lexeme,parent->t.line_num);
		parent->exp=integer;
	}
	else if(parent->s.terminal==TK_RNUM){
		//printf("%s %d realxx\n",parent->t.lexeme,parent->t.line_num);
		parent->exp=real;
	}

	if(parent->child!=NULL){
		//printf("if 2\n");
		typeChecker(parent->child);
	}
	if(parent->sibling!=NULL){
		//printf("if 3\n");
		typeChecker(parent->sibling);
	}
	if(parent->sibling==NULL){
		//printf("if 4\n");
		return;
	}
}

void checkIfDecAsGlobal(char* name,int line_num){
	int pos=hashFunc(name);
	int i=1;
	while(gST[pos].s!=empty)
	{
		if(i==5){
			return;
		}
		if(!strcmp(gST[pos].value,name))
		{
			printf("ERROR line %d:Variable %s already declared as a global can't be declared again\n",line_num,name);
			return;
			//exit(1);
		}
		pos = (pos + i*i)%M_SIZE;
		i++;
	}
}

void checkIfIdDecBeforeUse(char *name, int line_num){
	int pos=hashFunc(name);
	int flag=0;
	// check in global symbol table
	int i=1;
	while(gST[pos].s!=empty)
	{
		if(i==5){
			break;
		}
		if(!strcmp(gST[pos].value,name))
		{
			flag=1;
		}
		pos = (pos + i*i)%M_SIZE;
		i++;
	}
	if(gST[pos].s!=empty){
		flag=1;
	}
	//check in current function scope
	i =1;
	while(ST[scope_for_rule2].SymbolTable[pos].s != empty)
	{
		if(i==5){
			break;
		}
		if(!strcmp(ST[scope_for_rule2].SymbolTable[pos].value,name))
		{
			flag=1;
		}
		pos = (pos + i*i)%M_SIZE;
		i++;
	}
	if(ST[scope_for_rule2].SymbolTable[pos].s != empty){
		flag=1;
	}
	if(flag==0){
		printf("ERROR line %d: Variable %s not declared before use \n",line_num,name);
	}
	return;
}

void checkIfSameIpPars(abstractSyntaxTree temp, char *name,int line_num){
	//printf("called\n");
	abstractSyntaxTree new_temp=temp;
	//printf("%s\n",new_temp->t.lexeme);
	int pos=hashFunc(new_temp->t.lexeme);
	int count=0;
	while(new_temp->sibling!=NULL){
	new_temp=new_temp->sibling;
	}
	new_temp=new_temp->child;
	while(new_temp->s.terminal!=E){
		if(new_temp->s.terminal==TK_ID || new_temp->s.terminal==TK_RECORD || new_temp->s.terminal==TK_FIELDID)
			count++;
		new_temp=new_temp->child;
	}
	//printf("%d %d\n",count,ST[pos].argumentListip_size);
	if(count==ST[pos].argumentListip_size){
		return;
	}
	else{
		printf("ERROR line %d: Function %s called with %d parameters instead of %d\n",line_num,name,count,ST[pos].argumentListip_size);
	}
}

void semanticAnalyzer(abstractSyntaxTree ast){
	abstractSyntaxTree temp=ast;
	//rule 1 already done while filling symbol table
	
	if((temp->s.terminal==TK_FUNID && temp->sibling->s.terminal!=TK_WITH) || temp->s.terminal==TK_MAIN){
		scope_for_rule2=hashFunc(temp->t.lexeme);
		curr_func_line_no=temp->t.line_num;
	}
	
	//check rule 2
	if(temp->s.terminal==TK_ID){
		checkIfIdDecBeforeUse(temp->t.lexeme,temp->t.line_num);
	}
	//check rule 3
	if(temp->s.terminal==TK_ID && temp->parent->s.terminal==TK_TYPE && temp->sibling->s.terminal!=TK_GLOBAL){
		checkIfDecAsGlobal(temp->t.lexeme,temp->t.line_num);
	}
	
	//check rule 4 and check rule 5
	if(temp->s.terminal==TK_CALL){
		checkIfSameIpPars(temp->sibling,temp->t.lexeme,temp->t.line_num);
	}
	
	//check rule 10
	if(temp->s.terminal==TK_FUNID && temp->sibling->s.terminal==TK_WITH){
		int sc;
		sc=hashFunc(temp->t.lexeme);
		if(sc==scope_for_rule2){
			printf("ERROR line %d: Function %s called recursively\n",temp->t.line_num,temp->t.lexeme);
		}
	}
	
	//rule 11 done as function scope and global symbol table take care of whether a variable is defined within a scope
	
	//rule 12 done as record is stored in a separate table
	
	//check rule 14
	if((temp->s.terminal==TK_CALL) && (temp->sibling->s.terminal==TK_FUNID)){
		int l;
		int p=hashFunc(temp->sibling->t.lexeme);
		if(ST[p].s==empty){
			printf("ERROR line %d: Call to an undefined function %s\n",temp->t.line_num,temp->sibling->t.lexeme);
		}
		else if((ST[p].line_num)>=l){
			printf("ERROR line %d: Call to a function %s which is defined after the call takes place\n",temp->t.line_num,temp->sibling->t.lexeme);
		}
	}
		
	//DFS part
	if(temp->child!=NULL){
		//printf("if 2\n");
		semanticAnalyzer(temp->child);
	}
	if(temp->sibling!=NULL){
		//printf("if 3\n");
		semanticAnalyzer(temp->sibling);
	}
	if(temp->sibling==NULL){
		//printf("if 4\n");
		return;
	}
}

void printFuncType(abstractSyntaxTree ast,FILE *fout){
	abstractSyntaxTree temp=ast;
	//printf("called prinFuncAst\n");
	//printf("nt=%d t=%d\n",temp->s.nonterminal,temp->s.terminal);
	int n=0;
	if(temp->parent->s.type==1){
		n=temp->parent->s.terminal;
	}
	else if(temp->parent->s.type==0){
		n=temp->parent->s.nonterminal;
	}
	//printf("n=%d\n",n);
	if(temp->child!=NULL){
		//printf("go to child\n");
		if(temp->s.type==1){
			if(temp->s.terminal==E)
			{
				//printf("terminal is eps\n");
				char *val;
				temp->t.lexeme="eps";
				temp->t.line_num=-1;
				val="-------------";
				fprintf(fout,"%s\t\t\t        %d    \t%d\t\t %s   \t     %d\t\t\t     yes   \t\t     ----------type=%d  opType=%d\n",temp->t.lexeme,temp->t.line_num,temp->s.terminal,val,n,temp->exp,temp->expOp);
		
			}
			else
			{
				char *val;
				if(temp->s.terminal==4 || temp->s.terminal==5){
					val=temp->t.lexeme;
				}
				else{
					//printf("else\n");
					val="---------";
					//strcpy(val,"-------------");
					//printf("outofelse\n");
				}
				//fprintf(fout,"%s\n",temp->t.lexeme);
				fprintf(fout,"%s\t\t\t    %d    \t%d\t\t %s   \t     %d\t\t\t     no   \t\t     ----------type=%d  opType=%d\n",temp->t.lexeme,temp->t.line_num,temp->s.terminal,val,n,temp->exp,temp->expOp);
			}
		}
		else{
			//fprintf(fout,"%d\n",temp->s.nonterminal);
			fprintf(fout,"-----------------\t------\t-----\t-------------\t         %d        \t      no       \t        %d     type=%d  opType=%d\n",n, temp->s.nonterminal, temp->exp,temp->expOp);
		}
		printFuncType(temp->child,fout);
	}
	if(temp->sibling!=NULL){
		//printf("go to sib\n");
		if(temp->child==NULL){
			if(temp->s.type==1){
				if(temp->s.terminal==E)
				{
					//printf("terminal is eps\n");
					char *val;
					temp->t.lexeme="eps";
					temp->t.line_num=-1;
					val="-------------";
					fprintf(fout,"%s\t\t\t        %d    \t%d\t\t %s   \t     %d\t\t\t     yes   \t\t     ----------type=%d  opType=%d\n",temp->t.lexeme,temp->t.line_num,temp->s.terminal,val,n,temp->exp,temp->expOp);
		
				}
				else
				{
					char *val;
					if(temp->s.terminal==4 || temp->s.terminal==5){
						val=temp->t.lexeme;
					}
					else{
						//printf("else\n");
						val="---------";
						//strcpy(val,"-------------");
						//printf("outofelse\n");
					}
					//fprintf(fout,"%s\n",temp->t.lexeme);
					fprintf(fout,"%s\t\t\t    %d    \t%d\t\t %s   \t     %d\t\t\t     no   \t\t     ----------type=%d  opType=%d\n",temp->t.lexeme,temp->t.line_num,temp->s.terminal,val,n,temp->exp,temp->expOp);

				}
			}
			else{
				//fprintf(fout,"%d\n",temp->s.nonterminal);
				fprintf(fout,"-----------------\t------\t-----\t-------------\t         %d        \t      yes       \t        %d     type=%d  opType=%d\n",n, temp->s.nonterminal,temp->exp,temp->expOp);
			}
		}
		printFuncType(temp->sibling,fout);
	}
	if((temp->sibling==NULL) && (temp->child==NULL)){
		//printf("go back\n");
		if(temp->s.type==1){
			if(temp->s.terminal==E)
			{
				//printf("terminal is eps\n");
				char *val;
				temp->t.lexeme="eps";
				temp->t.line_num=-1;
				val="-------------";
				fprintf(fout,"%s\t\t\t        %d    \t%d\t\t %s   \t     %d\t\t\t     yes   \t\t     ----------type=%d  opType=%d\n",temp->t.lexeme,temp->t.line_num,temp->s.terminal,val,n,temp->exp,temp->expOp);
		
			}
			else
			{
				char *val;
				if(temp->s.terminal==4 || temp->s.terminal==5){
					val=temp->t.lexeme;
				}
				else{
					//printf("else\n");
					val="---------";
					//strcpy(val,"-------------");
					//printf("outofelse\n");
				}
				//fprintf(fout,"%s\n",temp->t.lexeme);
				fprintf(fout,"%s\t\t\t    %d    \t%d\t\t %s   \t     %d\t\t\t     no   \t\t     ----------type=%d  opType=%d\n",temp->t.lexeme,temp->t.line_num,temp->s.terminal,val,n,temp->exp,temp->expOp);

			}
		}
		else{
			//fprintf(fout,"%d\n",temp->s.nonterminal);
			fprintf(fout,"-----------------\t------\t-----\t-------------\t         %d        \t      yes       \t        %d     type=%d\n",n, temp->s.nonterminal,temp->exp);
		}
	}
}

void showType(abstractSyntaxTree ast){
	FILE *fp=fopen("typeCheckOut.txt","w");
	fprintf(fp,"lexemeCurrentNode\tlineno\ttoken\tvalueIfNumber\tparentNodeSymbol\tisLeafNode(yes/no)\tNodeSymbol\n");
	printFuncType(ast,fp);
	fclose(fp);
}
