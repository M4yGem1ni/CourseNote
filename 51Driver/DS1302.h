#ifndef __DS1302__
#define __DS1302__

extern unsigned char DS1302_Time[];

void DS1302_Init();
void DS1302_WriteByte(unsigned char Cmd,unsigned char Data);
unsigned char DS1302_ReadByte(unsigned char Cmd);
unsigned char DS1302_BCDtoD(unsigned char BCD);
unsigned char DS1302_DtoBCD(unsigned char D);
void DS1302_SetTime(void);
void DS1302_ReadTime(void);

#endif