## Polynomial

다항식을 double linked list를 이용하여 생성하고 덧셈, 뺄셈 기능 추가

- 항을 추가할때 앞, 중간, 뒤에서 추가하는 함수
- 오름차순, 내림차순 출력 함수
- 덧셈, 뺄셈 함수



main.c

- 실행

header.h

- 함수 선언
- 더블 연결리스트를 구현하기 위해 구조체에 계수, 차수 외에도 pre,next를 추가



func.c

- 함수 정의(구현)

- Node*new_Node(int coef, int degree) - 노드를 생성하는 함수. 인자로 계수와 차수를 넣어 바로 초기화할 수 있도록 함