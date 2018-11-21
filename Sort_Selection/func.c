#include"head.h"

int min_index(int num[20]){//최솟값 인덱스 찾기
	int i=0,j=0;
	int min=0;
	for(i=0;i<20;i++){
		if(num[min]>num[i]){
			min=i;
		}
	}
	return min;
}

void random_num(int arr[20]){//random 추출
	int i=0;
	for(i=0;i<20;i++){
		arr[i]=rand()%100+1;
	}
}

void print(int num[20]){//현재 배열상태 출력
	int i=0;
	for(i=0;i<20;i++){
		printf("%d ",num[i]);
	}
	printf("\n");
}


void selection_sort(int num[20]){//선택정렬
	int i=0,j=0,min=0,temp=0, n=0,k=0;
	for(i=0;i<19;i++){//19번째 까지하면 마지막 수는 자동 정렬
		min=i;//최소값 index갱신
		print(num);
		for(j=i+1;j<20;j++){
			if(num[j]<num[min]){
				min=j;
			}
		}
		temp=num[min];
		num[min]=num[i];
		num[i]=temp;
	}
}

void bubble_sort(int num[20]){//버블정렬
	int i=0,j=0,temp=0;
	for(i = 0; i < 19; i++) { // 인접값 비교 회수를 제어하기 위해
		for(j = 0; j < 19; j++){// 인접값 비교 및 교환 
			if(num[j]>num[j+1]){//앞에 있는 인자가 뒤에 있는것보다 클 경우->자리바꿈
				temp=num[j];
				num[j]=num[j+1];
				num[j+1]=temp; 
			} 
		}print(num);//현황 출력 
	}
}

void seq(int num[20],int search){
	int i=0;
	int a=0,n=0;
	for(i=0;i<20;i++){
		if(num[i]==search){
			a=num[i];
			n=i;
		}

		else if(search>num[i] && search<num[i+1]){
			if(search-num[i]>num[i+1]-search)
				a=num[i+1];
			else
				a=num[i];
			n=i;
		}
	}
	printf("탐색 횟수 : %d\n",n);
	printf("탐색 결과 : %d\n",a);
}

void bin(int num[20],int search){
	int a=0,n=0,i=0;
	int low=0,middle=0;
	int high=19;

	while(low<=high){//비교할 수가 남아있을 때 까지
		middle=(low+high)/2;
		if(search==num[middle]){
			a=num[middle];
			n=i;
			break;
		}
		else if(search>num[middle])
			low=middle+1;
		else
			high=middle-1;
		i++;
	}
	printf("탐색 횟수 : %d\n",n);
	printf("탐색 결과 : %d\n",a);
}	