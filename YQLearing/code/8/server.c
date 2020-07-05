#include <stdio.h>
#include <sys/types.h>         
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<linux/socket.h>
#include <unistd.h>

int main()
{
	//1.socket：创建一个套接字
	int socketfd0 = socket(AF_INET, SOCK_STREAM, 0);
	if(socketfd0 == -1)
	{
		perror("creat socketfd0 fail\n");
		return -1;
	}
	//2.bind:把一个套接字和网络地址 绑定在一起。
		struct sockaddr_in a; 
		a.sin_family = AF_INET;
		a.sin_port = htons(10086);
		a.sin_addr.s_addr = inet_addr("192.168.0.110");	
		
	int num = bind(socketfd0, (struct sockaddr *)&a,sizeof(struct sockaddr));
	if(num == -1)
	{
		perror("bind address fail\n");
		return -1;
	}
	//3.listen:让套接字进入一个“监听模式”
	num = listen(socketfd0, 5);
	if(num == -1)
	{
		perror("set listen fail\n");
		return -1;
	}

	//4.accept：接收客户端的连接
	struct sockaddr ad;
	socklen_t adl;
	int txfd  = accept(socketfd0, &ad, &adl); //等待客户端连接，如果没有客户端连接
	if(txfd == -1)								//程序会停止在这里等待（即程序阻塞在这里）
	{
		perror("accept fail\n");
	}
			
	//5.write 
	char buf[6] = "hello";
	num = write(txfd,buf,5);
	if(num == -1)
	{
		perror("write txfd fail\n");
	}
	
	  //read 
	
	
	//6.close:"四路挥手"
	close(txfd);
}