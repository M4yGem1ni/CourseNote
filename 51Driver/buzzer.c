#include <REGF51RC.H>
#include <INTRINS.H>
unsigned int Buzzer_FreqTable[]={
	0,
	63775,63874,63967,64055,64138,64217,64291,64360,64426,64489,64548,64603,
	64655,64705,64751,64795,64837,64876,64913,64948,64981,65012,65042,65069,
	65096,65120,65144,65166,65187,65206,65225,65242,65259,65274,65289,65303,
	65316,65328,65340,65351,65361,65371,65380,65389,65397,65405,65412,65419,
};
unsigned char Buzzer_FreqSel;
sbit Bz = P2^5;
/**
  * @brief	蜂鸣器专用延时函数(500us)
  * @param	无
  * @retval	无
  */
void Buzzer_Delay500us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 227;
	while (--i);
}
/**
  * @brief	蜂鸣器鸣响(2000Hz)
  * @param	ms	鸣响时长
  * @retval	无
  */
void Buzzer_Time(unsigned int ms)
{
	unsigned int i = 0;
	for(i=0;i<2*ms;i++)
	{
		Bz = !Bz;
		Buzzer_Delay500us();
	}
}
