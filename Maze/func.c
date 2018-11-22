#include "header.h"

void init_q(Queue *q) {

	q->front = q->rear = NULL;
}

int q_is_empty(Queue *q) {

	return (q->front == NULL);

}

void enqueue(Queue *q, int x, int y) {

	QueueNode *node = (QueueNode*)malloc(sizeof(Queue));
	if (node == NULL) printf("메모리 할당 실패\n");
	else {
		node->next = NULL;
		node->x = x;
		node->y = y;

		if (q_is_empty(q)) {
			q->front = node;
			q->rear = node;
		}
		else {
			q->rear->next = node;
			q->rear = node;
		}
	}
}

Point dequeue(Queue *q) {

	QueueNode *tmp = q->front;
	Point item;
	if (q_is_empty(q)) printf("큐가 비어 있습니다.\n");
	else {

		item.x = tmp->x;
		item.y = tmp->y;

		q->front = q->front->next;
		if (q->front == NULL)
			q->rear = NULL;

		return item;
	}

}


node* new_node(int x, int y) {
	node* tmp = (node*)malloc(sizeof(node));
	tmp->x = x;
	tmp->y = y;
	tmp->next = NULL;

	return tmp;
}

void push(stack* s, int x, int y) {
	node* tmp = new_node(x, y);

	tmp->next = s->top;
	s->top = tmp;
}

void pop(stack* s, int* x, int* y) {
	node* tmp;
	if (s->top == NULL)
		printf("pop error");
	else {
		*x = s->top->x;
		*y = s->top->y;
		tmp = s->top;
		s->top = s->top->next;
		free(tmp);
	}
}

stack* create_stack() {
	stack *tmp = (stack*)malloc(sizeof(stack));
	tmp->top = NULL;

	return tmp;
}

vertex* new_vertex(int x, int y) {
	vertex* tmp = (vertex*)malloc(sizeof(vertex));
	tmp->degree = NULL;
	tmp->next = NULL;
	tmp->x = x;
	tmp->y = y;

	return tmp;
}

arcNode* new_arcNode(int arc, int x, int y) {
	arcNode* tmp = (arcNode*)malloc(sizeof(arcNode));
	tmp->nextArc = NULL;
	tmp->x = x;
	tmp->y = y;
	tmp->arc = arc;

	return tmp;
}

graph* create_graph() {
	graph* g = (graph*)malloc(sizeof(graph));
	g->start = NULL;
	return g;
}

void insert_vertex(graph* g, int x, int y) {
	vertex* tmp = new_vertex(x, y);
	vertex* check;

	if (g->start == NULL) {
		g->start = tmp;
	}
	else {
		check = g->start;
		while (check->next != NULL) {
			check = check->next;
		}
		check->next = tmp;
	}
}
//add vertex to graph

void insert_edge(vertex* v, int arc, int x, int y) {
	arcNode* tmp = new_arcNode(arc, x, y);
	arcNode* check;

	if (v->degree == NULL) {
		v->degree = tmp;
	}
	else {
		check = v->degree;
		while (check->nextArc != NULL) {
			check = check->nextArc;
		}
		check->nextArc = tmp;
	}
}
//add edge to vertex

int print_arcNode(vertex *v) {
	arcNode *tmp = v->degree;

	if (tmp == NULL) return -1;

	printf("(%d, %d)  %d  ", tmp->x, tmp->y, tmp->arc);
	while (tmp->nextArc != NULL) {

		tmp = tmp->nextArc;
		printf("(%d, %d)  %d  ", tmp->x, tmp->y, tmp->arc);

	}

	printf("\n");

	return 0;

}

void print_graph(graph *g) {
	vertex* tmp = g->start;

	printf("(%d, %d)     ", tmp->x, tmp->y);
	print_arcNode(tmp);
	while (tmp->next != NULL) {
		tmp = tmp->next;
		printf("(%d, %d)     ", tmp->x, tmp->y);

		if (print_arcNode(tmp) == -1) printf("\n");

	}

}

