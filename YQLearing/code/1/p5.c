#include <stdio.h>

int isSuN(int n){
	for(int i=2;i<n;i++)
		if(n%i==0)
			return 0;
	return 1;
}

int main(){
	printf("5到100的素数有：");
	for(int i=5;i<100;i++){
		if(isSuN(i))
			printf("%d ",i);
	}
	printf("\n");
	
	return 0;
}