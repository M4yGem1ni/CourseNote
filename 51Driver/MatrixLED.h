#ifndef __MATRIXLED__
#define __MATRIXLED__
void MatrixLED_Init();
void _74HC595_WriteByte(unsigned char Byte);
unsigned char MatrixLED_Trans(unsigned char loc);
void MatrixLED_ShowColumn(unsigned char Column , unsigned char Data);
void MatrixLED_Animate(unsigned char FLAT,unsigned char* arg);
void MatrixLED_Frame(int FLAT,unsigned char* arg);

#include <REGF51RC.H>
#include <INTRINS.H>
#include "Delay.h"
sbit RCLK = P3^5;	//串行时钟使用上升沿
sbit SRCLK = P3^6;	//时钟,上升沿数据入栈
sbit SER = P3^4;	//数据缓存
#define MATRIX_LED_PORT P0
/**
  * @brief	LED点阵屏初始化
  * @param	无
  * @retval	无
  */
void MatrixLED_Init()
{
	SRCLK = 0;
	RCLK = 0;
}
/**
  * @brief	74HC595驱动程序
  * @param	Byte
  * @retval	无
  */
void _74HC595_WriteByte(unsigned char Byte)
{
	unsigned char i = 0;
	for (i=0;i<8;i++)
	{
		SER = Byte&(0x80>>i);SRCLK = 1;SRCLK = 0;		//赋值bit非0即1
	}
	RCLK = 1;RCLK = 0;
}
/**
  * @brief	一个位置转换
  * @param	位置	0~7
  * @retval	矩阵LED位置	0x01 ~ 0x80
  */
unsigned char MatrixLED_Trans(unsigned char loc)
{
	unsigned char MatrixLED_Loc[8]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
	return MatrixLED_Loc[loc];
}
/**
  * @brief	LED点阵显示一列
  * @param	Column	选择的列	0~7	0在左边
	* @param	Data	显示的数据	0x00 ~ 0xff	高位在上,1亮,0灭
  * @retval	无
  */
void MatrixLED_ShowColumn(unsigned char Column , unsigned char Data)
{
	_74HC595_WriteByte(Data);
	MATRIX_LED_PORT = ~(0x80>>Column);	//0为选中
	Delay(1);
	MATRIX_LED_PORT = 0xFF;
}

#define MATRIXLED_HIGTH 8
#define MATRIXLED_LENGTH 8

/**
  * @brief	LED显示流动动画
  * @param	数组长度FLAT,数组
  * @retval	无
  */
unsigned char MatrixLED = 0;
void MatrixLED_Animate(unsigned char FLAT,unsigned char* arg)
{
	unsigned char tmp = 0;
	for(tmp = 0;tmp < 3; tmp++)
	{
		unsigned char MatrixLED_j = 0;
		for(MatrixLED_j=0;MatrixLED_j<FLAT;MatrixLED_j++)
		{
			MatrixLED_ShowColumn(MatrixLED_j, *(arg+(MatrixLED + MatrixLED_j) % FLAT));
		}
	}
	MatrixLED = (MatrixLED+1) % FLAT;
}
/**
  * @brief	LED显示帧动画
  * @param	数组长度FLAT,数组arg
  * @retval	无
  */
int MatrixLED_FrameNum = 0;
void MatrixLED_Frame(int FLAT,unsigned char* arg)
{
	int columns = FLAT / MATRIXLED_LENGTH;
	int num=0;
	for(num=0;num<25;num++)
	{
		unsigned char i = 0;
		for (i=0;i<MATRIXLED_LENGTH;i++)
		{
			MatrixLED_ShowColumn(i , arg[MatrixLED_FrameNum * MATRIXLED_LENGTH + i]);
		}
		//Delay((unsigned int)(1/frame*100));
	}MatrixLED_FrameNum = (MatrixLED_FrameNum+1)%columns;
}
#endif