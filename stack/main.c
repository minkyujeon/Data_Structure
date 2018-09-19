#include <stdio.h>
#include <stdlib.h>
#include "ListBaseStack.h"

void StackInit(Stack*pstack){
	pstack->head=NULL;
}
int IsEmpty(Stack*pstack){
	if(pstack->head==NULL)
		return TRUE;
	else
		return FALSE;
}

void Push(Stack*pstack, int data){
	Node*newNode=(Node*)malloc(sizeof(Node));
	newNode->data=data;
	newNode->next=pstack->head;
	pstack->head=newNode;
}

int Pop(Stack*pstack){
	int rdata;
	Node*rnode;

	if(IsEmpty(pstack)){
		printf("Stack Memory Error!\n");
		exit(-1);
	}

	rdata=pstack->head->data;
	rnode=pstack->head;
	pstack->head=pstack->head->next;
	free(rnode);
	return rdata;
}

int Peek(Stack*pstack){
	if(IsEmpty(pstack)){
		printf("Stack Memory Error!\n");
		exit(-1);
	}

	return pstack->head->data;
}

int main(void){
	Stack stack;
	StackInit(&stack);

	Push(&stack,1);
	Push(&stack,2);
	Push(&stack,3);
	Push(&stack,4);
	Push(&stack,5);

	while(!IsEmpty(&stack))
		printf("%d ",Pop(&stack));
	return 0;
}