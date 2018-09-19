#include "header.h"

int main(void){
	int arr_bubble[MAX]={0};
	int arr_merge[MAX]={0};
	int arr_radix[MAX]={0};
	int i=0;
	time_t start, end;
	
	random(arr_bubble);
	start=clock();
	BubbleSort(arr_bubble,sizeof(arr_bubble)/sizeof(int));
	end=clock();
	printf("bubble : %f √ \n",(double)(end-start)/CLOCKS_PER_SEC);
	
	random(arr_merge);
	start=clock();
	MergeSort(arr_merge,0,sizeof(arr_merge)/sizeof(int)-1);
	end=clock();
	printf("merge : %f √ \n",(double)(end-start)/CLOCKS_PER_SEC);

	random(arr_radix);
	start=clock();
	RadixSort(arr_radix,sizeof(arr_radix)/sizeof(int));
	end=clock();
	printf("radix : %f √ \n",(double)(end-start)/CLOCKS_PER_SEC);

	return 0;
}