#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int coef;
	int degree;
	struct node*pre; //이전 노드를 가리킴
	struct node*next; //다음 노드를 가리킴
}Node;

Node*new_Node(int coef, int degree){
	Node*newNode=(Node*)malloc(sizeof(Node));
	newNode->coef=coef;
	newNode->degree=degree;
	newNode->pre=NULL;
	newNode->next=NULL;

	return newNode;
}

void insert_front(Node**head, int coef, int degree){ //앞에 추가
	Node*newNode=new_Node(coef, degree);

	newNode->next=(*head);
	(*head)->pre=newNode;
	(*head)=newNode;	
}

void insert_back(Node**tail, int coef, int degree){
	Node*newNode=new_Node(coef,degree);

	(*tail)->next=newNode;
	newNode->pre=(*tail);
	(*tail)=(*tail)->next;
}

void insert_middle(Node*head, int coef, int degree){
	Node*p=head;
	Node*newNode=new_Node(coef,degree);

	while(p->next->degree>=degree)
		p=p->next;
	if(degree==p->next->degree){
		printf("이미 존재 \n");
		return;
	}
	
	newNode->coef=coef;
	newNode->degree=degree;

	//p 위치 다음에 넣으려 함!
	//newNode의 뒷부분을 p의 next와 연결
	newNode->next=p->next; //현재 newNode에 연결된 것이 없으므로 newNode의 next에 p의 next를 연결
	p->next->pre=newNode; //p의 next의 pre에 newNode를 끼워넣음
	//newNode의 앞부분을 p와 연결
	newNode->pre=p; 
	p->next=newNode; 
}

void input(Node**head, Node**tail,int co, int de, int n){
	int coe=0,deg=0,i=0;
	Node*p=NULL;
	p=new_Node(coe,deg);
	*head=*tail=p;
	
	if(n>0){ //일반 다항식에 입력
		for(i=0;i<n;i++){
			printf("계수 : ");
			scanf_s("%d",&coe);
			printf("차수 : ");
			scanf_s("%d",&deg);
			p=new_Node(coe,deg);

			//함수 인자로 이미 **가 들어왔으니 주소를 주기위해 &head, &tail이 아닌 head tail로 넘겨줌!
			if(deg>(*head)->degree) insert_front(head,coe,deg);//앞에 추가
			else if(deg<(*tail)->degree) insert_back(tail,coe,deg); //뒤에 추가
			else insert_middle(*head,coe,deg); //중간에 추가
		}
	}
	else{ //result 다항식에 넣기 위해
		printf("덧셈!!!!!!!!!!!!!!!!!");
		if(de>(*head)->degree)
			insert_front(head,co,de);  //앞에 추가
		else if(de<(*tail)->degree)
			insert_back(tail,co,de); //뒤에 추가
		else
			insert_middle(*head,co,de); //중간에 추가
	}
}

void output_1(Node*head){ //높은 차수 항부터출력
	Node*p=NULL;
	p=head;

	printf("높은 차수부터 ");
	printf("%dx^%d",p->coef, p->degree);
	p=p->next;
	while(p->next!=NULL){
		if(p->coef>0){
			printf("+");
			printf("%dx^%d",p->coef, p->degree);
		}
		else
			printf("%dx^%d",p->coef, p->degree);
		p=p->next;
	}
	printf("\n");
}

void output_2(Node*tail){ //낮은 차수 항부터 출력 (output1에서 next를 pre로 바꾸면됨
	Node*p=NULL;
	p=tail;

	printf("낮은 차수부터 ");
	printf("%dx^%d",p->coef, p->degree);
	p=p->pre;
	while(p!=NULL){
		if(p->coef>0){
			printf("+");
			printf("%dx^%d",p->coef, p->degree);
		}
		else
			printf("%dx^%d",p->coef, p->degree);
		p=p->pre;
	}
	printf("\n");
}

