#include "stm32f10x.h"                  // Device header
#include "NRF24L01_Def.h"
#include "Delay.h"
//	RCC			时钟定义
#define	RCC_GPIO_SEL (RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB)

//	SPI	接口定义
#define	IRQ_PORT	GPIOB
#define	MISO_PORT	GPIOA

#define	CE_PORT		GPIOB
#define	MOSI_PORT	GPIOA
#define	SCK_PORT	GPIOA
#define	CSN_PORT	GPIOA

#define	IRQ_Pin		GPIO_Pin_1	//	接口8
#define	MISO_Pin	GPIO_Pin_6	//	接口7

#define	CE_Pin		GPIO_Pin_0	//	接口3
#define	MOSI_Pin	GPIO_Pin_7	//	接口6
#define	SCK_Pin		GPIO_Pin_5	//	接口5
#define	CSN_Pin		GPIO_Pin_4	//	接口4

//	NRF24L01初始化定义

uint8_t TX_ADR_WIDTH   = 5;			//	5位发送接收地址
uint8_t TX_PLOAD_WIDTH = 32;		//	一次发送32字节数据

uint8_t T_ADDR[5] = {0xF0,0xF0,0xF0,0xF0,0xF0};
//uint8_t R_ADDR[5] = {0xF0,0xF0,0xF0,0xF0,0xF0};


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
  * @brief	主机操作(写)
  * @param	Data	各个引脚上要写入的引脚
  * @retval	无
  */
void SPI_MOSI(uint8_t Data)	//主机控制MOSI引脚
{
	GPIO_WriteBit(MOSI_PORT,MOSI_Pin,(BitAction)Data);
}

void SPI_SCK(uint8_t Data)		//主机控制SCK引脚
{
	GPIO_WriteBit(SCK_PORT,SCK_Pin,(BitAction)Data);
}

void SPI_CSN(uint8_t Data)		//主机控制CSN引脚
{
	GPIO_WriteBit(CSN_PORT,CSN_Pin,(BitAction)Data);
}

void SPI_CE(uint8_t Data)		//主机控制CE引脚
{
	GPIO_WriteBit(CE_PORT,CE_Pin,(BitAction)Data);
}

/**
  * @brief	从机操作(读)
  * @param	无
  * @retval	读取到的各引脚的数据
  */
uint8_t SPI_IRQ(void)
{
	return GPIO_ReadInputDataBit(IRQ_PORT,IRQ_Pin);
}

uint8_t SPI_MISO(void)
{
	return GPIO_ReadInputDataBit(MISO_PORT,MISO_Pin);
}

/**
  * @brief	NRF24L01引脚初始化
  * @param	无
  * @retval	无
  */
void NRF24L01_Pin_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_GPIO_SEL,ENABLE);
	//	配置为推挽输出
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode	=	GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin		=	MOSI_Pin;
	GPIO_InitStructure.GPIO_Speed	=	GPIO_Speed_50MHz;
	GPIO_Init(MOSI_PORT,&GPIO_InitStructure);	//	配置MOSI
	
	GPIO_InitStructure.GPIO_Mode	=	GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin		=	SCK_Pin;
	GPIO_InitStructure.GPIO_Speed	=	GPIO_Speed_50MHz;
	GPIO_Init(SCK_PORT,&GPIO_InitStructure);	//	配置SCK
	
	GPIO_InitStructure.GPIO_Mode	=	GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin		=	CSN_Pin;
	GPIO_InitStructure.GPIO_Speed	=	GPIO_Speed_50MHz;
	GPIO_Init(CSN_PORT,&GPIO_InitStructure);	//	配置CSN
	
	GPIO_InitStructure.GPIO_Mode	=	GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin		=	CE_Pin;
	GPIO_InitStructure.GPIO_Speed	=	GPIO_Speed_50MHz;
	GPIO_Init(CE_PORT,&GPIO_InitStructure);		//	配置CE
	//	配置为上拉输入
	GPIO_InitStructure.GPIO_Mode	=	GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin		=	MISO_Pin;
	GPIO_InitStructure.GPIO_Speed	=	GPIO_Speed_50MHz;
	GPIO_Init(MISO_PORT,&GPIO_InitStructure);	//	配置MISO
	
	GPIO_InitStructure.GPIO_Mode	=	GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin		=	IRQ_Pin;
	GPIO_InitStructure.GPIO_Speed	=	GPIO_Speed_50MHz;
	GPIO_Init(IRQ_PORT,&GPIO_InitStructure);	//	配置IRQ
}

/**
  * @brief	SPI交换一个字节
  * @param	发送的字节
  * @retval	接收的字节
  */
