#include <stdio.h>
#include <time.h>

int factorial(int n){ //재귀호출을 이용-알고리즘이 간단함

	if(n<=1) return(1);
	else return(n*factorial(n-1));
}

int fact(int n){ //반복문 이용-속도가 빠르고 메모리 사용이 적음
	int i, f=1;
	if(n<=1) return(1);
	else{
		for(i=1;i<=n;i++)
			f=f*i;
		return f;
	}
}

int main(void){
	int n=0;
	clock_t start=0, end=0;

	scanf("%d",&n);
	start=clock();
	printf("factorial : %d\n",factorial(n));
	end=clock();
	printf("시간(재귀) : %lf\n",(double)end-start);

	start=clock();
	printf("fact : %d\n",fact(n));
	end=clock();
	printf("시간(반복) : %lf\n",(double)end-start);
	return 0;
}
