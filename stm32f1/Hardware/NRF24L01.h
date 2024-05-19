#ifndef __NRF24L01_H
#define __NRF24L01_H

extern uint8_t TX_ADR_WIDTH;			//	5位发送接收地址
extern uint8_t TX_PLOAD_WIDTH;			//	一次发送32字节数据

extern uint8_t T_ADDR[];				//	发送/接收的地址
//extern uint8_t R_ADDR[];

void SPI_MOSI(uint8_t Data);	//主机控制MOSI引脚
void SPI_SCK(uint8_t Data);		//主机控制SCK引脚
void SPI_CSN(uint8_t Data);		//主机控制CSN引脚
void SPI_CE(uint8_t Data);		//主机控制CE引脚
uint8_t SPI_IRQ(void);
uint8_t SPI_MISO(void);
void NRF24L01_Pin_Init(void);
uint8_t SPI_SwapByte(uint8_t Byte);
void SPI_WriteByte(uint8_t Cmd,uint8_t Byte);
uint8_t SPI_ReadByte(uint8_t Cmd);
void SPI_WriteArray(uint8_t Cmd , uint8_t* Buf , uint32_t Length);
void SPI_ReadArray(uint8_t Cmd , uint8_t* Buf , uint32_t Length);

void NRF24L01_Init(void);
void NRF24L01_ReceiveData(uint8_t* Buf);
//uint8_t NRF24L01_SendData(uint8_t* Buf);
void NRF24L01_RXMode(void);
void NRF24L1_TXMode(uint8_t* Buf);
uint8_t NRF24L01_AckCheck(uint8_t Clear);
uint8_t NRF24L01_RXLoop(uint8_t* Buf);

#endif
