#include <REGF51RC.H>
#include "NRF24L01_Def.h"

/**
 * _ooOoo_
 * o8888888o
 * 88" . "88
 * (| -_- |)
 *  O\ = /O
 * ___/`---'\____
 * .   ' \\| |// `.
 * / \\||| : |||// \
 * / _||||| -:- |||||- \
 * | | \\\ - /// | |
 * | \_| ''\---/'' | |
 * \ .-\__ `-` ___/-. /
 * ___`. .' /--.--\ `. . __
 * ."" '< `.___\_<|>_/___.' >'"".
 * | | : `- \`.;`\ _ /`;.`/ - ` : | |
 * \ \ `-. \_ __\ /__ _/ .-` / /
 * ======`-.____`-.___\_____/___.-`____.-'======
 * `=---='
 *          .............................................
 *           佛曰：bug泛滥，我已瘫痪！
 */


/*--------------------------------------------------Define--------------------------------------------------*/

//	接口定义
sbit IRQ_Pin 	= P1^4;
sbit MOSI_Pin 	= P1^1;
sbit CSN_Pin	= P1^3;
sbit MISO_Pin	= P1^6;
sbit SCK_Pin	= P1^7;
sbit CE_Pin		= P1^2;

unsigned char bdata Sta;	//	状态寄存器
sbit  RX_DR     = Sta^6;	//	接收数据状态码
sbit  TX_DS     = Sta^5;	//	发送数据状态码
sbit  MAX_RT    = Sta^4;	//	达到最大重发状态码

#define TX_ADR_WIDTH 5			//	5字节的发送/接收地址
unsigned char TX_PLOAD_WIDTH  = 4;		//	定义数据通道的有效位长度(一次发送几个数据),放到Init之前

unsigned char T_ADDR[TX_ADR_WIDTH] = {0xF0,0xF0,0xF0,0xF0,0xF0};	//	定义发送地址
//unsigned char code R_ADDR[TX_ADR_WIDTH] = {0xF0,0xF0,0xF0,0xF0,0xF0};	//	定义接收地址

//unsigned char RX_BUF[TX_PLOAD_WIDTH];		//	接收数据缓存区
//unsigned char TX_BUF[TX_PLOAD_WIDTH];		//	发送数据缓存区

/*--------------------------------------------------SPI--------------------------------------------------*/

/*
SPI通信简介:
首先把CSN拉低表示选中从机,数据通信开始
在SPI模式0中
CSN拉低的同时,主机和从机会把传输的数据放到MOSI和MISO上
SCK时钟上升沿时,主机和从机同时接受数据,并且数据发生移位
SCK时钟下降沿时,主机和从机同时把下一位要传输的数据放到MISO和MOSI上
如此重复8次,即可交换一个字节的数据
*/


/**
  * @brief	SPI交换一个字节数据
  * @param	发送的数据
  * @retval	换回的数据
  */
unsigned char SPI_SwapByte(unsigned char Byte)
{
	unsigned char i;
	for (i=0;i<8;i++)
	{
		MOSI_Pin = Byte&0x80;				//	高位发送
		Byte = Byte<<1;						//	数据左移
		SCK_Pin = 1;						//	时钟上升沿
		Byte |= (unsigned char)MISO_Pin;	//	低位接收
		SCK_Pin = 0;						//	时钟下降沿
	}
	return Byte;							//	返回数据
}

/**
  * @brief	SPI发送一字节数据
  * @param	Cmd 操作指令	Byte 发送数据
  * @retval	Status 状态码
  */
unsigned char SPI_WriteByte(unsigned char Cmd,unsigned char Byte)
{
	unsigned char Status;
	CSN_Pin = 0;
	Status = SPI_SwapByte(Cmd);		//	选择发送到的寄存器并读取出状态码
	SPI_SwapByte(Byte);				//	发送数据
	CSN_Pin = 1;
	return Status;
}

/**
  * @brief	SPI读取一字节数据
  * @param	Cmd 操作指令
  * @retval	Byte 读取到的数据
  */
unsigned char SPI_ReadByte(unsigned char Cmd)
{
	unsigned char Byte;			//	创建数据缓冲区
	CSN_Pin = 0;
	SPI_SwapByte(Cmd);			//	指定读取的寄存器
	Byte = SPI_SwapByte(NOP);	//	取出读取到的数据
	CSN_Pin = 1;
	return Byte;
}

/**
  * @brief	SPI读取Length个字节数据
  * @param	Cmd 寄存器命令	*Buf 存储位置	Length 发送数据长度
  * @retval	Status	状态码
  */
unsigned char SPI_ReadArray(unsigned char Cmd,unsigned char* Buf,unsigned char Length)
{
	unsigned char Status,i;
	CSN_Pin = 0;
	Status = SPI_SwapByte(Cmd);			//	选择读取的寄存器,并返回状态码
	for(i = 0;i<Length;i++)
	{
		Buf[i] = SPI_SwapByte(NOP);		//	依次取出数据,存放到相应的存储位置
	}
	CSN_Pin = 1;
	return Status;						//	返回状态码
}


/**
  * @brief	SPI写入Length个字节数据
  * @param	Cmd 寄存器命令	*Buf 写入数据存储位置	Length 写入数据长度
  * @retval	Status	状态码
  */
