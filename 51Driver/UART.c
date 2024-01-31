#include <REGF51RC.H>
#include <INTRINS.H>
/**
	* @brief	串口通信初始化
	* @param	无
	* @SCON	SCON[SM0/SF	SM1(低位)	SM2(高位)	REN	TB8	RB8	TI	RI]
	* @SCON	SM0/SF	帧中断
	* @SCON	SM1	SM2	两位确定四种中断优先级(SM2 * 2 + SM1)
	* @SCON	REN			1允许接受数据;0不允许接受数据
	* @SCON	TI			发送完数据自动置1,必须用软件复位(标志位)
	* @SCON	RI			接受完数据自动置1,必须用软件复位(标志位)
	* @retval	无
	*/
	
void UART_Init(void)		//4800bps@11.0592MHz
{
	PCON |= 0x80;		//使能波特率倍速位SMOD	0100	0000
	SCON = 0x50;		//8位数据,可变波特率	0101	0000
//	AUXR &= 0xBF;		//定时器1时钟为Fosc/12,即12T
//	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xF4;		//设定定时初值
	TH1 = 0xF4;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
	EA	= 1;
	ES	= 1;
}

void UART_SendByte(unsigned char Byte)	//发送字节
{
	SBUF = Byte;
	while(TI==0);
	TI = 0;	//置零
}

void UART_SendString(char* String)
{
	while(*String != '\0')
	{
		UART_SendByte(*String);
		String++;
	}
}
/*
void UART_Routine()	interrupt 4	//moudel
{
	if(RI == 1)
	{
		| = SBUF;
		RI = 0;
	}
}
*/