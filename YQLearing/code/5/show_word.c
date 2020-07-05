#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int *p = NULL;

/*16x16  智能家居*/
unsigned char word[4][32] = {{0x20,0x00,0x3E,0x7C,0x48,0x44,0x08,0x44,0xFF,0x44,0x14,0x44,0x22,0x7C,0x40,0x00,
0x1F,0xF0,0x10,0x10,0x10,0x10,0x1F,0xF0,0x10,0x10,0x10,0x10,0x1F,0xF0,0x10,0x10},{},{},{}}; //存储“智”字的模

void draw_point(int x, int y, int color)
{	
	if(x >= 0 && x < 800 && y >=0 && y < 480)
	{
		*(p + x + y * 800) = color;
	}
}
/*
	函数功能：在显示屏上显示字
	函数的参数：
		第一个参数show_x：是在屏幕上要显示的字的起始的横坐标
		第二个参数show_y：是在屏幕上要显示的字的起始的纵坐标
		第三个参数bytenum：一个字的模的字节数
		第四个参数word1：一个字节的具体的模的数据区域的首地址
		第五个参数perlinewide：字一行所占的位数
		第六个参数color：要在屏幕上显示的字的颜色
		
*/
void show_word(int show_x, int show_y,int bytenum,unsigned char* word1, int perlinewide,int color)
{
	int num,zj;
	int js = 0;
	int x,y;
	for(zj = 0; zj < bytenum/*32*/; zj++)				//代表字节的下标
	{
		for(num = 7; num >= 0; num--)
		{
			if(word1[zj] >> num & 0x01)
			{
				//画点
				x = js % perlinewide;  // x = (zj % 2) * 8 +(7 - num);
				y = js / perlinewide;  // y = zj / 2;
				draw_point(x + show_x,y + show_y, color);	
			}
			js++;
		}
	}
}

void show_all_word()
{
	for(i = 0; i < num; i++)
	{
		show_word(i * 20, 10, sizeof(word[i]),word[i],16,0x000000FF);
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
	//2.映射 
	p = mmap(NULL, 800*480*4, PROT_READ | PROT_WRITE, MAP_SHARED, lcd_fd, 0);
	if(p == MAP_FAILED)
	{
		perror("mmap error\n");
	}
	//3.刷底色
	int i,j;
	for(i = 0; i < 480; i++)
	{
		for(j = 0; j < 800; j++)
		{
			 draw_point(j, i, 0x0000FF00);
		}
	}
	
	//4.根据取模后的数据，把对应位置上的像素点显示与底色不同的颜色
	show_all_word();
	
	
	
	//5.收尾工作
	munmap(p, 800*480*4);
	close(lcd_fd);
	
	
	return 0;
}