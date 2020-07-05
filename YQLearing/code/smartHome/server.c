#include <stdio.h>
#include <sys/types.h>         
#include <sys/socket.h>
#include <linux/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

int tx_fd[1024] = {0};
int i = 0;

char curtain[3] = {'0', '0', '\0'}; // 保留服务器窗帘的状态，默认是关
char door[3] = {'1', '0', '\0'}; // 保留服务器门的状态，默认是关
char lamp[3] = {'2', '0', '\0'}; // 保留服务器灯的状态，默认是关

 // 根据客户端发送过来开关的状态去改变状态
void * task(void *ar)
{	
	int sockfd = *(int *)ar;
	char r[3] = {0};
	while(1)
	{
		// read
		int ret = read(sockfd, r, 2);
		if(ret == -1)
		{	
			perror("read sockefd fail\n");
			continue;
		}
		if(ret != 0) // 如果读到数据了
		{
			int i = 0;
			while (tx_fd[i] != 0) // 如果读到了数据就给每个客户端都发送数据
			{
				// int ret = read(sockfd, r, 2);
				// if(ret == -1)
				// {	
				// 	perror("read sockefd fail\n");
				// 	continue;
				// }
				// if(ret != 0)
				// {
					if (r[0] == '0') // 如果是窗帘
					{
						if (r[1] == '0') // 如果发过来的是关状态
						{
							// write
							char w[3] = {'0', '1', '\0'}; // 把窗帘更新为开状态
							int num = write(tx_fd[i], w, 2);
							if(num == -1)
							{
								perror("write fail\n");
								exit(1);
							}
							printf("curtain open\n");
							strcpy(curtain, w); // 保留窗帘状态
						}
						else if (r[1] == '1') // 如果发过来是开状态
						{
							// write
							char w[3] = {'0', '0', '\0'}; // 把窗帘更新为关状态
							int num = write(tx_fd[i], w, 2);
							if(num == -1)
							{
								perror("write fail\n");
								exit(1);
							}
							printf("curtain close\n");
							strcpy(curtain, w); // 保留窗帘状态
						}
					}
					else if (r[0] == '1') // 如果是门
					{
						if (r[1] == '0') // 如果发过来的是关状态
						{
							// write
							char w[3] = {'1', '1', '\0'}; // 把门更新为开状态
							int num = write(tx_fd[i], w, 2);
							if(num == -1)
							{
								perror("write fail\n");
								exit(1);
							}
							printf("door open\n");
							strcpy(door, w); // 保留门状态
						}
						else if (r[1] == '1') // 如果发过来的是开状态
						{
							// write
							char w[3] = {'1', '0', '\0'}; // 把门更新为关状态
							int num = write(tx_fd[i], w, 2);
							if(num == -1)
							{
								perror("write fail\n");
								exit(1);
							}
							printf("door close\n");
							strcpy(door, w); // 保留门状态
						}
					}
					else if (r[0] == '2') // 如果是灯
					{
						if (r[1] == '0') // 如果发过来的是关状态
						{
							// write
							char w[3] = {'2', '1', '\0'}; // 把灯更新为开状态
							int num = write(tx_fd[i], w, 2);
							if(num == -1)
							{
								perror("write fail\n");
								exit(1);
							}
							printf("lamp open\n");
							strcpy(lamp, w); // 保留灯状态
						}
						else if (r[1] == '1') // 如果发过来的是开状态
						{
							// write
							char w[3] = {'2', '0', '\0'}; // 把灯更新为关状态
							int num = write(tx_fd[i], w, 2);
							if(num == -1)
							{
								perror("write fail\n");
								exit(1);
							}
							printf("lamp close\n");
							strcpy(lamp, w); // 保留灯状态
						}
					}
					i++;
				// }
			}
		}
		// if (ret == 0) // 如果读到0代表与这个客户端的连接已经断开，跳出，并把断开了的文件描述符从数组中删掉
		// {
		// 	int x, y;
		// 	for (y = 0; y < i; y++)
		// 	{
		// 		if (tx_fd[y] == sockfd) // 先找到这个文件描述符
		// 		{
		// 			for (x = y; x < i; x++)
		// 			{
		// 				tx_fd[x] = tx_fd[x + 1]; // 把后面的文件描述符往前面挪
		// 			}
		// 		}
		// 	}
		// 	printf("client quit, sockfd is %d\n", sockfd);
		// 	break; // 跳出去关闭这个连接套接字
		// }
		
	}
	close(sockfd); // 四路挥手关闭
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
	a.sin_port = htons(10688);
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
		printf("%d\n", tx_fd[i]);
		struct sockaddr_in *ab = (struct sockaddr_in*)&ad; 
		
		printf("port is %d\n",ntohs(ab->sin_port));
		
		char *ip =inet_ntoa(ab->sin_addr);
		printf("ip is %s\n",ip);

		// 初始化窗帘，门，灯的状态
		// 发送窗帘状态信息
		write(tx_fd[i], curtain, 2);
		// 发送门状态信息
		write(tx_fd[i], door, 2);
		// 发送灯状态信息
		write(tx_fd[i], lamp, 2);


		// 并发出去读取数据并发送三个控件的状态
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





