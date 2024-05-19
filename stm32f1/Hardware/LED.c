#include "stm32f10x.h"                  // Device header

//LED请接在GPIOA上

typedef enum {ON = 1,OFF = 0} LED_Control;

/**
  * @brief	完成LED的初始化
  * @param	选中要初始化的端口
  * @retval	无
  */
void LED_Init(uint16_t LED_SEL)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = LED_SEL;	//选中Pin1和Pin2两个端口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//使用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_SetBits(GPIOA,LED_SEL);
}

/**
  * @brief	点亮LED
  * @param	LED_Pin	选中要点亮的LED(GPIO_Pin_0,...)	;	State	选择开关([ON,OFF])
  * @retval
  */
void LED(uint16_t LED_Pin,LED_Control State)
{
	if (State == ON)
	{
		GPIO_ResetBits(GPIOA,LED_Pin);
	}
	if (State == OFF)
	{
		GPIO_SetBits(GPIOA,LED_Pin);
	}
}

/**
  * @brief	翻转LED的状态
  * @param	选择LED的端口号
  * @retval	无
  */

void LED_Turn(uint16_t LED_Pin)
{
	if(GPIO_ReadOutputDataBit(GPIOA,LED_Pin) == 0)
	{
		GPIO_SetBits(GPIOA,LED_Pin);
	}
	else
	{
		GPIO_ResetBits(GPIOA,LED_Pin);
	}
}


