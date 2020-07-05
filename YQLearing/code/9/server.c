#include <stdio.h>
#include <sys/types.h>         
#include <sys/socket.h>
#include <linux/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>


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
	a.sin_port = htons(10086);
	a.sin_addr.s_addr = inet_addr("192.168.0.110");
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
	
	int tx_fd = accept(sockefd, &ad, &addl);  //如果没有客户端来连接会等待客户端来连接 程序会阻塞在这里
	if(tx_fd == -1)
	{
		perror("accept fail\n");
		return -1;
	}
			
	//5.write 
	char buf[6] = "hello";
	num = write(tx_fd,buf,5);
	if(num == -1)
	{
		perror("write tx_fd error\n");
		return -1;
	}
	  //read 
	
	
	//6.close:"四路挥手"
	close(tx_fd);
	close(sockefd);
	
	return 0;
}





