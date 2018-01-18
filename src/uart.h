/**********************************************************
@file		uart.h
@version	1.0
@date		12.01.2018
@author		M. Baour J. Tobler
@brief		header file of all uart RS232 functions
**********************************************************/

#ifndef UART_H_
#define UART_H_

// === Includes ===========================================
#include "stm32f4xx_usart.h"		/* UART STM32F4 Module*/
#include "globals.h"



// === Function prototypes ================================
// Init USART
void Init_USART1(void);

// IRQ HAndler for UART
void USART1_IRQHandler(void);


#endif /* UART_H_ */
