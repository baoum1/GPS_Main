/**********************************************************
@file		nmea.h
@version	1.0
@date		12.01.2018
@author		M. Baour J. Tobler
@brief		header file of nmea functions
**********************************************************/

#ifndef NMEA_H_
#define NMEA_H_

// === Includes ===========================================

#include <stm32f4xx.h>		// Processor STM32F407IG
#include "lcd.h"

// === Defines ============================================

#define NMEA_stringlength	120

// === Variables ==========================================

//NMEA-Data
extern char NMEA_string[NMEA_stringlength];
extern struct NMEA
{
	char GGA[NMEA_stringlength];
	char GLL[NMEA_stringlength];
	char GSA[NMEA_stringlength];
	char GSV[NMEA_stringlength];
	char RMC[NMEA_stringlength];
	char VTG[NMEA_stringlength];
	char ZDA[NMEA_stringlength];
}NMEA;
extern uint8_t NMEAStringReadyFlag = 0;
//Gyro-Data
extern int16_t X_RawError, Y_RawError, Z_RawError;

// === Function prototypes ================================

// get lcd segment lenght
uint8_t GetSegment_Length(char *str);

// display nmea string on LCD
void Display_NMEA(char *NMEA_string);

#endif /* NMEA_H_ */
