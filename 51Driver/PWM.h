#ifndef __PWM_H
#define __PWM_H

extern unsigned char PWM_Counter,PWM_Compare;
void PWM_Init();
void PWM_Motor(unsigned char Switcher);

/*
void Timer0_Routine() interrupt 1	//每隔100us进入中断
{
	TL0 = 0xA4;
	TH0 = 0xFF;
	PWM_Counter++;
	PWM_Counter%=100;
	if(PWM_Counter<PWM_Compare)
	{
		
	}
}
*/
#endif