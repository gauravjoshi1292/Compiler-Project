#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include "lexerDef.h"
//tokenInfo * ptr;
FILE *getStream(FILE *fp, buffer B, buffersize k,int *y){
    int j=0;
    char cc;
    if(fp==NULL){
        printf("file completely read\n");
    }
    while(j<k && fscanf(fp,"%c",&cc)!=EOF){
        B[j]=cc;
//printf("hi %d %c\n",(int)cc,cc);
        j++;
        (*y)++;
    }
    if(feof(fp)){
        B[j]=' ';
        (*y)++;
    }
    return fp;
}

int isDelimiter(char ch){
    if(ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='(' || ch==')' || ch=='[' || ch==']' || ch=='=' ||ch==';' || ch=='>' ||  ch=='<' || ch=='!' || ch=='~' || ch=='%' || ch==':' ||ch==' ' || ch=='\n' || ch=='\t' || ch==','||ch=='\r')
        return 1;
    else
        return 0;
}

int isSpecialChar(char ch){
    if(ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='(' || ch==')' || ch=='[' || ch==']' || ch=='=' ||ch==';' || ch=='>' ||  ch=='<' || ch=='!' || ch=='~' || ch=='%' || ch==':')
        return 1;
    else
        return 0;
}

int isKnownSymbol(char ch){
    if(ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='(' || ch==')' || ch=='[' || ch==']' || ch=='=' ||ch==';' || ch=='>' ||  ch=='<' || ch=='!' || ch=='~' || ch=='%' || ch==':' || ch=='@' || ch=='#' || ch=='%' || ch=='&' || ch=='_' || ch==':' || ch==';' || ch=='.' || ch==',' || (ch>='a' && ch<='z') || (ch>='A' && ch<='Z') || (ch>='0' && ch<='9'))
        return 1;
    else
        return 0;
}

int checkState(int s){
    if(s==0 || s==3 || s==5 || s==6 || s==7 || s==9 || s==11)
        return 1;
    else
        return 0;
}

