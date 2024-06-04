#include "stm32f10x.h"
#include <stdio.h>
#include <stdarg.h>
#define	SERIAL_USART1				//使用USART1
//#define	SERIAL_AFIO					//启动端口重映射
#define SERIAL_PRINTF				//开启printf重定向
#define	SERIAL_CHECKMOD		0		//定义校验模式[0:无校验;1:奇校验;2:偶校验]
#define SERIAL_BaudRate		9600
#define	SERIAL_RX			ENABLE
#define	SERIAL_TX			ENABLE
#define SERIAL_RXETR				//启用外部中断接收
#define SERIAL_PRINTF_MAXI	100

uint8_t Serial_RxData;
uint8_t Serial_RxFlag;

#if	defined(SERIAL_USART1)
	#define SERIAL_USARTSel					USART1
	#define	SERIAL_RCC_APBPeriphClockCmd	RCC_APB2PeriphClockCmd
	#define SERIAL_USART_IRQn				USART1_IRQn
	
	#if	defined(SERIAL_AFIO)
		#define	SERIAL_RCC_APBPeriph_USART	RCC_APB2Periph_USART1
		#define SERILA_RCCGPIOCMD			RCC_APB2PeriphClockCmd
		#define	SERILA_RCCGPIO				RCC_APB2Periph_GPIOB
		#define SERIAL_GPIOSel				GPIOB
		#define	SERIAL_TXPin				GPIO_Pin_6
		#define	SERIAL_RXPin				GPIO_Pin_7
	#else
		#define	SERIAL_RCC_APBPeriph_USART	RCC_APB2Periph_USART1
		#define SERILA_RCCGPIOCMD			RCC_APB2PeriphClockCmd
		#define	SERILA_RCCGPIO				RCC_APB2Periph_GPIOA
		#define SERIAL_GPIOSel				GPIOA
		#define	SERIAL_TXPin				GPIO_Pin_9
		#define	SERIAL_RXPin				GPIO_Pin_10
	#endif
#elif defined(SERIAL_USART2)
	#define SERIAL_USARTSel					USART2
	#define	SERIAL_RCC_APBPeriphClockCmd	RCC_APB1PeriphClockCmd
	#define	SERIAL_RCC_APBPeriph_USART		RCC_APB1Periph_USART2
	#define SERIAL_USART_IRQn				USART2_IRQn
	#define SERILA_RCCGPIOCMD				RCC_APB2PeriphClockCmd
	#define	SERILA_RCCGPIO					RCC_APB2Periph_GPIOA
	#define SERIAL_GPIOSel					GPIOA
	#define	SERIAL_TXPin					GPIO_Pin_2
	#define	SERIAL_RXPin					GPIO_Pin_3
#elif defined(SERIAL_USART3)
	#define SERIAL_USARTSel					USART3
	#define	SERIAL_RCC_APBPeriphClockCmd	RCC_APB1PeriphClockCmd
	#define	SERIAL_RCC_APBPeriph_USART		RCC_APB1Periph_USART3
	#define SERIAL_USART_IRQn				USART3_IRQn
	#define SERILA_RCCGPIOCMD				RCC_APB2PeriphClockCmd
	#define	SERILA_RCCGPIO					RCC_APB2Periph_GPIOB
	#define SERIAL_GPIOSel					GPIOB
	#define	SERIAL_TXPin					GPIO_Pin_10
	#define	SERIAL_RXPin					GPIO_Pin_11
#endif

