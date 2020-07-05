#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

int *p = NULL;


void draw_point(int x, int y, int color)
{	
	if(x >= 0 && x < 800 && y >= 0 && y < 480)
	{
		*(p + x + y * 800) = color; //颜色值给到映射区域的空间中去
	}
	
}

int main()
{
	//1.打开帧缓冲设备文件
	int lcd_fd = open("/dev/ubuntu_lcd",O_RDWR);
	if(lcd_fd < 0)
	{
		perror("open lcd_fd error\n");
	}
	//2.将打开后的帧缓冲设备文件映射到进程的地址空间中去
	p = mmap(NULL, 800*480*4, PROT_READ | PROT_WRITE, MAP_SHARED,lcd_fd, 0);
	if(p == MAP_FAILED)
	{
		perror("mmap error\n");
	}
	//3.再把颜色值写入到映射区域中去
	int i,j;
	for(i = 0; i < 480; i++)			//行
	{
		for(j = 0; j < 800; j++)		//列
		{
			draw_point(j, i, 0x0000FF00);
		}
	}
	
	//4.收尾工作 
		//解除映射 
		munmap(p, 800*480*4);
		//关闭文件
		close(lcd_fd);
		
	
	
	
	return 0;
}