void Poly_Add(Node*head1, Node*head2, Node**head3, Node**tail3){
	Node*newNode1=head1; //식1
	Node*newNode2=head2; //식2
	int sum=0;
	
	//같은 차수일 경우 더해주고
	//다른 차수일 경우 차수가 큰걸 앞으로, 차수가 작은걸 뒤로 가도록 정렬하며 삽입
	
	while(newNode1 && newNode2){ //newNode1, newNode2중에서 어느 한 식이 NULL을 만날때까지(끝날때까지)
		if(newNode1->degree==newNode2->degree){ // 두 식에서 차수가 같다면
			sum=newNode1->coef+newNode2->coef; //각 계수를 더하여 sum이라는 변수에 넣어주기
			printf("sum : %d\n",sum);
			if(sum!=0){ //그 sum이 0이 아니라면
				insert_back(tail3,sum,newNode1->degree);
			}
				newNode1=newNode1->next; //다음 차수로 넘어가기
				newNode2=newNode2->next; //다음 차수로 넘어가기
		}
		else if(newNode1->degree>newNode2->degree){ //차수가 다른 상태에서 첫번째 식의 차수가 더 클 경우
			printf("coef2 : %d\n",newNode1->coef);
			insert_back(tail3,newNode1->coef,newNode1->degree);
			newNode1=newNode1->next; // 저장이 끝난 식의 항이 다음 차수로 넘어가도록
		}
		else{ //두번째 식의 차수가 더 클 경우
			printf("coef3 : %d\n",newNode2->coef);
			insert_back(tail3,newNode2->coef,newNode2->degree);
			newNode2=newNode2->next; //다음 차수로 넘어가도록
		}
	}
	//둘중 하나의 식이 끝나면 남은 항들을 그대로 뒤에 붙이기만 하면 됨
	while(newNode1!=NULL){ //newNode1의 함수가 위에서 끝나지 않았다면 끝날때까지
		input(head3,tail3,newNode1->coef,newNode1->degree,-1); //나머지의 계수와 차수를 그대로 저장해주기
		newNode1=newNode1->next; //newNode1이 반복문을 돌며 계속 다음것을 가리킬 수 있도록
	}
	while(newNode2!=NULL){ //newNode2의 함수가 위에서 끝나지 않았다면 끝날때까지
		input(head3,tail3,newNode2->coef,newNode2->degree,-1); //나머지의 계수와 차수를 그대로 저장
		newNode2=newNode2->next; //newNode2가 반복문을 돌며 계속 다음것을 가리킬 수 있도록
	}
}

void Poly_Sub(Node*head1, Node*head2, Node**head3, Node**tail3){
	Node*newNode1; //식1
	Node*newNode2; //식2
	int sub=0;

	newNode1=head1;
	newNode2=head2; //각각 처음부터 search하기 위해
	
	//같은 차수일 경우 더해주고
	//다른 차수일 경우 차수가 큰걸 앞으로, 차수가 작은걸 뒤로 가도록 정렬하며 삽입
	
	while(newNode1 && newNode2){ //newNode1, newNode2중에서 어느 한 식이 NULL을 만날때까지(끝날때까지)
		if(newNode1->degree==newNode2->degree){ // 두 식에서 차수가 같다면
			sub=newNode1->coef-newNode2->coef; //각 계수를 더하여 sum이라는 변수에 넣어주기
			if(sub!=0){ //그 sub가 0이 아니라면
				input(head3,tail3,sub,newNode1->degree,-1);
				newNode1=newNode1->next; //다음 차수로 넘어가기
				newNode2=newNode2->next; //다음 차수로 넘어가기
			}
		}
		else if(newNode1->degree>newNode2->degree){ //차수가 다른 상태에서 첫번째 식의 차수가 더 클 경우
			input(head3,tail3,newNode1->coef,newNode1->degree,-1);//그대로 결과의 리스트에 더 큰 차수와 계수를 넣어준다
			newNode1=newNode1->next; // 저장이 끝난 식의 항이 다음 차수로 넘어가도록
		}
		else{ //두번째 식의 차수가 더 클 경우(-붙이고 넣어주기)
			input(head3,tail3,(-newNode2->coef),newNode2->degree,-1); 
			newNode2=newNode2->next; //다음 차수로 넘어가도록
		}
	}
	//둘중 하나의 식이 끝나면 남은 항들을 그대로 뒤에 붙이기만 하면 됨
	while(newNode1!=NULL){ //newNode1의 함수가 위에서 끝나지 않았다면 끝날때까지
		input(head3,tail3,newNode1->coef,newNode1->degree,-1); //나머지의 계수와 차수를 그대로 저장해주기
		newNode1=newNode1->next; //newNode1이 반복문을 돌며 계속 다음것을 가리킬 수 있도록
	}
	while(newNode2!=NULL){ //newNode2의 함수가 위에서 끝나지 않았다면 끝날때까지
		input(head3,tail3,(-newNode2->coef),newNode2->degree,-1); //나머지의 계수에 -를 붙이고 차수를 그대로 저장
		newNode2=newNode2->next; //newNode2가 반복문을 돌며 계속 다음것을 가리킬 수 있도록
	}
}
