## Ackermann 함수



A(m,n) =​	n+1				if m=0

​		A(m-1,1)			if m>0, n=0

​		A(m-1,A(m,n-1))	if m>0, n>0



- Recursion과 반복문을 통해 각각 구현하기



![1542785458586](C:\Users\jskst\AppData\Roaming\Typora\typora-user-images\1542785458586.png)