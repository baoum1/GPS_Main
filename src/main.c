/*
 @file		main.c
 @version	1.0
 @date		12.01.2018
 @author	M. Baour
 @brief		Main Programm GPS

 *********************************************************/

// === Includes ===========================================

#include "main.h"

// === Enums, Structs, etc ================================
typedef enum statesMain
{
	IDLE,
	GET_GPS,
	CHECK_GPS_VALID,
	GET_A_GYR_DATA,

} StatesMain;

// === Variables ==========================================

// for main menu FSM
StatesMain statesMain = IDLE;



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
	switch( statesMain )
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