unsigned char SPI_WriteArray(unsigned char Cmd,unsigned char* Buf,unsigned char Length)
{
	unsigned char Status,i;
	CSN_Pin = 0;
	Status = SPI_SwapByte(Cmd);
	for(i=0;i<Length;i++)
	{
		SPI_SwapByte(Buf[i]);
	}
	CSN_Pin = 1;
	return Status;
}

/*--------------------------------------------------NRF24L01--------------------------------------------------*/

/**
  * @brief	初始化IO引脚
  * @param	无
  * @retval	无
  */
void NRF24L01_Init(void)
{
	CE_Pin  = 0;        //	待机
    CSN_Pin = 1;        //	SPI禁止
    SCK_Pin = 0;        //	SPI时钟置低
    IRQ_Pin = 1;        //	中断复位
}

/**
  * @brief	配置为接收模式
  * @param	无
  * @retval	无
  */
void NRF24L01_RXMode(void)
{
	CE_Pin = 0;
	SPI_WriteArray(W_REGISTER + RX_ADDR_P0, T_ADDR, TX_ADR_WIDTH);	// 接收设备接收通道0使用和发送设备相同的发送地址
	SPI_WriteByte(W_REGISTER + EN_AA, 0x01);               			// 使能接收通道0自动应答
	SPI_WriteByte(W_REGISTER + EN_RXADDR, 0x01);           			// 使能接收通道0
	SPI_WriteByte(W_REGISTER + RF_CH, 40);                 			// 选择射频通道0x40
	SPI_WriteByte(W_REGISTER + RX_PW_P0, TX_PLOAD_WIDTH);  			// 接收通道0选择和发送通道相同有效数据宽度
	SPI_WriteByte(W_REGISTER + RF_SETUP, 0x07);            			// 数据传输率1Mbps，发射功率0dBm，低噪声放大器增益
	SPI_WriteByte(W_REGISTER + CONFIG, 0x0f);              			// CRC使能，16位CRC校验，上电，接收模式
	//Delay(150);
	CE_Pin = 1;															//	启动设备
}

/**
  * @brief	配置为发送模式
  * @param	发送的数据地址
  * @retval	无
  */
void NRF24L01_TXMode(unsigned char* Buf)
{
	CE_Pin = 0;
	SPI_WriteArray(W_REGISTER + TX_ADDR, T_ADDR, TX_ADR_WIDTH);     		// 写入发送地址
	SPI_WriteArray(W_REGISTER + RX_ADDR_P0, T_ADDR, TX_ADR_WIDTH);  		// 为了应答接收设备，接收通道0地址和发送地址相同
	SPI_WriteArray(W_TX_PAYLOAD, Buf, TX_PLOAD_WIDTH);                  	// 写数据包到TX FIFO
	SPI_WriteByte(W_REGISTER + EN_AA, 0x01);       							// 使能接收通道0自动应答
	SPI_WriteByte(W_REGISTER + EN_RXADDR, 0x01);   							// 使能接收通道0
	SPI_WriteByte(W_REGISTER + SETUP_RETR, 0x0a);  							// 自动重发延时等待250us+86us，自动重发10次
	SPI_WriteByte(W_REGISTER + RF_CH, 40);         							// 选择射频通道0x40
	SPI_WriteByte(W_REGISTER + RF_SETUP, 0x07);    							// 数据传输率1Mbps，发射功率0dBm，低噪声放大器增益
	SPI_WriteByte(W_REGISTER + CONFIG, 0x0e);      							// CRC使能，16位CRC校验，上电
	CE_Pin = 1;
}

/**
  * @brief	检查接收设备有无接收到数据包
  * @param	
  * @retval
  */
unsigned char NRF24L01_AckCheck(unsigned char Clear)
{
	unsigned char Status = 0x00;
	while(IRQ_Pin);
	Sta = SPI_ReadByte(STATUS);					//	返回状态寄存器
	if(TX_DS)
	{
		Status |= 0x01;
	}
	if(MAX_RT)
	{
		Status |= 0x10;
		if(Clear)
		{
			SPI_SwapByte(FLUSH_TX);				// 是否清除TX FIFO，没有清除在复位MAX_RT中断标志后重发
		}
	}
	SPI_WriteByte(W_REGISTER + STATUS, Sta);  	// 清除TX_DS或MAX_RT中断标志
	IRQ_Pin = 1;
	return Status;
}

/**
  * @brief	NRF24L01接收数据循环
  * @param	Buf 保存数据的地址
  * @retval	Flag 是否接收到数据
  */
unsigned char NRF24L01_RXLoop(unsigned char* Buf)
{
	unsigned char Flag = 0x00;
	Sta = SPI_ReadByte(STATUS);
	if(RX_DR)
	{
		SPI_ReadArray(R_RX_PAYLOAD, Buf, TX_PLOAD_WIDTH);  // 从RX FIFO读出数据
		Flag = 0x01;
	}
	SPI_WriteByte(W_REGISTER + STATUS, Sta);  // 清除RX_DS中断标志
	return Flag;
}

/*--------------------------------------------------END--------------------------------------------------*/
