#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "parser.h"
#include "lexer.h"
#include "stack.h"
#include <string.h>
#define MMALLOC(type,size) (type *) malloc (size*sizeof(type))

rule_stack rStack;

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
     }
     else if(type==1)
     {
     	l->s.terminal=Search_Term(l->name);
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
         for(pRule_Tok=strtok(buffer,delim);pRule_Tok!=NULL;pRule_Tok=strtok(NULL,delim))
         {
             if(pRule_Tok[0]=='/'){
             	break;
             }
             
             if(pRule_Tok[0]=='T'|| pRule_Tok[0]=='$' ||pRule_Tok[0]=='E' )
             {
                  type = 1;
                  node->next = createNode(pRule_Tok,type);
                  node = node->next;
                  
              }                
              else
              {
                       type = 0;
                      if(count==0)
                      {
                                 node = createNode(pRule_Tok,type);
                                 A[rule_num] = node;
                      }
                      else
                      {
                                 node->next = createNode(pRule_Tok,type);
                                 node = node->next;
                      }

              }
              count++;
         }
          count=0;
          rule_num++;
     }
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
                     }
          else
          {
                     node->next = createNode(Sym_Tok,type);
                     node = node->next;
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
                           
                           fprintf(fp,"%d ",T[i][j]);
                 }
         fprintf(fp,"\n");

         }
         
         
     }
}

int checkSet(Set A ,LINK s,sym rule,Table T,int rule_num)
{
    LINK node = A[rule.nonterminal]->next;
    int flag = 0;//Nullable Productions
    while(node!=NULL)
    {
     if(node->s.terminal!=E)
     {
       T[s->s.nonterminal][node->s.terminal]=rule_num;
     }
     else
     {
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
                                T[temp_sym.nonterminal][temp_node->s.terminal]=i;
                                break;
                                
                                
                               }
                           else
                               {
                               	while(temp_follow->next!=NULL)
                               	{
                               		temp_follow=temp_follow->next;
                              		T[temp_sym.nonterminal][temp_follow->s.terminal]=i;
                               	        
                              	}
                               }break;
	      		}
	      	   if(temp_node->s.type==0)//Non-Terminal
                      {
                            has_eps=checkSet(first_set,temp,temp_node->s,T,i);
                            if(has_eps==0)
                            	break;
                             
                            if(temp_node->next->s.nonterminal==50 && has_eps==1){
                            	
                            	while(temp_follow->next!=NULL)
                               	{
                               		temp_follow=temp_follow->next;
                              		T[temp_sym.nonterminal][temp_follow->s.terminal]=i;
                               	        
                              	}
                               break;
                            }
                          }

             }

             
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
          temp->sibling=NULL;
          temp->child=NULL;
          temp->parent=NULL;

          return temp;
}

