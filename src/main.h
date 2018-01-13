/**********************************************************
@file		main.h
@version	1.0
@date		13.01.2018
@author		M. Baour J. Tobler
@brief		main file of main.c
**********************************************************/

// === Includes ===========================================
#ifndef MAIN_H_
#define MAIN_H_

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




#endif /* MAIN_H_ */
