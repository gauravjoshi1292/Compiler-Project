#ifndef SYMBOLTABLE_H_INCLUDED
#define SYMBOLTABLE_H_INCLUDED

#include "SymbolTableDef.h"

//Function Prototypes
extern int hashFunc(char *name);
extern void SymbolTable_Initialize();
extern void global_SymbolTable_Initialize();
extern void rec_SymbolTable_Initialize();
extern void SymbolTable_print(FILE *fp);
extern int HashTableInsert_var(char *name,token Type,int offset,int line_num);
extern void HashTableInsert_Func(char *name,int line_num);
extern void HashTableInsert_Rec(char *name, int line_num);
extern int HashTableInsert_Rec_var(char *name,token Type,int offset,int line_num);
extern int HashTableInsert_global_var(char *name,token Type,int offset,int line_num);
extern int Var_Scope(char *name);
extern int Func_Scope(char *name);
extern int Global_Scope(char *name);
extern int Rec_Var_Scope(char *name);
extern int Rec_Scope(char *name);
extern void fillSymbolTable(abstractSyntaxTree ast);
extern void typeChecker(abstractSyntaxTree ast);
extern void SymbolTable_Initialize();
extern void global_SymbolTable_Initialize();
extern void rec_SymbolTable_Initialize();
extern void findIpParameters(abstractSyntaxTree temp);
extern void findOpParameters(abstractSyntaxTree temp);
extern void findIpAndOpParameters(abstractSyntaxTree temp);
extern void fillSymbolTable(abstractSyntaxTree ast);
extern void semanticAnalyzer(abstractSyntaxTree ast);
extern void checkIfDecAsGlobal(char* name,int line_num);
extern void checkIfIdDecBeforeUse(char *name, int line_num);
extern void checkIfSameIpPars(abstractSyntaxTree temp, char *name,int line_num);


#endif
