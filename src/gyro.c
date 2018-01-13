/**********************************************************
@file		gyro.c
@version	1.0
@date		13.01.2018
@author		M. Baour J. Tobler
@brief		source file of all gyro
**********************************************************/

// === Includes ===========================================
#include "gyro.h"
#include "main.h"

// === Variables ==========================================
/*----- Data types ---------------------------------------------------------*/
ERROR_CODES err_code __attribute__((unused));

// === Functions ==========================================
// init Gyorscope
void GyroInit(void)
{
	uint8_t value = 0x00;
	err_code = CARME_I2C_Write(I2C2,I2C_GYR_ADDR,CTRL_REG2,0,&value,1); // disable HPF
	value = 0x00;
	err_code = CARME_I2C_Write(I2C2,I2C_GYR_ADDR,CTRL_REG3,0,&value,1); // disable interrupts
	value = GYR_Res_250;
	err_code = CARME_I2C_Write(I2C2,I2C_GYR_ADDR,CTRL_REG4,0,&value,1); // Set Resolution
	value = 0x0F;
	err_code = CARME_I2C_Write(I2C2,I2C_GYR_ADDR,CTRL_REG1,0,&value,1); //Wakeup Gyro, enable x,y,z
	// Quick Calibration
	float X_BiasError, Y_BiasError, Z_BiasError = 0.0;
	uint16_t BiasErrorSplNbr = 500;
	uint16_t i = 0;

	for (i = 0; i < BiasErrorSplNbr; i++)
	{
		uint8_t angularrate[6];
			err_code = CARME_I2C_Read(I2C2, I2C_GYR_ADDR, OUT_X_L | (1 << 7), 0, angularrate, sizeof(angularrate));

	    X_BiasError += ((int16_t)(angularrate[1] << 8) | angularrate[0]);
	    Y_BiasError += ((int16_t)(angularrate[3] << 8) | angularrate[2]);
	    Z_BiasError += ((int16_t)(angularrate[5] << 8) | angularrate[4]);
	}
	// Set raw errors
	X_RawError = X_BiasError / BiasErrorSplNbr;
	Y_RawError = Y_BiasError / BiasErrorSplNbr;
	Z_RawError = Z_BiasError / BiasErrorSplNbr;
}

// read Dada from Gyro via Rs232
void ReadGyro(int16_t *dx, int16_t *dy, int16_t *dz)
{
	uint8_t value = 0;
	err_code = CARME_I2C_Read(I2C2,I2C_GYR_ADDR,STATUS_REG,0,&value,1); //Wakeup Gyro
	if ( value&0x08 )
	{
		uint8_t angularrate[6];
		err_code = CARME_I2C_Read(I2C2, I2C_GYR_ADDR, OUT_X_L | (1 << 7), 0, angularrate, sizeof(angularrate));

		*dx = ((int16_t)(angularrate[1] << 8) | angularrate[0]) + (-1*X_RawError);
		*dy = ((int16_t)(angularrate[3] << 8) | angularrate[2]) + (-1*Y_RawError);
		*dz = ((int16_t)(angularrate[5] << 8) | angularrate[4]) + (-1*Z_RawError);
	}

}

// display gyro Data on lcd
void Display_Gyro(int16_t *x, int16_t *y, int16_t *z)
{
	uint8_t MaxLength = LCD_HOR_RESOLUTION / LCD_GetFont()->width;
	char gyr_disp[MaxLength];

	if (*x != 0)
	{
		snprintf(gyr_disp, MaxLength, "Gyr_X:%d.%03d",(int)(*x*GYR_Scale_250),abs((int)(*x*GYR_Scale_250*1000)%1000));
		LCD_DisplayStringLine(12, gyr_disp);
	}
	if (*y != 0)
	{
		snprintf(gyr_disp, MaxLength, "Gyr_Y:%d.%03d",(int)(*y*GYR_Scale_250),abs((int)(*y*GYR_Scale_250*1000)%1000));
		LCD_DisplayStringLine(13, gyr_disp);
	}
	if (*z != 0)
	{
		snprintf(gyr_disp, MaxLength, "Gyr_Z:%d.%03d",(int)(*z*GYR_Scale_250),abs((int)(*z*GYR_Scale_250*1000)%1000));
		LCD_DisplayStringLine(14, gyr_disp);
	}
}
