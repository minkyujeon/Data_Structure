#include <stdio.h>
void BubbleSort(int * arr, int n);

int main(void){

	int arr[7];
	int i;

	for(i=0; i<7; i++)
	{
		printf("입력: ");
		scanf("%d", &arr[i]);
	}

	BubbleSort(arr, 7);

	for(i=0; i<7; i++)
		printf("%d ", arr[i]);

	return 0;;
}

void BubbleSort(int * arr, int n) //오름차순 버블Sort
{
	int i, j, temp;

	for(i=0; i<n-1; i++)
	{
		for(j=0; j<(n-i)-1; j++)
		{
			if(arr[j]>arr[j+1])
			{
				temp=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp;
			}
		}
	}
}
