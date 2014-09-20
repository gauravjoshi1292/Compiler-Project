#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED
#include "parserDef.h"

extern void createParseTable(grammar G,Table T,Set first_set,Set follow_set);
extern parseTree  parseInputSourceCode(Table T,grammar G);
extern void printParseTree(parseTree  PT, char *outfile);
extern abstractSyntaxTree createAbstractSyntaxtree(parseTree T, abstractSyntaxTree A, grammar G);
extern void printAST(abstractSyntaxTree A, char *outFile);//, int *totalAllocatedMemory);
#endif
