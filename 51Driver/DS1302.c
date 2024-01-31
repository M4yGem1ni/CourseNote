#include <REGF51RC.H>
#include <INTRINS.H>
#include "Delay.h"
//哭死,千万不要递归调用!!!!!!!!!!!!!!!!
void DS1302_Init();
void DS1302_WriteByte(unsigned char Cmd,unsigned char Data);
unsigned char DS1302_ReadByte(unsigned char Cmd);
unsigned char DS1302_BCDtoD(unsigned char BCD);
unsigned char DS1302_DtoBCD(unsigned char D);
void DS1302_SetTime(void);
void DS1302_ReadTime(void);
//引脚配置
sbit DS1302_SCLK	= P3^6;
sbit DS1302_IO		= P3^4;
sbit DS1302_CE		= P3^5;
unsigned char DS1302_Time[]={24,1,21,1,16,0,7};	//	2024/1/21 1:16:00 SUN.

//DS1302 WriteByte地址 , ReadByte = WriteByte+1
#define DS1302_SECOND		0x80
#define DS1302_MINUTE		0x82
#define DS1302_HOUR			0x84
#define DS1302_DATE			0x86
#define DS1302_MONTH		0x88
#define DS1302_DAY			0x8A
#define DS1302_YEAR			0x8C
#define	DS1302_WP				0x8E
/**
  * @brief	初始化DS1302芯片
  * @param	无
  * @retval	无
  */
void DS1302_Init()
{
	DS1302_SCLK = 0;
	DS1302_CE = 0;
	DS1302_SetTime();	//BUG!!!
}
/**
  * @brief	DS1302写入时间
  * @param	Cmd	写入的命令
  * @param	Data写入的数据
  * @retval	无
  */
void DS1302_WriteByte(unsigned char Cmd , unsigned char Data)
{
	unsigned char i = 0;
	DS1302_CE = 1;	//使能置1
	
	for(i=0;i<8;i++)
	{
		DS1302_IO = Cmd&(0x01<<i);	//将cmd第i位取出(非零即一)
		DS1302_SCLK = 1;	//上升沿将数据传入
		//Delay(1);	//51单片机速率慢,不需要延时
		DS1302_SCLK = 0;
	}
	for(i=0;i<8;i++)
	{
		DS1302_IO = Data&(0x01<<i);	//将data第i位取出(非零即一)
		DS1302_SCLK = 1;	//上升沿将数据传入
		//Delay(1);	//51单片机速率慢,不需要延时
		DS1302_SCLK = 0;
	}
	
	DS1302_CE = 0;	//使能置0
}
/**
  * @brief	DS1302读取时间
  * @param	Cmd	读取的位置
  * @retval	Data读取的数据
  */
unsigned char DS1302_ReadByte(unsigned char Cmd)
{
	unsigned char i = 0,Data = 0x00;
	DS1302_CE = 1;	//使能置1
	Cmd |= 0x01;	//末位置1 , cmd就可以使用WriteByte的地址了
	for(i=0;i<8;i++)
	{
		DS1302_IO = Cmd&(0x01<<i);	//将cmd第i位取出(非零即一)
		DS1302_SCLK = 0;	
		//Delay(1);	//51单片机速率慢,不需要延时
		DS1302_SCLK = 1;	//上升沿将数据传入
	}
	for(i=0;i<8;i++)
	{
		DS1302_SCLK = 1;
		//Delay(1);
		DS1302_SCLK = 0;	//下降沿时钟传入数据至IO
		if(DS1302_IO){Data|=(0x01<<i);}
	}
	DS1302_IO = 0;	//IO置零
	DS1302_CE = 0;
	//return DS1302_BCDtoD(Data);	//LCD用16进制输出即可避免BCD与十进制的冲突
	return Data;
}
/**
  * @brief	两位十进制转BCD码
  * @param	D 两位十进制数
  * @retval	BCD 两位BCD码
  */
unsigned char DS1302_DtoBCD(unsigned char D)	//两位十进制数转BCD码
{
	return D/10*16+D%10;
}
/**
  * @brief	两位BCD码转十进制
  * @param	BCD 两位BCD码
  * @retval	D 两位十进制数
  */
unsigned char DS1302_BCDtoD(unsigned char BCD)	//两位BCD码转十进制数
{
	return BCD/16*10+BCD%16;
}
/**
  * @brief	向DS1302写入时间
  * @param	无
  * @retval	无
  */
void DS1302_SetTime(void)
{
	DS1302_CE = 1;	//使能置1
	DS1302_WriteByte(DS1302_WP,0x00);	//关闭写入保护
	
	DS1302_WriteByte(DS1302_YEAR,DS1302_Time[0]/10*16+DS1302_Time[0]%10);
	DS1302_WriteByte(DS1302_MONTH,DS1302_Time[1]/10*16+DS1302_Time[1]%10);
	DS1302_WriteByte(DS1302_DATE,DS1302_Time[2]/10*16+DS1302_Time[2]%10);
	DS1302_WriteByte(DS1302_HOUR,DS1302_Time[3]/10*16+DS1302_Time[3]%10);
	DS1302_WriteByte(DS1302_MINUTE,DS1302_Time[4]/10*16+DS1302_Time[4]%10);
	DS1302_WriteByte(DS1302_SECOND,DS1302_Time[5]/10*16+DS1302_Time[5]%10);
	DS1302_WriteByte(DS1302_DAY,DS1302_Time[6]/10*16+DS1302_Time[6]%10);
	
	DS1302_WriteByte(DS1302_WP,0x80);	//打开写入保护
	DS1302_CE = 0;	//使能置0
}
/**
  * @brief	将DS1302中的时间读取出来
  * @param	无
  * @retval	无
  */
void DS1302_ReadTime(void)
{
	DS1302_Time[0] = DS1302_BCDtoD( DS1302_ReadByte(	DS1302_YEAR		));
	DS1302_Time[1] = DS1302_BCDtoD( DS1302_ReadByte(	DS1302_MONTH	));
	DS1302_Time[2] = DS1302_BCDtoD( DS1302_ReadByte(	DS1302_DATE		));
	DS1302_Time[3] = DS1302_BCDtoD( DS1302_ReadByte(	DS1302_HOUR		));
	DS1302_Time[4] = DS1302_BCDtoD( DS1302_ReadByte(	DS1302_MINUTE	));
	DS1302_Time[5] = DS1302_BCDtoD( DS1302_ReadByte(	DS1302_SECOND	));
	DS1302_Time[6] = DS1302_BCDtoD( DS1302_ReadByte(	DS1302_DAY		));
}