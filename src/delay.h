/**********************************************************
@file		delay.h
@version	1.0
@date		02.05.2017
@author		F. Wittwer
@brief		header file of a delay and a loopdelay function
**********************************************************/

#ifndef LOOPDELAY_H_
#define LOOPDELAY_H_

// === Includes ===========================================
#include <stdint.h>

// === Defines ============================================
#define _1MS  	(10)
#define _1S		(1000*DELAY1MS)
#define _100US	(1)

// === Function prototypes ================================
// init delay timer for 100us ticks using Timer 7
void initDelayFuctions();

// wait until loop delay timeout is reached
// 100us * time or use macros
void loopDelay( uint32_t time );

// wait until delay timeout is reached
// 100us * time or use macros
// note: this will have a random error < 100us
void delay( uint32_t time );

#endif /* LOOPDELAY_H_ */
