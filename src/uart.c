/**********************************************************
@file		uart.c
@version	1.0
@date		12.01.2018
@author		M. Baour J. Tobler
@brief		source file of all uart funcions (RS232)
**********************************************************/

// === Includes ===========================================
#include "uart.h"


// === Functions ==========================================
void Init_USART1(void)
{
	/* Init GPIO Ports [PA9=TX, PA10=RX] for UART1 */
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_StructInit(&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Speed = GPIO_Fast_Speed;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9,  GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

	// Set GPIOA & USART1 Peripherial Clock Ressource
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	// Init USART1 (to change settings disable USART1)
	USART_DeInit(USART1);
	// Init USART1 Clock
	USART_ClockInitTypeDef USART1_ClockInit;
	USART_ClockStructInit(&USART1_ClockInit);
	USART_ClockInit(USART1, &USART1_ClockInit);
	USART_Cmd(USART1, DISABLE);
	USART_InitTypeDef USART1_Init;
	USART_StructInit(&USART1_Init);
	USART_Init(USART1, &USART1_Init);
	// Enable UART1 Interrupts
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	//NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 10;	// set priority of the USART1 interrupt to highest (lowest=15)
	//NVIC_InitStructure.NVIC_IRQChannelSubPriority = 10;			// set the subpriority inside the group to highest (lowest=15)
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			 		// enable the USART1 interrupts globally
	NVIC_Init(&NVIC_InitStructure);							 		// NVIC_Init function takes care of the low level stuff
	USART_Cmd(USART1, ENABLE);
	USART_ClearFlag(USART1, USART_FLAG_RXNE);
	uint8_t i = 0xFF;
	// Wait until hardware is running
	while (i--);
}

/**
 * @brief		interrupt request handler (IRQ) for ALL USART1 interrupts
 */
void USART1_IRQHandler(void)
{
	// check if the USART1 receive interrupt flag was set
	if( USART_GetITStatus(USART1, USART_IT_RXNE) )
	{
		static uint8_t cnt = 0; // this counter is used to determine the current string length
		char t = USART1->DR;  // the character from the USART1 data register is saved in t
		static uint8_t NMEA_start = 0;
		if (cnt < NMEA_stringlength)
		{
			switch (t)
			{
				case '$':
					NMEA_start = 1;
					break;
				case '\r':
					NMEA_start = 0;
					break;
				case '\n':
					NMEA_start = 0;
					break;
				default:
					break;
			}
			if(NMEA_start)
			{
				NMEA_string[cnt++] = t;
			}
		}
		else
		{
			NMEAStringReadyFlag = 1;
			NMEA_start=0;
			cnt=0;
		}
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}
