#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<linux/input.h>	


void touch_event(int fd)
{
	//2.读取信息
	struct input_event ev;
	int x = 0,y = 0;
	while(1)
	{
		int ret = read(fd, &ev, sizeof(ev));
		if(ret == -1)
		{
			perror("read touch_fd error\n");
		}
		//printf("read byte is %d\n",ret);
		if(ret != sizeof(ev))
		{
			continue;
		}
		//3.分析信息
		//printf("ev.type = %d, ev.code = %d, ev.value = %d\n",ev.type,ev.code,ev.value);
		
	
		if(ev.type == EV_ABS)		//触摸屏事件
		{
			if(ev.code == ABS_X)  //x事件
			{
				x = ev.value;	//代表横坐标
			}
			else if(ev.code == ABS_Y)  //y事件
			{
				y = ev.value;		//代表纵坐标
				//4.打印信息
				printf("(%d,%d)\n",x,y);
				
			}
			
			
		}
	}
	
	//5.关闭触摸屏
	close(fd);
}

int main()
{
	//1.打开触摸屏
	int touch_fd = open("/dev/ubuntu_event",O_RDWR);
	if(touch_fd < 0)
	{
		perror("open touch_fd error\n");
	}
	
	touch_event(touch_fd);
	

	return 0;
}