#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *test(void *ar)
{
	while(1)
	{
		printf("this  is  son  thread\n");
		sleep(3);
	}
}


int main()
{
	printf("hello\n");
	
	pthread_t id;
	
	int n = pthread_create(&id, NULL,test, NULL);
	if(n != 0)
	{
		perror("create thread fail\n");
		return -1;
	}
	long int *p = (long int *)&id;
	printf("id is %ld\n",*p);
	while(1)
	{
		printf("this is main thread\n");
		sleep(3);
	}
	
	return 0;
}






