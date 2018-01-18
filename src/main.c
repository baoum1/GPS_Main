/**********************************************************
@file		main.c
@version	1.0
@date		12.01.2018
@author		M. Baour
@brief		Main Programm GPS
**********************************************************/

// === Includes ===========================================

#include "main.h"

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

// === Defines =============================================

#define gps_timeout	100 			// with a Loopdelay of 10ms equals 1s
#define a_gyr_timeout	10 			// with a Loopdelay of 10ms equals 100ms

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

uint8_t gps_data_timeout = 0;
uint8_t a_gyr_data_timeout = 0;

uint8_t gps_valid_flag = 0;
uint8_t gps_valid = 0;
uint8_t gps_checksum = 0;



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


	// Main endless loop
	for( ;; )
	{
		// loop delay
		loopDelay( 10 * _1MS );

		// timeout_variables
		gps_data_timeout ++;
		a_gyr_data_timeout ++;

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

			if (gps_data_timeout >= gps_timeout)
			{
				gps_data_timeout = 0;		// reset timeout
				statesMain = GET_GPS;		// change state
			}

			if (a_gyr_data_timeout >= a_gyr_timeout)
			{
				a_gyr_data_timeout = 0;
				statesMain = GET_A_GYR_DATA;
			}

			if (gps_valid_flag >= 1)
			{
				// display GPS-Data
			}
			else
			{
				// Kallmann Filter
			}

		break;

		case GET_GPS:

			// get gps Data
			// inbsert checksum function (asm)
			statesMain = CHECK_GPS_VALID;

		break;

		case CHECK_GPS_VALID:

			if((gps_valid >= 1) && (gps_checksum >=1))
			{
				gps_valid_flag = 1;
			}
			else
			{
				gps_valid_flag = 0;
			}
			statesMain = IDLE;

		break;

		case GET_A_GYR_DATA:

			ReadAccelero(&ax,&ay,&az);
			ReadGyro(&dx,&dy,&dz);

			statesMain = IDLE;

		break;


		default:
		break;
	}

}
