#include<stdio.h>
#include<stdlib.h>
#include"lexer.h"
#include"lexer.h"
#include"parser.h"
int main(int argc,char *argv[])
{
    FILE *fin=fopen(argv[1],"r");
    //FILE *fout=fopen(argv[2],"w");
    FILE *fout1=fopen("lexerOut.txt","w");
    //FILE *fout2=fopen(argv[2],"w");
    if(fin==NULL)
    {
        printf("error opening the file\n");
        return 0;
    }
    FILE *f,*f1,*f2,*f3,*f4;
    char ch;
    int i=0;
    tokenInfo *head,*save;
    head=NULL;
    save=NULL;
    head=(tokenInfo*)malloc(sizeof(tokenInfo));
    save=head;
    head->link=NULL;
    int coun=getTokenList(fin,save);
	fclose(fin);
    save=head->link;
    int choice;
    printf("Please enter your choice\n");
    scanf("%d",&choice);
    if(choice==1)
    {
    	fprintf(fout1,"Lexeme   Token_Type(ENUM)    Line_NO\n");
    	while(save!=NULL)
    	{
        	fprintf(fout1,"%s	\t",save->lexeme);
        	fprintf(fout1,"%d	\t",save->type);
        	fprintf(fout1,"%d\n",save->line_num);
        	save=save->link;
    	}
    	printf("tokenizing done\n");
    }
    parseTree pnode;
    printf("Please enter your choice\n");
    scanf("%d",&choice);
    if(choice==2)
    {
    tokenInfo gj;
    ptr=head->link;
    ptr2=head->link;
    ptr3=head->link;
	Table T;
	Set first,follow;
	grammar G;
	f=fopen("Grammar.txt","r");
	f1=fopen("FirstSets.txt","r");
	f2=fopen("FollowSets.txt","r");
	f3=fopen("PT.txt","w");
	//f4=fopen("printParseTree.txt","w");

	//printf("\nFirst\n");

	createFirst_Follow(f2,follow);
	createFirst_Follow(f1,first);

	//show_Set(first);
	//printf("\n\n\n\nFollow\n");
	//show_Set(follow);
	//printf("\n\n\n\nGrammar\n");
	createGrammar(f,G);

	//printf("\nSuccess----FOLLOW\n\n");
	//show_Grammar(G);
	parseTableInitialize(T);

	//printf("\nSuccess\n\n");
	//show_ParseTable(f3,T);
	//printf("\nSuccess\n\n");
	//fclose(f3);
	//f3=fopen("PT.txt","w");
	createParseTable(G,T,first,follow);

	//int i=Search_Term("E");

	//printf("%d",i);
	show_ParseTable(f3,T);
	
	pnode=parseInputSourceCode(T,G);
	
	//checking printParseTree//
	printParseTree(pnode,argv[2]);
	fclose(f);
	fclose(f1);
	fclose(f2);
	fclose(f3);
	printf("parsed successfully\n");
	}
	
	abstractSyntaxTree anode;
	
	printf("Please enter your choice\n");
    scanf("%d",&choice);
	if(choice==3)
	{
	f4=fopen("ast.txt","r");
	
	grammar A;
	createGrammar(f4,A);
	//show_Grammar(A);
	
	printf("creating AST\n");
	anode=createAbstractSyntaxtree(pnode,anode,A);
	
	//("pulling up trivially\n");
	pullup(anode);
	//printf("pulled up trivially\n");
	
	//printf("pulling up complex\n");
	pullupComplex(anode);
	//printf("pulled up complex\n");
	
	printf("created AST\n");
	
	printf("printing AST\n");
	printAST(anode, argv[3]);
	printf("printed AST\n");
	fclose(f4);
	}
	
	printf("Please enter your choice\n");
    scanf("%d",&choice);
	if(choice==4)
	{
		FILE *f5=fopen("symbolTableOut.txt","w");
		printf("initializing symbol tables\n");
		SymbolTable_Initialize();
		global_SymbolTable_Initialize();
		rec_SymbolTable_Initialize();
		printf("intialization done\n");
		printf("creating symbol table\n");
		fillSymbolTable(anode);		
		printf("created symbol tablle\n");
		SymbolTable_print(f5);
		fclose(f5);
	}
	
	printf("Please enter your choice\n");
    scanf("%d",&choice);
	if(choice==5)
	{
		printf("begin typechecking\n");
		typeChecker(anode);
		showType(anode);
		printf("typechecking done\n");
	}
	
	printf("Please enter your choice\n");
    scanf("%d",&choice);
	if(choice==6)
	{
		printf("begin semantic analysis\n");
		semanticAnalyzer(anode);
		printf("semantic analysis done\n");
	}	
	fclose(fout1);
	//fclose(fout2);
	
    return 0;
}
