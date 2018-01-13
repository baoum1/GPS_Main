/**********************************************************
@file		uart.h
@version	1.0
@date		12.01.2018
@author		M. Baour J. Tobler
@brief		header file of a uart RS232 functions
**********************************************************/

#ifndef GYRO_H_
#define GYRO_H_

// === Includes ===========================================
#include <stm32f4xx.h>		// Processor STM32F407IG

// === Defines ============================================

// Gyro I2C-Address
#define I2C_GYR_ADDR 		0x69 << 1
// Gyro Controlregisters
#define CTRL_REG1 			0x20
#define CTRL_REG2 			0x21
#define CTRL_REG3 			0x22
#define CTRL_REG4 			0x23
#define CTRL_REG5 			0x24
#define REFERENCE 			0x25
#define STATUS_REG 			0x27
// Gyro Dataregisters
#define OUT_X_L				0x28
#define OUT_X_H				0x29
#define OUT_Y_L				0x2A
#define OUT_Y_H				0x2B
#define OUT_Z_L				0x2C
#define OUT_Z_H				0x2D
// Gyro Scale
#define GYR_Scale_250		0.00875f
#define GYR_Scale_500		0.0175f
#define GYR_Scale_2000		0.07f
// Gyro Resolution
#define GYR_Res_250			0x00
#define GYR_Res_500			0x10
#define GYR_Res_2000		0x20

// === Variables ==========================================
/*----- Data types ---------------------------------------------------------*/
extern ERROR_CODES err_code __attribute__((unused));

// === Function prototypes ================================
// init Gyroscope
void GyroInit(void);

// Read Gyro Data
void ReadGyro(int16_t *dx, int16_t *dy, int16_t *dz);

// display Gyro data on LCD
void Display_Gyro(int16_t *x, int16_t *y, int16_t *z);

#endif /* GYRO_H_ */
