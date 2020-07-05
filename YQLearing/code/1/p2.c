#include <stdio.h>

int fbs(int n){
	return n>1? n+fbs(n-1):1;
}

int main(){
	int n;
	scanf("%d",&n);
	printf("累加得到：%d\n",fbs(n));
	
	return 0;
}