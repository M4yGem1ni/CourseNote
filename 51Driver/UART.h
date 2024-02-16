#ifndef __UART__
#define __UART__

extern unsigned char UART_CheckMod;
void UART_Init(void);
void UART_SendByte(unsigned char Byte);
void UART_SendString(char* String);
/*
void UART_Check_Init(void);
void UART_SendByte_Check(unsigned char Byte);
void UART_SendString_Check(char* String);
*/
#endif