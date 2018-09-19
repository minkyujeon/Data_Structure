#include <stdio.h>

//총 호출횟수를 저장할 전역변수
int cc=1;

//1,2,3,5,8,13,21, .....

long fib_linear(int n){
	if(n==1){
		printf("1");
		return 1;
	}
	return fib_linear_re(1, 2, n-2);
}

long fib_linear_re(int a, int b, int nth){
	cc++;
	printf("%d \n",a);
	if(nth<=0){
		printf("nth : %d\n",b);
		return b;
	}
	return fib_linear_re(b, a+b,nth-1);
}

long fib_re(int n){
	cc++;

	printf("fib_re(%d)호출 \n",n);
	if(n==1){
		printf("fib(1) : 1반환\n");
		return 1;
	}
	if(n==2){
		printf("fib(2) : 2 반환\n");
		return 2;
	}
	else
		return (fib_re(n-1)+fib_re(n-2));
}
int fib_iter(int n){ //반복문으로
	int ret=0;
	int i=0,temp=0,current=1, last=0;

	if(n<2) ret=n;
	else{
		for(i=2;i<=n;i++){
			temp=current;
			current+=last;
			last=temp;
		}
		ret=current;
	}
	return ret;
}
		
long fib_re_tri(int n){
	cc++;

	printf("fib_re_tri(%d) 호출 \n",n);
	if(n==1)return 1;
	if(n==2)return 2;
	if(n==3)return 3;
	else return(fib_re_tri(n-1)+fib_re_tri(n-2)+fib_re_tri(n-2));

}

int main(){
	long val;
	val=fib_linear(5);
	printf("%d, total count %d\n",val, cc);
	getchar();

	cc=0;
	val=fib_re(5);
	printf("%d, total count %d\n",val,cc);
	cc=0;
	val=fib_re_tri(6);
	printf("%d, total count %d \n",val, cc);
}