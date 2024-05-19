#ifndef __NRF24L01_DEF_H
#define __NRF24L01_DEF_H

//	NRF24L01	寄存器地址
#define CONFIG      0x00
#define EN_AA       0x01
#define EN_RXADDR   0x02
#define SETUP_AW    0x03
#define SETUP_RETR  0x04
#define RF_CH       0x05
#define RF_SETUP    0x06
#define STATUS      0x07
#define OBSERVE_TX  0x08
#define CD          0x09
#define RX_ADDR_P0  0x0A
#define RX_ADDR_P1  0x0B
#define RX_ADDR_P2  0x0C
#define RX_ADDR_P3  0x0D
#define RX_ADDR_P4  0x0E
#define RX_ADDR_P5  0x0F
#define TX_ADDR     0x10
#define RX_PW_P0    0x11
#define RX_PW_P1    0x12
#define RX_PW_P2    0x13
#define RX_PW_P3    0x14
#define RX_PW_P4    0x15
#define RX_PW_P5    0x16
#define FIFO_STATUS 0x17

//	NRF24L01	指令集
#define R_REGISTER 		0x00 	// 读寄存器命令
#define W_REGISTER	 	0x20 	// 写寄存器命令
#define REGISTER_MASK 	0x1F 	// 寄存器地址掩码
#define ACTIVATE 		0x50 	// 激活命令
#define R_RX_PAYLOAD 	0x61 	// 读取接收数据命令
#define W_TX_PAYLOAD 	0xA0 	// 写入发送数据命令
#define FLUSH_TX 		0xE1 	// 清空发送缓冲区命令
#define FLUSH_RX 		0xE2 	// 清空接收缓冲区命令
#define REUSE_TX_PL 	0xE3 	// 重用发送数据命令
#define NOP 			0xFF 	// 无操作命令

//	NRF24L01	状态码
#define	NRF24L01_RX		0x40
#define	NRF24L01_TX		0x20
#define	NRF24L01_MAXTX	0x10


#endif
