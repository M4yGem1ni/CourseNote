#include <REGF51RC.H>
#include "Delay.h"
//高位在前
sbit I2C_SCL = P2^1;
sbit I2C_SDA = P2^0;
/**@start
    _____
				 \_____ SCL
		__
		  \________ SDA
*/
/**
  * @brief	I2C开始操作
  * @param	无
  * @retval	无
  */
void I2C_Start()
{
	I2C_SDA = 1;//起始条件
	I2C_SCL = 1;
	I2C_SDA = 0;
	I2C_SCL = 0;
	
}
/**@stop
			 _________
		__/					 SCL
					 _____
		______/			 SDA
*/
/**
  * @brief	I2C结束
  * @param	无
  * @retval	无
  */
void I2C_Stop()
{
	I2C_SDA = 0;//起始条件
	I2C_SCL = 1;
	I2C_SDA = 1;
}
/**
  * @brief	I2C发送一个字节
  * @param	Byte	发送的字节
  * @retval	无
  */
void I2C_SendByte(unsigned char Byte)	//高位向低位发送
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		I2C_SDA = Byte & (0x80>>i);
		I2C_SCL = 1;
		I2C_SCL = 0;
	}
}
/**
  * @brief	I2C接收一个字节
  * @param	无
  * @retval	接收的字节
  */
unsigned char I2C_ReceiveByte()
{
	unsigned char i,Byte = 0x00;
	I2C_SDA = 1;
	for(i=0;i<8;i++)
	{
		I2C_SCL = 1;
		if(I2C_SDA){Byte |= (0x80>>i);}
		I2C_SCL = 0;
	}
	return Byte;
}
/**
  * @brief	主机发送应答(主机接收完一个字节的数据之后)
  * @param	AckBit	0:有应答	1:无应答
  * @retval	无
  */
void I2C_SendAck(unsigned char AckBit)
{
	I2C_SDA = AckBit;
	I2C_SCL = 1;
	I2C_SCL = 0;
	
}
/**
  * @brief	主机接收应答(主机发送一个字节的数据之后)
  * @param	无
  * @retval	AckBit	0:有应答	1:无应答
  */
unsigned char I2C_ReceiveAck()
{
	unsigned char AckBit = 0;
	I2C_SDA = 1;
	I2C_SCL = 1;
	if(I2C_SDA){AckBit = 1;}
	I2C_SCL = 0;
	return AckBit;
}
