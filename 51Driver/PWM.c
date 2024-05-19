#include <REGF51RC.H>


/** @param PWM_Counter	计数器[0,99]
	@param PWM_Compare	比较器[0,100]
	*/
unsigned char PWM_Counter,PWM_Compare;
sbit PWM_MotorSwitcher = P1^0;

/*
	PWM一般设置在10-20KHZ范围内
	过低会导致电机抖动
	采用1ms定时器的话频率在1KHZ,会产生人耳可以听到的噪音
	而过高会导致MCU资源的浪费
*/
void Timer0_Init_100us()	//配置100us定时器中断
{
	TMOD &= 0xF0;		//设置定时器模式,低四位清零,高四位不变
	TMOD |= 0x01;		//设置定时器模式,最低位赋1,高四位不变
	//计时器已65535为周期,赋初值0xFC66离结束还差1ms
	TL0 = 0xA4;		//设置定时初值
	TH0 = 0xFF;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	ET0 = 1;EA = 1;	//打通中断路径
	PT0 = 0;	//设置优先级为低优先级
}

void PWM_Init()
{
	Timer0_Init_100us();
}

void PWM_Motor(unsigned char Switcher)
{
	if(Switcher == 0)
	{
		PWM_MotorSwitcher = 0;
	}
	else if(Switcher == 1)
	{
		PWM_MotorSwitcher = 1;
	}
}
