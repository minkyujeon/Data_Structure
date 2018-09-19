#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define NUM_VERTEX 8
#define MAZE_MAX 10

//===================stack data structure======================
typedef struct node__ {
	int x;
	int y;
	struct node__* next;
}node;

typedef struct stack__ {
	node* top;
}stack;


//===================stack data structure end===================

typedef struct point{
	int x;
	int y;
}Point;

typedef struct vertex_{
	int x, y;
	//Point p;//vertex 번호 -> 미로에서 (x,y)좌표로 변환
	struct vertex_*next;//각각의 출발 vertex간 연결
	struct arcNode_*degree; //arc 노드의 포인터(하나의 출발점에 연결되어 있는 노드들 서로 연결)
}vertex;

typedef struct arcNode_{
	//Point p;//좌표
	int x,y;
	int arc;//arc 가중치(갈림길 노드까지의 거리)
	struct arcNode_*nextArc;//출발 vertex에 연결되어 있는 각각의 노드들 연결
}arcNode;

typedef struct graph_ {
   struct vertex_* start; //출발 graph하나로 쭉 연결된 그래프
}graph;

typedef struct dijkstra{ //다익스트라 테이블 구조체
	int found;//(k)최단거리를 찾았는가? 1=yes, 0=no
	int distance;//최단거리(미로의 한 갈림길에서 다음 갈림길까지의 거리)
	Point prev_vertex;//바로 직전에 어느 vertex를 거쳤는가(x,y좌표)
}Dijkstra;

typedef struct _dtable{
	Point p;//x,y좌표
	Dijkstra dij;//다익스트라 구조체
}Dtable;

Dtable dtable[NUM_VERTEX];

node* new_node(int x, int y);
void push(stack* s, int x, int y);
void pop(stack* s, int* x, int* y);
stack* create_stack();
int print_arcNode(vertex *v);
void add_edge(vertex* v, char maze[MAZE_MAX][MAZE_MAX]);
void print_graph(graph *g);
vertex* new_vertex(int x, int y);
arcNode* new_arcNode(int arc, int x, int y);
graph* create_graph();
void insert_vertex(graph* g, int x, int y);
void insert_edge(vertex* v, int arc, int x, int y);
void print_graph(graph *g);
void addEdge(Point p, int arc);
void initDTable(vertex*start,int n);
Point findDijkstraNextVertex(int n); // n : vertex 개수
void showDTable(int n);
Dtable*d_table(vertex*v);
void updateDTable(vertex*v,int n);//vertex가 새로 들어감으로써 
void doDijkstra(vertex*start);