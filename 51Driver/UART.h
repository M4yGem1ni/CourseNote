#ifndef __UART__
#define __UART__

void UART_Init(void);
void UART_SendByte(unsigned char Byte);
void UART_SendString(char* String);

#endif