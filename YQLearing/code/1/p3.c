#include <stdio.h>

int isRy(int n){
	if((n%4==0)&&(n%100!=0|n%400==0))
		return 1;
	else
		return 0;
}

int main(){
	int n;
	scanf("%d",&n);
	if(isRy(n)==1)
		printf("该年为闰年!\n");
	else
		printf("该年不为闰年!\n");
	
	return 0;
}