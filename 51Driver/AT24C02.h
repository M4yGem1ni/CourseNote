#ifndef __AT24C02__
#define __AT24C02__

void AT24C02_WriteByte(unsigned char WordAddress , unsigned char Data);
unsigned char AT24C02_ReadByte(unsigned char WordAddress);
void AT24C02_EraseAll();
#endif