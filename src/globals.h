/*
 * variables.h
 *
 *  Created on: Jan 13, 2018
 *      Author: Michel
 */

#ifndef VARIABLES_H_
#define VARIABLES_H_

// === Defines ============================================

#define NMEA_stringlength	120

//NMEA-Data
char NMEA_string[NMEA_stringlength];


uint8_t NMEAStringReadyFlag = 0;


//Gyro-Data
int16_t X_RawError, Y_RawError, Z_RawError;

#endif /* VARIABLES_H_ */