void add_edge(vertex* v, char maze[MAZE_MAX][MAZE_MAX]) {
	stack* s = create_stack();
	char copy[MAZE_MAX][MAZE_MAX];
	int x, y;
	int i, j, k;
	int count;	//갈림길의 갯수를 판별하는 변수
	int length; // vertex간의 거리를 재는 변수

	for (i = 0; i < MAZE_MAX; i++) {
		for (j = 0; j < MAZE_MAX; j++) {
			copy[i][j] = maze[i][j];
		}
	}

	copy[v->y][v->x] = 'e';

	if (copy[v->y - 1][v->x] == '0')
		push(s, v->y - 1, v->x);
	if (copy[v->y + 1][v->x] == '0')
		push(s, v->y + 1, v->x);
	if (copy[v->y][v->x - 1] == '0')
		push(s, v->y, v->x - 1);
	if (copy[v->y][v->x + 1] == '0')
		push(s, v->y, v->x + 1);
	//v의 갈림길의 시작점들을 스택에 push

	while (s->top != NULL) {
		pop(s, &y, &x);	//그 중에 하나를 pop 하고
		length = 0;

		while (1) {	//다음 vertex까지의 길을 찾아간다
			copy[y][x] = 'e';
			count = 0;

			if (y - 1 >= 0) {
				if (copy[y - 1][x] == '0') {
					push(s, y - 1, x);
					count++;
				}
			}
			if (y + 1 < MAZE_MAX) {
				if (copy[y + 1][x] == '0') {
					push(s, y + 1, x);
					count++;
				}
			}
			if (x - 1 >= 0) {
				if (copy[y][x - 1] == '0') {
					push(s, y, x - 1);
					count++;
				}
			}
			if (x + 1 < MAZE_MAX) {
				if (copy[y][x + 1] == '0') {
					push(s, y, x + 1);
					count++;
				}
			}
			length++;

			if (count > 1 || count == 0) {
				insert_edge(v, length, x, y);

				for (k = 0; k < count; k++) {
					pop(s, &y, &x);
				}

				break;
			}	//vertex를 찾았으면 그래프에 추가하고 다음 갈림길로 간다
			else
				pop(s, &y, &x);

		}
	}
}


//============미로 출력=============

void printMaze(char m[MAZE_MAX][MAZE_MAX])
{
	int i=0,j=0;
	for (i = 0; i < MAZE_MAX; i++) {
		for (j = 0; j < MAZE_MAX; j++) {
			switch (m[i][j]) {
			case '1':   //벽
				printf("■");   break;
			case '0':   //길
				printf("  ");   break;
			default:
				printf(" %c", m[i][j]);
			}
		}
		printf("\n");
	}
}
//==========dfs==========
vertex *search_v(graph *g, int x, int y) {//vertex 노드를 찾아주는 함수. vertex에 연결되어 있는 arcNode를 따라가다 해당 arcNode와 같은 x,y값을 가지고 있는 vertex값을 찾아 리턴해준다.
	vertex *v;
	v = g->start;
	while (v != NULL) {
		if (v->x == x && v->y == y) {//입력된 좌표값과 같은 vertex가 나오면
			return v;//v 리턴
		}
		else {
			v = v->next;//나올때까지 그 다음 vertex로 옮김
		}
	}
	return NULL;
}

int check_exist(stack* s, int x, int y) {//스택에 해당 노드가 존재하는지 확인하는 함수
	node* curr = s->top;
	while (curr != NULL) {
		if (curr->x == x && curr->y == y) {//입력된 좌표값과 같을 경우
			return 1;
		}
		curr = curr->next;//찾을때 까지 다음 노드 확인
	}
	return 0;
}

void print_stack2(node *node) {//재귀함수를 통해 스택의 맨 끝에서부터 해당 x,y값을 출력하게 해준다
	if (node == NULL) {
		return;
	}
	print_stack2(node->next);
	printf("(%d %d)", node->x, node->y);
}

void print_stack(stack* s) {
	//node* node = s->top;
	//printf("print path\n");
	//while (node != NULL) {
	//   printf("(%d %d) ", node->x, node->y);
	//   node = node->next;
	//}
	print_stack2(s->top);
}

