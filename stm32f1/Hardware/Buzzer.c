#include "stm32f10x.h"                  // Device header

//BUZZER请接在GPIOB上
//BUZZER是有源蜂鸣器,且低电平触发

uint16_t Buzzer_tmp = 0x0;
void Buzzer_Init(uint16_t Buzzer_SEL)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = Buzzer_SEL;	//选中蜂鸣器端口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//使用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB,Buzzer_SEL);
	Buzzer_tmp = Buzzer_SEL;
}

void Buzzer_ON(void)
{
	GPIO_ResetBits(GPIOB,Buzzer_tmp);
}

void Buzzer_OFF(void)
{
	GPIO_SetBits(GPIOB,Buzzer_tmp);
}

void Buzzer_Turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOB,Buzzer_tmp) == 0)
	{
		GPIO_SetBits(GPIOB,Buzzer_tmp);
	}
	else
	{
		GPIO_ResetBits(GPIOB,Buzzer_tmp);
	}
}