parseTree  parseInputSourceCode(Table T,grammar G)
{
           //put this in parsetree code
		   rStack=createRuleStack();
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
           
           //the program node
           parseTree pNode = createpNode();
           pNode->s.type=0;
           pNode->s.nonterminal=program;
           parseTree pNode_stored=pNode;
           
           //the root node
           parseTree rootNode = createpNode();
           rootNode->s.type=0;
           rootNode->s.terminal=-1;
           rootNode->s.nonterminal=-1;
           rootNode->t.lexeme="ROOT";
           rootNode->t.line_num=0;
           rootNode->child=pNode;
           pNode->parent=rootNode;
           rootNode->sibling=NULL;
            
           parseTree temp_node;

           //get 1st token

           int rule_num;
           sym tmp;
           tokenInfo temp_token;
           temp_token=getNextToken();
           
		   printf("\n******************\nParsing the Input Source Code\n********************\n");
           while(!isEmptyStack(st))
           {
               // printf("tokenxxx=%d\n",temp_token.type);	
                tmp=getTop(st);
                st=pop(st);
          
                if(tmp.type==1)
                {
               		if(tmp.terminal!=$)
                    {
						if(tmp.terminal==E)
						{
							continue;
						}
						else
						{
							pNode->t = temp_token;//put tokeninfo in the node
							//printf("\n&&& %s &&&\n",pNode->t.lexeme);
				
							  if(pNode->sibling!=NULL)
							   {
							   	pNode=pNode->sibling;
							   }
							  else
							   {
									//printf("hhhhhhhhhhhhhhhhhhhhhh\n");  
								    while(pNode->sibling==NULL ){
								    	if(pNode->s.terminal==-1 && pNode->s.nonterminal==-1){
								    		return pNode_stored;
								    	}
								    	//printf("see this NT=%d T=%d line=%d\n",pNode->s.nonterminal,pNode->s.terminal,pNode->t.line_num);
								    	pNode=pNode->parent;
								    }
								    pNode=pNode->sibling;
								    //printf("see this too NT=%d T=%d\n",pNode->s.nonterminal,pNode->s.terminal);
							   }
								temp_token=getNextToken();
				
						}
                    }
                    else
                    {
                    	break;
                    }
                
				}
                else if(tmp.type==0)
                {
                       rule_num=T[tmp.nonterminal][temp_token.type];
                      // printf("rule: %d\n",rule_num);
                       
                       if(rule_num==-1)
                       {
                        //Again use the same lexical error checker
                        //Error Handling Print all allowed tokens
                        //printf("\nError Details:Invalid Token for the respective grammar rule used\n");
						//printf("\nThe Token encountered is %s\nDoes Not match at Line num%d\n,",Terminals[temp_token.type],temp_token.line_num);
                        	printf("\nExpected Tokens are as follows\n");
                        	printf("xxxxxxxxxx parsing error xxxxxxx\n");
                        	exit(0);
                       }
                       
					   rStack=pushRule(rStack,rule_num);
                       
                       if(G[rule_num]->s.nonterminal!=tmp.nonterminal)
                       {
                            if(tmp.type==0)
                            printf("\nProduction Rule Missing\n");
                            exit(0);
                       }
                       
                       
                       LINK rule_ptr = G[rule_num];
                       int sym_term;
                       rule_ptr=rule_ptr->next;//rule_ptr points to first one on rhs of rule
		   
					   if(rule_ptr->s.terminal == E)
					   {
					   	   temp_node=createpNode();
						   temp_node->s=rule_ptr->s;
						   temp_node->parent=pNode;
						   pNode->child=temp_node;
						   st_tmp=push(st_tmp,rule_ptr->s);//push it in temp stack
						   			   			   
						   if(pNode->sibling!=NULL)
						   {
						   		pNode=pNode->sibling;
						   }
						   else
						   {
							   //printf("hfhfhfhfh\n");  
							    while(pNode->sibling==NULL){
							    	if(pNode->s.terminal==-1 && pNode->s.nonterminal==-1){
								    		return pNode_stored;
								    	}
							    	pNode=pNode->parent;
							    }
							    pNode=pNode->sibling;
							    //printf("T=%d NT=%d\n",pNode->s.terminal,pNode->s.nonterminal);
							  // pNode=pNode->parent;
						   }
					   }
					   else
					   {
					   	   //put the first one on rhs in tree
						   temp_node=createpNode();
						   temp_node->s=rule_ptr->s;
						   temp_node->parent=pNode;
						   pNode->child=temp_node;
						   st_tmp=push(st_tmp,rule_ptr->s);//push it in temp stack
						 //  printf("#### nt=%d t=%d\t",rule_ptr->s.nonterminal,rule_ptr->s.terminal);		   			   
						   rule_ptr=rule_ptr->next;//rule_ptr points to second one on the rhs of rule
						   
						   //connect the siblings
						   parseTree curr_node=pNode->child; //now curr_node is the child
						  
						   while(rule_ptr!=NULL && rule_ptr->s.nonterminal!=50)
						   {
							  // printf("#### nt=%d t=%d\t",rule_ptr->s.nonterminal,rule_ptr->s.terminal);
							   temp_node=createpNode();
							   temp_node->s=rule_ptr->s;
							  
							   temp_node->parent=pNode;
							   curr_node->sibling=temp_node;
							   st_tmp=push(st_tmp,rule_ptr->s);  //push all the things on the rhs of rule into temp stack
							   rule_ptr=rule_ptr->next;
							   curr_node=curr_node->sibling;
										   
						   }
									   
						   //now push everything in the real stack to get correct order
						   while(!isEmptyStack(st_tmp))
						   {
					       		st=push(st,getTop(st_tmp));
					       		st_tmp=pop(st_tmp);
						   }
						  pNode=pNode->child;
					  }
		  
           }
           
		   
   }
           
           return pNode_stored;
}

