#include <stdio.h>
#include <sys/types.h>         
#include <sys/socket.h>
#include <linux/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

int tx_fd[1024] = {0};
int i = 0;




void * task(void *ar)
{	
	int sockfd = *(int *)ar;
	//5.read 
	char buf[1024] = {0};
	while(1)
	{
		int ret = read(sockfd, buf,1024);
		if(ret == -1)
		{	
			perror("read sockefd fail\n");
			continue;
		}
		if(ret != 0)
		{
			printf("read's content is %s\n",buf);
			
		}
		
	}
	close(sockfd);
}





int main()
{
	//1.socket：创建一个套接字
	int sockefd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockefd == -1)
	{
		perror("creat socket fail\n");
		return -1;
	}
	//2.bind:把一个套接字和网络地址 绑定在一起。
	struct sockaddr_in a;
	a.sin_family = AF_INET;
	a.sin_port = htons(10520);
	a.sin_addr.s_addr = inet_addr("172.23.137.156");
	int num = bind(sockefd, (struct sockaddr *)&a,sizeof(struct sockaddr));	
	if(num == -1)
	{
		perror("bind fail\n");
		return -1;
	}
			
	//3.listen:让套接字进入一个“监听模式”
	num = listen(sockefd, 5);
	if(num == -1)
	{
		perror("listen fail\n");
		return -1;
	}
	
	
	//4.accept：接收客户端的连接
	struct sockaddr ad;
	socklen_t addl;
	
	while(1)
	{	
		tx_fd[i] = accept(sockefd, &ad, &addl);  //如果没有客户端来连接会等待客户端来连接 程序会阻塞在这里
		if(tx_fd[i] == -1)
		{
			perror("accept fail\n");
			return -1;
		}
		struct sockaddr_in *ab = (struct sockaddr_in*)&ad; 
		
		printf("port is %d\n",ntohs(ab->sin_port));
		
		char *ip =inet_ntoa(ab->sin_addr);
		printf("ip is %s\n",ip);

		pthread_t id;
		int n = pthread_create(&id, NULL, task, (void *)&tx_fd[i]);
		if(n != 0)
		{
			perror("create thread fail\n");
		}
		i++;	
	}
	


	
	
	//6.close:"四路挥手"
	close(sockefd);
	
	return 0;
}





