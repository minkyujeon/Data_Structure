typedef struct Node{
	int data;
	struct Node*next;
}Node;

int show_menu(); //메뉴 출력
Node*new_node(); //노드 생성
int ListLength(Node*head); //리스트 길이 출력
void insert_front(Node**head, int data); //list 앞에 삽입
void insert_back(Node**tail,int data); //list 뒤에 삽입
void insert_middle(Node*head,int data); //list 중간에 삽입
int search(Node*head,int data); //원하는 값의 index출력
void Delete(Node**head, Node**tail, int data); //삭제
void show(Node*head); //현재 상태 출력
int isEmpty(Node*head); //비어있는 여부 출력