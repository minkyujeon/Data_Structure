#include <stdio.h>
#include <malloc.h>

typedef struct matrix{
	int row;
	int col;
	int data;
}mat;

void input(mat*p, int n){
	int i=0;
	for(i=0;i<n;i++){
			printf("행 : ");
			scanf_s("%d",&(p[i].row));
			printf("열 : ");
			scanf_s("%d",&(p[i].col));
			printf("값 : ");
			scanf_s("%d",&(p[i].data));
			printf("\n");
	}
}

void add(mat*a,mat*b,mat*result){
	int i=0,j=0,tmp=0;
	while(i<3 && j<3){
		if(a[i].row == b[j].row && a[i].col == b[j].col){
			result[tmp].data=a[i].data+b[j].data;
			result[tmp].col=a[i].col;
			result[tmp].row=a[i].row;
			tmp++;
		}
		else{
			result[tmp].data=a[i].data;
			result[tmp].row=a[i].row;
			result[tmp].col=a[i].col;
			tmp++;

			result[tmp].data=b[j].data;
			result[tmp].row=b[j].row;
			result[tmp].col=b[j].col;
			tmp++;
		}
		i++;
		j++;
	}
}

void output(mat*result, int n){
	int i=0,j=0;

	for(i=0;i<n;i++){
		printf("행 : %d, 열 : %d, 값 : %d \n",result[i].row,result[i].col,result[i].data);
	}
}
int main(void){
	int i=0,j=0;
	mat*a=NULL;
	mat*b=NULL;
	mat*result=NULL;

	printf("행렬 a 값 입력 : \n");
	a=(mat*)malloc(sizeof(mat)*3); //0이 아닌 data 3개 {{1,0,0},{0,1,0},{0,0,3}} 가정
	input(a,3);
	printf("행렬 b 값 입력 : \n");
	b=(mat*)malloc(sizeof(mat)*3); //0이 아닌 data 3개 {{0,0,0}.{0,0,3},{4,0,1}} 가정
	input(b,3);

	result=(mat*)malloc(sizeof(mat)*5);
	add(a,b,result);
	output(result,5); //{{1,0,0},{0,1,3},{4,0,4}}의 결과 예상

	free(a);
	free(b);
	free(result);
	return 0;
}