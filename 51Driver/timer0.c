#include <REGF51RC.H>
#include <INTRINS.H>
/**
  * @brief	定时器初始化,1毫秒@11.0592MHz
  * @param	无
  * @retval	无
  */
void Timer0_Init(void)		//1毫秒@11.0592MHz
{
	//TMOD寄存器不能单独更改,只能整体更改
	/** @TMOD	0000 0001
  * @GATE	TMOD.7	x
  * @CT		TMOD.6	x
  * @M1		TMOD.5	x
  * @M0		TMOD.4	x
  * @GATE	TMOD.3	0
  * @CT		TMOD.2	0
  * @M1		TMOD.1	0
  * @M0		TMOD.0	1
  */
	TMOD &= 0xF0;		//设置定时器模式,低四位清零,高四位不变
	TMOD |= 0x01;		//设置定时器模式,最低位赋1,高四位不变
	//计时器已65535为周期,赋初值0xFC66离结束还差1ms
	TL0 = 0x66;		//设置定时初值(低位)
	TH0 = 0xFC;		//设置定时初值(高位)
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	ET0 = 1;EA = 1;	//打通中断路径
	PT0 = 0;	//设置优先级为低优先级
}

/**
  * @brief	定时器中断函数模板
  * @param	无
  * @retval	未知
  */
/*
void Timer0_Routine() interrupt 1	//module
{
	static unsigned int T0count;
	TL0 = 0x66;		//设置定时初值(低位)
	TH0 = 0xFC;		//设置定时初值(高位)
	
}
*/