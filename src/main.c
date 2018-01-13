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
#include "stdlib.h"					/* Standard Library	*/
#include "string.h"					/* String Library */

// delay
#include "delay.h"
// accelero
#include "accelero.h"
// gyroscope
#include "gyro.h"
// i2c
#include "i2c_init.h"
// uart
#include "uart.h"
// nmea
#include "nmea.h"



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



/*----- Data ---------------------------------------------------------------*/
static __IO uint32_t TimingDelay;


// === Function prototypes ================================

/* FSM of the main menu, inclusive the gui handling */
void mainFSM();



int main()
{

	/* LCD Init */
	LCD_SetTextColor(GUI_COLOR_WHITE);	// Schfiftfarbe setzen
	LCD_SetFont(&font_5x7);

	LCD_Init(); 						// CARME LCD initialisieren

	/* USART1 Init */
	Init_USART1();

	/* I2C Init */
	Init_I2C2();

	// Init Accelerometer
	AcceleroInit();

	// Init Gyro
	GyroInit();

	// Init NMEA struct
	strncpy(NMEA.GGA, "GGA:", 4);
	strncpy(NMEA.GSA, "GSA:", 4);
	strncpy(NMEA.GLL, "GLL:", 4);
	strncpy(NMEA.GSV, "GSV:", 4);
	strncpy(NMEA.RMC, "RMC:", 4);
	strncpy(NMEA.VTG, "VTG:", 4);
	strncpy(NMEA.ZDA, "ZDA:", 4);

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
