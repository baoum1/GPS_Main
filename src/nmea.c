/**********************************************************
@file		nmea.c
@version	1.0
@date		13.01.2018
@author		M. Baour J. Tobler
@brief		source file nmea functions
**********************************************************/

// === Includes ===========================================
#include "nmea.h"

// === Variables ==========================================

NMEA_typedef NMEA;

// === Functions ==========================================

void init_nmea (void)
{
	strncpy(NMEA.GGA, "GGA:", 4);
	strncpy(NMEA.GSA, "GSA:", 4);
	strncpy(NMEA.GLL, "GLL:", 4);
	strncpy(NMEA.GSV, "GSV:", 4);
	strncpy(NMEA.RMC, "RMC:", 4);
	strncpy(NMEA.VTG, "VTG:", 4);
	strncpy(NMEA.ZDA, "ZDA:", 4);
}

// get lcd segment lenght
uint8_t GetSegment_Length(char *str)
{
	uint8_t MaxLength = min((LCD_HOR_RESOLUTION / LCD_GetFont()->width),strlen(str));
	for (int segment_index = 0; segment_index<MaxLength; segment_index++)
	{
		switch (str[segment_index])
		{
			case '$':
				return 0;
			case '*':
				return segment_index+3;
			default:
				break;
		}
	}
	return 0;
}

// display nmea string on LCD
void Display_NMEA(char *NMEA_string)
{
	// Disable UART1 Interrupts
	NVIC_DisableIRQ(USART1_IRQn);
	uint8_t SegmentLength = 1;
	for ( int search=0 ; search<NMEA_stringlength-6 ; search+=SegmentLength )
	{
		if ((NMEA_string[search] == '$' && NMEA_string[search+1] == 'G') && NMEA_string[search+2] == 'P')
		{
			switch (NMEA_string[search+3])
			{
				case 'G':
					switch (NMEA_string[search+4]) {
						case 'G':
							if (NMEA_string[search+5] == 'A')
							{
								SegmentLength = GetSegment_Length(&NMEA_string[search+6]);
								// TODO: only copy if checksum correct: EXOR(NMEA_string[search+1]-to-NMEA_string[search+SegmentLength+2]
								strncpy(&NMEA.GGA[4], &NMEA_string[search+6], SegmentLength);
								if (SegmentLength == 0) SegmentLength = 1;
								else SegmentLength+=6;
							}
							break;
						case 'S':
							if (NMEA_string[search+5] == 'A')
							{
								SegmentLength = GetSegment_Length(&NMEA_string[search+6]);
								strncpy(&NMEA.GSA[4], &NMEA_string[search+6], SegmentLength);
								if (SegmentLength == 0) SegmentLength = 1;
								else SegmentLength+=6;
							}
							else if (NMEA_string[search+5] == 'V')
							{
								SegmentLength = GetSegment_Length(&NMEA_string[search+6]);
								strncpy(&NMEA.GSV[4], &NMEA_string[search+6], SegmentLength);
								if (SegmentLength == 0) SegmentLength = 1;
								else SegmentLength+=6;
							}
							break;
						case 'L':
							if (NMEA_string[search+5] == 'L')
							{
								SegmentLength = GetSegment_Length(&NMEA_string[search+6]);
								strncpy(&NMEA.GLL[4], &NMEA_string[search+6], SegmentLength);
								if (SegmentLength == 0) SegmentLength = 1;
								else SegmentLength+=6;
							}
							break;
						default:
							break;
					}

					break;
				case 'R':
					if (NMEA_string[search+4] == 'M' && NMEA_string[search+5] == 'C')
					{
						SegmentLength = GetSegment_Length(&NMEA_string[search+6]);
						strncpy(&NMEA.RMC[4], &NMEA_string[search+6], SegmentLength);
						if (SegmentLength == 0) SegmentLength = 1;
						else SegmentLength+=6;
					}
					break;
				case 'V':
					if (NMEA_string[search+4] == 'T' && NMEA_string[search+5] == 'G')
					{
						SegmentLength = GetSegment_Length(&NMEA_string[search+6]);
						strncpy(&NMEA.VTG[4], &NMEA_string[search+6], SegmentLength);
						if (SegmentLength == 0) SegmentLength = 1;
						else SegmentLength+=6;
					}
					break;
				case 'Z':
					if (NMEA_string[search+4] == 'D' && NMEA_string[search+5] == 'A')
					{
						SegmentLength = GetSegment_Length(&NMEA_string[search+6]);
						strncpy(&NMEA.ZDA[4], &NMEA_string[search+6], SegmentLength);
						if (SegmentLength == 0) SegmentLength = 1;
						else SegmentLength+=6;
					}
					break;
				default:
					break;
			}
		}
		else SegmentLength = 1;
	}

	// Empty NMEA string
	for (int i = 0; i<NMEA_stringlength; i++)
		NMEA_string[i] = '\0';
	// Reenable UART1 interrupts
	NVIC_EnableIRQ(USART1_IRQn);
	if (NMEA.GGA[4] != 0)
	{
		LCD_DisplayStringLine(0, NMEA.GGA);
		for (int i = 4; i<NMEA_stringlength; i++)
			if (NMEA.GGA[i] != 0) NMEA.GGA[i] = 0;
			else break;
	}
	if (NMEA.GLL[4] != 0)
	{
		LCD_DisplayStringLine(1, NMEA.GLL);
		for (int i = 4; i<NMEA_stringlength; i++)
			if (NMEA.GLL[i] != 0) NMEA.GLL[i] = 0;
			else break;
	}
	if (NMEA.GSA[4] != 0)
	{
		LCD_DisplayStringLine(2, NMEA.GSA);
		for (int i = 4; i<NMEA_stringlength; i++)
			if (NMEA.GSA[i] != 0) NMEA.GSA[i] = 0;
			else break;
	}
	if (NMEA.GSV[4] != 0)
	{
		LCD_DisplayStringLine(3, NMEA.GSV);
		for (int i = 4; i<NMEA_stringlength; i++)
			if (NMEA.GSV[i] != 0) NMEA.GSV[i] = 0;
			else break;
	}
	if (NMEA.RMC[4] != 0)
	{
		LCD_DisplayStringLine(4, NMEA.RMC);
		for (int i = 4; i<NMEA_stringlength; i++)
			if (NMEA.RMC[i] != 0) NMEA.RMC[i] = 0;
			else break;
	}
	if (NMEA.VTG[4] != 0)
	{
		LCD_DisplayStringLine(5, NMEA.VTG);
		for (int i = 4; i<NMEA_stringlength; i++)
			if (NMEA.VTG[i] != 0) NMEA.VTG[i] = 0;
			else break;
	}
	if (NMEA.ZDA[4] != 0)
	{
		LCD_DisplayStringLine(6, NMEA.ZDA);
		for (int i = 4; i<NMEA_stringlength; i++)
			if (NMEA.ZDA[i] != 0) NMEA.ZDA[i] = 0;
			else break;
	}

}
