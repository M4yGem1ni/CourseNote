#include "stm32f10x.h"                  // Device header
#include "Delay.h"

//选中GPIOB作为输入

uint16_t Keys[16]; 	//存储选中的每个端口
uint8_t Key_len = 0;	//计算选中端口数量
uint8_t Key_table[16];	//记录每个端口的索引

/**
  * @brief	完成读取按键函数的初始化,并分离端口
  * @param	无
  * @retval	无
  */
void Key_Init(uint16_t Key_SEL)
{
	uint8_t i = 0;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode	= 	GPIO_Mode_IPU;	//选择端口输入模式
	GPIO_InitStructure.GPIO_Pin		=	Key_SEL;	
	GPIO_InitStructure.GPIO_Speed	=	GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	for(i = 0;i<16;i++)	//单独取出选中的端口号
	{
		if(	(Key_SEL&(0x0001<<i)) != 0	)
		{
			Keys[Key_len] = 0x0001<<i;
			Key_table[Key_len] = i;
			Key_len+=1;
		}
	}
}

/**
  * @brief	读取按键按下的端口号
  * @param	无
  * @retval	端口号索引
  */
int8_t Key(void)
{
	int8_t KeyNum = -1;	//返回端口号
	uint8_t	i = 0;
	for (i = 0;i<Key_len;i++)
	{
		if(	(GPIO_ReadInputDataBit(GPIOB,Keys[i]) == 0)	)
		{
			Delay_ms(20);
			while(GPIO_ReadInputDataBit(GPIOB,Keys[i]) == 0);
			Delay_ms(20);
			KeyNum = Key_table[i];
		}
	}
	return KeyNum;
}