void printFunc(parseTree PT,FILE *fout)
{
	//printf("print called\n");
	parseTree temp=PT;
	if(temp->s.type==1){
	//printf("at a terminal\n");
	if(temp->s.terminal!=E){
		//printf("terminal not eps\n");
		//fprintf(fout,"T=%d\tlexeme=%s\tline=%d\t\n",temp->s.terminal,temp->t.lexeme,temp->t.line_num);
		char *val;
		if(temp->s.terminal==4 || temp->s.terminal==5){
			val=temp->t.lexeme;
		}
		else{
			val="-------------";
		}
		fprintf(fout,"%s\t\t\t    %d    \t%d\t\t %s   \t     %d\t\t\t     yes   \t\t     ----------\n",temp->t.lexeme,temp->t.line_num,temp->s.terminal,val,temp->parent->s.nonterminal);
	}
	else if(temp->s.terminal==E){
			//printf("terminal is eps\n");
			char *val;
			temp->t.lexeme="eps";
			temp->t.line_num=-1;
			val="-------------";
			fprintf(fout,"%s\t\t\t        %d    \t%d\t\t %s   \t     %d\t\t\t     yes   \t\t     ----------\n",temp->t.lexeme,temp->t.line_num,temp->s.terminal,val,temp->parent->s.nonterminal);
		}
	}
	if(temp->child!=NULL)
	{
		//printf("go to child\n");
		fprintf(fout,"-----------------\t------\t-----\t-------------\t         %d        \t      no       \t        %d     \n",temp->parent->s.nonterminal, temp->s.nonterminal);
		printFunc(temp->child,fout);
	}
	if(temp->sibling!=NULL)
	{
		//printf("go to sib\n");
		//printf("NT=%d T=%d\tsibling is not null\n",temp->s.nonterminal,temp->s.terminal);
		printFunc(temp->sibling,fout);
	}
	if( temp->sibling==NULL)
	{
		//printf("go back\n");
		return;
		//fprintf(fout,"T=%d\tlexeme=%s\tline=%d\t\n",temp->s.terminal,temp->t.lexeme,temp->t.line_num);
		//printf("NT=%d T=%d\tchild and sibling are null\n",temp->s.nonterminal,temp->s.terminal);
	}
	return;
}

void printParseTree(parseTree PT, char *outfile){
	FILE *fp=fopen(outfile,"w");
	fprintf(fp,"lexemeCurrentNode\tlineno\ttoken\tvalueIfNumber\tparentNodeSymbol\tisLeafNode(yes/no)\tNodeSymbol\n");
	printFunc(PT,fp);
	fclose(fp);
}

abstractSyntaxTree createAstNode()
{
	  abstractSyntaxTree temp = (abstractSyntaxTree)malloc(sizeof(struct astNode));
	  if(temp==NULL)
	  {
		            printf("\n*****Error*****\n*****Insufficient Memory*****\n");
		            exit(0);
		            }
	  temp->s.type=-1;
	  temp->sibling=NULL;
	  temp->child=NULL;
	  temp->parent=NULL;

	  return temp;
}

