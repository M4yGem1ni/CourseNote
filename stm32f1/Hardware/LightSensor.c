#include "stm32f10x.h"                  // Device header

//光敏传感器接在GPIOB上

uint16_t LightSensor_tmp = 0x0;

void LightSensor_Init(uint16_t LightSensor_SEL)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = LightSensor_SEL;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//使用端口输入模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	LightSensor_tmp = LightSensor_SEL;
}

/**
  * @brief	光敏传感器读取光线强度
  * @param	无
  * @retval	[1:"暗",0:"亮"]
  */
uint8_t LightSensor_Read(void)
{
	return GPIO_ReadInputDataBit(GPIOB,LightSensor_tmp);
}
