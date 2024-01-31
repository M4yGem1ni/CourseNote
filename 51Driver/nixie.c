#include <REGF51RC.H>
#include <INTRINS.H>
#define NIXIE_LENGTH 8
unsigned char Nixie_Buf[9];
unsigned char code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
unsigned char code tabledot[]={0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef};
/**
  * @brief	控制数码管亮起的位置和显示的数字
  * @param	loc(位置)
	* @param	num(显示数字)[0-9无小数点;10-19有小数点;255负号]
  * @retval	无
  */
void Nixie(unsigned char loc,unsigned char num)
{

	P0 = 0x00;  //防止篡位
	switch(loc)
	{
		case 0:P2_4=0;P2_3=0;P2_2=0;break;
		case 1:P2_4=0;P2_3=0;P2_2=1;break;
		case 2:P2_4=0;P2_3=1;P2_2=0;break;
		case 3:P2_4=0;P2_3=1;P2_2=1;break;
		case 4:P2_4=1;P2_3=0;P2_2=0;break;
		case 5:P2_4=1;P2_3=0;P2_2=1;break;
		case 6:P2_4=1;P2_3=1;P2_2=0;break;
		case 7:P2_4=1;P2_3=1;P2_2=1;break;
	}
	if(num == 255){P0 = 0x40;}
	else if(num >= 10 && num <=19){P0 = tabledot[num-10];}
	else if(num>=0 && num<=9){P0 = table[num];}
	else{P0 = 0x00;}
}
void Nixie_SetBuf(unsigned char loc,unsigned char Data)
{
	Nixie_Buf[loc] = Data;
}

/**
  * @brief	定时器扫描数码管(2ms一次)
  * @param	无
  * @retval	无
  */
void Nixie_Loop()
{
	static unsigned char i = 0;
	Nixie(i,Nixie_Buf[i]);
	i++;
	i = i%NIXIE_LENGTH;
}