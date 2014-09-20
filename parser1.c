#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "parser.h"
#include "lexer.h"
#include "stack.h"
#include <string.h>
#define MMALLOC(type,size) (type *) malloc (size*sizeof(type))

//#define MAXNONTERM 50
//#define MAXTERM 56 //added dollar also
//#define MAXRULES 91
//#define MAX 50

char nonTerminals[][30]=
{
"program",
"mainFunction",
"otherFunctions",
"function",
"input_par",
"output_par",
"parameter_list",
"dataType",
"primitiveDatatype",
"constructedDatatype",
"remaining_list",
"stmts",
"typeDefinitions",
"typeDefinition",
"fieldDefinitions",
"fieldDefinition",
"moreFields",
"declarations",
"declaration",
"global_or_not",
"otherStmts",
"stmt",
"assignmentStmt",
"singleOrRecId",
"singleOrRecIDElse" ,
"funCallStmt",
"outputParameters",
"inputParameters",
"iterativeStmt",
"conditionalStmt",
"elsePart",
"ioStmt",
"allVar",
"arithmeticExpression",
"expPrime",
"term",
"termPrime",
"factor",
"highPrecedenceOperators",
"lowPrecedenceOperators",
"all",
"temp",
"booleanExpression",
"var",
"logicalOp",
"relationalOp",
"returnStmt",
"optionalReturn",
"idList",
"more_ids"
};

char Terminals[][30]=
{
	"TK_ASSIGNOP",
	"TK_COMMENT",
	"TK_FIELDID",
	"TK_ID",
	"TK_NUM",
	"TK_RNUM",
	"TK_FUNID",
	"TK_RECORDID",
	"TK_WITH",
	"TK_PARAMETERS",
	"TK_END",
	"TK_WHILE",
	"TK_TYPE",
	"TK_MAIN",
	"TK_GLOBAL",
	"TK_PARAMETER",
	"TK_LIST",
	"TK_SQL",
	"TK_SQR",
	"TK_INPUT",
	"TK_OUTPUT",
	"TK_INT",
	"TK_REAL",
	"TK_SEM",
	"TK_COLON",
	"TK_DOT",
	"TK_ENDWHILE",
	"TK_OP",
	"TK_CL",
	"TK_IF",
	"TK_THEN",
	"TK_ENDIF",
	"TK_READ",
	"TK_WRITE",
	"TK_RETURN",
	"TK_PLUS",
	"TK_MINUS",
	"TK_MUL",
	"TK_DIV",
	"TK_CALL",
	"TK_RECORD",
	"TK_ENDRECORD",
	"TK_ELSE",
	"TK_AND",
	"TK_OR",
	"TK_NOT",
	"TK_COMMA",
	"TK_LT",
	"TK_LE",
	"TK_EQ",
	"TK_GT",
	"TK_GE",
	"TK_NE",
        "$",
        "E"
};

token Search_Term(char word[])
{
    int i,j,k;

    int flag=1;
    for(i=0; i<MAXTERM; i++)
    {
        //if(strcmp(word,Terminals[i])==0)
        /*for(j=0;Terminals[i][j]==word[j];j++)
        {
        	if(Terminals[i][j]=='\0')
        	return i;
        }*/
        //printf("%s\n",word);
       
        //printf("%d %d\n",strlen(Terminals[i]),strlen(word));
        if(strcmp(word,Terminals[i])==0)
            return i;
     }
     return 54;
}

NT Search_NonTerm(char word[])
{
    int i;
    for(i=0; i<MAXNONTERM; i++)
    {
        if(strcmp(word,nonTerminals[i])==0)
            return i;
    }
    return 50;
}

void show_Grammar(Set A)
{
     LINK temp;
     int i;
     for( i=0;i<MAXRULES;i++)
     {
             temp=A[i];
             printf("%s =",temp->name);
             while(temp->next!=NULL)
             {
                        temp=temp->next;
                        printf("  %d",temp->s.terminal);
             }
             printf("\n");

     }
}


void show_Set(Set A)
{
     LINK temp;
     int i;
     for( i=0;i<MAXNONTERM;i++)
     {
             temp=A[i];
             printf("%s =",temp->name);
             while(temp->next!=NULL)
             {
                        temp=temp->next;
                        printf(" %s",temp->name);
             }
             printf("\n");

     }

}