abstractSyntaxTree createAbstractSyntaxtree(parseTree T, abstractSyntaxTree A, grammar G) 
{
		   printf("********* creating the AST **********\n");
		   
		   rule_stack temp_stack=createRuleStack();
		   while(!isEmptyRuleStack(rStack)){
				temp_stack=pushRule(temp_stack,getTopRule(rStack));
				rStack=popRule(rStack);
			}
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
           
           //the program node
           abstractSyntaxTree aNode = createAstNode();
           aNode->s.type=0;
           aNode->s.nonterminal=program;
           abstractSyntaxTree aNode_stored=aNode;
           
           //the root node
           abstractSyntaxTree rootNode = createAstNode();
           rootNode->s.type=0;
           rootNode->s.terminal=-1;
           rootNode->s.nonterminal=-1;
           rootNode->t.lexeme="ROOT";
           rootNode->t.line_num=0;
           rootNode->child=aNode;
           aNode->parent=rootNode;
           rootNode->sibling=NULL;
            
           abstractSyntaxTree temp_node;

           //get 1st token

           int rule_num;
           sym tmp;
           tokenInfo temp_token;
           temp_token=getNext();
           //printf("tokenxxx=%d\n",temp_token.type);	
           while(temp_token.type==TK_SEM || temp_token.type==TK_CL || temp_token.type==TK_OP || temp_token.type==TK_SQR || temp_token.type==TK_SQL || temp_token.type==TK_COLON || temp_token.type==TK_COMMA || temp_token.type==TK_END || temp_token.type==TK_ENDWHILE || temp_token.type==TK_ENDRECORD || temp_token.type==TK_ENDIF){
           		temp_token=getNext();
           		if(temp_token.type==$){
           			return aNode_stored;
           		}
           }
           
         	//printf("token1=%d\n",temp_token.type);	
         	
           while(!isEmptyStack(st))
           {
               // printf("token=%d\n",temp_token.type);
                tmp=getTop(st);
                st=pop(st);
          
                if(tmp.type==1)
                {
               		if(tmp.terminal!=$)
                    {
						if(tmp.terminal==E)
						{
							continue;
						}
						else
						{
							aNode->t = temp_token;//put tokeninfo in the node
							//printf("\n&&& %s &&&\n",aNode->t.lexeme);
							if(temp_token.type==TK_NUM || temp_token.type==TK_RNUM || temp_token.type==TK_INT ||temp_token.type==TK_RECORD || temp_token.type==TK_REAL)	{
								if(temp_token.type==TK_NUM || temp_token.type==TK_INT){aNode->exp=integer;aNode->expOp=noop;}
								else if(temp_token.type==TK_RNUM ||temp_token.type==TK_REAL){aNode->exp=real;aNode->expOp=noop;}
								else if(temp_token.type==TK_RECORD){aNode->exp=record;aNode->expOp=noop;}
							}
							else if(temp_token.type==TK_PLUS || temp_token.type==TK_MINUS || temp_token.type==TK_MUL ||temp_token.type==TK_DIV || temp_token.type==TK_EQ || temp_token.type==TK_NE)	{
								aNode->expOp=arithmetic;aNode->exp=notype;	
							}
							else if(temp_token.type==TK_OR || temp_token.type==TK_AND)	{
								aNode->expOp=logical;aNode->exp=notype;
							}
							else if(temp_token.type==TK_GT || temp_token.type==TK_LT || temp_token.type==TK_GE ||temp_token.type==TK_LE)	{
								aNode->expOp=relational;aNode->exp=notype;	
							}
							else{
								aNode->exp=notype;
								aNode->expOp=noop;
							}
							  if(aNode->sibling!=NULL)
							   {
							   	aNode=aNode->sibling;
							   }
							  else
							   {
									//printf("hhhhhhhhhhhhhhhhhhhhhh\n");  
								    while(aNode->sibling==NULL ){
								    	if(aNode->s.terminal==-1 && aNode->s.nonterminal==-1){
								    		return aNode_stored;
								    	}
								    	//printf("see this NT=%d T=%d line=%d\n",aNode->s.nonterminal,aNode->s.terminal,aNode->t.line_num);
								    	aNode=aNode->parent;
								    }
								    aNode=aNode->sibling;
								    //printf("see this too NT=%d T=%d\n",aNode->s.nonterminal,aNode->s.terminal);
							   }
								temp_token=getNext();
								while(temp_token.type==TK_SEM || temp_token.type==TK_CL || temp_token.type==TK_OP || temp_token.type==TK_SQR || temp_token.type==TK_SQL || temp_token.type==TK_COLON || temp_token.type==TK_COMMA || temp_token.type==TK_END || temp_token.type==TK_ENDRECORD || temp_token.type==TK_ENDIF || temp_token.type==TK_ENDWHILE){
           		temp_token=getNext();
           		//printf("token=%s %d\n",temp_token.lexeme,temp_token.line_num);
           		if(temp_token.type==$ ){
           			//printf("$\n");
           			return aNode_stored;
           			
           		}
           		//printf("token=%s %d\n",temp_token.lexeme,temp_token.line_num);
           }
          // printf("tokenxxx=%s \n",temp_token.lexeme);
				
						}
                    }
                    else
                    {
                    	break;
                    }
                
				}
                else if(tmp.type==0)
                {
                       //rule_num=T[tmp.nonterminal][temp_token.type];
                       rule_num=getTopRule(temp_stack);
                       temp_stack=popRule(temp_stack);
                      // printf("Ast rule: %d\n",rule_num);
                       
                       
                       if(rule_num==-1)
                       {
                        //Again use the same lexical error checker
                        //Error Handling Print all allowed tokens
                        //printf("\nError Details:Invalid Token for the respective grammar rule used\n");
						//printf("\nThe Token encountered is %s\nDoes Not match at Line num%d\n,",Terminals[temp_token.type],temp_token.line_num);
                        	printf("\nExpected Tokens are as follows\n");
                        	exit(0);
                       }
                       
                       
                       if(G[rule_num]->s.nonterminal!=tmp.nonterminal)
                       {
                            if(tmp.type==0)
                            printf("\nProduction Rule Missing\n");
                            exit(0);
                       }
                       
                       
                       LINK rule_ptr = G[rule_num];
                       int sym_term;
                       rule_ptr=rule_ptr->next;//rule_ptr points to first one on rhs of rule
		   
					   if(rule_ptr->s.terminal == E)
					   {
					   	   temp_node=createAstNode();
						   temp_node->s=rule_ptr->s;
						   temp_node->parent=aNode;
						   aNode->child=temp_node;
						   //aNode->exp=notype;
						   st_tmp=push(st_tmp,rule_ptr->s);//push it in temp stack
						   			   			   
						   if(aNode->sibling!=NULL)
						   {
						   		aNode=aNode->sibling;
						   }
						   else
						   {
							   //printf("hfhfhfhfh\n");  
							    while(aNode->sibling==NULL){
							    	if(aNode->s.terminal==-1 && aNode->s.nonterminal==-1){
								    		return aNode_stored;
								    	}
							    	aNode=aNode->parent;
							    }
							    aNode=aNode->sibling;
							    //printf("T=%d NT=%d\n",aNode->s.terminal,aNode->s.nonterminal);
							  // aNode=aNode->parent;
						   }
					   }
					   else
					   {
					   	   //put the first one on rhs in tree
						   temp_node=createAstNode();
						   temp_node->s=rule_ptr->s;
						   temp_node->parent=aNode;
						   aNode->child=temp_node;
						   aNode->exp=notype;
						   aNode->expOp=noop;
						   st_tmp=push(st_tmp,rule_ptr->s);//push it in temp stack
						 //  printf("#### nt=%d t=%d\t",rule_ptr->s.nonterminal,rule_ptr->s.terminal);		   			   
						   rule_ptr=rule_ptr->next;//rule_ptr points to second one on the rhs of rule
						   
						   //connect the siblings
						   abstractSyntaxTree curr_node=aNode->child; //now curr_node is the child
						  
						   while(rule_ptr!=NULL && rule_ptr->s.nonterminal!=50)
						   {
							  // printf("#### nt=%d t=%d\t",rule_ptr->s.nonterminal,rule_ptr->s.terminal);
							   temp_node=createAstNode();
							   temp_node->s=rule_ptr->s;
							  
							   temp_node->parent=aNode;
							   curr_node->sibling=temp_node;
							   st_tmp=push(st_tmp,rule_ptr->s);  //push all the things on the rhs of rule into temp stack
							   rule_ptr=rule_ptr->next;
							   curr_node=curr_node->sibling;
										   
						   }
									   
						   //now push everything in the real stack to get correct order
						   while(!isEmptyStack(st_tmp))
						   {
					       		st=push(st,getTop(st_tmp));
					       		st_tmp=pop(st_tmp);
						   }
						  aNode=aNode->child;
					  }
		  
           }
           
		   
   }
           
           return aNode_stored;
           
}

