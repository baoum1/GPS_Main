/*
 @file		main.c
 @version	1.0
 @date		12.01.2018
 @author	M. Baour
 @brief		Main Programm GPS

 *********************************************************/

// === Includes ===========================================
#include <stm32f4xx.h>		// Processor STM32F407IG
#include <carme.h>			// CARME Module
#include <stdio.h>
#include <lcd.h>
// buttons

// delay
#include "delay.h"
// accelero

// gyroscope



// === Enums, Structs, etc ================================
typedef enum statesMain
{
	IDLE,
	GET_GPS,
	CHECK_GPS_VALID,
	GET_A_GYR_DATA,

} StatesMainMenu;

// === Variables ==========================================

// for main menu FSM
StatesMainMenu statesMainMenu = IDLE;

// === Function prototypes ================================

/* FSM of the main menu, inclusive the gui handling */
void mainFSM();



int main()
{

	// init Buttons


	// init I2C


	// init loop delay on timer 7
	initDelayFuctions();

	// init LCD
	//LCD_Init();

	// init Accelero

	// endless
	for( ;; )
	{
		// loop delay
		loopDelay( 10 * _1MS );


		// Main FSM
		mainFSM();

	}
	return 0U;
}

/* FSM of the main menu, inclusive the gui handling */
void mainFSM()
{
	switch( statesMainMenu )
	{
		case IDLE:


		break;

		case GET_GPS:


		break;

		case CHECK_GPS_VALID:


		break;

		case GET_A_GYR_DATA:


		break;


		default:
		break;
	}

}
