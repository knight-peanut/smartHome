#include <stdio.h>
#include <sys/types.h>         
#include <sys/socket.h>
#include <linux/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
	//1.socket:
	int sockefd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockefd == -1)
	{
		perror("creat socket fail\n");
		return -1;
	}
	//2.bind：可要可不要
	//3.connect： 主动与TCP Server建立连接
				//“三次握手”
	struct sockaddr_in a; 
	//(struct sockaddr *)&a
		a.sin_family = AF_INET;
		a.sin_port = htons(10086);
		a.sin_addr.s_addr = inet_addr("192.168.0.110");
	int num = connect(sockefd, (struct sockaddr *)&a,sizeof(struct sockaddr));
	if(num == -1)
	{
		perror("connect fail\n");
		return -1;
		
	}
			
	//4.write 
	// read 
	char buf[6] = {0};
	num = read(sockefd,buf,5);
	if(num == -1)
	{
		perror("read fail\n");
		return -1;
	}

	printf("read's content is %s\n",buf);

	
			
	//5.close 
	close(sockefd);


	return 0;
}