LINK createNode(char *name,int type)
{
     sym s;
     LINK l=(LINK)malloc(sizeof(linknode));
     strcpy(l->name,name);
     
     if(type==0)
     {
                l->s.nonterminal=Search_NonTerm(name);
                //if(l->s.nonterminal==-1)
                //printf("Non Terminal %s \t\t",l->name);
                //printf("Index %d\n",l->s.nonterminal);
                }
     else if(type==1)
     {
             l->s.terminal=Search_Term(l->name);
             //if(l->s.terminal==-1)
             //printf("Terminal %s \t\t",l->name);
             //printf("Index %d\n",l->s.terminal);
             }
     l->s.type=type;
     l->next=NULL;

     return l;
}

void createGrammar(FILE *fp,grammar A)
{
     char buffer[200];
     char *pRule_Tok;
     char delim[]=" ";
     int rule_num=0;
     LINK node=NULL;
     int type,count=0;
     int size =0;

     while(fgets(buffer,200,fp))
    {
         size=strlen(buffer);
         buffer[size-2]=' ';
         size=strlen(buffer);
         //printf("%d\n",size);
         for(pRule_Tok=strtok(buffer,delim);pRule_Tok!=NULL;pRule_Tok=strtok(NULL,delim))
         {
             if(pRule_Tok[0]=='T'|| pRule_Tok[0]=='$' ||pRule_Tok[0]=='E' )
             {
                  type = 1;
                  node->next = createNode(pRule_Tok,type);
                  //printf("Terminal %s\t\t",node->next->name);
                  //printf("\t\tIndex %d\n",node->next->s.terminal);
                  node = node->next;
                  
              }                
              else
              {
                       type = 0;
                      if(count==0)
                      {
                                 node = createNode(pRule_Tok,type);
                                 A[rule_num] = node;
                                 //printf("**NON Terminal %s %d\n",node->name,node->s.nonterminal);

                      }
                      else
                      {
                                 node->next = createNode(pRule_Tok,type);
                                 node = node->next;
                                 //printf("**NON Terminal %s %d\n",node->name,node->s.nonterminal);
                      }

              }
              count++;
         }
          count=0;
          rule_num++;
     }
     //printf("Count rule %d\n",rule_num);
}

void createFirst_Follow(FILE *fp,Set A)
{
    char buffer[200];
    char *Sym_Tok;
    char delim[] = " \n";
    int type,pos;
    LINK node,temp;
    int size=0;
    while(fgets(buffer,200,fp))
    {
     type = 0;
     size=strlen(buffer);
         buffer[size-2]=' ';
         size=strlen(buffer);
     for(Sym_Tok=strtok(buffer,delim);Sym_Tok!=NULL;Sym_Tok=strtok(NULL,delim))
     {
      if(type==0)
          {
                     node = createNode(Sym_Tok,type);
                     pos = Search_NonTerm(Sym_Tok);
                     A[pos] = node;
                     type=1;
                     //printf("NON Terminal %s\n",Sym_Tok);
                     }
          else
          {
                     node->next = createNode(Sym_Tok,type);
                     node = node->next;
                     //printf("Terminal %s\n",Sym_Tok);
                     }
      }
	
     }
     
}

void parseTableInitialize(Table T)
{
     int i,j;
     for(i =0;i<MAXNONTERM;i++)
     {
             for(j = 0;j<MAXTERM;j++)
             T[i][j]=-1;
     }
}

void show_ParseTable(FILE *fp,Table T)
{
     int i,j;
     if(fp==NULL)
     printf("\n*******show_ParseTable*******\n*********Invalid File Pointer********\n");
     
     else
     {
         for(i = 0;i<MAXNONTERM;i++)
         {
                 for(j = 0;j<MAXTERM;j++)
                 {
                           //fprintf(fp,"Rule Number used for Non-Terminal %d and Terminal %d is %d",i+1,j+1,T[i][j]);
                           fprintf(fp,"%d ",T[i][j]);
                 }
         fprintf(fp,"\n");

         }
         
         
     }
}