void DFS(graph *g) {
	int x, y;      //더미
	stack* s;   //노드를 넣을 스택 선언
	vertex* init_node;
	node* current_node ;
	s = (stack*)malloc(sizeof(stack));   //스택 할당
	s->top = NULL;

	init_node = g->start;      //그래프의 시작노드와 init_node를 같다고 설정
	push(s, init_node->x, init_node->y);      //처음 노드는 미로의 입구이므로 무조건 스택에 push
	current_node = s->top;   //스택의 현재 노드를 가르키는 current node


	while (current_node != NULL) {// 현재 노드가 0이 아닐때
		vertex* find_degree_from = search_v(g, current_node->x, current_node->y);   //search_v를 통해 찾은 current 와 같은 좌표를 가진 vertex를 저장
		arcNode* next_edge = find_degree_from->degree;   //find_degree_from에 연결된 arcNode를 next_edge에 저장

		while (next_edge != NULL && check_exist(s, next_edge->x, next_edge->y)) {      //next_edge가 null이 아니고, 스택에 존재한다면
			next_edge = next_edge->nextArc;      //다음 arcNode로 넘어감
		}

		if (next_edge == NULL) {      //arc Node노드가 더이상 없다면 (다음 경로를 찾을 수 없다)
			pop(s, &x, &y); //->??? x, y 값을 어떻게 알아여..?
			current_node = s->top;
		}
		else {      //arcNode 노드가 있을 경우(다음 경로를 찾을 수 있다)
					//printf("push %d %d\n", next_edge->x, next_edge->y);
			find_degree_from->degree = next_edge->nextArc;   //지나온 곳은 넘어감
			push(s, next_edge->x, next_edge->y);   //스택에 push
			current_node = s->top;
			if (next_edge->x == 9 && next_edge->y == 8) {   //미로 탈출에 성공했을 경우
				printf("DFS result : ");
				print_stack(s);   //경로 출력
				break;
			}
		}
	}
}

//====bfs====
void bfs(graph *g) {//도착노드 좌표

	vertex* v, *check;
	arcNode *w;
	Point item;
	int x, y;

	Queue q;
	init_q(&q);

	v = g->start;
	x = v->x;
	y = v->y;

	visited[x][y] = 1;
	pre[x][y].x = -2;
	pre[x][y].y = -2;
	//printf("%d, %d\n", x, y);

	enqueue(&q, x, y);


	while (!q_is_empty(&q)) {

		item = dequeue(&q);
		x = item.x;
		y = item.y;

		for (v = g->start; v->x != x||v->y != y; v = v->next);

		for (w = v->degree; w != NULL; w = w->nextArc) {

			if (visited[w->x][w->y] == 0) {
				visited[w->x][w->y] = 1;
				//printf("%d, %d\n", w->x, w->y);
				enqueue(&q, w->x, w->y);
			}
			if(pre[x][y].x!=w->x&&pre[x][y].y != w->y)
				if (dis[w->x][w->y] == 0 || dis[w->x][w->y] > dis[x][y] + w->arc) {
					dis[w->x][w->y] = dis[x][y] + w->arc;
					pre[w->x][w->y].x = x;
					pre[w->x][w->y].y = y;
				}
		}
	}
}

//========dijkstra========
void initDTable(vertex*start,int n){ //테이블 초기화(테이블 개수는 정해지지X, vertex 개수만큼 만들면 됨)->vertex개수를 n으로 정해줌!
	int i=0;
	vertex*tmp=start;
	vertex*pre=start;
	dtable[i].p.x=tmp->x;
	dtable[i].p.x=tmp->x;
	dtable[i].p.y=tmp->y;
	dtable[i].dij.found=0;
	dtable[i].dij.distance=0;//최솟값으로 바로 대체될 수 있도록
	dtable[i].dij.prev_vertex.x=-1;//이전에 거쳐온게 없음(초기화니깐),(x,y)좌표로!
	dtable[i].dij.prev_vertex.y=-1;
	
	while (tmp->next != NULL) {
		i++;
		tmp = tmp->next;
		dtable[i].p.x=tmp->x;
		dtable[i].p.y=tmp->y;
		dtable[i].dij.found=0;
		dtable[i].dij.distance=9999;//최솟값으로 바로 대체될 수 있도록
		dtable[i].dij.prev_vertex.x=-1;
		dtable[i].dij.prev_vertex.y=-1;
	}
}

