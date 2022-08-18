/*
 * OLED_Driver.h
 *
 *  Created on: 10 ago. 2021
 *      Author: Alan Zamudio
 */

#ifndef OLED_DRIVER_H_
#define OLED_DRIVER_H_

#define I2C_ADDRESS 		 0x3C

enum{
	enAddressByte = 0,
	enControlByte,
	enCommandByte,
	enCompleteMessage
};

void LCD_start(void);
void LCD_clear(void);
void LCD_print_text(char LCD_line1[18], char LCD_line2[18], char LCD_line3[18], char LCD_line4[18]);

#endif /* OLED_DRIVER_H_ */
