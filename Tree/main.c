#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <Windows.h>

void gotoxy(int x,int y){
	COORD pos={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

typedef struct treeNode{
	int data;
	struct treeNode *left, *right;
}TreeNode;

int calc_direc_size(TreeNode*node, char *s){
	int left_size=0, right_size=0;
	printf("%s ",s);
	if(node==NULL){
		printf("  NULL return \n");
		return 0;
	}
	else{
		printf("   node : %d \n", node->data);
		left_size+=calc_direc_size(node->left,"left");
		right_size+=calc_direc_size(node->right,"right");
		
		return(node->data + left_size + right_size);
	}
}

void preorder(TreeNode*node,char*s,int x, int y){
	printf("%s ",s);

	if(node!=NULL){
		gotoxy(x,y);
		printf("[%3d] \n", node->data);
		Sleep(700);
		preorder(node->left,"left",x-15,y+4);
		preorder(node->right,"right",x+15,y+4);
	}
}

void inorder(TreeNode *node, char*s, int x, int y){
	if(node!=NULL){
		inorder(node->left,"left",x-15,y+4);
		gotoxy(x,y);
		printf("[%3d] \n", node->data);
		Sleep(700);
		inorder(node->right,"right",x+15,y+4);
	}
}

void postorder(TreeNode *node, char*s, int x, int y){
	if(node!=NULL){
		postorder(node->left,"left",x-15,y+4);
		postorder(node->right,"right",x+15,y+4);
		gotoxy(x,y);
		printf("[%3d]\n",node->data);
		Sleep(700);
	}
}

int showmenu(){
	printf("*****************\n");
	printf("1. preorder \n");
	printf("2. inorder \n");
	printf("3. postorder \n");
	printf("4. directory 계산(postorder)\n");
	printf("0. 종료\n");
	printf("*****************\n");
	return 0;
}

int main(){
	TreeNode n8={30,NULL,NULL};
	TreeNode n7={20,NULL,NULL};
	TreeNode n6={500,NULL,NULL};
	TreeNode n5={200,NULL,NULL};
	TreeNode n4={40,&n7,&n8};
	TreeNode n3={100,&n5,&n6};
	TreeNode n2={50,&n4,NULL};
	TreeNode n1={0,&n2,&n3};
	int menu='1';
	int pos_x=60,pos_y=2;

	while(menu!='0'){
		showmenu();
		printf("menu:");
		menu=getchar();
		fflush(stdin);
		system("cls");

		switch(menu){
		case '1' : preorder(&n1,"root",pos_x,pos_y);
			break;
		case '2' : inorder(&n1,"root",pos_x,pos_y);
			break;
		case '3' : postorder(&n1,"root",pos_x,pos_y);
			break;
		case '4' : printf("디렉토리의 크기=%d\n",calc_direc_size(&n1,"root"));
			break;
		case '0' : break;
		default : printf("메뉴 : 0~4\n");
			break;
		}
	}
	return 0;
}