//아직 최단거리가 밝혀지지 않은 vertex 중 가장 작은 distance를 가진 vertex 반환
//모든 vertex의 최단거리가 알려졌을경우 return -1
Point findDijkstraNextVertex(int n){
	int i=0;
	int smallest_distance=9999;//가장 짧은것의 거리(미로에서 갈림길을 만나기전 걸린 거리)
	Point smallest_vertex={-1,-1};//가장 짧은것의 vertex번호(x,y좌표)
	
	for(i=0;i<n;i++){//table을 다 뒤져서
		if((dtable[i].dij.found==0) && (dtable[i].dij.distance<smallest_distance)){//아직 가장 짧은 길이 정해지지 않았고 알려진 길이보다 더 작은 길이가 있다면
			smallest_vertex.x=dtable[i].p.x;//smallest_distance보다 작은 거리이므로 smallest_vertex, 미로에 적용한다면...dtable의 i번째 좌표값을 넣어주기
			smallest_vertex.y=dtable[i].p.y;
			smallest_distance=dtable[i].dij.distance;
		}
	}//조건문을 통과하지 못하면(다 이미 알려져있다면) (-1,-1)반환
	return smallest_vertex;
}

void showDTable(int n){
	int i=0;
	printf("dtable\n");
	printf(" 현재 좌표| 찾았는가 최단 거리 바로 전 좌표 \n");
	for(i=0;i<n;i++){
		printf(" (%d,  %d)  |  %4d    %6d     (%d %d) \n",dtable[i].p.x, dtable[i].p.y ,dtable[i].dij.found, dtable[i].dij.distance, dtable[i].dij.prev_vertex.x, dtable[i].dij.prev_vertex.y);
	}
}

//최단거리가 알려진 vertex가 있을 때 새로운 vertex가 들어감으로써 새로 갈 수 있는 노드(vertex)들 찾기(v에 붙어있는 노드들 이용)
void updateDTable(vertex*v,int n){//v는 update할 vertex, n은 vertex의 개수(테이블 수) , vertex v에 연결된 모든 arc들 검사해야함
	int i=0,t=0,p=0;
	vertex*cur_ver=v;
	arcNode*cur_arc=v->degree;//cur에는 vertex에 해당하는 arc정보가 들어감
	
	for(i=0;i<n;i++){//들어온 vertex v의 dtable상 위치=t
		if((v->x==dtable[i].p.x) && (v->y==dtable[i].p.y))
			t=i;
	}
	//최단거리가 알려지지 않았고,(found==0)
	//기존 알려진 거리보다 t를 통할경우가 더 가까우면, dtable을 업데이트
	while(cur_arc!=NULL){
		for(i=0;i<n;i++){
			if((dtable[i].p.x==cur_arc->x) && (dtable[i].p.y==cur_arc->y))//table에서 해당하는 위치를 찾아서
				p=i;
		}
		if((dtable[p].dij.found==0) && (dtable[p].dij.distance > dtable[t].dij.distance+cur_arc->arc)){
			dtable[p].dij.distance=dtable[t].dij.distance+cur_arc->arc; //v를 거쳐서 가는 거리
			dtable[p].dij.prev_vertex.x=v->x;//이전 노드에 p 넣기
			dtable[p].dij.prev_vertex.y=v->y;
		}
		cur_arc=cur_arc->nextArc; //한 vertex 내에서 arc를 찾기 위해
	}
}

void doDijkstra(vertex*start){ // start : 시작할 vertex
	int i=0,j=0,t=0;
	vertex*cur=start;
	Point next_vertex={start->x,start->y};
	
	while((next_vertex.x=findDijkstraNextVertex(8).x)!=-1 && (next_vertex.y=findDijkstraNextVertex(8).y)!=-1){//찾은경우	
		for(j=0;j<8;j++){
			if((dtable[j].p.x==next_vertex.x) && (dtable[j].p.y==next_vertex.y))
				t=j;
		}//next_vertex에 해당하는 테이블 위치 찾아서
		dtable[t].dij.found=1;//찾은 값에 1을 넣기(찾았다는걸 표시)
		while((cur->x!=next_vertex.x) || (cur->y!=next_vertex.y))//update함수에 넣어줄 vertex 찾기위해(하나만 달라도 다른거니까)
			cur=cur->next;
		updateDTable(cur,8);//dtable 업데이트(이전 경로보다 짧은 길이 발견되면 대체)
	}
	showDTable(8);
}
//========dijkstra-----------

void print_path(int x, int y) {//도착 좌표 입력

	if (pre[x][y].x == -1 && pre[x][y].y == -1) {

		printf("도착지점까지 경로가 존재하지 않습니다.\n");
		return;
	}
	if (pre[x][y].x == -2 && pre[x][y].y == -2) {

		printf("BFS 탐색 최단 경로 : (%d, %d)", x, y);
		return;

	}
	print_path(pre[x][y].x, pre[x][y].y);
	printf("  (%d, %d)", x, y);

}