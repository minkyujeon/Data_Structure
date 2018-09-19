#include "header.h"

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
	node*tmp=NULL;
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
//===========================graph data structure end====================

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



vertex* new_vertex(int x, int y) {
   vertex* tmp = (vertex*)malloc(sizeof(vertex));
   tmp->degree = NULL;
   tmp->next = NULL;
   tmp->x=x;
   tmp->y=y;

   return tmp;
}

arcNode* new_arcNode(int arc, int x, int y) {
   arcNode* tmp = (arcNode*)malloc(sizeof(arcNode));
   tmp->nextArc=NULL;
   tmp->x=x;
   tmp->y=y;
   tmp->arc = arc;

   return tmp;
}
graph* create_graph() {
	graph* g = (graph*)malloc(sizeof(graph));
	g->start = NULL;
	return g;	
}

void insert_vertex(graph* g, int x, int y) {
   vertex* tmp = new_vertex(x,y);
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