void Serial_Init(void)
{
	//引脚,时钟初始化部分
	SERIAL_RCC_APBPeriphClockCmd(SERIAL_RCC_APBPeriph_USART,ENABLE);
	SERILA_RCCGPIOCMD(SERILA_RCCGPIO,ENABLE);
	#if defined(SERIAL_USART1)
		#if	defined(SERIAL_AFIO)
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);
			GPIO_PinRemapConfig(GPIO_Remap_USART1,ENABLE);
		#endif
	#endif
	if(SERIAL_TX == ENABLE)
	{
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Pin = SERIAL_TXPin;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_Init(SERIAL_GPIOSel,&GPIO_InitStructure);
	}
	if(SERIAL_RX == ENABLE)
	{
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Pin = SERIAL_RX;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_Init(SERIAL_GPIOSel,&GPIO_InitStructure);
		#if defined(SERIAL_RXETR)
			USART_ITConfig(SERIAL_USARTSel,USART_IT_RXNE,ENABLE);
			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
			NVIC_InitTypeDef NVIC_InitStructure;
			NVIC_InitStructure.NVIC_IRQChannel						=	SERIAL_USART_IRQn;
			NVIC_InitStructure.NVIC_IRQChannelCmd					=	ENABLE;
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	=	1;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority			=	1;
			NVIC_Init(&NVIC_InitStructure);
		#endif
	}
	//串口模块初始化部分
	if(SERIAL_CHECKMOD	==	0)
	{
		uint16_t	USART_ModeSel = 0x00;
		USART_InitTypeDef	USART_InitStructure;
		USART_InitStructure.USART_BaudRate				=	SERIAL_BaudRate;
		USART_InitStructure.USART_HardwareFlowControl	=	USART_HardwareFlowControl_None;
		if(SERIAL_TX == ENABLE){USART_ModeSel|=USART_Mode_Tx;}
		if(SERIAL_RX == ENABLE){USART_ModeSel|=USART_Mode_Rx;}
		USART_InitStructure.USART_Mode					=	USART_ModeSel;
		USART_InitStructure.USART_Parity				=	USART_Parity_No;
		USART_InitStructure.USART_StopBits				=	USART_StopBits_1;
		USART_InitStructure.USART_WordLength			=	USART_WordLength_8b;
		USART_Init(SERIAL_USARTSel,&USART_InitStructure);
	}
	USART_Cmd(SERIAL_USARTSel,ENABLE);
}

void Serial_SendByte(uint8_t Byte)
{
	USART_SendData(SERIAL_USARTSel,Byte);
	while(USART_GetFlagStatus(SERIAL_USARTSel,USART_FLAG_TXE) == RESET);	//等待发送标志位置1完成发送
}

void Serial_SendArray(uint8_t* Array,uint16_t Length)
{
	uint16_t i;
	for(i = 0;i<Length;i++)
	{
		Serial_SendByte(Array[i]);
	}
}

void Serial_SendString(char* String)
{
	uint16_t i=0;
	while(String[i] != '\0')
	{
		Serial_SendByte(String[i]);
		i++;
	}
}

uint32_t Serial_Power(uint8_t Num,uint8_t Pow)
{
	if(Pow == 0){return 1;}
	uint32_t Ans = 1;
	uint8_t i = 0;
	for(i=0;i<Pow;i++){Ans = Ans*Num;}
	return Ans;
}

void Serial_SendNum(uint32_t Num,uint8_t Length)
{
	uint8_t i = 0;
	for (i=0;i<Length;i++)
	{
		Serial_SendByte(Num/Serial_Power(10,Length-i-1)%10 + '0');
	}
}

#if defined(SERIAL_PRINTF)
int fputc(int ch,FILE *f)
{
	Serial_SendByte(ch);
	return ch;
}
#endif

void Serial_Printf(char* format,...)
{
	char String[SERIAL_PRINTF_MAXI];
	va_list arg;					//定义了一个类似指针的变量
	va_start(arg,format);			//将format中的变量接入列表
	vsprintf(String,format,arg);	//转化好的字符串存到String里面
	va_end(arg);					//释放参数表
	Serial_SendString(String);
}

uint8_t Serial_GetRxFlag(void)
{
	if(Serial_RxFlag == 1)
	{
		Serial_RxFlag = 0;
		return 1;
	}
	return 0;
}

uint8_t Serial_GetRxData(void)
{
	return Serial_RxData;
}

void USART1_IRQHandler()
{
	if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == SET)
	{
		Serial_RxData = USART_ReceiveData(USART1);
		Serial_RxFlag = 1;
		USART_ClearITPendingBit(USART1,USART_FLAG_RXNE);
	}
}


