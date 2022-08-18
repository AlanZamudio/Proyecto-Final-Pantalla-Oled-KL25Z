/**
 * @file    IIC test.c
 * @brief   Application entry point.
 */

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "I2CDrive.h"
#include "OLED_Driver.h"

/*
 * @brief   Application entry point.
 */

char LCD_line1[18];
char LCD_line2[18];
char LCD_line3[18];
char LCD_line4[18];

int main(void) {
	I2C_vfnDriverInit();
	I2C_vfnSlaveInit();
	LCD_start();

	LCD_clear();

	sprintf(LCD_line1,"gsxngdng");
	sprintf(LCD_line2,"hola");
	sprintf(LCD_line3,"buenos dias");
	sprintf(LCD_line4,"1234");

	LCD_print_text(LCD_line1, LCD_line2, LCD_line3, LCD_line4);

    return 0 ;
}
