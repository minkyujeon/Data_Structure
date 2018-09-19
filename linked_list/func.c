#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "header.h"

int show_menu(){
   int menu = 0;
   printf("##############################################\n");
   printf("1. insert　  2. delete\n");
   printf("3. search　  4. length\n");
   printf("5. show      6. 종료\n");
   printf("##############################################\n");

   scanf("%d",&menu);
   return menu;
}

//노드 생성
Node*new_node(){
	Node*newNode=(Node*)malloc(sizeof(Node));
	newNode->data=0;
	newNode->next=NULL;

	return newNode;
}

int ListLength(Node*head){
	Node*cur=head;
	int count=0;
	while(cur!=NULL){
		count++;
		cur=cur->next;
	}
	return count-1;//맨 앞 더미변수(0) 뺀값
}

void insert_front(Node**head, int data){//head보다 작은 값이 들어왔을때 head의 앞부분에 삽입하는 함수.
	//head자체의 변경이 필요하므로 주소의 접근이 필요하다.
	//따라서 원래 Node*head로 main에서 선언했으므로 주소를 넘기기 위해 Node**head를 넘겨준다.
	Node*newNode=new_node();//노드 생성

	newNode->data=data;//데이터 초기화
	newNode->next=*head;//원래 head의 값이 새 노드의 next가 됨
	*head=newNode;//head를 새로 설정함
}

void insert_back(Node**tail,int data){//tail보다 큰 값이 들어왔을때 tail의 뒷부분에 삽입하는 함수.
	//위와 마찬가지의 이유로 Node**tail을 함수 인자로 넘겨준다.
	Node*newNode=new_node();
	newNode->data=data;//데이터 선언
	
	(*tail)->next=newNode;//원래 tail의 next값으로 새로운 노드가 들어감
	(*tail)=(*tail)->next;//새로 들어간 노드가 tail이됨
}

void insert_middle(Node*head,int data){//위 두가지 경우가 모두 아닌 중간에 삽입하는 함수
	//middle에 넣는 함수는 head나 tail을 직접 바꿔줄 일이 없다
	//따라서 주소를 넘기지 않아도 되고 삽입이 될 위치를 찾기 위해 처음 head값만 넘겨주어 찾도록한다.
	Node*p=head;//반복문을 돌면서 각각의 노드를 가리킬 구조체 포인터 p
	Node*newNode=new_node(); //새로 리스트에 추가할 노드

	while(p->next->data<=data)//insert할 위치를 찾기위해
		p=p->next;
	if(data==p->next->data){//중복을 막아줌
		printf("이미 존재\n");
		return;
	}
	newNode->data=data;
	newNode->next=p->next;//newNode의 next에 위치를 찾은것의 next를 연결
	p->next=newNode;//결국 'p'의 위치에 앞뒤로 연결
}

int search(Node*head,int data){
	Node*find=head;
	int idx=0;

	while(1){
		if(find->data==data){
			return idx;
			break;
		}
		else{
			find=find->next;
			idx++;
		}
	}
	return -1;
}

void Delete(Node**head, Node**tail, int data){
	Node*remove=*head;//맨 앞(head)부터 찾기위해(현재 헤드값은 더미노드(0))
	Node*pre=NULL;//삭제하기 위해 이전 값으로 삭제할 값 다음값을 연결해줘야함

	while(remove!=NULL){//끝까지 탐색
		if(remove->data==data){//지울값을 찾으면
			pre->next=remove->next;//그 지울 위치의 next값을 지울 위치의 이전 값에 넣음(연결을 위해)
			break;
		}
		else{
			pre=remove;//다음 노드로 계속 탐색을 위해
			remove=remove->next;
		}
	}
	free(remove);
}

void show(Node*head){
	Node*p=head;

	if(isEmpty(head)==0)
		printf("비어 있습니다.\n");
	else{
		while(p!=NULL){
			printf("%d ",p->data);
			p=p->next;
		}
	}
	printf("\n");
}

int isEmpty(Node*head){
	if(head->next==NULL)
		return 0;
	else
		return 1;
}


