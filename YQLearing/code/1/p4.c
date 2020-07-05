#include <stdio.h>

int isFs(int n){
	int a = n%10; // 个位数
	int b = (n/10)%10; //十位数
	int c = n/100; //百位数
	
	if(a*a*a+b*b*b+c*c*c==n)
		return 1;
	else
		return 0;
}

int main(){
	printf("1000以内的水仙花数有:");
	for(int i=1;i<1000;i++){
		if(isFs(i))
			printf("%d\t",i);
	}
	printf("\n");

	return 0;
}