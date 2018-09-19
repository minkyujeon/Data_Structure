#include <stdio.h>
#include <stdlib.h> //malloc함수를 이용하기 위한 헤더 파일

struct list *create();
void print(struct list *head,int n);

struct list{
	int data;
	struct list *next;
};

struct list *create(){
	struct list *a,*b,*c;

	a = (struct list *)malloc(sizeof(struct list)); //포인터에는 따로 메모리가 없으니 메모리 할당
	b = (struct list *)malloc(sizeof(struct list));
	c = (struct list *)malloc(sizeof(struct list));

	a->data = 10;
	b->data = 20;
	c->data = 30;
	a->next = b;
	b->next = c;
	c->next = NULL;
	return a;
}

void print(struct list *head,int n){
	
	while(head){
		if(head->data == n) head = head->next;
		printf("%d\n",head->data);
		head = head->next;
	}
}

void main(){
	struct list *head; //첫번째 노드를 저장하는 구조체 포인터 
	int num;
	head = create();//head 도 struct 형의 포인터이니,create도 struct형의 포인터 함수로 해줘야만 한다
	printf("삭제할 노드의 data값을 입력하세요 ");
	scanf("%d",&num);
	print(head,num);
}
