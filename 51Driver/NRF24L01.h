#ifndef __NRF24L01_H
#define __NRF24L01_H
/*--------------------------------------------------可改变量--------------------------------------------------*/

extern unsigned char T_ADDR[];	//	定义发送地址
extern unsigned char TX_PLOAD_WIDTH;	//	定义数据通道的有效位长度(一次发送几个数据)

/*--------------------------------------------------函数--------------------------------------------------*/

unsigned char SPI_SwapByte(unsigned char Byte);
unsigned char SPI_WriteByte(unsigned char Cmd,unsigned char Byte);
unsigned char SPI_ReadByte(unsigned char Cmd);
unsigned char SPI_ReadArray(unsigned char Cmd,unsigned char* Buf,unsigned char Length);
unsigned char SPI_WriteArray(unsigned char Cmd,unsigned char* Buf,unsigned char Length);

void NRF24L01_Init(void);
void NRF24L01_RXMode(void);
void NRF24L01_TXMode(unsigned char* Buf);
unsigned char NRF24L01_AckCheck(unsigned char Clear);
unsigned char NRF24L01_RXLoop(unsigned char* Buf);

/*--------------------------------------------------END--------------------------------------------------*/

#endif
