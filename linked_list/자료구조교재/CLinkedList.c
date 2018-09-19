#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include"CLinkedList.h"

void ListInit(List*plist){
	plist->tail=NULL;
	plist->cur=NULL;
	plist->before=NULL;
	plist->numOfData=0;
}

void LInsertFront(List*plist, Data data){
	Node*newNode=(Node*)malloc(sizeof(Node));
	newNode->data=data;

	if(plist->tail==NULL){
		plist->tail=newNode;
		newNode->next=newNode;
	}
	else{
		newNode->next=plist->tail->next; //새 노드와 4가 저장된 노드 연결
		plist->tail->next=newNode; //2가 저장된 노드와 새 노드 연결
	}
	(plist->numOfData)++;
}

void LInsert(List*plist, Data data){
	Node*newNode=(Node*)malloc(sizeof(Node));
	newNode->data=data;

	if(plist->tail==NULL){
		plist->tail=newNode;
		newNode->next=newNode;
	}
	else{
		newNode->next=plist->tail->next;
		plist->tail->next=newNode;
		plist->tail=newNode;
	}
	(plist->numOfData)++;
}

int LFirst(List*plist, Data*pdata){
	if(plist->tail==NULL)
		return FALSE;
	plist->before=plist->tail;
	plist->cur=plist->tail->next;

	*pdata=plist->cur->data;
	return TRUE;
}

int LNext(List*plist, Data*pdata){
	if(plist->tail==NULL)
		return FALSE;
	plist->before=plist->cur;
	plist->cur=plist->cur->next;

	*pdata=plist->cur->data;
	return TRUE;
}

Data LRemove(List*plist){
	Node*rpos=plist->cur;
	Data rdata=rpos->data;

	if(rpos==plist->tail){ //삭제 대상을 tail이 가리킨다면
		if(plist->tail==plist->tail->next)
			plist->tail=NULL;
		else
			plist->tail=plist->before;
	}

	plist->before->next=plist->cur->next;
	plist->cur=plist->before;

	free(rpos);
	(plist->numOfData)--;
	return rdata;
}
