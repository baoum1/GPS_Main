/**********************************************************
@file		accelero.h
@version	1.0
@date		13.01.2018
@author		M. Baour J. Tobler
@brief		header file of accelero functions
**********************************************************/

#ifndef ACCELERO_H_
#define ACCELERO_H_

// === includes ============================================

#include <stm32f4xx.h>		// Processor STM32F407IG
#include "i2c.h"
#include "lcd.h"
#include "string.h"
#include "stdlib.h"					/* Standard Library*/
#include "globals.h"
#include "stdio.h"

// === Defines ============================================

// Accelero I2C-Address
#define I2C_AXL_ADDR		0x53 << 1
// Accelero Controlregisters
#define BW_RATE				0x2C
#define POWER_CTL			0x2D
#define DATA_FORMAT			0x31
// Accelero Dataregisters
#define DATAX0 				0x32 //X
#define DATAX1 				0x33
#define DATAY0 				0x34 //Y
#define DATAY1 				0x35
#define DATAZ0 				0x36 //Z
#define DATAZ1 				0x37
// Accelero Scale
#define ACC_Scale			0.0039f

// === Function prototypes ================================
// init Accelerometer
void AcceleroInit(void);

// read data from accelerometer
void ReadAccelero(int16_t *gx, int16_t *gy, int16_t *gz);

// display data from accelerometer on LCD
void Display_Accelero(int16_t *x, int16_t *y, int16_t *z);

#endif /* ACCELERO_H_ */