int checkSet(Set A ,LINK s,sym rule,Table T,int rule_num)
{
    LINK node = A[rule.nonterminal]->next;
   // printf("TT %d\n",node->s.terminal);
   // printf("NT %d\n",node->s.nonterminal);
    int flag = 0;//Nullable Productions
    while(node!=NULL)
    {
    // printf("TT %d \t rule num= %d\n",node->s.terminal,rule_num);
     if(node->s.terminal!=E)
     {
       T[s->s.nonterminal][node->s.terminal]=rule_num;
     }
     else
     {
     	//printf("checkset\n");
       flag=1;
     }
     node=node->next;
    }
    return flag;
}

void createParseTable(grammar G,Table T,Set first_set,Set follow_set)
{
     parseTableInitialize(T);
     
     LINK temp_node,temp_first=NULL,temp_follow=NULL,temp;
     sym temp_sym;
     int has_eps ;
     int i;
     int index;
     int count=0;
     for(i = 0;i<MAXRULES;i++)
     {
	     
	     temp_node = G[i];
	     temp=temp_node;
	     temp_first=first_set[i];
	     temp_sym = temp_node->s;
	     temp_follow=follow_set[temp_sym.nonterminal];
	     if(temp_sym.type!=0)
	     printf("\n!!!!!!ERROR!!!!!!\n First Symbol not Non Terminal\n");
	     count++;
             while(temp_node->next!=NULL)
             {	
             		
             	  has_eps=0;
                  temp_node=temp_node->next;
                  
                  if(temp_node->s.type==1)//Terminal
                      {
                      index=Search_Term(temp_node->name);
                     
                      
                           
                           if(index != 54)
                               {
                                //printf("NT %d T %d\t",temp_sym.nonterminal,temp_node->s.terminal);
                                //printf("## %d\n", i);
                                T[temp_sym.nonterminal][temp_node->s.terminal]=i;
                                break;
                                
                                
                               }
                           else
                               {
                               //printf("xx %d xx %d\t",temp_sym.nonterminal,temp_node->s.terminal);
                               //printf("@@ %d\n", i);
                               	while(temp_follow->next!=NULL)
                               	{
                               		temp_follow=temp_follow->next;
                              		T[temp_sym.nonterminal][temp_follow->s.terminal]=i;
                               	        
                              	}
                               }break;
	      		}
	      	   if(temp_node->s.type==0)//Non-Terminal
                      {
                            //printf("## %d\n",temp_node->s.nonterminal);
                            //printf("@@ %d\n",temp->s.nonterminal);
                            has_eps=checkSet(first_set,temp,temp_node->s,T,i);
                            //printf("panty %d has eps %d \n",temp_node->s.nonterminal,has_eps);
                            if(has_eps==0)
                            	break;
                             //printf("pantyshah %d has eps %d \n",temp_node->next->s.nonterminal,has_eps);
                            if(temp_node->next->s.nonterminal==50 && has_eps==1){
                            	//printf("hfd\n");
                            	while(temp_follow->next!=NULL)
                               	{
                               		temp_follow=temp_follow->next;
                              		T[temp_sym.nonterminal][temp_follow->s.terminal]=i;
                               	        
                              	}
                               break;
                            }
                          }

             }
             //T[20][54]=21;

             
     }

}



parseTree createpNode()
{
          parseTree temp = (parseTree)malloc(sizeof(struct Node));
          if(temp==NULL)
          {
                        printf("\n*****Error*****\n*****Insufficient Memory*****\n");
                        exit(0);
                        }
          temp->s.type=-1;
          //temp->s.terminal=NUL;
          //temp->s.nonterminal;
          temp->sibling=NULL;
          temp->child=NULL;
          temp->parent=NULL;

          return temp;
}

