#ifndef STACKDEF_H_INCLUDED
#define STACKDEF_H_INCLUDED
#include"parserDef.h"
//typedef struct _stackNode stackNode;
typedef struct _stackNode *Link;

typedef struct _stackNode{
	sym s;
	Link next;
}stackNode;

typedef struct{
	Link top;
	int size;
}Stack;

typedef struct _ruleNode *nxt;

typedef struct _ruleNode{
	int rule_no;
	nxt next;
}ruleNode;

typedef struct{
	nxt top;
	int size;
}rule_stack;

#endif
