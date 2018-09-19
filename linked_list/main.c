#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "header.h"

int main(void){
	Node*newNode=new_node();//맨 앞에 더미노드 추가 -> 삭제 시 가장 앞에 있는 노드를 삭제할때도 pre값의 설정이 가능
	Node*head=NULL;
	Node*tail=NULL;
	int menu=0,i=0,data=0,idx=0;
	head=tail=newNode; //더미노드
	while(1){
		menu=show_menu();
		if(menu==6){
			printf("종료합니다 .\n");
			break;
		}
		switch(menu){
		case 1:
			printf("삽입할 수 입력 (자연수만 가능): ");
			scanf_s("%d",&data);
			if(data==0){
				printf("자연수만 입력 가능합니다\n");//예외처리
				break;
			}
			if(data<head->data) insert_front(&head,data); //head가 가리키는 값보다 작다면 앞에 삽입
			else if(data>tail->data) insert_back(&tail,data); //tail이 가리키는 값보다 크다면 뒤에 삽입
			else insert_middle(head,data); //둘다 아니라면 중간에 삽입
			break;
		case 2:
			printf("삭제할 값 입력 : ");
			scanf_s("%d",&data);
			Delete(&head,&tail,data);
			break;
		case 3:
			printf("검색할 값 입력 : ");
			scanf_s("%d",&data);
			printf("data의 index : %d\n",search(head,data));
			break;
		case 4:
			printf("길이 : %d\n",ListLength(head));
			break;
		case 5:
			show(head);
			break;
		}
	}
}