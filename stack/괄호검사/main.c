#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack{
	char stack[100];
	int top;
}StackType;

void init(StackType*s){
	s->top=-1;
}

int is_empty(StackType*s){
	return (s->top==-1);
}

int is_full(StackType*s){
	return(s->top == 99);
}

void push(StackType*s, char item){
	if(is_full(s)){
		printf("스택 포화 에러\n");
		exit(1);
	}
	else
		s->stack[++(s->top)]=item;
}

char pop(StackType*s){
	if(is_empty(s)){
		printf("스택이 비었습니다\n");
		exit(1);
	}
	else
		return s->stack[(s->top)--];
}

int check(char*input){
	StackType s;
	char a, b;
	int i=0,n=strlen(input);
	init(&s);
	for(i=0;i<n;i++){//문자열 길이만큼 반복문 돌면서
		a=input[i];
		switch(a){
		case '(':
		case '{':
		case '[':
			push(&s,a);
			break;
		case ')':
		case '}':
		case ']':
			if(is_empty(&s)){ //stack이 비어있었다면
				return -1;
			}
			else{
				b=pop(&s);
				if(b=='(' && a!=')' || b=='{' && a!='}' || b == '[' && a!=']'){//닫는괄호가 이전괄호와 짝이 맞는지!(안맞으면 에러)
					return -1;
				}
				else
					break;
			}
		}
	}
	
	if(is_empty(&s))
		return 0;
	else
		return -1;
}

int main(void){
	int i=0;
	char input[100]={'0'};

	printf("문자열 입력 : ");
	fgets(input,100,stdin);
	
	if(check(input)==0) printf("괄호가 적절함");
	else printf("괄호가 적절하지 않음");

	return 0;
}