void pullup(abstractSyntaxTree ast){
	abstractSyntaxTree parent=ast;
	//printf("xxxxx NT=%d xxxx T=%d XXXX\n",parent->s.nonterminal,parent->s.terminal);
	if(parent->child!=NULL){
		//printf("if 1\n");
		if(parent->child->s.terminal==E){
			parent->s=parent->child->s;
			parent->t=parent->child->t;
			parent->exp=notype;
			parent->expOp=noop;
			free(parent->child);
			parent->child=NULL;
		}
		else if(parent->child->s.type==1 && parent->child->s.terminal!=54){
			abstractSyntaxTree temp=NULL;
			temp=parent->child;
			parent->t=temp->t;
			parent->s=temp->s;
			parent->exp=temp->exp;
			parent->expOp=temp->expOp;
			parent->child=NULL;
			//if(temp->sibling!=NULL){
				parent->child=temp->sibling;
			//}
			//else{
				//parent->child=NULL;
			//}
			//free(temp);
		}
	}
	if(parent->child!=NULL){
		//printf("if 2\n");
		pullup(parent->child);
	}
	if(parent->sibling!=NULL){
		//printf("if 3\n");
		pullup(parent->sibling);
	}
	if(parent->sibling==NULL){
		//printf("if 4\n");
		return;
	}
}

