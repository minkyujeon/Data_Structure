#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define NUM_VERTEX 5
#define NUM_EDGES 8

typedef struct point{
	int x;
	int y;
}Point;

typedef struct node{
	int v;//vertex 번호 -> 미로에서 (x,y)좌표로 변환
	int weight; //가중치(갈림길 노드까지의 거리)
	struct node*next;//up,down,left,right
}Node; //그래프노드로 만들어보기

typedef struct dijkstra{ //다익스트라 테이블 구조체
	int found;//(k)최단거리를 찾았는가? 1=yes, 0=no
	int distance;//최단거리(미로의 한 갈림길에서 다음 갈림길까지의 거리)
	int prev_vertex;//바로 직전에 어느 vertex를 거쳤는가(x,y좌표)
}Dijkstra;

Dijkstra dtable[NUM_VERTEX]; //표가 vertex 개수만큼 있어야함
Node*graph[NUM_VERTEX];

//vertex방문여부 표시 배열
//if visited[i]==1, visited
//				 0, otherwise
int visited[NUM_VERTEX]={0};

void addEdge(int v1, int v2, int w){//v1 : 출발vertex , v2 : 도착vertex , w : 가중치
	Node*new_one=(Node*)malloc(sizeof(Node));
	Node*cur=graph[v1];//v1에서 출발하는 노드로 이루어진 graph

	new_one->v=v2;
	new_one->next=NULL;
	new_one->weight=w;

	if(cur==NULL)//v1에 아무 vertex도 붙어있지 않은 상태
		graph[v1]=new_one;
	else{//v1에 이미 다른 vertex가 붙어있는 상태
		while(cur->next!=NULL)//마지막 노드까지
			cur=cur->next;//계속 다음걸로 넘어가면서
		cur->next=new_one;//다 넘어갔으면 그 다음으로 노드 연결
	}
}//결국 새로운 노드를 그래프에 연결해주는 함수

void initDTable(){ //테이블 초기화
	int i=0;
	for(i=0;i<NUM_VERTEX;i++){//VERTEX 개수만큼 초기화
		dtable[i].found=0;//못찾은 상태
		dtable[i].distance=9999;//최솟값으로 바로 대체될 수 있도록
		dtable[i].prev_vertex=-1;//이전에 거쳐온게 없음(초기화니깐),(x,y)좌표로!
	}
}

//아직 최단거리가 밝혀지지 않은 vertex 중 가장 작은 distance를 가진 vertex 반환
//모든 vertex의 최단거리가 알려졌을경우 return -1
int findDijkstraNextVertex(){
	int i=0;
	int smallest_distance=9999;//가장 짧은것의 거리(미로에서 갈림길을 만나기전 걸린 거리)
	int smallest_vertex=-1;//가장 짧은것의 vertex번호(x,y좌표)

	for(i=0;i<NUM_VERTEX;i++){//table을 다 뒤져서
		if((dtable[i].found==0) && (dtable[i].distance<smallest_distance)){//아직 가장 짧은 길이 정해지지 않았고 알려진 길이보다 더 작은 길이가 있다면
			smallest_vertex=i;//smallest_distance보다 작은 거리이므로 smallest_vertex, 미로에 적용한다면...'몇번째 미로 갈림길'이라는 식으로 가능할까(구조체에 변수 하나 더 추가하고 전역변수로 관리하면 가능할수도?)
			smallest_distance=dtable[i].distance;
		}
	}//조건문을 통과하지 못하면(다 이미 알려져있다면) -1반환
	return smallest_vertex;
}

void showDTable(){
	int i;
	for(i=0;i<NUM_VERTEX;i++){
		printf("%d : %d %d %d \n",i,dtable[i].found, dtable[i].distance, dtable[i].prev_vertex);
	}
}

//최단거리가 알려진 vertex가 있을 때 v가 들어감으로써 새로 갈 수 있는 노드(vertex)들 찾기(v에 붙어있는 노드들 이용)
void updateDTable(int v){//v에 붙어있는 노드를 이용해서..! 
	Node*cur=graph[v]; //v에 연결된 모든 노드 찾아서
	
	while(cur!=0){
		//최단거리가 알려지지 않았고,(found==0)
		//기존 알려진 거리보다 v를 통할경우가 더 가까우면, dtable을 업데이트
		if(dtable[cur->v].found==0 && (dtable[cur->v].distance>dtable[v].distance+cur->weight)){
			dtable[cur->v].distance=dtable[v].distance+cur->weight; //v를 거쳐서 가는 거리
			dtable[cur->v].prev_vertex=v;//이전 노드에 v 넣기
		}
		cur=cur->next;
	}
}

void doDijkstra(int v){ // v : 어디서부터 찾기 시작할지
	int next_vertex=-1;//최단거리가 밝혀진 vertex찾기
	dtable[v].distance=0;//시작 테이블은 바로0(시작하는 vertex의 최단거리는 0)

	while((next_vertex=findDijkstraNextVertex())!=-1){//찾은경우
		dtable[next_vertex].found=1;//최단거리를 찾았다고 표시
		updateDTable(next_vertex);//dtable 업데이트(이전 경로보다 짧은 길이 발견되면 대체)
	}
	showDTable();
}

int main(){

	addEdge(0,1,1); //마지막 1 : reverse가능하도록(양방향... but 미로는 양방향 없도록 하자)
	addEdge(0,2,3);
	addEdge(0,4,5);
	addEdge(1,2,2);
	addEdge(1,4,4);
	addEdge(2,4,6);
	addEdge(2,3,7);
	addEdge(3,4,8);

	initDTable();

	doDijkstra(0);//0번에서 갖는 모든 최단거리 찾기(괄호 안의 수는 1,2,..출발점에따라 달라짐)
}