uint8_t SPI_SwapByte(uint8_t Byte)
{
	uint8_t i,ReceiveByte = 0x00;
	for(i = 0;i<8;i++)
	{
		SPI_MOSI(Byte&(0x80>>i));
		SPI_SCK(1);	//	上升沿
		if (SPI_MISO() == 1)
		{
			ReceiveByte = ReceiveByte|(0x80>>i);
		}
		SPI_SCK(0);	//	下降沿
	}
	return ReceiveByte;
}

/**
  * @brief	SPI发送一个字节
  * @param	Cmd	指令码;	Byte	发送的数据
  * @retval	无
  */
void SPI_WriteByte(uint8_t Cmd,uint8_t Byte)
{
	SPI_CSN(0);				//	选中SPI
	SPI_SwapByte(Cmd);		//	发送指令
	SPI_SwapByte(Byte);		//	发送数据
	SPI_CSN(1);				//	关闭选中SPI
}

/**
  * @brief	SPI接收一个字节
  * @param	Cmd	指令码
  * @retval	ReceiveByte	接收到的数据
  */
uint8_t SPI_ReadByte(uint8_t Cmd)
{
	uint8_t ReceiveByte;
	SPI_CSN(0);							//	选中SPI
	SPI_SwapByte(Cmd);					//	发送指令
	ReceiveByte = SPI_SwapByte(NOP);	//	读取数据
	SPI_CSN(1);							//	关闭选中SPI
	return ReceiveByte;
}

/**
  * @brief	SPI写入一组数据
  * @param	Cmd	指令码;	*Buf写入数据数组的首地址;	Length	发送数据的个数
  * @retval	无
  */
void SPI_WriteArray(uint8_t Cmd , uint8_t* Buf , uint32_t Length)
{
	uint32_t i;
	SPI_CSN(0);
	SPI_SwapByte(Cmd);
	for(i = 0;i<Length;i++)
	{
		SPI_SwapByte(Buf[i]);
	}
	SPI_CSN(1);
}

/**
  * @brief	SPI读取一组数据
  * @param	Cmd	指令码;		Length	接收数据的个数
  * @underline	*Buf	存放数据数组的首地址;
  * @retval	无
  */
void SPI_ReadArray(uint8_t Cmd , uint8_t* Buf , uint32_t Length)
{
	uint32_t i;
	SPI_CSN(0);
	SPI_SwapByte(Cmd);
	for(i = 0;i<Length;i++)
	{
		Buf[i] = SPI_SwapByte(NOP);
	}
	SPI_CSN(1);
}

/**
  * @brief	NRF24L01芯片初始化
  * @param	无
  * @retval	无
  */
void NRF24L01_Init(void)
{
	NRF24L01_Pin_Init();
	//NRF24L01_RXMode();
//	SPI_CE(0);
//	
//	SPI_WriteArray(W_REGISTER+TX_ADDR,T_ADDR,5);	//	配置发送地址
//	SPI_WriteArray(W_REGISTER+RX_ADDR_P0,R_ADDR,5);	//	配置接收通道0
//	SPI_WriteByte(W_REGISTER+CONFIG,0x0f);			//	配置成接收模式
//	SPI_WriteByte(W_REGISTER+EN_AA,0x01);			//	配置通道0开启自动应答
//	SPI_WriteByte(W_REGISTER+RF_CH,0x00);			//	配置通信频率2.4GHz
//	SPI_WriteByte(W_REGISTER+RX_PW_P0,32);			//	配置接收通道0的数据宽度为32位
//	SPI_WriteByte(W_REGISTER+EN_RXADDR,0x01);		//	接收通道0使能
//	SPI_WriteByte(W_REGISTER+SETUP_RETR,0x1a);		//	配置580us自动重发,重发10次
//	SPI_WriteByte(FLUSH_RX,NOP);					//	清除接收缓存器
//	
//	SPI_CE(1);
}

/**
  * @brief	NRF24L01接收数据
  * @param	*Buf	数据保存的地址
  * @retval	无
  */
void NRF24L01_ReceiveData(uint8_t* Buf)
{
	uint8_t Status;									//	定义读寄存器状态
	Status = SPI_ReadByte(R_REGISTER+STATUS);		//	读取状态
	
	if(Status & NRF24L01_RX)						//	接收到数据的情况下
	{
		SPI_ReadArray(R_RX_PAYLOAD,Buf,32);			//	读取数据并把数据放到指定位置
		SPI_WriteByte(FLUSH_RX,NOP);				//	清空读寄存器
		SPI_WriteByte(W_REGISTER+STATUS,Status);	//	清除寄存器状态
	}
	Delay_us(100);									//	延时100us没必要读太快
}

