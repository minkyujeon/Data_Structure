#include <stdio.h>

int power_1(int x, int n){//exponential by for loop
	int i;
	int r=1;

	for(i=0;i<n;i++)
		r=r*x;
	return (r);
}

int power_2(int x, int n){//exponential by recursion
	if(n==0) return 1;
	else if((n%2)==0) //even
		return power_2(x*x,n/2);
	else if((n%2)==1) //odd
		return x*power_2(x*x,(n-1)/2);
}