#include <REGF51RC.H>
#include "Delay.h"
/**
	* @brief	读取矩阵键盘
	* @param	无
	* @retval	返回按键位置(1~16),无输入返回0
	松手触发
	*/
unsigned char MatrixKey()
{
	unsigned char MatrixKey_KeyNumber = 0;
	P1 = 0xff;
	P1_3 = 0;
	if(P1_7 == 0){Delay(20);while(P1_7 == 0);Delay(20);MatrixKey_KeyNumber = 1;return MatrixKey_KeyNumber;}
	if(P1_6 == 0){Delay(20);while(P1_6 == 0);Delay(20);MatrixKey_KeyNumber = 5;return MatrixKey_KeyNumber;}
	if(P1_5 == 0){Delay(20);while(P1_5 == 0);Delay(20);MatrixKey_KeyNumber = 9;return MatrixKey_KeyNumber;}
	if(P1_4 == 0){Delay(20);while(P1_4 == 0);Delay(20);MatrixKey_KeyNumber = 13;return MatrixKey_KeyNumber;}
	
	P1 = 0xff;
	P1_2 = 0;
	if(P1_7 == 0){Delay(20);while(P1_7 == 0);Delay(20);MatrixKey_KeyNumber = 2;return MatrixKey_KeyNumber;}
	if(P1_6 == 0){Delay(20);while(P1_6 == 0);Delay(20);MatrixKey_KeyNumber = 6;return MatrixKey_KeyNumber;}
	if(P1_5 == 0){Delay(20);while(P1_5 == 0);Delay(20);MatrixKey_KeyNumber = 10;return MatrixKey_KeyNumber;}
	if(P1_4 == 0){Delay(20);while(P1_4 == 0);Delay(20);MatrixKey_KeyNumber = 14;return MatrixKey_KeyNumber;}
	
	P1 = 0xff;
	P1_1 = 0;
	if(P1_7 == 0){Delay(20);while(P1_7 == 0);Delay(20);MatrixKey_KeyNumber = 3;return MatrixKey_KeyNumber;}
	if(P1_6 == 0){Delay(20);while(P1_6 == 0);Delay(20);MatrixKey_KeyNumber = 7;return MatrixKey_KeyNumber;}
	if(P1_5 == 0){Delay(20);while(P1_5 == 0);Delay(20);MatrixKey_KeyNumber = 11;return MatrixKey_KeyNumber;}
	if(P1_4 == 0){Delay(20);while(P1_4 == 0);Delay(20);MatrixKey_KeyNumber = 15;return MatrixKey_KeyNumber;}
	
	P1 = 0xff;
	P1_0 = 0;
	if(P1_7 == 0){Delay(20);while(P1_7 == 0);Delay(20);MatrixKey_KeyNumber = 4;return MatrixKey_KeyNumber;}
	if(P1_6 == 0){Delay(20);while(P1_6 == 0);Delay(20);MatrixKey_KeyNumber = 8;return MatrixKey_KeyNumber;}
	if(P1_5 == 0){Delay(20);while(P1_5 == 0);Delay(20);MatrixKey_KeyNumber = 12;return MatrixKey_KeyNumber;}
	if(P1_4 == 0){Delay(20);while(P1_4 == 0);Delay(20);MatrixKey_KeyNumber = 16;return MatrixKey_KeyNumber;}
	
	return MatrixKey_KeyNumber;
}
