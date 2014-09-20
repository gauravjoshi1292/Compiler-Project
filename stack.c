#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

Stack createStack()
{
	Stack s;
	s.top = NULL;
	s.size = 0;
	return s;
}

Link createStackNode(sym s)
{
	Link newNode;
	newNode = (Link)malloc(sizeof(stackNode));
	if(newNode==NULL)
	{
		printf("Error : Insufficient Memory.\n");
		exit(0);
	}
	newNode->s.type = s.type;
	if(s.type==0)
	newNode->s.nonterminal=s.nonterminal;
	else if(s.type==1)
	newNode->s.terminal=s.terminal;
	newNode->next = NULL;
	return newNode;
}

int isEmptyStack(Stack s)
{
	if(s.top==NULL)
		return 1;
	else
		return 0;
}

sym getTop(Stack s)
{
	return (s.top->s);
}

Stack push(Stack s,sym s1)
{
	Link newNode;
	newNode = createStackNode(s1);
	if(s.top==NULL)
	{
		s.top = newNode;
		s.size++;
	}
	else
	{
		newNode->next = s.top;
		s.top = newNode;
		s.size++;
	}
	return s;
}

Stack pop(Stack s)
{
	Link temp;
	temp = s.top;
	s.top = s.top->next;
	s.size--;
	free(temp);
	return s;
}

rule_stack createRuleStack()
{
	rule_stack s;
	s.top = NULL;
	s.size = 0;
	return s;
}

nxt createRuleNode(int n)
{
	nxt newNode;
	newNode = (nxt)malloc(sizeof(ruleNode));
	if(newNode==NULL)
	{
		printf("Error : Insufficient Memory.\n");
		exit(0);
	}
	newNode->rule_no = n;
	newNode->next = NULL;
	return newNode;
}

int isEmptyRuleStack(rule_stack s)
{
	if(s.top==NULL)
		return 1;
	else
		return 0;
}

int getTopRule(rule_stack s)
{
	return (s.top->rule_no);
}

rule_stack pushRule(rule_stack s,int n)
{
	nxt newNode;
	newNode = createRuleNode(n);
	if(s.top==NULL)
	{
		s.top = newNode;
		s.size++;
	}
	else
	{
		newNode->next = s.top;
		s.top = newNode;
		s.size++;
	}
	return s;
}

rule_stack popRule(rule_stack s)
{
	nxt temp;
	temp = s.top;
	s.top = s.top->next;
	s.size--;
	free(temp);
	return s;
}