///**
//  * @brief	NRF24L01发送数据
//  * @param	*Buf	发送数据数组的首地址
//  * @retval	Status	状态码
//  */
//uint8_t NRF24L01_SendData(uint8_t* Buf)
//{
//	uint8_t Status;									//	定义状态码
//	SPI_WriteArray(W_TX_PAYLOAD,Buf,32);			//	数据写入寄存器
//	
//	SPI_CE(0);										//	芯片待机
//	SPI_WriteByte(W_REGISTER+CONFIG,0x0e);			//	准备执行发送命令
//	SPI_CE(1);										//	芯片启动
//	
//	while(SPI_IRQ() == 1);							//	等待数据发送完成
//	Status = SPI_ReadByte(R_REGISTER+STATUS);		//	读取发送状态
//	
//	if(Status & NRF24L01_MAXTX)						//	完全发送数据
//	{
//		SPI_WriteByte(FLUSH_TX,NOP);				//	清空数据发送寄存器
//		SPI_WriteByte(W_REGISTER+STATUS,Status);	//	清空状态寄存器的状态
//	}
//	if(Status & NRF24L01_TX)						//	发送数据异常
//	{
//		SPI_WriteByte(W_REGISTER+STATUS,Status);	//	清空发送的数据
//	}
//	
//	return Status;									//	返回状态码
//}

void NRF24L01_RXMode(void)
{
	SPI_CE(0);
	
	SPI_WriteArray(W_REGISTER + RX_ADDR_P0, T_ADDR, TX_ADR_WIDTH);	// 接收设备接收通道0使用和发送设备相同的发送地址
	SPI_WriteByte(W_REGISTER + EN_AA, 0x01);               			// 使能接收通道0自动应答
	SPI_WriteByte(W_REGISTER + EN_RXADDR, 0x01);           			// 使能接收通道0
	SPI_WriteByte(W_REGISTER + RF_CH, 40);                 			// 选择射频通道0x40
	SPI_WriteByte(W_REGISTER + RX_PW_P0, TX_PLOAD_WIDTH);  			// 接收通道0选择和发送通道相同有效数据宽度
	SPI_WriteByte(W_REGISTER + RF_SETUP, 0x07);            			// 数据传输率1Mbps，发射功率0dBm，低噪声放大器增益
	SPI_WriteByte(W_REGISTER + CONFIG, 0x0f);              			// CRC使能，16位CRC校验，上电，接收模式
	
	SPI_CE(1);
}

void NRF24L1_TXMode(uint8_t* Buf)
{
	SPI_CE(0);
	
	SPI_WriteArray(W_REGISTER + TX_ADDR, T_ADDR, TX_ADR_WIDTH);     		// 写入发送地址
	SPI_WriteArray(W_REGISTER + RX_ADDR_P0, T_ADDR, TX_ADR_WIDTH);  		// 为了应答接收设备，接收通道0地址和发送地址相同
	SPI_WriteArray(W_TX_PAYLOAD, Buf, TX_PLOAD_WIDTH);                  	// 写数据包到TX FIFO
	SPI_WriteByte(W_REGISTER + EN_AA, 0x01);       							// 使能接收通道0自动应答
	SPI_WriteByte(W_REGISTER + EN_RXADDR, 0x01);   							// 使能接收通道0
	SPI_WriteByte(W_REGISTER + SETUP_RETR, 0x0a);  							// 自动重发延时等待250us+86us，自动重发10次
	SPI_WriteByte(W_REGISTER + RF_CH, 40);         							// 选择射频通道0x40
	SPI_WriteByte(W_REGISTER + RF_SETUP, 0x07);    							// 数据传输率1Mbps，发射功率0dBm，低噪声放大器增益
	SPI_WriteByte(W_REGISTER + CONFIG, 0x0e);      							// CRC使能，16位CRC校验，上电
	
	SPI_CE(1);
}

uint8_t NRF24L01_AckCheck(uint8_t Clear)
{
	uint8_t Sta = 0x00,Status;
	while(SPI_IRQ() == 1);
	Status = SPI_ReadByte(STATUS);					//	返回状态寄存器
	if(Status & 0x20)								//	接收ACK标志位	TX_DS == 1
	{
		Sta |= 0x01;
	}
	if(Status & 0x10)								//	最大发送标志位	MAX_RT == 1
	{
		Sta |= 0x10;
		if(Clear)
		{
			SPI_SwapByte(FLUSH_TX);					//	是否清除TX FIFO
		}
	}
	SPI_WriteByte(W_REGISTER + STATUS, Sta);  		// 清除TX_DS或MAX_RT中断标志
	return Sta;
}

uint8_t NRF24L01_RXLoop(uint8_t* Buf)
{
	uint8_t Flag;
	uint8_t Status; 
	Flag = 0x00;
	Status = SPI_ReadByte(STATUS);
	if( Status&0x40 )										//	RX_DR == 1
	{
		SPI_ReadArray(R_RX_PAYLOAD, Buf, TX_PLOAD_WIDTH);  	// 从RX FIFO读出数据
		Flag = 0x01;
	}
	SPI_WriteByte(W_REGISTER + STATUS, Status);  			// 清除RX_DS中断标志
	return Flag;
}

