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
uint8_t gps_sat_number = 0;

char display_text[30];		/* buffer for LCD text */


// === Function prototypes ================================

/* FSM of the main menu, inclusive the gui handling */
void mainFSM();



int main()
{
	initDelayFuctions();

	/* LCD Init */
	LCD_SetTextColor(GUI_COLOR_WHITE);	// Schfiftfarbe setzen
	LCD_SetFont(&font_6x13);

	LCD_Init(); 						// CARME LCD initialisieren
	snprintf(display_text, sizeof(display_text), "Very nice GPS system");
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

			snprintf(display_text, sizeof(display_text), "%02d SAT", gps_sat_number);
			LCD_DisplayStringLine(8, display_text);

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

			if ((gps_valid_flag >= 1) && (gps_sat_number >= 3))
			{
				LCD_ClearLine(3);
				display_gps_pos();
			}
			else
			{
				snprintf(display_text, sizeof(display_text), "No GPS Data available");
				LCD_DisplayStringLine(3, display_text);
				// Kallmann Filter
			}

		break;

		case GET_GPS:

			// get gps Data
			if (NMEAStringReadyFlag)
			{
				NMEAStringReadyFlag = 0;
				empty_NMEA_string();			// clear for new data
				read_NMEA(NMEA_string);
				gps_sat_number = get_gps_sat_number();
			}


			// insert checksum function (asm)
			gps_checksum = 1; // As long as checksum function doensnt exist
			statesMain = CHECK_GPS_VALID;

		break;

		case CHECK_GPS_VALID:

			if((gps_sat_number >= 3) && (gps_checksum >=1))
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
