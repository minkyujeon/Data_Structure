#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct _node{
	int data;
	struct _node *next; //오른쪽 노드를 가리키는 포인터 변수
	struct _node *pre; //왼쪽 노드를 가리키는 포인터 변수
}Node;
