#include"head.h"

int main(void){
	int i=0,j=0,n=0,a=0;
	int search=0;
	int num[20]={0};
	while(1){
		printf("===========메뉴==========\n");
		printf("1. 난수 20개 생성하기\n");
		printf("2. 현재 배열 출력하기\n");
		printf("3. 정렬하기\n");
		printf("4. 탐색하기\n");
		printf("5. 종료\n");
		printf("=========================\n\n");
		printf("메뉴를 입력하시오 : ");
		scanf_s("%d",&n);
		if(n==5){
			printf("종료합니다.\n");
			break;
		}
	switch(n){
		case 1:
			srand((unsigned)time(NULL));
	
			for(i=0;i<20;i++){
				num[i]=rand()%100+1;
			}
			break;
			case 2:
			print(num);
			break;
		case 3:
			printf("1. 선택정렬\n");
			printf("2. 버블정렬\n");
			scanf_s("%d",&a,sizeof(a));
	
			if(a==1)
				selection_sort(num);
			else if(a==2)
				bubble_sort(num);
			break;
		case 4:
			printf("1. 순차탐색\n");
			printf("2. 이진탐색\n");
			scanf_s("%d",&a,sizeof(a));
			printf("탐색할 값을 입력하시오 : ");
			scanf_s("%d",&search,sizeof(search));
			if(a==1)
				seq(num,search);
			else if(a==2)
				bin(num,search);
			break;
		}
	}
}