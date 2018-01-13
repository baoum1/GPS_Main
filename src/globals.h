/**********************************************************
@file		globals.h
@version	1.0
@date		13.01.2018
@author		M. Baour J. Tobler
@brief		global variables and includes
**********************************************************/

#ifndef VARIABLES_H_
#define VARIABLES_H_

// === Includes ===========================================

#include "carme.h"

// === Defines ============================================

#define NMEA_stringlength	120

// === Variables ==========================================

//NMEA-Data
char NMEA_string[NMEA_stringlength];


uint8_t NMEAStringReadyFlag = 0;


//Gyro-Data
int16_t X_RawError, Y_RawError, Z_RawError;

/*----- Data types ---------------------------------------------------------*/
ERROR_CODES err_code __attribute__((unused));

#endif /* VARIABLES_H_ */
