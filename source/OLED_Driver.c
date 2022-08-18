/*
 * OLE_Driver.c
 *
 *  Created on: 10 ago. 2021
 *      Author: Alan Zamudio
 */

#include <stdio.h>
#include <stdlib.h>
#include "I2CDrive.h"
#include "OLED_Driver.h"
#include "letras.h"

#define Message_Length		3

unsigned char LCD_screen_buffer[1024];

unsigned char OLED_length[enCompleteMessage] = {I2C_ADDRESS, 0x00, 0x00};

void LCD_start(void){ //secuencia de arranque
	unsigned char init_sequence[27]={0xAE,0xD5,0x80,0xA8,63,0xD3,0x00,0x40,0x8D,0xD5,0x14,0x20,0x00,0xA1,0xC8,0xDA,0x12,0x81,0xCF,0xD9,0xF1,0xDB,0x40,0xA4,0xA6,0x2E,0xAF};

	OLED_length[enControlByte] = 0x00;

	for(int x=0; x<27; x++)
		{
			OLED_length[enCommandByte] = init_sequence[x];
			I2C_vfnSendData (&OLED_length,Message_Length);
		}
}

void LCD_clear(void)
{
	unsigned char start_screen[6]={0x22,0x00,0xFF,0x21,0x00,127}; //Preparacion de pantalla

	for(int x=0; x<7; x++)
	{
		OLED_length[enCommandByte] = start_screen[x];
		I2C_vfnSendData (&OLED_length,Message_Length);
	}

	LCD_send_Data(LCD_screen_buffer,1024);

}

void LCD_send_Data(unsigned char* data_, unsigned int data_lenght)
{
	OLED_length[enControlByte] = 0x40;
	for (int x=0; x<data_lenght; x++)
	{
		OLED_length[enCommandByte] = data_[x];
		I2C_vfnSendData (&OLED_length,Message_Length);
	}
}

void LCD_print_text(char LCD_line1[18], char LCD_line2[18], char LCD_line3[18], char LCD_line4[18])
{
	char buffer_letra[8];

	for(int y=0; y<18 ;y++)
	{
		LCD_parse(buffer_letra, LCD_line1[y]);
		for(int z=0; z<7 ;z++)
		{
			LCD_screen_buffer[129 + (7*y) + z] = buffer_letra[0+z];
		}
	}
	for(int y=0; y<18 ;y++)
	{
		LCD_parse(buffer_letra, LCD_line2[y]);
		for(int z=0; z<7 ;z++)
		{
			LCD_screen_buffer[385+ (7*y) +z] = buffer_letra[0+z];
		}
	}

	for(int y=0; y<18 ;y++)
	{
		LCD_parse(buffer_letra, LCD_line3[y]);
		for(int z=0; z<7 ;z++)
		{
			LCD_screen_buffer[641+ (7*y) +z] = buffer_letra[0+z];
		}
	}

	for(int y=0; y<18 ;y++)
	{
		LCD_parse(buffer_letra, LCD_line4[y]);
		for(int z=0; z<7 ;z++)
		{
			LCD_screen_buffer[897+ (7*y) +z] = buffer_letra[0+z];
		}
	}
	LCD_screen_buffer[1000] = 0x1;
	LCD_send_Data(LCD_screen_buffer,1024);
}
