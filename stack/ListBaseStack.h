#ifndef __LB_STACK_H__
#define __LB_STACK_H__

#define TRUE 1
#define FALSE 0

typedef struct node{
	int data;
	struct node*next;
}Node;

typedef struct _listStack{
	Node*head;
}Stack;

void StackInit(Stack*pstack);
int IsEmpty(Stack*pstack);
void Push(stack*pstack, int data);
int Pop(Stack*pstack);
int Peek(Stack*pstack);

#endif