/**********************************************************
@file		delay.c
@version	1.0
@date		02.05.2017
@author		F. Wittwer
@brief		source file of a delay and a loopdelay function
@note		this file uses timer 7
**********************************************************/

// === Includes ===========================================
#include "delay.h"
#include "stm32f4xx_tim.h"

// ms tick variable
static volatile uint32_t cntLoopDelay = 0;
static volatile uint32_t cntDelay = 0;

// === Functions ==========================================

// init delay for 100us ticks using Timer 7
void initDelayFuctions()
{
	// init Timer 7 for 1ms ticks
	const int APB1_CLK=42E6;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM7 , ENABLE );
	TIM_TimeBaseStructInit( &TIM_TimeBaseStructure );
	TIM_TimeBaseStructure.TIM_Prescaler = APB1_CLK / 10000 - 1;
	TIM_TimeBaseStructure.TIM_Period = 1;
	TIM_TimeBaseInit( TIM7, &TIM_TimeBaseStructure);

	// enable irqs
	__disable_irq();
	TIM_ITConfig( TIM7, TIM_IT_Update, ENABLE );
	NVIC_EnableIRQ( TIM7_IRQn );

	TIM_Cmd( TIM7 , ENABLE);
	__enable_irq();
}

// wait until loop delay timeout is reached
// 100us * time or use macros
void loopDelay( uint32_t time )
{
	while( cntLoopDelay < time );
	cntLoopDelay = 0;
}

// wait until delay timeout is reached
// 100us * time or use macros
void delay( uint32_t time )
{
	cntDelay = 0;
	while( cntDelay < time );
	cntDelay = 0;
}

// irq each 100us, increment cnt variables
void TIM7_IRQHandler ()
{
	// reset time flag
	TIM_ClearFlag( TIM7, TIM_FLAG_Update);
	// incremend systicks
	cntLoopDelay++;
	cntDelay++;
}


