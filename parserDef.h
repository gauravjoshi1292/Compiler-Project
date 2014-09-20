#ifndef PARSERDEF_H_INCLUDED
#define PARSERDEF_H_INCLUDED
#include "lexerDef.h"
#define MAXNONTERM 51
#define MAXTERM 55 //added dollar also
#define MAXRULES 90
#define MAX 50
typedef enum
{
program=0,
mainFunction,
otherFunctions,
function,
input_par,
output_par,
parameter_list,
dataType,
primitiveDatatype,
constructedDatatype,
remaining_list,
stmts,
typeDefinitions,
typeDefinition,
fieldDefinitions,
fieldDefinition,
moreFields,
declarations,
declaration,
global_or_not,
otherStmts,
stmt,
assignmentStmt,
singleOrRecId,
singleOrRecIDElse,
funCallStmt,
outputParameters,
inputParameters,
iterativeStmt,
conditionalStmt,
elsePart,
ioStmt,
allVar,
arithmeticExpression,
expPrime,
term,
termPrime,
factor,
highPrecedenceOperators,
lowPrecedenceOperators,
all,
temp,
booleanExpression,
var,
logicalOp,
relationalOp,
returnStmt,
optionalReturn,
idList,
more_ids
}NT;

typedef enum
{
boolean=0,
integer,
real,
record,
notype
}dtype;

typedef enum
{
arithmetic=0,
relational,
logical,
noop
}op;

//typedef struct GrammarSymbol sym;

typedef struct GrammarSymbol
{
	int type;
	token terminal;
	NT nonterminal;
}sym;

typedef struct link linknode;
typedef linknode *LINK;
struct link
	{	char name[MAX];
		sym s;
		LINK next;
	};

typedef LINK grammar[MAXRULES];
typedef LINK Set[MAXNONTERM+1];
typedef int Table[MAXNONTERM][MAXTERM];

typedef struct Node *parseTree;
typedef struct Node
        {   sym s;
       	    tokenInfo t;
            parseTree parent;
            parseTree child;
            parseTree sibling;
        }treeNode;

typedef struct astNode *abstractSyntaxTree;       
 
struct astNode{
	sym s;
	tokenInfo t;
	abstractSyntaxTree parent;
	abstractSyntaxTree child;
	abstractSyntaxTree sibling;
	dtype exp;
	op expOp;
};

typedef struct astNode astNode;
    
#endif
