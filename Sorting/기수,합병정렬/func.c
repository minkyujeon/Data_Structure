#include "header.h"

void random(int arr[]){
	int i=0;
	srand(time(NULL));
	for(i=0;i<MAX;i++)
		arr[i]=(rand()%100000)+1; //1부터 100000사이로 랜덤숫자
}

void BubbleSort(int * arr, int n){ //오름차순 버블Sort
	int i, j, temp;

	for(i=0; i<n-1; i++){
		for(j=0; j<(n-i)-1; j++){
			if(arr[j]>arr[j+1]){
				temp=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp;
			}
		}
	}
}

void merge(int arr[],int left, int mid, int right){ //두 배열 합치기
	int front=left;
	int back=mid+1;
	int i;

	int*sorted=(int*)malloc(sizeof(int)*(right+1));
	int tmp=left;

	while(front<=mid && back<=right){//두 정렬 배열에서 작은것부터 앞으로 끼워넣음
		if(arr[front]<=arr[back]) 
			sorted[tmp]=arr[front++];
		else
			sorted[tmp]=arr[back++];
		tmp++;
	}

	if(front>mid){
		for(i=back;i<=right;i++){
			sorted[tmp]=arr[i];
			tmp++;
		}
	}
	else{
		for(i=front;i<=mid;i++){
			sorted[tmp]=arr[i];
			tmp++;
		}
	}
	for(i=left;i<=right;i++)
		arr[i]=sorted[i];

	free(sorted);
}

void MergeSort(int arr[], int left, int right){
	int mid;

	if(left<right){
		mid=(left+right)/2; //중간 지점 계산

		MergeSort(arr,left,mid);
		MergeSort(arr,mid+1,right);

		merge(arr,left,mid,right);
	}
}

void RadixSort(int*arr, int n){
	int i=0,j=0,max=0,exp=1,idx=0,k=0,tmp=0;
	int bucket[10][MAX]={0};
	int count[10]={0};

	for(i=0;i<n;i++){//최댓값 찾기
		if(arr[i]>max)
			max=arr[i];
	}

	while(max/exp>=1){
		for(i=0;i<10;i++) //버킷안의 수의 개수 초기화
			count[i]=0;

		for(j=0;j<n;j++){//버킷에 담기
			idx=(arr[j]/exp)%10; //자리에 맞는 숫자뽑기
			bucket[idx][count[idx]]=arr[j]; //추출한 숫자를 버킷에 저장
			count[idx]=count[idx]+1; //같은 버킷에 담기는 수의 개수
		}
		
		for(i=0;i<10;i++){ //버킷에 있던 수를 원래 배열에 다시 저장
			for(k=0;k<count[i];k++){
				arr[tmp]=bucket[i][k];
				tmp++;
			}
		}
		tmp=0;
		exp*=10;
	}
}

void sorted(int arr[]){
	int i=0;
	for(i=0;i<MAX;i++)
		printf("%d ",arr[i]);
}