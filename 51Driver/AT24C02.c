#include <REGF51RC.H>
#include "I2C.h"
#include "Delay.h"

#define AT24C02_ADDRESS 0xA0
/**
  * @brief	AT24C02写入一个字节
  * @param	WordAddress		写入的地址
	* @param	Data					写入的数据
  * @retval	无
  */
void AT24C02_WriteByte(unsigned char WordAddress , unsigned char Data)
{
	I2C_Start();
	I2C_SendByte(AT24C02_ADDRESS);
	I2C_ReceiveAck();
	I2C_SendByte(WordAddress);
	I2C_ReceiveAck();
	I2C_SendByte(Data);
	I2C_ReceiveAck();
	I2C_Stop();
	Delay(5);
}
/**
  * @brief	AT24C02读取一个字节的数据
  * @param	WordAddress:读取的地址
	* @retval	Data:				返回的数据
  */
unsigned char AT24C02_ReadByte(unsigned char WordAddress)
{
	unsigned char Data;
	I2C_Start();
	I2C_SendByte(AT24C02_ADDRESS);
	I2C_ReceiveAck();
	I2C_SendByte(WordAddress);
	I2C_ReceiveAck();
	
	I2C_Start();
	I2C_SendByte(AT24C02_ADDRESS|0x01);
	I2C_ReceiveAck();
	Data = I2C_ReceiveByte();
	I2C_SendAck(1);
	I2C_Stop();
	return Data;
}
/**
  * @brief	清除AT24C02中的所有数据
  * @param	无
  * @retval	无
  */
void AT24C02_EraseAll()
{
	unsigned char i;
	for(i=0;i<255;i++)
	{
		AT24C02_WriteByte(i,0);
	}
	AT24C02_WriteByte(255,0);
}