/**********************************************************
@file		globals.h
@version	1.0
@date		13.01.2018
@author		M. Baour J. Tobler
@brief		global variables and includes
**********************************************************/

#ifndef GLOBALS_H_
#define GLOBALS_H_

// === Includes ===========================================

#include "carme.h"

// === Defines ============================================

#define NMEA_stringlength	120

// === Variables ==========================================

//NMEA-Data
char NMEA_string[NMEA_stringlength];


extern uint8_t NMEAStringReadyFlag;


//Gyro-Data
int16_t X_RawError, Y_RawError, Z_RawError;
int16_t ax, ay, az, dx, dy, dz;

/*----- Data types ---------------------------------------------------------*/
ERROR_CODES err_code __attribute__((unused));

#endif /* VARIABLES_H_ */
