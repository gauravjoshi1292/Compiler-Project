#ifndef SYMBOLTABLEDEF_H_INCLUDED
#define SYMBOLTABLEDEF_H_INCLUDED


#include "lexer.h"
#include "parser.h"
//#include<stdio.h>

#define M_SIZE 100
#define MAX_ARGUMENTS 50

typedef enum {variable=0, func}type;
typedef enum {empty=0, full}entry_status;

typedef struct
{
	entry_status s;//Empty or Filled Positon in Hash Table
    char value[MAX];//Name
    token t;//Type
    int offset;//Offset
    int line_num;//Line Number
}symtab_entry;

typedef struct
{
	entry_status s;
	char value[MAX];
	int argumentListip_size;//Number of I/P Arguments
	int argumentListip[MAX_ARGUMENTS];//Position of I/P Arguments in Hash Table
	int argumentListop_size;//Number of O/P Arguments
	int argumentListop[MAX_ARGUMENTS];//Position of O/P Arguments in Hash Table
	int argument_output;//Output arguments present
	//int argument_end;//Position of End of Argument List
	int line_num;//Line number of function declaration
	symtab_entry SymbolTable[M_SIZE];
}symtab;

typedef struct
{
	entry_status s;
	char value[MAX];
	int line_num;
	symtab_entry SymbolTable[M_SIZE];	
}rec;

//Global Variable for
int curr_scope;//Current Scope
int rec_curr_scope;//Record Scope

symtab ST[M_SIZE];//Symbol Table Array
symtab_entry gST[M_SIZE];//Global Variable Symbol Table
rec rST[M_SIZE];//Global Record Symbol Table

symtab_entry init_val = (symtab_entry){0,"",54,0,-1};// Initial Value of Symbol Table Entries

int globalOff=0;
int flag_func=0;
int main_flag=0;
int scope_for_rule2=0;
int curr_func_line_no=0;

#endif
