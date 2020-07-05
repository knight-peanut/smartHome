#ifndef __FUNCTION_H__
#define __FUNCTION_H__
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <linux/input.h> // 触摸事件结构体存放
#include <sys/socket.h>
#include <linux/socket.h> // 网络地址结构体存放
#include <arpa/inet.h> // 字节序转换
#include <netinet/in.h> // ip地址转换
#include <pthread.h> // 线程
#define LCD_SIZE 800*480*4

// 打开LCD
void lcd_open();

// 刷底色
void drawColor(int color);

// 在屏幕上画点
void drawPoint(int x, int y, int color);

// 显示一个字 任意字体
void displayWord(int x, int y, int bytenum, unsigned char word[], int perlineBit, int color);

// 显示一组字 小四字体
void displayAllWord1(int x, int y, unsigned char word[][32], int num, int perlineBit, int color);

// 显示一组字 小二字体
void displayAllWord2(int x, int y, unsigned char word[][72], int num, int perlineBit, int color);

// 显示单个成员的姓名和学号 小四字体
void displayMem(int x, int y, int color, char *p, int num, unsigned char mem[][32]);

// 显示一组的姓名和学号 小四字体
void displayGroup(int x, int y, int color);

// 显示智能家居四个字 小二字体
void displayTitle(int x, int y, int color);

// 通过bmp文件头获取图片参数(宽，高，位深)
void getPicPar(int fdBmp, int *width, int *height, unsigned short *bit_per_pix);

// 转换位深（bmp文件的24位位深转换为开发板上的32位位深）
void drawBmp(const unsigned char *p, const int pad, const int width, const int height, int x, int y);

// 显示一张图片
void showPic(const char *path, int x, int y);

// 获取LCD触摸屏鼠标点击处的位置
void getPos(int *x, int *y);

// 显示控件 鼠标控制
void showControl();

// 关闭LCD
void lcd_close();

// 初始化客户端网络
int initNet();

// 线程并发读取数据，根据读取到的数据去改变开关的状态
void * task(void *ar);

// 根据收到的数据更改相应控件的状态
void changeStatus(char *r);
#endif