#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define SIZE 6

typedef struct element{
	int r;//행
	int c;//열
}Element;

typedef struct node{
	Element data; //data 좌표
	struct node *left, *right, *up, *down;
}Node;

void new_Node(Node*root,int r, int c){
	Node*New;
	New=(Node*)malloc(sizeof(Node));
	root=New;
	root->data.r=r;
	root->data.c=c;
	New->down=NULL;
	New->left=NULL;
	New->right=NULL;
	New->up=NULL;
}

void generate_miro(Node*tree,int**miro){
	int x=0,y=0,r=0,c=0,n=0;
	Node*new_node1, *new_node2, *new_node3, *new_node4;

	while(miro[x][y]!=3){
		r=x;
		c=y;
		n=0;
		if(miro[r][c-1]==0){ //left
			new_Node(new_node1,r-1,c);
			tree->left=new_node1; //tree의 left를 새로운 노드와 연결
			new_node1->right=tree; //새로운 노드의 right를 tree에 연결
			miro[r][c-1]=1; //이미 지나온 길 1로 채우기
			n++;
		}
		if(miro[r][c+1]==0){ //right
			new_Node(new_node2,r,c+1);
			tree->right=new_node2; //tree의 right를 새로운 노드와 연결
			new_node2->left=tree; //새로운 노드의 left를 tree에 연결
			miro[r][c+1]=1;
			n++;
		}
		if(miro[r-1][c]==0){//up
			new_Node(new_node3,r-1,c);
			tree->up=new_node3;
			new_node3->down=tree;
			miro[r-1][c]=1;
			n++;
		}
		if(miro[r+1][c]==0){
			new_Node(new_node4,r+1,c);
			tree->down=new_node4;
			new_node4->up=tree;
			miro[r+1][c]=1;
			n++;
		}
	}
}

void postorder(Node*root){
	if(root){
		postorder(root->left);
		postorder(root->right);
		printf("%d",root->data);
	}
}


int main(void){
	int x=0,y=1,r=0,c=0;

	int miro[6][6]={
		{1,1,1,1,1,1},
		{2,0,0,0,0,1},
		{1,0,1,0,1,1},
		{1,1,1,0,0,3},
		{1,1,1,0,1,1},
		{1,1,1,1,1,1}
	};

	
	return 0;
}