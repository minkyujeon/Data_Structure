#include "DLinkedList.h"

void ListInit(List*plist){
	plist->head=(Node*)malloc(sizeof(Node));//더미노드 생성
	plist->head->next=NULL;
	plist->comp=NULL;
	plist->numOfData=0;
}

void FInsert(List*plist, LData data){ //comp가 NULL일때 호출
	Node*newNode=(Node*)malloc(sizeof(Node));
	newNode->data=data;

	newNode->next=plist->head->next;//더미노드 다음에 추가
	plist->head->next=newNode; //더미노드가 새 노드를 가리키게 함
	(plist->numOfData)++;
}

void LInsert(List*plist, LData data){
	if(plist->comp==NULL)
		FInsert(plist,data);
	else
		SInsert(plist,data);
}

int LFirst(List*plist, LData *pdata){ //조회함수
	if(plist->head->next==NULL)
		return FALSE;
	plist->before=plist->head; //before는 더미노드를 가리키게함
	plist->cur=plist->head->next; //cur은 첫 번째(더미노드 이후 첫번째)노드를 가리키게 함

	*pdata=plist->cur->data;
	return TRUE;
}

int LNext(List*plist, LData*pdata){
	if(plist->cur->next==NULL)
		return FALSE;
	plist->before=plist->cur; //cur이 가리키던 것을 before가 가리킴
	plist->cur=plist->cur->next; //cur은 그 다음 노드를 가리킴

	*pdata=plist->cur->data;
	return TRUE;
}

//LFirst 혹은 LNext함수가 반환한 데이터를 삭제한다
LData LRemove(List*plist){
	Node*rpos=plist->cur; //소멸 대상의 주소값을 rpos에 저장
	LData rdata=rpos->data; //소멸 대상의 데이터를 rdata에 저장
	
	plist->before->next=plist->cur->next;//소멸 대상을 리스트에서 제거
	plist->cur=plist->before; //cur이 가리키는 위치 재조정

	free(rpos); //리스트에서 제거된 노드 소멸
	(plist->numOfData)--; //저장된 데이터 수 하나 감소
	return rdata; //제거된 노드의 데이터 반환

}

int LCount(List*plist){
	return plist->numOfData;
}

void SetSortRule(List*plist, int(*comp)(LData d1, LData d2)){
	plist->comp=comp;
}

void SInsert(List*plist, LData data){
	Node*newNode=(Node*)malloc(sizeof(Node));
	Node*pred=plist->head; //pred는 더미 노드를 가리킴
	newNode->data=data;

	while(pred->next!=NULL && plist->comp(data, pred->next->data)!=0){
//새 노드가 들어갈 위치를 찾기 위한 반복문(pred가 마지막 노드를 가리키는 것도 아니고, 새 데이터가 들어갈 자리도 아직 찾지 못했다면 pred를 다음 노드로 이동시킨다
		pred=pred->next; //다음 노드로 이동
	}
	newNode->next=pred->next; //새 노드의 오른쪽을 연결
	pred->next=newNode;

	(plist->numOfData)++;
}
