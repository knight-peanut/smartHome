#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	
	// 1.定义一个800*480个int的存储空间，将800*480个你要显示的颜色值存到这个定义的空间里面去
	int buf[480][800] = {0};
	int color[7] = {0x00FF0000,0x00FFFF00,0x00FF00FF,0x0000FFFF,0x00FFFFFF,0x00000000,0x0000FF00};
	int i,j,num;
	for(num = 0; num < 7; num++)  //代表要显示的颜色值
	{
		for(i = 0; i < 480; i++)  //行
		{
			for(j = 0; j < 800; j++) //列
			{
				buf[i][j] = color[num];
			}
		}
		
		// 2.打开帧缓冲设备文件
		int lcd_fd = open("/dev/ubuntu_lcd",O_RDWR);
		if(lcd_fd < 0)
		{
			printf("open lcd_fd error\n");
		}
		
		// 3.将这个存储颜色值的空间里面的颜色值写到帧缓冲文件中去
		int ret = write(lcd_fd,buf,800*480*4);
		if(ret < 800*480*4)
		{
			printf("write lcd_fd error\n");
		}
		
		
		// 4.关闭帧缓冲文件
		int value = close(lcd_fd);
		if(value == -1)
		{
			printf("close lcd_fd error\n");
		}
		
		sleep(2);
		
	}
	
	
	
	
	return 0;
}