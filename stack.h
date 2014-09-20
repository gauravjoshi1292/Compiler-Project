#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include"stackDef.h"

extern Stack createStack();

extern Link createStackNode(sym s);

extern int isEmptyStack(Stack s);

extern sym getTop(Stack s);

extern Stack push(Stack s,sym s1);

extern Stack pop(Stack s);

extern rule_stack createRuleStack();

extern nxt createRuleNode(int n);

extern int isEmptyRuleStack(rule_stack s);

extern int getTopRule(rule_stack s);

extern rule_stack pushRule(rule_stack s,int n);

extern rule_stack popRule(rule_stack s);

#endif
