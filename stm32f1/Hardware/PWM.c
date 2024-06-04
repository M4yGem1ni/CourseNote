#include "stm32f10x.h"

#define PWM_TIMSel 						TIM3				//初始化TIM3定时器(通用定时器)
#define PWM_RCC_APB1Periph_TIMER_TIMSel RCC_APB1Periph_TIM3	//初始化TIM3的定时器时钟
//#define PWM_TIM_IRQnSel 				TIM3_IRQn			//选择TIM3在NVIC中的通道

#define PWM_TIM_OCInit 					TIM_OC1Init			//选择CH1作为输出口
#define PWM_RCC_APB2Periph_GPIOSel		RCC_APB2Periph_GPIOA
#define PWM_GPIOSel						GPIOA				//使用PA6作为输出通道
#define PWM_GPIOPinSel					GPIO_Pin_6 
#define PWM_TIM_SetCompareSel			TIM_SetCompare1		//选择CH1口单独设置CRC

#define PWM_AFIO						DISABLE					//是否开启端口重映射
#define PWM_GPIO_PinRemapConfigSel		GPIO_PartialRemap_TIM3	//选择开启的端口号
#define PWM_GPIO_Remap_SWJ_JTA			DISABLE					//是否解放调试口

uint16_t Timer_CCR = 0;	//将CCR设置为全局变量

void PWM_AFIO_Init(void)	//开启AFIO时钟进行端口重映射
{
	RCC_APB2PeriphClockCmd(PWM_RCC_APB2Periph_GPIOSel,ENABLE);
	GPIO_PinRemapConfig(PWM_GPIO_PinRemapConfigSel,ENABLE);
	if(PWM_GPIO_Remap_SWJ_JTA == ENABLE)
	{
		GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);	//关闭PA15等引脚的调试功能,使其变为普通GPIO口
	}
}

/**
  * @brief	PWM初始化函数
  * @param	PSC	预分频系数(方便计算,输入值为PSC+1)
  * @param	ARR	自动重装值(方便计算,输入值为ARR+1)
  * @param	CCR	输出比较
  * @retval
  * @PWM参数计算公式:
	PWM频率:	Freq = CK_PSC(默认72MHZ)/(PSC+1)/(ARR+1)
	PWM占空比:	Duty = CCR/(ARR+1) * 100%
	PWM分辨率:	Reso = 1/(ARR+1)
*/
void PWM_Init(uint16_t PSC,uint16_t ARR)
{
	//RCC开启时钟,由于TIM2配置在APB1总线上,所以要开启APB1的时钟
	RCC_APB1PeriphClockCmd(PWM_RCC_APB1Periph_TIMER_TIMSel,ENABLE);
	
	//开启输出端口的时钟
	RCC_APB2PeriphClockCmd(PWM_RCC_APB2Periph_GPIOSel,ENABLE);
	if(PWM_AFIO == ENABLE){PWM_AFIO_Init();}
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = PWM_GPIOPinSel;	//选中Pin1和Pin2两个端口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//使用复用推挽输出(由于普通推挽输出引脚的控制权在MCU,而这里想要让定时器直接控制引脚,所以要切换为复用推挽输出)
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PWM_GPIOSel,&GPIO_InitStructure);
	
	//选择内部时钟,虽然默认选择的是内部时钟
	TIM_InternalClockConfig(PWM_TIMSel);
	//配置时基单元
	TIM_TimeBaseInitTypeDef TimeBaseInitStructure;
	TimeBaseInitStructure.TIM_ClockDivision	= TIM_CKD_DIV1;	//采样的频率的分频模式(按键消抖时可以使用)
	TimeBaseInitStructure.TIM_CounterMode	= TIM_CounterMode_Up;	//选择计数模式(向上计数,向下技术,中央对齐...)
	TimeBaseInitStructure.TIM_Period		= ARR - 1;//自动重装
	TimeBaseInitStructure.TIM_Prescaler		= PSC - 1;//预分频
	TimeBaseInitStructure.TIM_RepetitionCounter = 0;	//重复计数器,高级定时器才需要,这边直接给0	
	TIM_TimeBaseInit(PWM_TIMSel,&TimeBaseInitStructure);
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);	//给结构体变量赋初始值,防止使用高级定时器时出现问题
	TIM_OCInitStructure.TIM_OCMode		= TIM_OCMode_PWM1;	//输出比较模式
	TIM_OCInitStructure.TIM_OCPolarity	= TIM_OCPolarity_High;	//输出比较的极性(选择高电平有效)
	TIM_OCInitStructure.TIM_OutputState	= TIM_OutputState_Enable;	//设置输出使能
	TIM_OCInitStructure.TIM_Pulse		= Timer_CCR;	//设置CCR
	PWM_TIM_OCInit(PWM_TIMSel,&TIM_OCInitStructure);
	
	/* 不需要配置NVIC使其进入MCU
	TIM_ClearFlag(PWM_TIMSel,TIM_IT_Update);		//清除定时器初始化产生的更新中断(初始化时为了将值从缓冲器写入寄存器,需要一个更新中断介入,这样会导致程序一开始就会产生一个中断,这句话为了防止这一现象的产生)
	
	//使能中断
	TIM_ITConfig(PWM_TIMSel,TIM_IT_Update,ENABLE);	//采用更新中断,并使能中断使其到达NVIC
	//NVIC配置
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel		= PWM_TIM_IRQnSel;	//选择TIMx在NVIC中的通道
	NVIC_InitStructure.NVIC_IRQChannelCmd	= ENABLE;	//使能通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= 2;	//响应优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority			= 1;
	NVIC_Init(&NVIC_InitStructure);
	*/
	//启动定时器
	TIM_Cmd(PWM_TIMSel,ENABLE);
}


/**
  * @brief	设置CCR的值
  * @param	CCR	
  * @retval	无
  */
void PWM_SetCCR(uint16_t CCR)
{
	Timer_CCR = CCR;
	PWM_TIM_SetCompareSel(PWM_TIMSel,Timer_CCR);
}
