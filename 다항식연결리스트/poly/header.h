typedef struct node{
	int coef;
	int degree;
	struct node*pre; //이전 노드를 가리킴
	struct node*next; //다음 노드를 가리킴
}Node;

Node*new_Node(int coef, int degree);
void insert_front(Node**head, int coef, int degree);
void insert_back(Node**tail, int coef, int degree);
void insert_middle(Node*head, int coef, int degree);
void input(Node**head, Node**tail,int co, int de, int n);
void output_1(Node*head);
void output_2(Node*tail);
void Poly_Add(Node*head1, Node*head2, Node**head3, Node**tail3);
void Poly_Sub(Node*head1, Node*head2, Node**head3, Node**tail3);

