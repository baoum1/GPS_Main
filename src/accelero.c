/**********************************************************
@file		uart.c
@version	1.0
@date		13.01.2018
@author		M. Baour J. Tobler
@brief		source file of all accelero functions
**********************************************************/

// === Includes ===========================================
#include "accelero.h"
#include "main.h"

// === Functions ==========================================
void AcceleroInit(void)
{
	uint8_t value = 0x0F;
	err_code = CARME_I2C_Write(I2C2,I2C_AXL_ADDR,BW_RATE,0,&value,1); //Set Data rate

	value = 0x08;
	err_code = CARME_I2C_Write(I2C2,I2C_AXL_ADDR,POWER_CTL,0,&value,1); //Choose power-mode

	value = 0x08;
	err_code = CARME_I2C_Write(I2C2,I2C_AXL_ADDR,DATA_FORMAT,0,&value,1); //Data format
}

void ReadAccelero(int16_t *gx, int16_t *gy, int16_t *gz)
{
	uint8_t gravitation[6];
	err_code = CARME_I2C_Read(I2C2, I2C_AXL_ADDR, DATAX0, 0, gravitation, sizeof(gravitation));

	*gx = ((int16_t)(gravitation[1] << 8) | gravitation[0]);
	*gy = ((int16_t)(gravitation[3] << 8) | gravitation[2]);
	*gz = ((int16_t)(gravitation[5] << 8) | gravitation[4]);
}

/*
 * @brief 		displays measured acceleration in all 3 axis
 */
void Display_Accelero(int16_t *x, int16_t *y, int16_t *z)
{
	uint8_t MaxLength = LCD_HOR_RESOLUTION / LCD_GetFont()->width;
	char acc_disp[MaxLength];

	if (*x != 0)
	{
		snprintf(acc_disp, MaxLength, "Acc_X:%d.%03d", (int)(*x*ACC_Scale),abs((int)(*x*ACC_Scale*1000)%1000));
		LCD_DisplayStringLine(8, acc_disp);
	}
	if (*y != 0)
	{
		snprintf(acc_disp, MaxLength, "Acc_Y:%d.%03d",(int)(*y*ACC_Scale),abs((int)(*y*ACC_Scale*1000)%1000));
		LCD_DisplayStringLine(9, acc_disp);
	}
	if (*z != 0)
	{
		snprintf(acc_disp, MaxLength, "Acc_Z:%d.%03d",(int)(*z*ACC_Scale),abs((int)(*z*ACC_Scale*1000)%1000));
		LCD_DisplayStringLine(10, acc_disp);
	}
}
