#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define NUM_VERTEX 5
#define NUM_EDGES 8

typedef struct point{
	int x;
	int y;
}Point;

typedef struct vertex{
	Point p;//vertex 번호 -> 미로에서 (x,y)좌표로 변환
	struct vertex*next;//각각의 출발 vertex간 연결
	struct arcnode*degree; //arc 노드의 포인터(하나의 출발점에 연결되어 있는 노드들 서로 연결)
}Vertex;

typedef struct arcnode{
	Point p;//좌표
	int arc;//arc 가중치(갈림길  노드까지의 거리)
	struct arcnode*next_arc;//출발 vertex에 연결되어 있는 각각의 노드들 연결
}ArcNode;

typedef struct dijkstra{ //다익스트라 테이블 구조체
	int found;//(k)최단거리를 찾았는가? 1=yes, 0=no
	int distance;//최단거리(미로의 한 갈림길에서 다음 갈림길까지의 거리)
	int prev_vertex;//바로 직전에 어느 vertex를 거쳤는가(x,y좌표)
}Dijkstra;

typedef struct _dtable{
	Point p;//x,y좌표
	Dijkstra dij;//다익스트라 구조체
}Dtable;

Dtable dtable[NUM_VERTEX]; //표가 vertex 개수만큼 있어야함

//Vertex* new_vertex(Point p);
//ArcNode* new_arcNode(int arc, Point p);
//void insert_vertex(graph* g, Point p);
//void insert_edge(vertex* v, int arc, Point p);
//void print_vertex(graph* g);
void addEdge(Point p1, Point p2, int arc); //p1 : 출발 vertex, p2 : 도착 vertex, arc : 가중치, 길이
void initDTable();
Point findDijkstraNextVertex();
void showDTable();
void updateDTable(Point p);
void doDijkstra(Point p);