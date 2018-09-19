#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct node{
	int coef;
	int degree;
	struct node*pre; //이전 노드를 가리킴
	struct node*next; //다음 노드를 가리킴
}Node;

typedef struct list{
	Node*head;
	Node*tail;
	int num;//list내의 개수 저장
}List;

void new_List(List*plist){
	plist->head=NULL;
	plist->tail=NULL;
	plist->num=0;
}

void insert(List*plist,int coef, int degree){
	Node*newNode=(Node*)malloc(sizeof(Node));//삽입할 노드
	if(newNode==NULL){
		printf("에러!\n");
		exit(1);
	}

	newNode->coef=coef;
	newNode->degree=degree;
	newNode->next=NULL;

	if(plist->head==NULL){ //처음 입력(삽입) 
		plist->head=newNode; 
		plist->tail=newNode; //처음 노드에 head와 tail을 동시에 설정
	}
	else{
		plist->tail->next=newNode; //newNode를 tail뒤에 붙이고
		plist->tail=newNode; //newNode를 tail로 재설정
	}
	plist->num++; //리스트 내의 개수 하나 추가
}

void Poly_Add(List*plist1, List*plist2, List*plist3){
	Node*newNode1;
	Node*newNode2;
	int sum=0;

	newNode1=plist1->head; 
	newNode2=plist2->head; //각각 처음부터 search하기 위해
	
	//같은 차수일 경우 더해주고
	//다른 차수일 경우 차수가 큰걸 앞으로, 차수가 작은걸 뒤로 가도록 정렬하며 삽입

	while(newNode1 && newNode2){ //newNode1, newNode2중에서 어느 한 식이 NULL을 만날때까지(끝날때까지)
		if(newNode1->degree==newNode2->degree){ // 두 식에서 차수가 같다면
			sum=newNode1->coef+newNode2->coef; //각 계수를 더하여 sum이라는 변수에 넣어주기
			if(sum!=0){ //그 sum이 0이 아니라면
				insert(plist3,sum,newNode1->degree); //plist3이라는 리스트 덧셈의 결과를 넣을 리스트에 sum값(계수)과 그 당시의 degree(차수)를 저장
				newNode1=newNode1->next; //다음 차수로 넘어가기
				newNode2=newNode2->next; //다음 차수로 넘어가기
			}
		}
		else if(newNode1->degree>newNode2->degree){ //차수가 다른 상태에서 첫번째 식의 차수가 더 클 경우
			insert(plist3,newNode1->coef,newNode1->degree); //그대로 결과의 리스트에 더 큰 차수와 계수를 넣어준다
			newNode1=newNode1->next; // 저장이 끝난 식의 항이 다음 차수로 넘어가도록
		}
		else{ //두번째 식의 차수가 더 클 경우
			insert(plist3,newNode2->coef,newNode2->degree); //위와 마찬가지로 두번째 식의 차수가 더 클 경우 더 큰 차수와 계수를 넣어줌
			newNode2=newNode2->next; //다음 차수로 넘어가도록
		}
	}
	//둘중 하나의 식이 끝나면 남은 항들을 그대로 뒤에 붙이기만 하면 됨
	while(newNode1!=NULL){ //newNode1의 함수가 위에서 끝나지 않았다면 끝날때까지
		insert(plist3,newNode1->coef,newNode1->degree); //나머지의 계수와 차수를 그대로 저장해주기
		newNode1=newNode1->next; //newNode1이 반복문을 돌며 계속 다음것을 가리킬 수 있도록
	}
	while(newNode2!=NULL){ //newNode2의 함수가 위에서 끝나지 않았다면 끝날때까지
		insert(plist3,newNode2->coef,newNode2->degree); //나머지의 계수와 차수를 그대로 저장
		newNode2=newNode2->next; //newNode2가 반복문을 돌며 계속 다음것을 가리킬 수 있도록
	}
}

void Poly_Print(List*plist){ //출력해주기
	Node*p=plist->head; //처음부터 출력하기위해 head를 넣어줌
	while(p!=NULL){
		printf("%d * %d ",p->coef,p->degree);
		p=p->next;
	}
}

