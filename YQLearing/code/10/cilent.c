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
		a.sin_port = htons(10520);
		a.sin_addr.s_addr = inet_addr("112.74.113.206");
	int num = connect(sockefd, (struct sockaddr *)&a,sizeof(struct sockaddr));
	if(num == -1)
	{
		
		perror("connect fail\n");
		return -1;
		
	}
			
	//4.write 
	// read 

	
	char buf[8] ="dwadwaw";
	while(1)
	{
		num = write(sockefd,buf,7);
		if(num == -1)
		{
			perror("write fail\n");
			return -1;
		}
		sleep(4);
	}
	

	

	
			
	//5.close 
	close(sockefd);


	return 0;
}





