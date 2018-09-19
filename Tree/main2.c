#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
 
#define MAX_WORD_SIZE     100
#define MAX_MEANING_SIZE 200
 
// 데이터 형식
typedef struct e {
    char word[MAX_WORD_SIZE];        // 키필드
    char meaning[MAX_MEANING_SIZE];
} element;
// 노드의 구조
typedef struct treeNode {
    element key;
    struct treeNode *left, *right;
} TreeNode;
 
// 만약 e1 > e2 -> 1 반환
// 만약 e1 == e2 -> 0  반환 
// 만약 e1 < e2 -> -1 반환
int compare(element e1, element e2)
{
    return strcmp(e1.word, e2.word);
}
// 이진 탐색 트리 출력 함수
void display(TreeNode *p)
{
    if( p != NULL ) {
        printf("("); 
        display(p->left);
        printf("%s", p->key.word);
        display(p->right);
        printf(")");
    }
}
// 이진 탐색 트리 탐색 함수
TreeNode *search(TreeNode *root, element key) 
{    
    TreeNode *p=root;
    
    if(p==NULL) return p;
    if(compare(key, p->key) == 0)  return p;
    if(compare(key, p->key) == -1) search(p->left, key);
    else search(p->right, key);
 
    /* 반복
    while(p != NULL){ 
        switch(compare(key, p->key)){
        case -1:
            p = p->left;
            break;
        case 0:
            return p;
        case 1:
              p = p->right;
            break;
        }
    } 

    return p;     // 탐색에 실패했을 경우 NULL 반환
    */
    } 
// key를 이진 탐색 트리 root에 삽입한다. 
// key가 이미 root안에 있으면 삽입되지 않는다.
void insert_node(TreeNode **root, element key) 
{
    TreeNode *p, *t; // p는 부모 노드, p는 자식 노드 
    TreeNode *n;     // n은 새로운 노드
    TreeNode *tmp;
    t = *root;
    p = NULL;
 
 
    // 탐색을 먼저 수행 
    while (t != NULL){
      if( compare(key, t->key)==0 ) return;
      p = t;
      if( compare(key , t->key)<0 ) t = t->left;
      else t = t->right;
    }
    
 
 
    // item이 트리 안에 없으므로 삽입 가능
    n = (TreeNode *) malloc(sizeof(TreeNode));
    if( n == NULL ) return;
    // 데이터 복사
    n->key = key;
    n->left = n->right = NULL;
    // 부모 노드와 링크 연결
    if( p != NULL ) {
        if( compare(key, p->key)<0 ) p->left = n;
        else p->right = n;
    }
    else *root = n;
}
// 삭제 함수
void delete_node(TreeNode **root, element key)
{
    TreeNode *p, *child, *succ, *succ_p, *t;
 
    // key를 갖는 노드 t를 탐색, p는 t의 부모노드
    p = NULL;
    t = *root;
    while( t != NULL && compare(t->key, key) != 0 ){
        p = t;
        t = ( compare(key, t->key)<0 ) ? 
                t->left : t->right;
    }
    if( t == NULL ) {     // 탐색트리에 없는 키
        printf("key is not in the tree");
        return;
    }
    // 단말노드인 경우
    if( (t->left==NULL) && (t->right==NULL) ){ 
        if( p != NULL ){
            if( p->left == t )     p->left = NULL;
            else   p->right = NULL;
        }
        else   *root = NULL; // 부모노드가 없으면 루트
    }
    // 하나의 자식만 가지는 경우
    else if((t->left==NULL)||(t->right==NULL)){
        child = (t->left != NULL) ? t->left : t->right;
        if( p != NULL ){ // 부모노드를 자식노드와 연결 
            if( p->left == t ) p->left = child;
            else p->right = child;
        }
        else *root = child;
    }
    else{        // 두개의 자식을 가지는 경우
        // 오른쪽 서브트리에서 후속자를 찾는다.
        succ_p = t;
        succ = t->right;
        // 후속자를 찾아서 계속 왼쪽으로 이동한다.
        while(succ->left != NULL){
            succ_p = succ;
            succ = succ->left;
        }
        // 후속자의 부모와 자식을 연결 
        if( succ_p->left == succ )    succ_p->left = succ->right;
        else         succ_p->right = succ->right;
        // 후속자를 현재 노드로 이동한다.
        t->key = succ->key;
        t = succ;
    }
    free(t);
}
//
void menu()
{
   printf("**************\n");
   printf("i: 입력\n");
   printf("d: 삭제\n");
   printf("s: 탐색\n");
   printf("p: 출력\n");
   printf("q: 종료\n");
   printf("**************\n");
}
// 이진 탐색 트리를 사용하는 영어 사전 프로그램 
int main()
{
    char command;
     element e;
    TreeNode *root=NULL;
    TreeNode *tmp;
 
    do{
        menu();
           command = getchar();
        fflush(stdin);
 
        switch(command){
        case 'i':
            printf("단어:");
            gets(e.word);
            printf("의미:");
            gets(e.meaning);
            insert_node(&root, e);
            break;
        case 'd':
            printf("단어:");
            gets(e.word);
            delete_node(&root, e);
            break;
        case 'p':
            display(root);
            printf("\n");
            break;
        case 's':
            printf("단어:");
            gets(e.word);
            tmp=search(root, e);
            if( tmp != NULL )
                printf("의미:%s\n", tmp->key.meaning);
            else printf("못 찾았음! \n");
            break;
        }
        
    } while(command != 'q');
}
