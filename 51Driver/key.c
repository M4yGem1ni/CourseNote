#include <REGF51RC.H>
#include "Delay.h"

unsigned char Key_KeyNum;

/**
	* @brief	读取独立按键位置
	* @param	无
	* @retval	返回按键位置(A~D),无输入返回0
	松手触发
	*/
unsigned char Key()
{
	unsigned char KeyNum = 0;
	if(P3_0==0){Delay(20);while(P3_0==0);Delay(20);KeyNum = 'B';return KeyNum;}
	if(P3_1==0){Delay(20);while(P3_1==0);Delay(20);KeyNum = 'A';return KeyNum;}
	if(P3_2==0){Delay(20);while(P3_2==0);Delay(20);KeyNum = 'C';return KeyNum;}
	if(P3_3==0){Delay(20);while(P3_3==0);Delay(20);KeyNum = 'D';return KeyNum;}
	return KeyNum;
}
/**
  * @brief	返回按键结果,配合定时器(20ms)扫描按键使用,取消Delay结构
  * @param	无
  * @retval	独立按键键值
  */
unsigned char _Key_()
{
	unsigned char Tmp;
	Tmp = Key_KeyNum;
	Key_KeyNum = 0;
	return Tmp;
}
/**
  * @brief	扫描按键结果,并把结果保存,配合定时器(20ms)扫描按键使用,取消Delay结构
  * @param	无
  * @retval	独立按键键值
  */
unsigned char Key_GetState()
{
	unsigned char KeyNum = 0;
	if(P3_0==0){KeyNum = 'B';return KeyNum;}
	if(P3_1==0){KeyNum = 'A';return KeyNum;}
	if(P3_2==0){KeyNum = 'C';return KeyNum;}
	if(P3_3==0){KeyNum = 'D';return KeyNum;}
	return KeyNum;
}
/**
  * @brief	定时器(20ms)扫描按键,取消Delay结构
  * @param	无
  * @retval	无
  */
void Key_Loop()
{
	static unsigned char NowState,LastState;
	LastState = NowState;
	NowState = Key_GetState();
	if(NowState == 0 && LastState == 'A'){Key_KeyNum = 'A';}
	if(NowState == 0 && LastState == 'B'){Key_KeyNum = 'B';}
	if(NowState == 0 && LastState == 'C'){Key_KeyNum = 'C';}
	if(NowState == 0 && LastState == 'D'){Key_KeyNum = 'D';}
}