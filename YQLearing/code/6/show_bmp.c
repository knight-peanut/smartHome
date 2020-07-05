#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int *p = NULL;

void draw_point(int x, int y, int color)
{	
	if(x >= 0 && x < 800 && y >=0 && y < 480)
	{
		*(p + x + y * 800) = color;
	}
}

//显示图片

void show_bmp(char *path, int x, int y)
{
	//3.打开图片文件
	int picture_fd = open(path,O_RDWR);
	if(picture_fd < 0)
	{
		perror("open picture_fd error\n");
	}
	//4.从图片文件的头获取图片文件的信息
		//从文件的头获取像素点的宽度
	int locat = lseek(picture_fd,0x12,SEEK_SET);
	if(locat == -1)
	{
		perror("lseek picture_fd error\n");
	}
	printf("location is %d\n",locat);
	int wide = 0; //保存像素点宽度
	int ret = read(picture_fd, &wide,4);
	if(ret == -1)
	{
		perror("read picture_fd error\n");
	}
	printf("read's byte is %d\n", ret);
	printf("picture's wide is %d\n", wide);
	
	//从文件的头获取像素点的高度
	locat = lseek(picture_fd,0x16,SEEK_SET);
	if(locat == -1)
	{
		perror("lseek picture_fd error\n");
	}
	printf("location is %d\n",locat);
	int height = 0; //保存像素点的高度
	ret = read(picture_fd, &height,4);
	if(ret == -1)
	{
		perror("read picture_fd error\n");
	}
	printf("read's byte is %d\n", ret);
	printf("picture's height is %d\n", height);
	
	//从文件的头获取像素点的色深
	locat = lseek(picture_fd,0x1C,SEEK_SET);
	if(locat == -1)
	{
		perror("lseek picture_fd error\n");
	}
	printf("location is %d\n",locat);
	short int colordeep = 0; //保存像素点的色深
	ret = read(picture_fd, &colordeep,2);
	if(ret == -1)
	{
		perror("read picture_fd error\n");
	}
	printf("read's byte is %d\n", ret);
	printf("picture's colordeep is %d\n", colordeep);
	
	int perlinebyte = 0; 	//每行的实际字节数
	int laizi = 0; 			//表示每行补的字节数
	if(wide * colordeep /8 % 4 != 0)
	{
		perlinebyte = wide * colordeep / 8 + 4 - (wide * colordeep /8 % 4 );
		laizi = 4 - (wide * colordeep /8 % 4 );
	}
	else
	{
		perlinebyte = wide * colordeep / 8;
		laizi = 0;
	}
	
	printf("laizi is %d\n",laizi);
	//5.从图片文件中读取数据到buf所指向的空间（buf所指向的空间是你自己定义的空间）
		//略过文件的头54个字节
	locat = lseek(picture_fd, 54, SEEK_SET);
	if(locat == -1)
	{
		perror("lseek picture_fd error\n");
	}
	printf("location is %d\n",locat);	
		//从图片文件中读取数据
	unsigned char buf[800*480*3] = {0};
	ret = read(picture_fd, buf,perlinebyte * height);
	if(ret == -1)
	{
		perror("read picture_fd error\n");
	}
	printf("read's yanse byte is %d\n", ret);

	//5.r g b  -》 a  r  g  b  将读取到的数据转换成开发板上32位色深的格式
	unsigned char a = 0; 
	int color = 0;
	int num = 0;
				 // buf[0]   b
				 // buf[1]   g     int
				 // buf[2]   r
	int i,j;
	
	for(i = 0; i < height; i++)	//行
	{
		for(j = 0; j < wide; j++) //列
		{	
			//将读取到的数据转换成开发板上32位色深的格式
			color  = a << 24 | buf[2 + num] << 16 |  buf[1 + num] << 8 | buf[0 + num];      //第0个像素点
							//  buf[5]		   buf[4]		 buf[3]	  	  //..1........
							// 8				7				6	      //..2........
							// 11				10				9
			//6.将转换以后的数据写入到帧缓冲设备文件中去
			draw_point(x + j, y + height - 1 - i, color);
			num = num + 3;			
		}
		num = num + laizi;
	}
	
	//关闭图片文件
		close(picture_fd);
	
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
	//图片显示模块代码
	show_bmp("./test.bmp",0,0);
	show_bmp("./www.bmp",200,150);	
	//7.收尾工作
		//解映射
		munmap(p, 800*480*4);
		//关闭帧缓冲设备文件(关闭显示屏)
		close(lcd_fd);
	return 0;
}
