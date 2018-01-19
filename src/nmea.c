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

void init_nmea(void)
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
//uint8_t GetSegment_Length(char *str)
//{
	//uint8_t MaxLength = min((LCD_HOR_RESOLUTION / LCD_GetFont()->width),strlen(str));
	//for (int segment_index = 0; segment_index<MaxLength; segment_index++)
	//{
		//switch (str[segment_index])
		//{
			//case '$':
				//return 0;
			//case '*':
				//return segment_index+3;
			//default:
				//break;
		//}
	//}
	//return 0;
//}

// sort nmea strin into struct
void sort_NMEA(char *NMEA_string)
{
	// Disable UART1 Interrupts
	NVIC_DisableIRQ(USART1_IRQn);
	uint8_t SegmentLength = 1;
	for ( int search=0 ; search<NMEA_stringlength-6 ; search+=SegmentLength )
	{
		if ( (NMEA_string[search] == '$' && NMEA_string[search+1] == 'G') && NMEA_string[search+2] == 'P' && Kontrollsumme(&NMEA_string[search]) )
		{
			SegmentLength = GetSegment_Length(&NMEA_string[search]);
			switch (NMEA_string[search+3])
			{
				case 'G':
					switch (NMEA_string[search+4]) {
						case 'G':
							if (NMEA_string[search+5] == 'A')
							{
								strncpy(&NMEA.GGA[4], &NMEA_string[search+6], SegmentLength-6);
							}
							break;
						case 'S':
							if (NMEA_string[search+5] == 'A')
							{
								strncpy(&NMEA.GSA[4], &NMEA_string[search+6], SegmentLength-6);
							}
							else if (NMEA_string[search+5] == 'V')
							{
								strncpy(&NMEA.GSV[4], &NMEA_string[search+6], SegmentLength-6);
							}
							break;
						case 'L':
							if (NMEA_string[search+5] == 'L')
							{
								strncpy(&NMEA.GLL[4], &NMEA_string[search+6], SegmentLength-6);
							}
							break;
						default:
							break;
					}

					break;
				case 'R':
					if ( NMEA_string[search+4] == 'M' && NMEA_string[search+5] == 'C')
					{
						strncpy(&NMEA.RMC[4], &NMEA_string[search+6], SegmentLength-6);
					}
					break;
				case 'V':
					if (NMEA_string[search+4] == 'T' && NMEA_string[search+5] == 'G')
					{
						strncpy(&NMEA.VTG[4], &NMEA_string[search+6], SegmentLength-6);
					}
					break;
				case 'Z':
					if (NMEA_string[search+4] == 'D' && NMEA_string[search+5] == 'A')
					{
						strncpy(&NMEA.ZDA[4], &NMEA_string[search+6], SegmentLength-6);
					}
					break;
				default:
					break;
			}
			if (SegmentLength == 0) SegmentLength = 1;
			else SegmentLength += 3;
		}
		else SegmentLength = 1;
	}
	// Reenable UART1 interrupts
	NVIC_EnableIRQ(USART1_IRQn);
}

void display_raw_NMEA(void)
{
	// for DBG purpose
	LCD_DisplayStringLine(2, NMEA.GGA);
	LCD_DisplayStringLine(3, NMEA.GLL); // for DBG purpose
	LCD_DisplayStringLine(4, NMEA.GSA); // for DBG purpose
	LCD_DisplayStringLine(5, NMEA.GSV); // for DBG purpose
	LCD_DisplayStringLine(6, NMEA.RMC); // for DBG purpose
	LCD_DisplayStringLine(7, NMEA.VTG); // for DBG purpose
	LCD_DisplayStringLine(8, NMEA.ZDA); // for DBG purpose
}

