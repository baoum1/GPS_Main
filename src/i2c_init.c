/**********************************************************
@file		i2c_init.c
@version	1.0
@date		12.01.2018
@author		M. Baour J. Tobler
@brief		source file of i2c init functions
**********************************************************/

// === Includes ===========================================

#include "i2c_init.h"					/* Carme-I2C Module						*/

// === Functions ==========================================
void Init_I2C2(void)
{
	/* Configure the GPIO [PH4=SCL, PH5=SDA] for I2C2*/
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_StructInit(&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Speed = GPIO_Fast_Speed;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOH, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOH, GPIO_PinSource4, GPIO_AF_I2C2);
	GPIO_PinAFConfig(GPIOH, GPIO_PinSource5, GPIO_AF_I2C2);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);

	I2C_InitTypeDef I2C_InitStruct;
	I2C_StructInit(&I2C_InitStruct);
	I2C_InitStruct.I2C_ClockSpeed = 100000;
	I2C_InitStruct.I2C_OwnAddress1 = 0xA0;
	I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
	I2C_Cmd(I2C2, DISABLE);
	I2C_DeInit(I2C2);
	I2C_Init(I2C2, &I2C_InitStruct);
	I2C_Cmd(I2C2, ENABLE);
	uint8_t i = 0xFF;
	// Wait until hardware is running
	while (i--);
}
