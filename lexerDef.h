#ifndef LEXERDEF_H_INCLUDED
#define LEXERDEF_H_INCLUDED





typedef enum
{
	TK_ASSIGNOP=0,
	TK_COMMENT,
	TK_FIELDID,
	TK_ID,
	TK_NUM,
	TK_RNUM,
	TK_FUNID,
	TK_RECORDID,
	TK_WITH,
	TK_PARAMETERS,
	TK_END,
	TK_WHILE,
	TK_TYPE,
	TK_MAIN,
	TK_GLOBAL,
	TK_PARAMETER,
	TK_LIST,
	TK_SQL,
	TK_SQR,
	TK_INPUT,
	TK_OUTPUT,
	TK_INT,
	TK_REAL,
	TK_SEM,
	TK_COLON,
	TK_DOT,
	TK_ENDWHILE,
	TK_OP,
	TK_CL,
	TK_IF,
	TK_THEN,
	TK_ENDIF,
	TK_READ,
	TK_WRITE,
	TK_RETURN,
	TK_PLUS,
	TK_MINUS,
	TK_MUL,
	TK_DIV,
	TK_CALL,
	TK_RECORD,
	TK_ENDRECORD,
	TK_ELSE,
	TK_AND,
	TK_OR,
	TK_NOT,
	TK_COMMA,
	TK_LT,
	TK_LE,
	TK_EQ,
	TK_GT,
	TK_GE,
	TK_NE,
        $,
        E
}token;


struct node{
    token type;
    char *lexeme;
    int line_num;
    float r_num;
    int num;
    struct node *link;
};
typedef struct node tokenInfo;

typedef char *buffer;

typedef int buffersize;
tokenInfo *ptr;
tokenInfo *ptr2;
tokenInfo *ptr3;

/*struct token_node{
    tokenInfo t_info;
    struct token_list *next;
};

typedef struct token_node token_node;
*/

#endif // LEXERDEF_H_INCLUDED
