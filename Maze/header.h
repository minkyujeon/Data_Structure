#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>

#define MAZE_MAX 10

typedef struct point {

	int x;
	int y;
}Point;

//=======queue========
typedef struct queuenode {

	int x, y;
	struct queuenode *next;
}QueueNode;

typedef struct queue {

	QueueNode *front;
	QueueNode *rear;
}Queue;

//===========stack ADT=========
typedef struct node__ {
	int x;
	int y;
	struct node__* next;
}node;

typedef struct stack__ {
	node* top;
}stack;
//=========graph=========

typedef struct vertex_ {
	struct vertex_* next;
	int x, y;
	struct arcNode_* degree;
}vertex;

typedef struct arcNode_ {
	int x, y;
	int arc;
	struct arcNode_* nextArc;
}arcNode;

typedef struct graph_ {
	struct vertex_* start;
}graph;

int visited[MAZE_MAX][MAZE_MAX] = { 0 };
int dis[MAZE_MAX][MAZE_MAX] = { 0 };
Point pre[MAZE_MAX][MAZE_MAX] = { -1, -1 };

typedef struct dijkstra{ //다익스트라 테이블 구조체
	int found;//(k)최단거리를 찾았는가? 1=yes, 0=no
	int distance;//최단거리(미로의 한 갈림길에서 다음 갈림길까지의 거리)
	Point prev_vertex;//바로 직전에 어느 vertex를 거쳤는가(x,y좌표)
}Dijkstra;

typedef struct _dtable{
	Point p;//x,y좌표
	Dijkstra dij;//다익스트라 구조체
}Dtable;

Dtable dtable[8];

void init_q(Queue *q);
void enqueue(Queue *q, int x, int y);
Point dequeue(Queue *q);
node* new_node(int x, int y);
void push(stack* s, int x, int y);
void pop(stack* s, int* x, int* y);
stack* create_stack();
vertex* new_vertex(int x, int y);
arcNode* new_arcNode(int arc, int x, int y);
graph* create_graph();
void insert_vertex(graph* g, int x, int y);
void insert_edge(vertex* v, int arc, int x, int y);
int print_arcNode(vertex *v);
void print_graph(graph *g);
void add_edge(vertex* v, char maze[MAZE_MAX][MAZE_MAX]);
void printMaze(char m[MAZE_MAX][MAZE_MAX]);

//==========dfs==========
vertex *search_v(graph *g, int x, int y);
int check_exist(stack* s, int x, int y);
void print_stack2(node *node);
void print_stack(stack* s);
void DFS(graph *g);
void bfs(graph *g);

//======dijkstra=====
void initDTable(vertex*start,int n);
Point findDijkstraNextVertex(int n);
void showDTable(int n);
void updateDTable(vertex*v,int n);
void doDijkstra(vertex*start);
void print_path(int x, int y);