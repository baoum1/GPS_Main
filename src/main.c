/**********************************************************
@file		main.c
@version	1.0
@date		12.01.2018
@author		M. Baour
@brief		Main Programm GPS
**********************************************************/

// === Includes ===========================================

#include <stm32f4xx.h>		// Processor STM32F407IG
#include <carme.h>			// CARME Module
#include <stdio.h>
#include <lcd.h>
#include "stdlib.h"					/* Standard Library	*/
#include "string.h"					/* String Library */
//#include "globals.h"					/* Global Variables */

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
// NMEA-Variables
uint8_t NMEAStringReadyFlag;

static __IO uint32_t TimingDelay;

uint8_t gps_data_timeout = 0;
uint8_t a_gyr_data_timeout = 0;

uint8_t gps_valid = 0;
uint8_t gps_sat_number = 0;

char display_text[(LCD_HOR_RESOLUTION / 6)];		/* buffer for LCD text */


// === Function prototypes ================================

/* FSM of the main menu, inclusive the gui handling */
void mainFSM();



int main()
{
	initDelayFuctions();

	/* LCD Init */
	LCD_SetTextColor(GUI_COLOR_WHITE);	// Schfiftfarbe setzen
	LCD_SetFont(&font_5x7);

	LCD_Init(); 						// CARME LCD initialisieren
	snprintf(display_text, sizeof(display_text), "Display GPS-Data if avalible:");
	LCD_DisplayStringLine(0, display_text);

	/* USART1 Init */
	Init_USART1();

	/* I2C Init */
	Init_I2C2();

	// Init Accelerometer
	AcceleroInit();

	// Init Gyro
	GyroInit();

	// Init NMEA struct
	init_nmea();

	// Main endless loop
	for( ;; )
	{

		// timeout_variables
		gps_data_timeout ++;
		//a_gyr_data_timeout ++;

		// Main FSM
		mainFSM();


		// loop delay
		loopDelay( 10 * _1MS );

	}
	return 0U;
}

/* FSM of the main menu, inclusive the gui handling */
void mainFSM()
{
	switch( statesMain )
	{
		case IDLE:

			if ((gps_data_timeout >= gps_timeout))
			{
				gps_data_timeout = 0;		// reset timeout
				statesMain = GET_GPS;		// change state
			}

			/*if ((a_gyr_data_timeout >= a_gyr_timeout) && !(gps_data_timeout >= gps_timeout))
			{
				a_gyr_data_timeout = 0;
				statesMain = GET_A_GYR_DATA;
			}*/



		break;

		case GET_GPS:

			// get gps Data
			if (NMEAStringReadyFlag)
			{
				NMEAStringReadyFlag = 0;
				sort_NMEA(NMEA_string);
				display_raw_NMEA();
				//gps_sat_number = get_gps_sat_number();
				empty_NMEA_string();			// clear for new data
			}
			statesMain = CHECK_GPS_VALID;

		break;

		case CHECK_GPS_VALID:

			snprintf(display_text, sizeof(display_text), "There are %02d Satelites around.", gps_sat_number);
			LCD_DisplayStringLine(10, display_text);
			if (gps_sat_number >= 3)
			{
				LCD_ClearLine(9);
				//display_gps_pos();
			}
			else
			{
				snprintf(display_text, sizeof(display_text), "Sadly, there is no GPS available here.");
				LCD_DisplayStringLine(9, display_text);
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