int  getTokenList( FILE *fp,tokenInfo *info)
{
    int s = 0;
    char ch;
    int l_no=1;
    int flag=0;
    buffer B;
    int pa=0;
    int x=0;
    buffersize k=30;
    B=(char*)malloc(k*sizeof(char));
    fp = getStream(fp,B,k,&x);
    int z=x;
    char fg;
    int i=0;
    tokenInfo temp;
    temp.lexeme=(char*)malloc(100*sizeof(char));
   // temp.type=(char*)malloc(100*sizeof(char));

    if(fp==NULL){
        printf("file is empty or completely read\n");
    }
    int coun=0;
    int poi=0;
    char* lex=NULL;
    tokenInfo *temp1;
    label1:
    while(i<z){
            if(poi==0)
            {
                lex = (char*)malloc(100*sizeof(char));
            }
            ch = B[i];
	//printf("hi %d %c\n",(int)ch,ch);
            if(ch=='\n' && flag==0){
                l_no++;
                flag=1;
            }
            else if(ch!='\n'){
                flag=0;
            }

            if(s==24 || s==139 || ch=='%'){
                i=i;
            }
            else if(isSpecialChar(ch)==1 && checkState(s)==1){
                lex[poi]=ch;
		//printf("%c\n",lex[poi]);

		poi++;
            }
            else if(ch!=' ' && ch!='\n' && ch!='\r' && ch!='\t' && (isSpecialChar(ch)==0))
            {
                lex[poi]=ch;
 		//if(ch=='\n')
		//printf("hi\n");
		//printf("hi %d %c\n",(int)lex[poi],lex[poi]);
                poi++;

            }

            i++;
            switch(s){
            //the initial big state//
            case 0:
            {
                   //return TK_PLUS
                   if(ch=='+'){
                    s=0;
                    temp.type=TK_PLUS;
                    temp.lexeme=lex;
                    temp.line_num=l_no;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else if(ch=='-'){
                    //return TK_MINUS;
                    s=0;
                    temp.type=TK_MINUS;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else if(ch=='*'){
                    //return TK_MUL;
                    s=0;
                    temp.type=TK_MUL;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else if(ch=='/'){
                    //return TK_DIV;
                    s=0;
                    temp.type=TK_DIV;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else if(ch=='='){
                    s=3;break;
                }
                else if(ch=='<'){
                    s=5;break;
                }
                else if(ch=='>'){
                    s=9;break;
                }
                else if(ch=='!'){
                    s=11;break;
                }
                else if(ch=='~'){
                    s=0;
                    temp.type=TK_NOT;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else if(ch=='@'){
                    s=14;break;
                }
                else if(ch=='&'){
                    s=17;break;
                }
                else if(ch=='('){
                    //return TK_OP;
                    s=0;
                    temp.type=TK_OP;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else if(ch==')'){
                    //return TK_CL;
                    s=0;
                    temp.type=TK_CL;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else if(ch==';'){
                    //return TK_SEM;
                    s=0;
                    temp.type=TK_SEM;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }

                else if(ch==':'){
                    //return TK_COLON;
                    s=0;
                    temp.type=TK_COLON;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else if(ch=='.'){
                    //return TK_DOT;
                    s=0;
                    temp.type=TK_DOT;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else if(ch==','){
                	//return TK_COMMA;
                    s=0;
                    temp.type=TK_COMMA;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else if(ch=='%'){
                    //return TK_COMMENT;
                    s=24;
                    break;
                }
                else if(ch=='#'){
                    s=26;break;
                }
                else if(ch=='_'){
                    s=29;break;
                }
                else if(ch>='0' && ch<='9'){
                    if(ch>='0' && ch<='9'){
                        s=38;
                        break;
                    }
                    else{
                        //return TK_NUM;
                        s=0;
                        temp.type=TK_NUM;
                        temp.lexeme=lex;
			temp.num=atoi(lex);
			//printf("%d\n",temp.num);
                        temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->num=temp.num;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                        break;
                    }
                }
                else if(ch=='['){
                    //return TK_SQL;
                    s=0;
                    temp.type=TK_SQL;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else if(ch==']'){
                    //return TK_SQR;
                    s=0;
                    temp.type=TK_SQR;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }

                else if(ch=='e'){
                    s=44;break;
                }
                else if(ch=='p'){
                    s=63;break;
                }
                else if(ch=='w'){
                    s=72;break;
                }
                else if(ch=='r'){
                    s=85;break;
                }
                else if(ch=='i'){
                    s=98;break;
                }
                else if(ch=='t'){
                    s=106;break;
                }
                else if(ch=='o'){
                    s=113;break;
                }
                else if(ch=='l'){
                    s=119;break;
                }
                else if(ch=='g'){
                    s=123;break;
                }
                else if(ch=='c'){
                    s=129;break;
                }
                else if((ch>='b' && ch<='d') && ch!='c'){
                    s=133;break;
                }
                else if((ch>='a' && ch<='z') && (ch!='e' && ch!='p' && ch!='w' && ch!='r' && ch!='i' && ch!='t' && ch!='o' && ch!='l' && ch!='g' && ch!='c' && ch!='b' && ch!='d')){
                    s=136;
                    break;
                }
                else if(ch==' '||ch=='\t' || ch=='\n'||ch=='\r'){
		//printf(" hi %c",ch);
                    s=0;
                 goto label1;
                }
                else{
                    s=139;i--;break;
                }
            }

            case 3:
                if(ch=='='){
                    //return TK_EQ;
                    s=0;
                    temp.type=TK_EQ;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                   // error
                    break;
                }
            case 5:
                if(ch=='='){
                    //return TK_LE;
                    s=0;
                    temp.type=TK_LE;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else if(ch=='-'){
                    s=6;
                    break;
                }
                else{
                    //return TK_LT;
                    s=0;
                    temp.type=TK_LT;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
            case 6:
                if(ch=='-'){
                    s=7;
                    break;
                }
                else{
                    //errror//
                    s=139;i--;
                    //s=0;
                    break;
                }
            case 7:
                 if(ch=='-'){
                    //return TK_ASSIGNOP;
                    s=0;
                    temp.type=TK_ASSIGNOP;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    //errror//
                     s=139;i--;
                    //s=0;
                    break;
                }

            case 9:
                if(ch=='='){
                   // return TK_GE;
                    s=0;
                    temp.type=TK_GE;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    //return TK_GT;
                    s=0;
                    temp.type=TK_GT;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }

          case 11:
                if(ch=='='){
                    //return TK_NE;
                    s=0;
                    temp.type=TK_NE;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    //errror//
                    s=139;i--;break;
                    // rewind 1 char
                }

            case 14:
                if(ch=='@'){
                    s=15;
                    break;
                }
                else{
                    //errror//
                    s=139;i--;
                    //s=0;
                    break;
                }
            case 15:
                if(ch=='@'){
                    s=0;
                    temp.type=TK_OR;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    //return TK_OR;
                    break;
                }
                else{
                    //errror//
                     s=139;i--;
                    break;
                }

            case 17:
                if(ch=='&'){
                    s=18;
                    break;
                }
                else{
                    //errror//
                     s=139;i--;
                    break;
                }

            case 18:
                if(ch=='&'){
                    //return TK_AND;
                    s=0;
                    temp.type=TK_AND;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    //errror//
                     s=139;i--;
                    break;
                }

            case 24:
                if(ch=='\n'){
                    s=0;
                    break;
                }
                else{
                    //return TK_COMMENT;
                    s=24;
                    break;
                }

            case 26:
                if(ch>='a' && ch<='z'){
                    s=27;
                    break;
                }
                else{
                    //errror//
                    s=139;i--;
                    break;
                }
            case 27:
                if(ch>='a' && ch<='z'){
                    s=27;
                    break;
                }
                else if(isDelimiter(ch)==1){i--;
                   // return "TOKEN_RECORDID;
                    s=0;
                    temp.type=TK_RECORDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;

                    break;
                }
                else{
                    s=139;i--;
                    break;
                }

            case 29:
                if(((ch>='a' && ch<='z') || (ch>='A' && ch<='Z')) && (ch!='m')){
                    s=30;
                    break;
                }
                else if(ch=='m'){
                    s=32;
                    break;
                }
                else{
                    //errror//
                     s=139;i--;
                    //rewind i char
                   // s=0;
                    break;
                }
            case 30:
                if(poi>=30){
                    s=142;
                    break;
                }
                else if((ch>='a' && ch<='z') || (ch>='A' && ch<='Z')){
                    s=30;
                    break;
                }
                else if(ch>=0 && ch<=9){
                    s=31;
                    break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_FUNID;
                    s=0;
                    temp.type=TK_FUNID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    //errror//
                    s=139;i--;
                    //rewind i char
                    //s=0;
                    break;
                }
            case 31:
                if(poi>=30){
                    s=143;
                    break;
                }
                else if(ch>=0 && ch<=9){
                    s=31;
                    break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_FUNID;
                    s=0;
                    temp.type=TK_FUNID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 32:
                if(ch=='a'){
                    s=33;
                    break;
                }
                else if(((ch>='a' && ch<='z') || (ch>='A' && ch<='Z')) && (ch!='a')){
                    s=30;
                    break;
                }
                else if(ch>='0' && ch<='9'){
                    s=31;
                    break;
                }
                else{
                    //errror//
                    s=139;i--;

                    //s=0;
                    break;
                }
            case 33:
                 if(ch=='i'){
                    s=34;
                    break;
                }
                else if(((ch>='a' && ch<='z') || (ch>='A' && ch<='Z')) && (ch!='i')){
                    s=30;
                    break;
                }
                else if(ch>='0' && ch<='9'){
                    s=31;
                    break;
                }
                else{
                    //errror//
                     s=139;i--;
                    //s=0;
                    break;
                }
            case 34:
                 if(ch=='n'){
                    s=35;
                    break;
                }
                else if(((ch>='a' && ch<='z') || (ch>='A' && ch<='Z')) && (ch!='a')){
                    s=30;
                    break;
                }
                else if(ch>='0' && ch<='9'){
                    s=31;
                    break;
                }
                else{
                    //errror//
                     s=139;i--;
                    //s=0;
                    break;
                }
            case 35:
                if((ch>='a' && ch<='z') || (ch>='A' && ch<='Z')){
                    s=30;
                    break;
                }
                else if(ch>='0' && ch<='9'){
                    s=31;
                    break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_MAIN;
                    s=0;

                    temp.type=TK_MAIN;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }

            case 38:
                if(ch>='0' && ch<='9'){
                    s=38;
                    break;
                }
                else if(ch=='.'){
                    s=39;
                    break;
                }
                else if(isDelimiter(ch)==1){i--;
                   // return TK_NUM;
                    s=0;

                    temp.type=TK_NUM;
                    temp.lexeme=lex;
	temp.num=atoi(lex);
//printf("%d\n",temp.num);
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->num=temp.num;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 39:
                if(ch>='0' && ch<='9'){
                    s=40;
                    break;
                }
                else{
                    //errror//
                     s=139;i--;

                    //s=0;
                    break;
                }
            case 40:
                if(ch>='0' && ch<='9'){
                    s=41;
                    break;
                }
                else{
                    //errror//
                    s=139;i--;

                   // s=0;
                    break;
                }
            case 41:
                 if(ch>='0' && ch<='9'){
                    //errror//
                    s=139;i--;

                    //s=0;
                    break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_RNUM;

                    s=0;
                    temp.type=TK_RNUM;
                    temp.lexeme=lex;
			temp.r_num=atof(lex);
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->r_num=temp.r_num;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }

            case 44:
                if(ch=='n'){
                    s=45;
                    //fprintf(fout,"44\n");
                    break;
                }
                else if(ch=='l'){
                    s=49;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='n' && ch!='l')){
                 //go to field id 2nd state
                    s=136;
                    break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_FIELDID;

                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 45:
                if(ch=='d'){
                    s=46;
                    //fprintf(fout,"45\n");
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='d') ){
                    //go to field id 2nd state;//
                       s=136;
                       break;
                }
                else if(isDelimiter(ch)==1){i--;
                   // return TK_fieldid;

                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 46:
                if(ch=='i'){
                    s=47;
                    break;
                }
                else if(ch=='w'){
                    s=52;
                    break;
                }
                else if(ch=='r'){
                    s=57;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='i' && ch!='w' && ch!='r')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    s=0;
                    temp.type=TK_END;
                    temp.lexeme=lex;
                    //fprintf(fout,"46\n");
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 47:
                if(ch=='f'){
                    s=48;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='f')){
                    //go to field id 2nd state;//
                      s=136;
                      break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;

                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 48:
                if(ch>='a' && ch<='z'){
                    //go to field id 2nd state
                    s=136;
                    break;
                }
                else if(isDelimiter(ch)==1){i--;

                    s=0;
                    temp.type=TK_ENDIF;
                    temp.lexeme=lex;
                    printf("%d %d\n",x,i);
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 49:
                if(ch=='s'){
                    s=50;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='s')){
                    //go to field id 2nd state;//
                     s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;

                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 50:
                if(ch=='e'){
                    s=51;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='e')){
                    //go to field id 2nd state;//
                       s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;

                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 51:
                if(ch>='a' && ch<='z'){
                    //go to field id 2nd state
                    s=136;
                    break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_ELSE;

                    s=0;
                    temp.type=TK_ELSE;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 52:
                if(ch=='h'){
                    s=53;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='h')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;

                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 53:
                if(ch=='i'){
                    s=54;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='i')){
                    //go to field id 2nd state;//
                       s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;

                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 54:
                if(ch=='l'){
                    s=55;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='l')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;

                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 55:
            if(ch=='e'){
                    s=56;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='e')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;

                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 56:
                if(ch>='a' && ch<='z'){
                    //go to field id 2nd state
                    s=136;
                    break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_ENDWHILE;
			//printf("hi\n");
                    s=0;
                    temp.type=TK_ENDWHILE;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 57:
                if(ch=='e'){
                    s=58;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='e')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;

                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 58:
                if(ch=='c'){
                    s=59;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='c')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                   // return TK_fieldid;

                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 59:
                if(ch=='o'){
                    s=60;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='o')){
                    //go to field id 2nd state;//
                       s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;

                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 60:
                if(ch=='r'){
                    s=61;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='r')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;

                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 61:
                if(ch=='d'){
                    s=62;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='d')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;

                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 62:
                if(ch>='a' && ch<='z'){
                    //go to field id 2nd state
                    s=136;
                    break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_ENDRECORD;

                    s=0;
                    temp.type=TK_ENDRECORD;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 63:
                if(ch=='a'){
                    s=64;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='a')){
                    //go to field id 2nd state;//
                       s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;
                    ;
                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 64:
                if(ch=='r'){
                    s=65;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='r')){
                    //go to field id 2nd state;//
                       s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;
                    ;
                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 65:
                if(ch=='a'){
                    s=66;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='a')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;
                    ;
                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 66:
                if(ch=='m'){
                    s=67;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='m')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;
                    ;
                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 67:
                if(ch=='e'){
                    s=68;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='e')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                   // return TK_fieldid;
                    ;
                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 68:
                if(ch=='t'){
                    s=69;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='t')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;
                    ;
                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 69:
                if(ch=='e'){
                    s=70;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='e')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;
                    ;
                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 70:
                if(ch=='r'){
                    s=71;
                    break;
                }

                else if((ch>='a' && ch<='z')&&(ch!='r' && ch!='s')){
                    //go to field id 2nd state;//
                       s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;

                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 71:
                 if(ch=='s'){
                    s=137;
                    break;
                }
                else if(ch>='a' && ch<='z'){
                    //go to field id 2nd state
                    s=136;
                    break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_PARAMETER;

                    s=0;
                    temp.type=TK_PARAMETER;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 72:
                if(ch=='r'){
                    s=73;
                    break;
                }
                else if(ch=='i'){
                    s=78;
                    break;
                }
                else if(ch=='h'){
                    s=81;
                   // fprintf(fout,"81\n");
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='r' && ch!='i' && ch!='h')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;
                    ;
                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 73:
                if(ch=='i'){
                    s=75;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='i')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;

                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            /*case 74:
                //if(ch=='i'){
                    s=75;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='i')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;

                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }*/
            case 75:
                if(ch=='t'){
                    s=76;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='t')){
                    //go to field id 2nd state;//
                     s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;

                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 76:
                if(ch=='e'){
                    s=77;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='e')){
                    //go to field id 2nd state;//
                     s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;

                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 77:
                if(ch>='a' && ch<='z'){
                    //go to field id 2nd state
                    s=136;
                    break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_WRITE;

                    s=0;
                    temp.type=TK_WRITE;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }

            case 78:
                if(ch=='t'){
                    s=79;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='t')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;

                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 79:
                if(ch=='h'){
                    s=80;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='h')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;

                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 80:
                if(ch>='a' && ch<='z'){
                    //go to field id 2nd state
                    s=136;
                    break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_WITH;

                    s=0;
                    temp.type=TK_WITH;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 81:
                if(ch=='i'){
                    s=82;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='i')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;

                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 82:
                if(ch=='l'){
                    s=83;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='l')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;
                    ;
                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 83:
                if(ch=='e'){
                    s=84;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='e')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;

                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 84:
                if(ch>='a' && ch<='z'){
                    //go to field id 2nd state
                    s=136;
                    break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_WHILE;

                    s=0;
                    temp.type=TK_WHILE;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 85:
                if(ch=='e'){
                    s=86;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='e')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;

                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 86:
                if(ch=='a'){
                    s=87;
                    break;
                }
                else if(ch=='t'){
                    s=90;
                    break;
                }
                else if(ch=='c'){
                    s=94;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='a' && ch!='t' && ch!='c')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;

                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 87:
                if(ch=='d'){
                    s=88;
                    break;
                }
                else if(ch=='l'){
                    s=89;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='d' && ch!='l')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;

                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 88:
                if(ch>='a' && ch<='z'){
                    //go to field id 2nd state
                    s=136;
                    break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_READ;

                    s=0;
                    temp.type=TK_READ;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 89:
                if(ch>='a' && ch<='z'){
                    //go to field id 2nd state
                    s=136;
                    break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_REAL;

                    s=0;
                    temp.type=TK_REAL;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }

            case 90:
                if(ch=='u'){
                    s=91;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='u')){
                    //go to field id 2nd state;//
                     s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;

                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }

            case 91:
                if(ch=='r'){
                    s=92;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='r')){
                    //go to field id 2nd state;//
                     s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;

                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 92:
                if(ch=='n'){
                    s=93;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='n')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;

                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 93:
                if(ch>='a' && ch<='z'){
                    //go to field id 2nd state
                    s=136;
                    break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_RETURN;

                    s=0;
                    temp.type=TK_RETURN;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 94:
                if(ch=='o'){
                    s=95;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='o')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;

                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 95:
                if(ch=='r'){
                    s=96;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='r')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;

                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 96:
                if(ch=='d'){
                    s=97;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='d')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;

                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 97:
                if(ch>='a' && ch<='z'){
                    //go to field id 2nd state
                    s=136;
                    break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_RECORD;

                    s=0;
                    temp.type=TK_RECORD;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }

            case 98:
                if(ch=='n'){
                    s=99;
                    break;
                }
                else if(ch=='f'){
                    s=105;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='n' && ch!='f')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;
                    ;
                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 99:
                if(ch=='t'){
                    s=101;
                    break;
                }
                else if(ch=='p'){
                    s=102;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='t' && ch!='p')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;

                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 101:
                if(ch>='a' && ch<='z'){
                    //go to field id 2nd state
                    s=136;
                    break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_INT;

                    s=0;
                    temp.type=TK_INT;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 102:
                if(ch=='u'){
                    s=103;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='u')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;

                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 103:
                if(ch=='t'){
                    s=104;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='t')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;

                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 104:
                if(ch>='a' && ch<='z'){
                    //go to field id 2nd state
                    s=136;
                    break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_INPUT;

                    s=0;
                    temp.type=TK_INPUT;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }

            case 105:
                if(ch>='a' && ch<='z'){
                    //go to field id 2nd state
                    break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_IF;

                    s=0;
                    temp.type=TK_IF;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }

            case 106:
                if(ch=='y'){
                    s=107;
                    break;
                }
                else if(ch=='h'){
                    s=110;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='y' && ch!='h')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;
                    ;
                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 107:
                if(ch=='p'){
                    s=108;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='p')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;
                    ;
                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 108:
                if(ch=='e'){
                    s=109;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='e')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;
                    ;
                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 109:
                    if(ch>='a' && ch<='z'){
                    //go to field id 2nd state
                    s=136;
                    break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_TYPE;
                    ;
                    s=0;
                    temp.type=TK_TYPE;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 110:
                if(ch=='e'){
                    s=111;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='e')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;
                    ;
                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 111:
                if(ch=='n'){
                    s=112;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='n')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;
                    ;
                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 112:
                if(ch>='a' && ch<='z'){
                    //go to field id 2nd state
                    s=136;
                    break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_THEN;
                    ;
                    s=0;
                    temp.type=TK_THEN;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 113:
                if(ch=='u'){
                    s=114;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='u')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;
                    ;
                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 114:
                if(ch=='t'){
                    s=115;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='t')){
                    //go to field id 2nd state;//
                       s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;
                    ;
                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 115:
                if(ch=='p'){
                    s=116;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='p')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;
                    ;
                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 116:
                if(ch=='u'){
                    s=117;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='u')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;
                    ;
                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 117:
                if(ch=='t'){
                    s=118;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='t')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;
                    ;
                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 118:
                if(ch>='a' && ch<='z'){
                    //go to field id 2nd state
                    s=136;
                    break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_OUTPUT;
                    ;
                    s=0;
                    temp.type=TK_OUTPUT;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 119:
                if(ch=='i'){
                    s=120;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='i')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;
                    ;
                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 120:
                if(ch=='s'){
                    s=121;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='s')){
                    //go to field id 2nd state;//
                       s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                   // return TK_fieldid;
                    ;
                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 121:
                if(ch=='t'){
                    s=122;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='t')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;
                    ;
                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 122:
                if(ch>='a' && ch<='z'){
                    //go to field id 2nd state
                    s=136;
                    break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_LIST;
                    ;
                    s=0;
                    temp.type=TK_LIST;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 123:
                if(ch=='l'){
                    s=124;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='l')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;
                    ;
                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 124:
                if(ch=='o'){
                    s=125;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='o')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;
                    ;
                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 125:
                if(ch=='b'){
                    s=126;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='b')){
                    //go to field id 2nd state;//
                       s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;
                    ;
                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 126:
                if(ch=='a'){
                    s=127;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='a')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;
                    ;
                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 127:
                if(ch=='l'){
                    s=128;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='l')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;
                    ;
                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 128:
                if(ch>='a' && ch<='z'){
                    //go to field id 2nd state
                    s=136;
                    break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_GLOBAL;
                    ;
                    s=0;
                    temp.type=TK_GLOBAL;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 129:
                if(ch=='a'){
                    s=130;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='a')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(ch>='2' && ch<='7'){
                    s=134;
                    break;
                    //go to tk_id 3rd state
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;
                    ;
                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 130:
                if(ch=='l'){
                    s=131;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='l')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;
                    ;
                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 131:
                if(ch=='l'){
                    s=132;
                    break;
                }
                else if((ch>='a' && ch<='z')&&(ch!='l')){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;
                    ;
                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 132:
                if(ch>='a' && ch<='z'){
                    ////go to field id 2nd state
                    s=136;
                    break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_CALL;
                    ;
                    s=0;
                    temp.type=TK_CALL;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 133:
                if(ch>='2' && ch<='7'){
                    s=134;
                    break;
                }
                else if(ch>='a' && ch<='z'){
                    //go to field id 2nd state;//
                      s=136;break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_fieldid;
                    ;
                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 134:
                if(poi>=20){
                    s=140;
                    break;
                }
                else if(ch>='b' && ch<='d'){
                    s=134;
                    break;
                }
                else if(ch>='2' && ch<='7'){
                    s=135;
                    break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_ID;
                    ;
                    s=0;
                    temp.type=TK_ID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 135:
                if(poi>=20){
                    s=141;
                    break;
                }
                else if(ch>='2' && ch<='7'){
                    s=135;
                    break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_ID;
                    ;
                    s=0;
                    temp.type=TK_ID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }

            case 136:
                if(ch>='a' && ch<='z'){
                    s=136;
                    break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_FIELDID;
                    ;
                    s=0;
                    temp.type=TK_FIELDID;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }

            case 137:
                if(ch>='a' && ch<='z'){
                    ////go to field id 2nd state
                    s=136;
                    break;
                }
                else if(isDelimiter(ch)==1){i--;
                    //return TK_PARAMETERS;

                    s=0;
                    temp.type=TK_PARAMETERS;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }

            case 139:
                //errror state
                if(isKnownSymbol(ch)==1){
                    s=145;
                    break;
                }
                else if(isKnownSymbol(ch)==0){
                    s=144;
                    break;
                }

            case 140:
                if(isDelimiter(ch)){i--;
                    s=0;
printf("length of lexeme %s for TK_ID exceeded 20 at line number %d\n",lex,l_no);

//temp.type=TK_ERROR;//length for TK_ID exceeded 20;
                    //temp.lexeme=lex;
                    //temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    break;
                }
                else if(ch>='b' && ch<='d'){
                    s=140;
                    break;
                }
                else if(ch>='2' && ch<='7'){
                    s=141;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }
            case 141:
                if(isDelimiter(ch)){i--;
                    s=0;
printf("length of lexeme %s for TK_ID exceeded 20 at line number %d\n",lex,l_no);
                    /*temp.type=TK_ERROR;//length for TK_ID exceeded 20;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    */break;
                }
                else if(ch>='2' && ch<='7'){
                    s=141;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }

            case 142:
                if(isDelimiter(ch)){i--;
                    s=0;
printf("length of lexeme %s for TK_FUNID exceeded 30 at line number %d\n",lex,l_no);
/*temp.type=TK_ERROR;//length for TK_FUNID exceeded 30;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    */break;
                }
                else if((ch>='a' && ch<='z') || (ch>='A' && ch<='Z')){
                    s=142;
                    break;
                }
                else if(ch>='0' && ch<='9'){
                    s=143;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }

            case 143:
                 if(isDelimiter(ch)){i--;
                    s=0;
printf("length of lexeme %s for TK_FUNID exceeded 30 at line number %d\n",lex,l_no);
                   /* temp.type=TK_ERROR;//length for TK_FUNID exceeded 30;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    */break;
                }
                else if(ch>='0' && ch<='9'){
                    s=143;
                    break;
                }
                else{
                    s=139;i--;
                    break;
                }

            case 144:
                if(isDelimiter(ch)){i--;
                    s=0;
printf("Unknown symbol in the lexeme %s at line number %d\n",lex,l_no);
/*temp.type=TK_ERROR;//unknown symbol in the lexeme;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                    */break;
                }
                else{
                    s=144;
                    break;
                }

            case 145:
                if(isKnownSymbol(ch)==1){
                    s=145;
                    break;
                }
                else if(isDelimiter(ch)==1){i--;
                    s=0;
printf("Unknown pattern in the lexeme %s at line number %d\n",lex,l_no);
                    /*temp.type=TK_ERROR;// unnknown pattern in the lexeme;
                    temp.lexeme=lex;
                    temp1=(struct node *)malloc(sizeof(struct node));temp1->lexeme=temp.lexeme;temp1->type=temp.type;temp1->line_num=l_no;info->link=temp1;info=temp1;coun++;int yz;for(yz=poi;yz<k;yz++)lex[yz]=NULL;poi=0;
                   */ break;
                }



            default:
                i++;
                s=0;
                //do nothing
        }

        if(i==z)
        {
             x=0;
             fp = getStream(fp,B,k,&x);
             i=0;
             z=x;
             //continue;
        }
    }

    if(!feof(fp))
    {
         x=0;
             fp = getStream(fp,B,k,&x);
             i=0;
             z=x;
             goto label1;
    }
return coun;
}

tokenInfo getNextToken()
{
    tokenInfo t;
    if(ptr!=NULL)
    {
        t.lexeme=ptr->lexeme;
        t.line_num=ptr->line_num;
        t.num=ptr->num;
        t.r_num=ptr->r_num;
        t.type=ptr->type;
        ptr=ptr->link;
        return t;
    }
}

void add$(){
	while(ptr3!=NULL){
		printf("token=%s\n",ptr3->lexeme);
		ptr3=ptr3->link;
	}
	//ptr3->lexeme="$";
	printf("%d\n",ptr3);
	ptr3=(tokenInfo*)malloc(sizeof(tokenInfo));
	ptr3->type=$;
	printf("%d\n",ptr3);
	return;
}

tokenInfo getNext()
{
    tokenInfo t;
    if(ptr2!=NULL)
    {
        t.lexeme=ptr2->lexeme;
        t.line_num=ptr2->line_num;
        t.num=ptr2->num;
        t.r_num=ptr2->r_num;
        t.type=ptr2->type;
        ptr2=ptr2->link;
        return t;
    }
    else{
    	tokenInfo temp;
    	temp.type=$;
    	return temp;
    }
}



