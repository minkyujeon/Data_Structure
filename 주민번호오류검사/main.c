#include<stdio.h>

void check_ID(char id[14],char weight[13]);

int main(void){
	int i=0,j=0;
	char id[14]={0};
	char weight[13]={'2','3','4','5','6','7','8','9','2','3','4','5'}; // 가중치
	int sum=0;

	printf("주민등록번호를 입력하시오 : ");
	scanf_s("%s",id,sizeof(id));

	check_ID(id,weight);


	return 0;
}

void check_ID(char id[14],char weight[13]){

	int i=0,j=0;
	int check=0;
	int sum=0;

	printf("주민번호의 오류를 검사합니다. %s\n",id);

	for(i=0;i<12;i++){
		sum+=((id[i]-'0')*(weight[i]-'0'));
	}

	check=(11-(sum%11))%10;
	printf("주민번호 마지막 : %c\n",id[12]);
	printf("check : %d\n",check);
	if(check==(id[12]-'0'))
		printf("correct!!");
	else printf("False!!");
}