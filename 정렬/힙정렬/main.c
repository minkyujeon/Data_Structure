#include <stdio.h>

typedef struct heap{
	int key[10];
	int heap_size;
}HeapType;

void init(HeapType*heap){
	heap->heap_size=0;
}

void insert_heap(HeapType*heap, int data){ //최대 힙 삽입
	int i=0;
	i=++(heap->heap_size); //마지막 index 자리에 먼저 삽입하기 위해 설정
	
	while(i!=1 && data>heap->key[i/2]){ //root 노드가 아닐때까지, 입력된 data가 부모노드보다 작아질 때까지 계속 올라감
		heap->key[i]=heap->key[i/2];//자리를 찾아감
		i/=2;
	}
	heap->key[i]=data;//찾은 index자리에 data넣기
}

int delete_heap(HeapType*heap){ //최대 힙 삭제
	int parent=1, child=2;
	int data=0, tmp=0;

	data=heap->key[parent]; //root노드의 data
	tmp=heap->key[(heap->heap_size)--];//마지막 노드

	while(child<=heap->heap_size){//child index가 전체 힙 사이즈보다 크거나 같은 동안(단말노드까지 쭉 내려가면서 비교해야 하므로)
		if((child<heap->heap_size) && (heap->key[child]) <heap->key[child+1])//현재 노드의 자식노드 중 더 작은 자식노드가 있다면
			child++;
		if(tmp>=heap->key[child])//해당 노드가 자식 노드보다 크거나 같아지면 종료
			break;
		heap->key[parent]=heap->key[child];
		parent=child;
		child*=2;//계속 자식노드로 내려감
	}
	heap->key[parent]=tmp;//삭제된 후의 자리를 찾아서 tmp라는 data를 넣음
	return data;
}

void heap_sort(HeapType*heap,int*arr,int n){
	int i=0;

	for(i=0;i<n;i++)
		insert_heap(heap,arr[i]);

	for(i=heap->heap_size-1;i>=0;i--)
		arr[i]=delete_heap(heap);
}

int main(void){
	int arr[]={8,9,1,5,7,2,4,3,6,10};
	int i=0;
	HeapType heap;
	heap.heap_size=0;

	printf("before : ");
	for(i=0;i<10;i++)
		printf("%d ",arr[i]);
	printf("\n");
	
	heap_sort(&heap,arr,10);
	printf("after : ");
	for(i=0;i<10;i++)
		printf("%d ",arr[i]);
	printf("\n");

	return 0;
}