void empty_NMEA_string (void)
{
	// Empty NMEA string
	for (int i = 0; i<NMEA_stringlength; i++)
		NMEA_string[i] = '\0';

	// Empty NMEA struct
	if (NMEA.GGA[4] != 0)
	{

		for (int i = 4; i<NMEA_stringlength; i++)
			if (NMEA.GGA[i] != 0) NMEA.GGA[i] = 0;
			else break;
	}
	if (NMEA.GLL[4] != 0)
	{

		for (int i = 4; i<NMEA_stringlength; i++)
			if (NMEA.GLL[i] != 0) NMEA.GLL[i] = 0;
			else break;
	}
	if (NMEA.GSA[4] != 0)
	{

		for (int i = 4; i<NMEA_stringlength; i++)
			if (NMEA.GSA[i] != 0) NMEA.GSA[i] = 0;
			else break;
	}
	if (NMEA.GSV[4] != 0)
	{

		for (int i = 4; i<NMEA_stringlength; i++)
			if (NMEA.GSV[i] != 0) NMEA.GSV[i] = 0;
			else break;
	}
	if (NMEA.RMC[4] != 0)
	{
		for (int i = 4; i<NMEA_stringlength; i++)
			if (NMEA.RMC[i] != 0) NMEA.RMC[i] = 0;
			else break;
	}
	if (NMEA.VTG[4] != 0)
	{
		for (int i = 4; i<NMEA_stringlength; i++)
			if (NMEA.VTG[i] != 0) NMEA.VTG[i] = 0;
			else break;
	}
	if (NMEA.ZDA[4] != 0)
	{
		for (int i = 4; i<NMEA_stringlength; i++)
			if (NMEA.ZDA[i] != 0) NMEA.ZDA[i] = 0;
			else break;
	}

}

uint8_t get_gps_sat_number(void)
{
	int count = 0;
	for (int i = 1; i < NMEA_stringlength; i++)
	{
		if (NMEA.GGA[i] == ',')
		{
			count ++;
		}

		if(count == 7)
		{
			return (10*((NMEA.GGA[i+1])-'0') + ((NMEA.GGA[i+2])-'0'));
		}
	}
	return 0;
}

void display_gps_pos(void)
{
	uint8_t long_min;
	uint8_t long_sec_h;
	uint8_t long_sec_l;
	char long_orientation;
	uint8_t lat_min;
	uint8_t lat_sec_h;
	uint8_t lat_sec_l;
	char lat_orientation;

	char display_text_nmea[30];		/* buffer for LCD text */

	int count = 0;
	for (int i = 1; i < NMEA_stringlength; i++)
	{
		if (NMEA.GGA[i] == ',')
		{
			count ++;
		}

		if(count == 2)
		{
			lat_min = (10*(((int)NMEA.GGA[i+1])-'0') + (((int)NMEA.GGA[i+2])-'0'));
			lat_sec_h = (10*(((int)NMEA.GGA[i+3])-'0') + (((int)NMEA.GGA[i+4])-'0'));
			lat_sec_l = (100*(((int)NMEA.GGA[i+6])-'0') + 10*(((int)NMEA.GGA[i+7])-'0') + (((int)NMEA.GGA[i+8])-'0'));
		}

		if(count == 3)
		{
			lat_orientation = NMEA.GGA[i+1];
		}

		if(count == 4)
		{
			long_min = (100*(((int)NMEA.GGA[i+1])-'0') + 10*(((int)NMEA.GGA[i+2])-'0') + (((int)NMEA.GGA[i+3])-'0'));
			long_sec_h = (10*(((int)NMEA.GGA[i+4])-'0') + (((int)NMEA.GGA[i+5])-'0'));
			long_sec_l = (100*(((int)NMEA.GGA[i+7])-'0') + 10*(((int)NMEA.GGA[i+8])-'0') + (((int)NMEA.GGA[i+9])-'0'));
		}

		if(count == 5)
		{
			long_orientation = NMEA.GGA[i+1];
		}
	}

	LCD_ClearLine(4);
	snprintf(display_text_nmea, sizeof(display_text_nmea), "%2d° %2d,%3d ", lat_min, lat_sec_h, lat_sec_l  );
	strcat(display_text_nmea, &lat_orientation);
	LCD_DisplayStringLine(4, display_text_nmea);

	LCD_ClearLine(5);
	snprintf(display_text_nmea, sizeof(display_text_nmea), "%3d° %2d,%3d ", long_min, long_sec_h, long_sec_l );
	strcat(display_text_nmea, &long_orientation);
	LCD_DisplayStringLine(5, display_text_nmea);
}
