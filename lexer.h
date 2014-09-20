#ifndef LEXER_H_INCLUDED
#define LEXER_H_INCLUDED

#include "lexerDef.h"

extern FILE *getStream(FILE *fp, buffer B, buffersize k,int *y);
extern int isDelimiter(char ch);
extern int isSpecialChar(char ch);
extern int isKnownSymbol(char ch);
extern int checkState(int s);
extern tokenInfo getNextToken();
extern tokenInfo getNext();
extern void add$();
extern int  getTokenList( FILE *fp,tokenInfo *info);

#endif // LEXER_H_INCLUDED
