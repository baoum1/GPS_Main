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
#include "string.h"
#include "globals.h"

// === Variables ==========================================

typedef struct
{
	char GGA[NMEA_stringlength];
	char GLL[NMEA_stringlength];
	char GSA[NMEA_stringlength];
	char GSV[NMEA_stringlength];
	char RMC[NMEA_stringlength];
	char VTG[NMEA_stringlength];
	char ZDA[NMEA_stringlength];
}NMEA_typedef;

// === Function prototypes ================================

// get lcd segment lenght
//uint8_t GetSegment_Length(char *str);

// display nmea string on LCD
void Display_NMEA(char *NMEA_string);

#endif /* NMEA_H_ */

// === Assembler subroutines prototypes ================================
extern int Kontrollsumme(char *str);
extern int GetSegment_Length(char *str);
