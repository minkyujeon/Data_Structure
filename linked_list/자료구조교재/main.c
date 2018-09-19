#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "DLinkedList.h"

int WhoIsPrecede(int d1, int d2){//값이작을수록 우선순위가 높다. (오름차순 정렬)
	if(d1<d2)
		return 0;
	else
		return 1;
}

int main(void){
	List list;
	int data;
	ListInit(&list);

	SetSortRule(&list, WhoIsPrecede); //정렬의 기준을 등록

	LInsert(&list,11); LInsert(&list,11);
	LInsert(&list,22); LInsert(&list,22);
	LInsert(&list,33);

	printf("현재 데이터의 수 : %d\n", LCount(&list));

	if(LFirst(&list,&data)){
		printf("%d ",data);

		while(LNext(&list,&data))
			printf("%d ",data);
	}
	printf("\n\n");

	//숫자 22을 검색하여 모두 삭제
	if(LFirst(&list,&data)){
		if(data==22)
			LRemove(&list);
		while(LNext(&list,&data)){
			if(data==22)
				LRemove(&list);
		}
	}

	printf("현재 데이터의 수 : %d\n",LCount(&list));

	if(LFirst(&list,&data)){
		printf("%d ",data);

		while(LNext(&list,&data))
			printf("%d ",data);
	}
	printf("\n\n");
	return 0;
}