parseTree  parseInputSourceCode(Table T,grammar G)
{
           //FILE *fp = fopen("Grammar.txt","r");
           //FILE *fp1 = fopen(testcaseFile,"r");

           //grammar G;
           //Table T;
           //createGrammar(fp,G);
           //createParseTable(G,T);

           //fclose(fp);

               sym a,b;
               //Bottom of Stack contains $ symbol
               a.type=1;
               a.terminal=$;
               //Start symbol of Source Code
               b.type=0;
               b.nonterminal=program;

           //Populating Stack with $ and <program> symbols
           Stack st=createStack();
           st=push(st,a);
           st=push(st,b);

           Stack st_tmp=createStack();//Temporary Stack

           parseTree pNode = createpNode();
           pNode->s.type=0;
           pNode->s.nonterminal=program;
           parseTree temp_node=NULL,sib_node=NULL;

           //get 1st token

           int rule_num;
           sym tmp;
           tokenInfo temp_token;
           temp_token=getNextToken();
           //printf(" hi %d\n",temp_token.type);
		   printf("\n******************\nParsing the Input Source Code\n********************\n");
           while(!isEmptyStack(st))
           {
                tmp=getTop(st);
                //printf("## %d\n",tmp.nonterminal);
                //printf("@@ %d\n",tmp.terminal);
                printf("MAIN while ---- type= %d  token= %d  nonterminal= %d  \n",tmp.type,tmp.terminal,tmp.nonterminal);
                st=pop(st);
                if(tmp.type==1)
                {
                       //printf("Terminal Symbol\n");
                       if(tmp.terminal!=temp_token.type)
                       {
                        //Error call lexical error analyser
                        printf("Error Details:The following token %s for lexeme %s is incorrect");
                        exit(0);
                       }
                       
                       
                       //printf("** %d ** %d\n",tmp.terminal,temp_token.type);
                       if(tmp.terminal!=$)
                       {
                        pNode->t = temp_token;
                        printf("** %d ** %d LINE %d\n",pNode->t.type,temp_token.type,temp_token.line_num);

                        while(pNode->sibling==NULL){
                        	printf("hi\n");
                        	
                        	pNode=pNode->parent;
                        }
						printf("hi234\n");
                        pNode=pNode->sibling;
                        temp_token=getNextToken();
                        printf(" hi 567567 %d\n",temp_token.type);
                       }
                }
                else
                if(tmp.type==0)
                {
                       //printf("Non Terminal Symbol");
                       printf("xxxx %d  %d LINE %d\t",tmp.nonterminal,temp_token.type,temp_token.line_num);
                       rule_num=T[tmp.nonterminal][temp_token.type];
                       printf("rule: %d\n",rule_num);
                       
                       
                       if(rule_num==-1)
                       {
                        //Again use the same lexical error checker
                        //Error Handling Print all allowed tokens
                        printf("\nError Details:Invalid Token for the respective grammar rule used\n");
                        printf("\nThe Token encountered is %s\nDoes Not match at Line num%d\n,",Terminals[temp_token.type],temp_token.line_num);
                        printf("\nExpected Tokens are as follows\n");

                        exit(0);
                       }
                       
                       
                       if(G[rule_num]->s.nonterminal!=tmp.nonterminal)
                       {
                            if(tmp.type==0)
                            printf("\nProduction Rule Missing\n");
                            exit(0);
                       }
                       
                       
                       printf("^^^%d \n",G[rule_num]->s.nonterminal);
                       LINK rule_ptr = G[rule_num];
                       rule_ptr=rule_ptr->next;
                       int sym_term;
                       if(rule_ptr->s.type==0)
                       sym_term=rule_ptr->s.nonterminal;
                       else
                       sym_term=rule_ptr->s.terminal;
                       
                       printf("----NT %d\t TT %d ----",rule_ptr->s.nonterminal,rule_ptr->s.terminal);

                       if(sym_term==E)
                       {
                            //continue;
                            temp_node=createpNode();
                            pNode->child=temp_node;
                            temp_node->s=rule_ptr->s;
                            temp_node->parent=pNode;
                            temp_node->sibling=NULL;
                            temp_node->child=NULL;
                            
                            
                            /*while(pNode==NULL)
                            {
                            if(pNode->sibling!=NULL)
                            	pNode=pNode->sibling;
                            else
                            if(pNode->sibling==NULL&& pNode->parent!=NULL)
                            pNode=pNode->parent;
                            }*/
		            Label1: if(pNode->sibling==NULL)
		                    {pNode=pNode->parent;
		                    goto Label1;}
		                    else
		                    pNode=pNode->sibling;
                            /*else
                            pNode=pNode->parent;
                            while(pNode->sibling==NULL && pNode->parent->sibling!=NULL)
                            {
                             pNode=pNode->parent;
                            }
                           // if(pNode->parent!=NULL)
                           //  pNode=pNode->sibling;*/
                       }
                       else
                       {
                           temp_node=createpNode();
                           pNode->child=temp_node;
                           temp_node->s=rule_ptr->s;
                           temp_node->parent=pNode;
                           st_tmp=push(st_tmp,rule_ptr->s);
                           rule_ptr=rule_ptr->next;
                           while(rule_ptr!=NULL)
                           {
		                   if(rule_ptr->s.nonterminal==50)
		                   {
		                   rule_ptr=rule_ptr->next;
		                   continue;
		                   }
		                   
		                   sib_node=pNode->child;
		                   temp_node=createpNode();
		                   temp_node->s=rule_ptr->s;
		                   temp_node->parent=pNode;
		                   
		                   sib_node->sibling=temp_node;
		                   sib_node=sib_node->sibling;
		                   
		                   st_tmp=push(st_tmp,rule_ptr->s);
		                   
		                   printf("+++ %d %d %d **** \n",sib_node->s.type,sib_node->s.terminal,sib_node->s.nonterminal);
		                   rule_ptr=rule_ptr->next;
		                   
		                   
                           }
                           
                       }
                       while(!isEmptyStack(st_tmp))
                       {
                        st=push(st,getTop(st_tmp));
                        st_tmp=pop(st_tmp);
                       }
                       pNode=pNode->child;
                }
           }
           //fclose(fp);
           //fclose(fp1);
           return pNode;
}
/*int main()
{
    FILE *fin=fopen("input.txt","r");
    FILE *fout=fopen("output.txt","w");
    if(fin==NULL){
        fprintf(fout,"error opening the file\n");
        return 0;
    }
    char ch;
    //tokenInfo *info;
    //info=(tokenInfo*)malloc(40*sizeof(tokenInfo));
    int i=0;
    tokenInfo *head,*save;
    head=NULL;
    save=NULL;
    head=(tokenInfo*)malloc(sizeof(tokenInfo));
    save=head;
    head->link=NULL;
    int coun=getTokenList(fin,fout,save);

    fclose(fin);
    // FILE * fp1=fopen("token.txt","w");
    save=head->link;
    while(save!=NULL)
    {
        //fprint(fp1,"%d\n",save->)
        fprintf(fout,"%s\t",save->lexeme);
        fprintf(fout,"%d\t",save->type);
        fprintf(fout,"%d\n",save->line_num);
        save=save->link;
    }
    fclose(fout);
    tokenInfo gj;
    char *testcaseFile="input.txt";
ptr=head->link;
Table T;
//gj=getNextToken();
parseTree abc=parseInputSourceCode(testcaseFile,T);

	FILE *f,*f1,*f2,*f3;
	Table T;
	Set first,follow;
	grammar G;	
	
	
	f=fopen("Grammar.txt","r");
	f1=fopen("FirstSets.txt","r");
	f2=fopen("FollowSets1.txt","r");
	f3=fopen("PT.txt","w");
	
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
	createParseTable(G,T,first,follow);
	//int i=Search_Term("E");
	printf("\nSuccess\n\n");
	//printf("%d",i);
	//show_ParseTable(f3,T);	
	parseTree  parseInputSourceCode(char *testcaseFile,T,G)	
	fclose(f);
	fclose(f1);
	fclose(f2);
	fclose(f3);
	
	return(0);
}*/
/*void printParseTree(parseTree  PT, char *outfile)
{
    parseTree pNode;
    //int k = 0;
    FILE *fp = fopen(outfile,"w");
    if(fp==NULL)
    {
        printf("Error: Unable to open to Output File");
        exit(0);
    }
    pNode=PT;
    fprintf(fp,"lexemeCurrentNode     lineno   token   valueIfNumber   parentNodeSymbol   isLeafNode(yes/no)    NodeSymbol");

}
/*
void createAbstractSyntaxtree(parseTree T, abstractSyntaxTree A)
{}

void printAST(abstractSyntaxTree A, char *outFile, int *totalAllocatedMemory)
{}
*/