void pullupComplex(abstractSyntaxTree ast){
	abstractSyntaxTree parent=ast;
	//printf("xxxxx NT=%d xxxx T=%d XXXX\n",parent->s.nonterminal,parent->s.terminal);
	if(parent->s.nonterminal==booleanExpression){
		abstractSyntaxTree temp;
		temp=parent->child->sibling;
		parent->t=temp->t;
		parent->s=temp->s;
		parent->exp=temp->exp;
		parent->expOp=temp->expOp;
		parent->child->sibling=temp->sibling;
	}
	else if(parent->s.nonterminal==expPrime || parent->s.nonterminal==termPrime || parent->s.nonterminal==dataType){
		abstractSyntaxTree temp;
		temp=parent->child;
		parent->s=temp->s;
		parent->t=temp->t;
		parent->exp=temp->exp;
		parent->expOp=temp->expOp;
		parent->child=temp->sibling;
	}

	if(parent->child!=NULL){
		//printf("if 2\n");
		pullupComplex(parent->child);
	}
	if(parent->sibling!=NULL){
		//printf("if 3\n");
		pullupComplex(parent->sibling);
	}
	if(parent->sibling==NULL){
		//printf("if 4\n");
		return;
	}
}

/*
void printAST(abstractSyntaxTree A, char *outFile, int *totalAllocatedMemory)
{}
*/

void printFuncAst(abstractSyntaxTree ast,FILE *fout){
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
				fprintf(fout,"%s\t\t\t        %d    \t%d\t\t %s   \t     %d\t\t\t     yes   \t\t     ----------\n",temp->t.lexeme,temp->t.line_num,temp->s.terminal,val,n);
		
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
				fprintf(fout,"%s\t\t\t    %d    \t%d\t\t %s   \t     %d\t\t\t     no   \t\t     ----------\n",temp->t.lexeme,temp->t.line_num,temp->s.terminal,val,n);
			}
		}
		else{
			//fprintf(fout,"%d\n",temp->s.nonterminal);
			fprintf(fout,"-----------------\t------\t-----\t-------------\t         %d        \t      no       \t        %d     \n",n, temp->s.nonterminal);
		}
		printFuncAst(temp->child,fout);
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
					fprintf(fout,"%s\t\t\t        %d    \t%d\t\t %s   \t     %d\t\t\t     yes   \t\t     ----------\n",temp->t.lexeme,temp->t.line_num,temp->s.terminal,val,n);
		
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
					fprintf(fout,"%s\t\t\t    %d    \t%d\t\t %s   \t     %d\t\t\t     no   \t\t     ----------\n",temp->t.lexeme,temp->t.line_num,temp->s.terminal,val,n);

				}
			}
			else{
				//fprintf(fout,"%d\n",temp->s.nonterminal);
				fprintf(fout,"-----------------\t------\t-----\t-------------\t         %d        \t      yes       \t        %d     \n",n, temp->s.nonterminal);
			}
		}
		printFuncAst(temp->sibling,fout);
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
				fprintf(fout,"%s\t\t\t        %d    \t%d\t\t %s   \t     %d\t\t\t     yes   \t\t     ----------\n",temp->t.lexeme,temp->t.line_num,temp->s.terminal,val,n);
		
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
				fprintf(fout,"%s\t\t\t    %d    \t%d\t\t %s   \t     %d\t\t\t     no   \t\t     ----------\n",temp->t.lexeme,temp->t.line_num,temp->s.terminal,val,n);

			}
		}
		else{
			//fprintf(fout,"%d\n",temp->s.nonterminal);
			fprintf(fout,"-----------------\t------\t-----\t-------------\t         %d        \t      yes       \t        %d     \n",n, temp->s.nonterminal);
		}
	}
}


void printAST(abstractSyntaxTree A, char *outfile){
	FILE *fp=fopen(outfile,"w");
	fprintf(fp,"lexemeCurrentNode\tlineno\ttoken\tvalueIfNumber\tparentNodeSymbol\tisLeafNode(yes/no)\tNodeSymbol\n");
	printFuncAst(A,fp);
	fclose(fp);
}
