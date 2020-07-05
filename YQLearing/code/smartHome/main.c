#include "action.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
	// 打开LCD
	lcd_open();
	// 显示背景图片
	showPic("./bmps/1.bmp", 0, 0);
	// 居中正上方显示 ‘智能家居’ 小二字体 中蓝色
	displayTitle(352, 30, 0xFF0000);
	// 右下角显示 ‘小组成员+姓名+学号’ 小四字体 白色
	displayGroup(620, 386, 0xC71585);
	// 显示控件 鼠标控制
	showControl();
	// 关闭LCD
	lcd_close();
	return 0;
}